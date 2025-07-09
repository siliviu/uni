from repo.memory_repository import *
from domain.book import *
from service.util import *

class BookController:
    def __init__(self, data: Repo):
        """
        Initialises book controller
        * self - BookController
        * data - Data
        """
        self.__data = data

    def get_book_list(self):
        """
        Returns a list of all book objects
        * self - BookController
        """
        return self.__data.get_list()

    def add_book(self, *args):
        """
        Adds book to list
        Raises operation exception if the book is a duplicate
        self - BookController
        * id - (int >=0) - id of the book
        * title - (nonempty) - title of book
        * desc - (nonempty) - desc of book
        * author - (nonempty) - author of book
        * copies - (int >=0) - uid of the book
        """
        b = book(*args)
        self.__data.add(b)

    def get_book(self, id: int):
        """
        Gets book from list by id
        Raises operation exception if there's no book with id
        * self - BookController
        * id - (int >= 0) - id of the book to search
        """
        book_validator.validate_id(id)
        return self.__data.get(id)

    def remove_book(self, id: int):
        """
        Removes book from list by id
        Raises operation exception if there's no book with id
        * self - BookController
        * id - (int >= 0) - id of the book to remove
        """
        book_validator.validate_id(id)
        self.__data.remove(id)

    def modify_book(self, id: int, prop: property, val: int | str):
        """
        Modifies book from list by id
        Raises OperationException if there's no book with id or ConstraintException if val is invalid
        * self - BookController
        * id - (int >= 0) - id of the book to modify
        * prop - property - property to modify
        * val - int | string - value to modify
        """
        book_validator.validate_id(id)
        book = self.__data.get(id)
        prop.__set__(book, val)
        self.__data.set(id, book)

    def change_borrow(self, id: int, func, event_id: int):
        """
        Adds borrow event to book. FOR TESTING ONLY
        * self - BookController
        * id - id of the book to modify
        * func - function to add/remove borrow from book
        * event_id - event id to add
        """
        b = self.__data.get(id)
        func(b, event_id)
        self.__data.set(id, b)

    def get_books_criteria(self, mode: int, arg: int | str):
        """
        Gets list book objects meeting criteria for search
        Raises ConstraintException if the search arg is invalid
        * self - BookControllera
        * mode - int -
            * 0 if searching by id
            * 1 if searching by title
            * 2 if searching by author
        * arg - int | string - search argument
        """
        books = self.__data.get_list()
        if mode == 0:
            book_validator.validate_id(arg)
            return [self.__data.get(arg)]
        elif mode == 1:
            book_validator.validate_title(arg)
            return [book for book in books if Utils.norm(arg) in Utils.norm(book.title)]
        else:
            book_validator.validate_author(arg)
            return [book for book in books if Utils.norm(arg) in Utils.norm(book.author)]