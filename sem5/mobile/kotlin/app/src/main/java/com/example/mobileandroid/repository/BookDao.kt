package com.example.mobileandroid.repository

import androidx.room.Dao
import androidx.room.Insert
import androidx.room.OnConflictStrategy
import androidx.room.Query
import androidx.room.Update
import com.example.mobileandroid.dto.BookDto
import kotlinx.coroutines.flow.Flow

@Dao
interface BookDao {

    @Query("SELECT * FROM tickets")
    fun getAll(): Flow<List<BookDto>>

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    fun insert(book: BookDto)

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    fun insert(books: List<BookDto>)

    @Update
    fun update(book: BookDto): Int

    @Query("DELETE FROM tickets WHERE _id = :uuid")
    fun deleteById(uuid: String): Int

    @Query("DELETE FROM tickets")
    fun deleteAll()
}