package com.example.mobileandroid

import android.app.Activity
import android.content.Intent
import android.os.Bundle
import android.widget.Button
import android.widget.CheckBox
import android.widget.EditText
import androidx.appcompat.app.AppCompatActivity
import androidx.appcompat.widget.Toolbar
import com.example.mobileandroid.client.Api
import com.example.mobileandroid.client.ApiClient
import com.example.mobileandroid.dto.BookDto
import com.example.mobileandroid.utils.MyAppDatabase
import java.util.logging.Logger

import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response

class EditBookActivity : AppCompatActivity() {

    private val log: Logger = Logger.getLogger(EditBookActivity::class.java.name)

    private val database: MyAppDatabase by lazy { MyAppDatabase.getDatabase(this) }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_edit_book)

        val toolbar = findViewById<Toolbar>(R.id.toolbar)
        setSupportActionBar(toolbar)

        val nameField = findViewById<EditText>(R.id.et_name)
        val descriptionField = findViewById<EditText>(R.id.et_description)
        val complexityField = findViewById<EditText>(R.id.et_complexity)
        val isDoneField = findViewById<CheckBox>(R.id.cb_done)
        val buttonSubmit = findViewById<Button>(R.id.btn_save)

        val token = Api.token

        val book = intent.getSerializableExtra("book", BookDto::class.java)

        buttonSubmit.setOnClickListener {
            val call = ApiClient.apiService.updateBook("Bearer $token", book?._id ?: "",BookDto(
                _id = book?._id ?: "",
                title = nameField.text.toString(),
                author = descriptionField.text.toString(),
                price = complexityField.text.toString().toInt(),
                read = isDoneField.isChecked
            ))
            call.enqueue(object : Callback<BookDto> {
                override fun onResponse(call: Call<BookDto>, response: Response<BookDto>) {
                    if (response.isSuccessful) {
                        val editedBookData = response.body()
                        log.warning(book.toString())
                        val returnIntent = Intent()
                        returnIntent.putExtra("editedBook", editedBookData)
                        if (book != null) {
                            database.bookDao().update(editedBookData!!)
                        }
                        setResult(Activity.RESULT_OK, returnIntent)
                        finish()
                    } else {
                        log.warning("Update book failed: ${response.code()}")
                    }
                }

                override fun onFailure(call: Call<BookDto>, t: Throwable) {
                    log.warning(t.toString())
                }
            })
        }

        supportActionBar?.setDisplayHomeAsUpEnabled(true)

        if (book != null) {
            nameField.setText(book.title)
            descriptionField.setText(book.author)
            complexityField.setText(book.price.toString())
            isDoneField.isChecked = book.read
        }
    }

    override fun onSupportNavigateUp(): Boolean {
        onBackPressed()
        return true
    }
}