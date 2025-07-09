package com.example.mobileandroid.client;

import com.example.mobileandroid.dto.LoginRequest
import com.example.mobileandroid.dto.LoginResponse
import com.example.mobileandroid.dto.BookDto
import retrofit2.Call
import retrofit2.http.Body
import retrofit2.http.GET
import retrofit2.http.Header
import retrofit2.http.Headers
import retrofit2.http.POST
import retrofit2.http.PUT
import retrofit2.http.Path

interface ApiService {
    @Headers("Content-Type: application/json")
    @POST("login")
    fun login(@Body username: LoginRequest): Call<LoginResponse>

    @Headers("Content-Type: application/json")
    @GET("books")
    fun getBooks(@Header("Authorization") authorization: String): Call<List<BookDto>>

    @Headers("Content-Type: application/json")
    @PUT("books/{id}")
    fun updateBook(@Header("Authorization") authorization: String, @Path("id") bookId: String, @Body book: BookDto): Call<BookDto>
}
