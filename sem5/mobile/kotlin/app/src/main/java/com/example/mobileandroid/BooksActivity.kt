package com.example.mobileandroid

import android.animation.AnimatorSet
import android.animation.ObjectAnimator
import android.animation.ValueAnimator
import android.app.Activity
import android.app.NotificationChannel
import android.app.NotificationManager
import android.content.Context
import android.content.Intent
import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import android.net.ConnectivityManager
import android.net.NetworkCapabilities
import android.net.Uri
import android.os.Bundle
import android.os.Environment
import android.provider.MediaStore
import android.view.animation.LinearInterpolator
import android.widget.Button
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.NotificationCompat
import androidx.core.content.FileProvider
import androidx.lifecycle.lifecycleScope
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import androidx.work.OneTimeWorkRequestBuilder
import androidx.work.WorkManager
import com.example.mobileandroid.client.Api
import com.example.mobileandroid.client.ApiClient
import com.example.mobileandroid.dto.BookDto
import com.example.mobileandroid.utils.MyAppDatabase
import com.example.mobileandroid.utils.MyWorker
import com.example.mobileandroid.utils.BookAdapter
import kotlinx.coroutines.launch
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response
import java.io.File
import java.text.SimpleDateFormat
import java.util.Date
import java.util.Locale
import java.util.concurrent.TimeUnit
import java.util.logging.Logger

class BooksActivity : AppCompatActivity(), SensorEventListener {

    val log: Logger = Logger.getLogger(BooksActivity::class.java.name)
    val recyclerview: RecyclerView by lazy { findViewById(R.id.recyclerview) }


    private lateinit var sensorView: TextView
    private var accelerometer: Sensor? = null
    private lateinit var sensorManager: SensorManager

    private val channelId = "BOOKS_CHANNEL"
    private val REQUEST_EDIT_BOOK = 1
    private val REQUEST_CAMERA = 2
    private var imageFilePath: String? = null

    private val database: MyAppDatabase by lazy { MyAppDatabase.getDatabase(this) }

    private fun createNotificationChannel() {
        val name = "Book Notifications"
        val descriptionText = "Notifications about books"
        val importance = NotificationManager.IMPORTANCE_DEFAULT
        val channel = NotificationChannel(channelId, name, importance).apply {
            description = descriptionText
        }

        val notificationManager = getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager
        notificationManager.createNotificationChannel(channel)
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_books)

        // Create the notification channel
        createNotificationChannel()
        val builder = NotificationCompat.Builder(this, channelId)
            .setSmallIcon(R.drawable.ic_launcher_foreground)
            .setContentTitle("Books")
            .setContentText("Application started!!!")
            .setPriority(NotificationCompat.PRIORITY_DEFAULT)

        val notificationManager = getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager
        val notificationId = 1013
        notificationManager.notify(notificationId, builder.build())

        recyclerview.layoutManager = LinearLayoutManager(this)

