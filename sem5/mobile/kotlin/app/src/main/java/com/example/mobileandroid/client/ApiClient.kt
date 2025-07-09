package com.example.mobileandroid.client

import com.google.gson.GsonBuilder
import okhttp3.OkHttpClient
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory

object Api {

    private const val BASE_URL = "http://172.17.141.44:3000/"

    private var gson = GsonBuilder().create()

    var token: String? = null

    val retrofit: Retrofit by lazy {
        Retrofit.Builder()
            .baseUrl(BASE_URL)
            .addConverterFactory(GsonConverterFactory.create(gson))
            .build()
    }
}

object ApiClient {
    val apiService: ApiService by lazy {
        Api.retrofit.create(ApiService::class.java)
    }
}