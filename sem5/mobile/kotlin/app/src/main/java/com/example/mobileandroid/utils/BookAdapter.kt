package com.example.mobileandroid.utils

import android.graphics.Color
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.LinearLayout
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.example.mobileandroid.R
import com.example.mobileandroid.dto.BookDto

class BookAdapter(private val mList: MutableList<BookDto>, private val onItemClick: (BookDto) -> Unit) : RecyclerView.Adapter<BookAdapter.ViewHolder>() {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val view = LayoutInflater.from(parent.context)
            .inflate(R.layout.item_book, parent, false)

        return ViewHolder(view)
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {

        val book = mList[position]

        if (book.read) {
            holder.mainLayout.setBackgroundColor(Color.GREEN)
        } else {
            holder.mainLayout.setBackgroundColor(Color.RED)
        }
        holder.nameView.text = book.title
        holder.authorView.text = "By: " + book.author
        holder.priceView.text = "Price: " + book.price.toString()
        holder.itemView.setOnClickListener {
            onItemClick.invoke(book)
        }
    }

    override fun getItemCount(): Int {
        return mList.size
    }

    fun updateBook(updatedBook: BookDto) {
        val position = mList.indexOfFirst { it._id == updatedBook._id }
        if (position != -1) {
            mList[position] = updatedBook
            notifyItemChanged(position)
        }
    }

    class ViewHolder(ItemView: View) : RecyclerView.ViewHolder(ItemView) {
        val mainLayout: LinearLayout = itemView.findViewById(R.id.ll_main_layout)
        val nameView: TextView = itemView.findViewById(R.id.text_name)
        val authorView: TextView = itemView.findViewById(R.id.text_description)
        val priceView: TextView = itemView.findViewById(R.id.text_complexity)
    }
}