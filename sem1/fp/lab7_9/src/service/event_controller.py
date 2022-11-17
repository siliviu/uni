from service.book_controller import *
from service.client_controller import *
from service.util import *
from repo.memory_repository import *
from domain.book import *
from domain.client import *
from domain.event import *

class EventController:
    def __init__(self, data: MemoryRepo, book_ctrl: BookController, client_ctrl: ClientController):
        """
        Initialises event controller
        * self - EventController
        * data - Data
        """
        self.__data = data
        self.__book_ctrl = book_ctrl
        self.__client_ctrl = client_ctrl

    def borrow_book(self, client_id: int, book_id: int):
        """
        Borrow a book, updating the client, book and creating an event for the action.
        Raises OperationException if the client or book don't exist
        * self - EventController
        * client_id, book_id - ints representing the id of the client and book to update
        """
        b = self.__book_ctrl.get_book(book_id)
        c = self.__client_ctrl.get_client(client_id)
        event_id = self.__data.get_length() + 1
        
        self.__book_ctrl.change_borrow(book_id, book.add_borrowed, event_id)
        self.__client_ctrl.change_borrow(client_id, client.add_borrowed, event_id)

        e = event(event_id, b.id, c.id)
        self.__data.add(e)
        return event_id

    def return_book(self, event_id: int):
        """
        Returning a book, updating the client, book
        * self - EventController
        * event_id - int representing the id of a VALID borrow action
        """
        event = self.__data.get(event_id)
        b = self.__book_ctrl.get_book(event.book)
        c = self.__client_ctrl.get_client(event.owner)

        self.__book_ctrl.change_borrow(b.id, book.remove_borrowed, event_id)
        self.__client_ctrl.change_borrow(c.id, client.remove_borrowed, event.id)
