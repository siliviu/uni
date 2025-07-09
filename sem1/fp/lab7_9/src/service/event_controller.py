from service.book_controller import *
from service.client_controller import *
from service.util import *
from repo.memory_repository import *
from domain.event import *


class EventController:
    def __init__(self, event_data: Repo, book_data: Repo, client_data: Repo):
        """
        Initialises event controller
        * self - EventController
        * data - Data
        """
        self.__data = event_data
        self.__book_data = book_data
        self.__client_data = client_data

    def borrow_book(self, client_id: int, book_id: int):
        """
        Borrow a book, updating the client, book and creating an event for the action.
        Raises OperationException if the client or book don't exist
        * self - EventController
        * client_id, book_id - ints representing the id of the client and book to update
        """
        b = self.__book_data.get(book_id)
        c = self.__client_data.get(client_id)
        event_id = self.__data.get_length() + 1
        b.add_borrowed(event_id)
        self.__book_data.set(b.id, b)
        c.add_borrowed(event_id)
        self.__client_data.set(c.id, c)

        e = event(event_id, b.id, c.id)
        self.__data.add(e)
        return event_id

    def return_book(self, event_id: int):
        """
        Returning a book, updating the client, book
        Raises OperationException if the event is invalid or the book has already been returned
        * self - EventController
        * event_id - int representing the id of a VALID borrow action
        """
        event = self.__data.get(event_id)
        b = self.__book_data.get(event.book)
        c = self.__client_data.get(event.owner)

        b.remove_borrowed(event_id)
        self.__book_data.set(b.id, b)
        c.remove_borrowed(event_id)
        self.__client_data.set(c.id, c)
