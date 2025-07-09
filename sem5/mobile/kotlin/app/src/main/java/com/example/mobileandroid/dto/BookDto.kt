package com.example.mobileandroid.dto

import androidx.room.Entity
import androidx.room.PrimaryKey
import java.io.Serializable

@Entity(tableName = "tickets")
data class BookDto(
    @PrimaryKey
    val _id: String = "",
    val title: String = "",
    val author: String = "",
    val price: Int = 0,
    val read: Boolean = false,
    val lat: Double = 0.0,
    val lng: Double = 0.0
//    val created: String = "",
//    val updated: String = ""
    ) : Serializable