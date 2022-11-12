from repo.data import *
from domain.book import *
from domain.client import *
from domain.event import *
from service.util import *


class EventController:
    def __init__(self, data: Data):
        """
        Initialises event controller
        * self - EventController
        * data - Data
        """
        self.__data = data

    def borrow_book(self, client_id, book_id):
        """
        Borrow a book, updating the client, book and creating an event for the action.
        Raises OperationException if the client or book don't exist
        * self - EventController
        * client_id, book_id - ints representing the id of the client and book to update
        """
        client = self.__data.get_client(client_id)
        book = self.__data.get_book(book_id)
        event_id = self.__data.get_new_event_id()
        self.__data.add_book_borrowed(book_id, event_id)
        self.__data.add_client_borrowed(client_id, event_id)
        e = event(event_id, book.id, client.id)
        self.__data.add_event(e)

    def return_book(self, event_id):
        """
        Returning a book, updating the client, book
        * self - EventController
        * event_id - int representing the id of a VALID borrow action
        """
        event = self.__data.get_event(event_id)
        book = self.__data.get_book(event.book)
        client = self.__data.get_client(event_id)
        self.__data.remove_book_borrowed(book, event_id)
        self.__data.remove_client_borrowed(client, event.id)
