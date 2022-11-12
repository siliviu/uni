from domain.book import *
from domain.client import *


class Data:
    def __init__(self):
        self.__clients = {}
        self.__books = {}
        self.__events = []

    def initiate_test_data(self):
        self.add_client(client(1, "Gigel", 128))
        self.add_client(client(2, "Gigelescu", 49))

        self.add_book(book(1, "Ana are mere", "Ana si mere", "Anuta Anisoara", 3))
        self.add_book(book(2, "Ana are mere 2", "Ana si mai multe mere", "Anuta Anisoara", 1))
        self.add_book(book(3, "Ana", "Doar ana", "Anica Anuta", 10))

    def get_book_list(self):
        return [book for book in self.__books.values()]

    def get_client_list(self):
        return [client for client in self.__clients.values()]

    def get_book(self, book_id):
        if not (book_id in self.__books):
            raise OperationException("Book doesn't exist in collection")
        return self.__books[book_id]

    def set_book(self, book_id, book: book):
        if not (book_id in self.__books):
            raise OperationException("Book doesn't exist in collection")
        self.__books[book_id] = book

    def get_client(self, client_id):
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
