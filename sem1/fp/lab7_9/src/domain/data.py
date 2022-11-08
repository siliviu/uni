from domain.book import *
from domain.client import *


class data:
    def __init__(self):
        self._clients = {}
        self._books = {}
        self._events = []

    def get_book_list(self):
        return [book for book in self._books.values()]

    def get_client_list(self):
        return [client for client in self._clients.values()]

    def get_book(self, book_id):
        if not (book_id in self._books):
            raise TypeError("Book doesn't exist in collection")
        return self._books[book_id]

    def set_book(self, book_id, book: book):
        if not (book_id in self._books):
            raise TypeError("Book doesn't exist in collection")
        self._books[book_id] = book
    
    def get_client(self, client_id):
        if not (client_id in self._clients):
            raise TypeError("Client isn't in the list")
        return self._clients[client_id]

    def set_client(self, client_id, client: client):
        if not (client_id in self._clients):
            raise TypeError("Client isn't in the list")
        self._clients[client_id] = client

    def add_book(self, book: book):
        if book.get_id() in self._books:
            raise TypeError("Book already exists in collection")
        self._books[book.get_id()] = book

    def remove_book(self, book_id):
        if not (book_id in self._books):
            raise TypeError("Book doesn't exist in collection")
        del self._books[book_id]

    def add_client(self, client: client):
        if client.get_id() in self._clients:
            raise TypeError("Client already exists")
        self._clients[client.get_id()] = client

    def remove_client(self, client_id):
        if not (client_id in self._clients):
            raise TypeError("Client already exists")
        del self._clients[client_id]
