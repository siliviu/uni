package com.example.mobileandroid.utils

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase
import com.example.mobileandroid.dto.BookDto
import com.example.mobileandroid.repository.BookDao

@Database(entities = arrayOf(BookDto::class), version = 1)
abstract class MyAppDatabase : RoomDatabase() {
    abstract fun bookDao(): BookDao

    companion object {
        @Volatile
        private var INSTANCE: MyAppDatabase? = null

        fun getDatabase(context: Context): MyAppDatabase {
            return INSTANCE ?: synchronized(this) {
                val instance = Room.databaseBuilder(
                    context,
                    MyAppDatabase::class.java,
                    "app_database"
                )
                    .allowMainThreadQueries().build()
                INSTANCE = instance
                instance
            }
        }
    }
}
