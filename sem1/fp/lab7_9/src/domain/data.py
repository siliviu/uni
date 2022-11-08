from domain.book import *
from domain.client import *


class data:
    def __init__(self):
        self._clients = {}
        self._books = {}
        self._events = []

    def get_book_list(self):
        return [book for [key,book] in self._books.items()]

    def get_book(self, book_id):
        return self._books[book_id]
    
    def set_book(self, book_id, book:book):
        self._books[book_id]=book

    def add_book(self, book:book):
        if book.get_id() in self._books:
            raise TypeError("Book already exists in collection")
        self._books[book.get_id()] = book

    def remove_book(self, book:book):
        del self._books[book.get_id()]

    pass
