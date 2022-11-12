from domain.book import *
from domain.client import *
from domain.event import *


class Data:
    def __init__(self):
        """Initialise data object"""
        self.__clients = {}
        self.__books = {}
        self.__events = {}

    def initiate_test_data(self):
        """Test helper function"""
        self.add_client(client(1, "Gigel", 128))
        self.add_client(client(2, "Gigelescu", 49))

        self.add_book(book(1, "Ana are mere", "Ana si mere", "Anuta Anisoara", 3))
        self.add_book(book(2, "Ana are mere 2", "Ana si mai multe mere", "Anuta Anisoara", 1))
        self.add_book(book(3, "Ana", "Doar ana", "Anica Anuta", 10))

    def get_book_list(self):
        return [book for book in self.__books.values()]

    def get_client_list(self):
        return [client for client in self.__clients.values()]

    def get_event_list(self):
        return [event for event in self.__events.values()]

    def get_book(self, book_id) -> book:
        if not (book_id in self.__books):
            raise OperationException("Book doesn't exist in collection")
        return self.__books[book_id]

    def set_book(self, book_id, book: book):
        if not (book_id in self.__books):
            raise OperationException("Book doesn't exist in collection")
        self.__books[book_id] = book

    def get_client(self, client_id) -> client:
        if not (client_id in self.__clients):
            raise OperationException("Client isn't in the list")
        return self.__clients[client_id]

    def set_client(self, client_id, client: client):
        if not (client_id in self.__clients):
            raise OperationException("Client isn't in the list")
        self.__clients[client_id] = client

    def add_book(self, book: book):
        if book.id in self.__books:
            raise OperationException("Book already exists in collection")
        self.__books[book.id] = book

    def remove_book(self, book_id):
        if not (book_id in self.__books):
            raise OperationException("Book doesn't exist in collection")
        del self.__books[book_id]

    def add_client(self, client: client):
        if client.id in self.__clients:
            raise OperationException("Client already exists")
        self.__clients[client.id] = client

    def remove_client(self, client_id):
        if not (client_id in self.__clients):
            raise OperationException("Client already exists")
        del self.__clients[client_id]

    def add_book_borrowed(self, object_id, event_id):
        book = self.get_book(object_id)
        book.add_borrowed(event_id)
        self.set_book(object_id, book)

    def remove_book_borrowed(self, object_id, event_id):
        book = self.get_book(object_id)
        book.remove_borrowed(event_id)
        self.set_book(object_id, book)

    def add_client_borrowed(self, object_id, event_id):
        client = self.get_client(object_id)
        client.add_borrowed(event_id)
        self.set_client(object_id, client)

    def remove_client_borrowed(self, object_id, event_id):
        client = self.get_client(object_id)
        client.remove_borrowed(event_id)
        self.set_client(object_id, client)

    def add_event(self, event: event):
        self.__events[event.id] = event

    def get_event(self, event_id) -> event:
        if not (event_id in self.__events):
            raise OperationException("Event doesn't exist")
        return self.__events[event_id]

    def get_new_event_id(self):
        return len(self.__events) + 1
