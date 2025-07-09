package com.example.mobileandroid.utils

import android.content.Context
import android.util.Log
import android.widget.Toast
import androidx.work.CoroutineWorker
import androidx.work.WorkerParameters
import kotlinx.coroutines.delay

class MyWorker(context: Context, params: WorkerParameters) :
    CoroutineWorker(context.applicationContext, params) {

    override suspend fun doWork(): Result {
        return try {
            for (i in 1..10) {
                delay(1000)
                Log.d("MyWorker", "Count: $i")
                showToast("WorkManager Count: $i")
            }

            Result.success()
        } catch (e: Exception) {
            Result.failure()
        }
    }

    private fun showToast(message: String) {
        applicationContext.let {
            android.os.Handler(it.mainLooper).post {
                val toast = Toast.makeText(it, message, Toast.LENGTH_SHORT)
                val handler = android.os.Handler()
                handler.postDelayed({ toast.cancel() }, 1000)
                toast.show()
            }
        }
    }
}