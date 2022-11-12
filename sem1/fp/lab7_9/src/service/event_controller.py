from repo.data import *
from domain.book import *
from domain.client import *
from domain.event import *
from service.util import *


class EventController:
    def __init__(self, data: Data):
        self.__data = data

    def borrow_book(self, client_id, book_id):
        client = self.__data.get_client(client_id)
        book = self.__data.get_book(book_id)
        event_id = self.__data.get_new_event_id()
        book.add_borrowed(event_id)
        client.add_borrowed(event_id)
        e = event(event_id, book.id, client.id)
        self.__data.add_event(e)
        for x in self.__data.get_event_list():
            print(x)

    def return_book(self, event_id):
        event = self.__data.get_event(event_id)
        book = self.__data.get_book(event.book)
        client = self.__data.get_client(event_id)
        book.remove_borrowed(event_id)
        client.remove_borrowed(event.id)
        for x in self.__data.get_event_list():
            print(x)