        sensorManager = getSystemService(SENSOR_SERVICE) as SensorManager
        accelerometer = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER)

        val textView = findViewById<TextView>(R.id.textView)
        textView.text = isOnline(this)

        sensorView = findViewById<TextView>(R.id.sensorView)
        sensorView.text = "Accelerometer loading"

        val btnCamera = findViewById<Button>(R.id.btn_photo)
        btnCamera.setOnClickListener {
            dispatchTakePictureIntent()
        }

        val scaleX = ObjectAnimator.ofFloat(btnCamera, "scaleX", 1f, 0.75f, 1f).apply {
            duration = 1000
            repeatCount = ValueAnimator.INFINITE
            repeatMode = ValueAnimator.REVERSE
        }
        val scaleY = ObjectAnimator.ofFloat(btnCamera, "scaleY", 1f, 0.75f, 1f).apply {
            duration = 1000
            repeatCount = ValueAnimator.INFINITE
            repeatMode = ValueAnimator.REVERSE
        }

        val animatorSet = AnimatorSet()
        animatorSet.playTogether(scaleX, scaleY)
        animatorSet.interpolator = LinearInterpolator()
        animatorSet.start()

        val workRequest = OneTimeWorkRequestBuilder<MyWorker>()
            .setInitialDelay(0, TimeUnit.SECONDS)
            .build()
        WorkManager.getInstance(applicationContext).enqueue(workRequest)

        val token = Api.token

        val btnLogout = findViewById<Button>(R.id.btn_logout)
        btnLogout.setOnClickListener {
            logout()
        }

        val call = ApiClient.apiService.getBooks("Bearer $token")

        if ("STATUS: WIFI".equals(isOnline(this))) {
            call.enqueue(object : Callback<List<BookDto>> {
                override fun onResponse(
                    call: Call<List<BookDto>>,
                    response: Response<List<BookDto>>
                ) {
                    if (response.isSuccessful) {
                        val books = response.body()
                        val booksArray = Array<BookDto>(books!!.size) { books[it] }
                        log.warning(books.toString())
                        database.bookDao().insert(booksArray.toList())
                        val adapter = BookAdapter(booksArray.toMutableList()) { book ->
                            val intent =
                                Intent(this@BooksActivity, EditBookActivity::class.java)
                            intent.putExtra("book", book)
                            startActivityForResult(intent, 1)
                        }
                        recyclerview.adapter = adapter
                    } else {
                        Toast.makeText(
                            this@BooksActivity,
                            "Get books failed",
                            Toast.LENGTH_SHORT
                        ).show()
                    }
                }

                override fun onFailure(call: Call<List<BookDto>>, t: Throwable) {
                    Toast.makeText(this@BooksActivity, "Network error", Toast.LENGTH_LONG).show()
                    log.warning(t.toString())
                }
            })
        } else {

            lifecycleScope.launch {
                database.bookDao().getAll().collect { newBooks ->

                    val adapter = BookAdapter(newBooks.toMutableList()) { book ->
                        val intent = Intent(this@BooksActivity, EditBookActivity::class.java)
                        intent.putExtra("book", book)
                        startActivityForResult(intent, 1)
                    }

                    recyclerview.adapter = adapter
                }
            }
        }
    }

    override fun onResume() {
        super.onResume()
        accelerometer?.also { accel ->
            sensorManager.registerListener(this, accel, SensorManager.SENSOR_DELAY_NORMAL)
        }
    }

    override fun onSensorChanged(event: SensorEvent) {
        if (event.sensor.type == Sensor.TYPE_ACCELEROMETER) {
            val x = event.values[0]
            val y = event.values[1]
            val z = event.values[2]

            sensorView.text = "ACCELEROMETER:\n($x, $y, $z)"
        }
    }

    override fun onAccuracyChanged(sensor: Sensor?, accuracy: Int) {
    }

    private fun dispatchTakePictureIntent() {
        val takePictureIntent = Intent(MediaStore.ACTION_IMAGE_CAPTURE)
        try {
            val photoFile = createImageFile()
            val photoURI: Uri = FileProvider.getUriForFile(
                this,
                "com.example.mobileandroid.fileprovider",
                photoFile
            )
            takePictureIntent.putExtra(MediaStore.EXTRA_OUTPUT, photoURI)
            startActivityForResult(takePictureIntent, REQUEST_CAMERA)
        } catch (ex: Exception) {
            // Error occurred while creating the File
            ex.printStackTrace()
        }
    }

    @Throws(Exception::class)
    private fun createImageFile(): File {
        // Create an image file name
        val timeStamp = SimpleDateFormat("yyyyMMdd_HHmmss", Locale.getDefault()).format(Date())
        val storageDir: File? = getExternalFilesDir(Environment.DIRECTORY_PICTURES)
        return File.createTempFile(
            "JPEG_${timeStamp}_", /* prefix */
            ".jpg", /* suffix */
            storageDir /* directory */
        ).apply {
            // Save a file path for use with ACTION_VIEW intents
            imageFilePath = absolutePath
        }
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)

        if (requestCode == REQUEST_EDIT_BOOK && resultCode == Activity.RESULT_OK) {
            log.warning("Edit Activity finished")
            val editedBook = data?.getSerializableExtra("editedBook") as BookDto
            Toast.makeText(this, "Book ${editedBook.title} updated", Toast.LENGTH_SHORT).show()

            (recyclerview.adapter as? BookAdapter)?.updateBook(editedBook)
        }
        if(requestCode == REQUEST_CAMERA) {
            if (resultCode == Activity.RESULT_OK) {
                log.warning("Camera Activity finished")
                Toast.makeText(this, "Photo saved at $imageFilePath", Toast.LENGTH_SHORT).show()
            }
            Toast.makeText(this, "Camera intent returned $resultCode", Toast.LENGTH_SHORT).show()
        }
    }

    private fun isOnline(context: Context): String {
        val connectivityManager =
            context.getSystemService(Context.CONNECTIVITY_SERVICE) as ConnectivityManager
        if (connectivityManager != null) {
            val capabilities =
                connectivityManager.getNetworkCapabilities(connectivityManager.activeNetwork)
            if (capabilities != null) {
                if (capabilities.hasTransport(NetworkCapabilities.TRANSPORT_CELLULAR)) {
                    return "STATUS: CELLULAR"
                } else if (capabilities.hasTransport(NetworkCapabilities.TRANSPORT_WIFI)) {
                    return "STATUS: WIFI"
                } else if (capabilities.hasTransport(NetworkCapabilities.TRANSPORT_ETHERNET)) {
                    return "STATUS: ETHERNET"
                }
            }
        }
        return "NO CONNECTION"
    }

    private fun logout() {
        val sharedPreferences = getSharedPreferences("MyPrefs", Context.MODE_PRIVATE)
        val editor = sharedPreferences.edit()
        editor.remove("token")
        editor.apply()
        val intent = Intent(this, LoginActivity::class.java)
        intent.flags = Intent.FLAG_ACTIVITY_NEW_TASK or Intent.FLAG_ACTIVITY_CLEAR_TASK
        startActivity(intent)
        finish()
    }
}