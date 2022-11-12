from repo.data import *
from domain.book import *
from service.util import *


class BookController:
    def __init__(self, data: Data):
        self.__data = data

    def get_book_list(self):
        return self.__data.get_book_list()

    def add_book(self, id, title, desc, author, copies):
        b = book(id, title, desc, author, copies)
        self.__data.add_book(b)

    def get_book(self, id):
        return self.__data.get_book(id)

    def remove_book(self, id):
        book_validator.validate_id(id)
        self.__data.remove_book(id)

    def modify_book(self, id, prop, val):
        book = self.__data.get_book(id)
        prop.__set__(book, val)
        self.__data.set_book(id, book)

    def get_books_criteria(self, mode, arg):
        books = self.__data.get_book_list()
        if mode == 0:
            book_validator.validate_id(arg)
            return [self.__data.get_book(arg)]
        elif mode == 1:
            book_validator.validate_title(arg)
            return [book for book in books if Utils.norm(arg) in Utils.norm(book.title)]
        else:
            book_validator.validate_author(arg)
            return [book for book in books if Utils.norm(arg) in Utils.norm(book.author)]
