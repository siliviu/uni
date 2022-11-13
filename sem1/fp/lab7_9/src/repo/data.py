from domain.book import *
from domain.client import *
from domain.event import *


class Data:
    def __init__(self):
        """
        Initialise data object
        * self - Data
        """
        self.__clients = {}
        self.__books = {}
        self.__events = {}

    def initiate_test_data(self):
        """
        Test helper function
        * self - Data
        """
        self.add_client(client(1, "Gigel", 128))
        self.add_client(client(2, "Gigelescu", 49))

        self.add_book(book(1, "Ana are mere", "Ana si mere", "Anuta Anisoara", 3))
        self.add_book(book(2, "Ana are mere 2", "Ana si mai multe mere", "Anuta Anisoara", 1))
        self.add_book(book(3, "Ana", "Doar ana", "Anica Anuta", 10))

    def get_book_list(self):
        """
        Returns a list of all book objects
        * self - Data
        """
        return [book for book in self.__books.values()]

    def get_client_list(self):
        """
        Returns a list of all client objects
        * self - Data
        """
        return [client for client in self.__clients.values()]

    def get_event_list(self):
        """
        Returns a list of all event objects
        * self - Data
        """
        return [event for event in self.__events.values()]

    def get_book(self, book_id: int) -> book:
        """
        Returns the book object with the corresponding id.
        Raises OperationException if book doesn't exit
        * self - Data
        * book_id - int(>=0) - id of the book
        """
        if not (book_id in self.__books):
            raise OperationException("Book doesn't exist in collection")
        return self.__books[book_id]

    def set_book(self, book_id: int, book: book):
        """
        Sets the existing book with book_id to a new book object
        Raises OperationException if book doesn't exit
        * self - Data
        * book_id - int (>=0) - id of the book to modify
        * book - book - modified version of book
        """
        if not (book_id in self.__books):
            raise OperationException("Book doesn't exist in collection")
        self.__books[book_id] = book

    def get_client(self, client_id: int) -> client:
        """
        Returns the client object with the corresponding id.
        Raises OperationException if client doesn't exit
        * self - Data
        * client_id - int(>=0) - id of the client
        """
        if not (client_id in self.__clients):
            raise OperationException("Client isn't in the list")
        return self.__clients[client_id]

    def set_client(self, client_id: int, client: client):
        """
        Sets the existing client with client_id to a new client object
        Raises OperationException if client doesn't exit
        * self - Data
        * client_id - int (>=0) - client of the book to modify
        * client - client - modified version of client
        """
        if not (client_id in self.__clients):
            raise OperationException("Client isn't in the list")
        self.__clients[client_id] = client

    def add_book(self, book: book):
        """
        Adds a book object to the list
        Raises OperationException if the book already exists
        * self - Data
        * book - book - Book to add
        """
        if book.id in self.__books:
            raise OperationException("Book already exists in collection")
        self.__books[book.id] = book

    def remove_book(self, book_id: int):
        """
        Removes book with id book_id from the list
        Raises OperationException if the book doesn't exist
        * self - Data
        * book_id - int (>=0) - Id of the book to remove
        """
        if not (book_id in self.__books):
            raise OperationException("Book doesn't exist in collection")
        del self.__books[book_id]

    def add_client(self, client: client):
        """
        Adds a client object to the list
        Raises OperationException if the client already exists
        * self - Data
        * client - client - Client to add
        """
        if client.id in self.__clients:
            raise OperationException("Client already exists")
        self.__clients[client.id] = client

    def remove_client(self, client_id: int):
        """
        Removes client with id client_id from the list
        Raises OperationException if the client doesn't exist
        * self - Data
        * client_id - int (>=0) - Id of the client to remove
        """
        if not (client_id in self.__clients):
            raise OperationException("Client already exists")
        del self.__clients[client_id]

    def add_book_borrowed(self, object_id: int, event_id: int):
        """
        Adds borrow event to book
        * self - Data
        * object_id - id of the book
        * event_id - id of the event
        """
        book = self.get_book(object_id)
        book.add_borrowed(event_id)
        self.set_book(object_id, book)

    def remove_book_borrowed(self, object_id: int, event_id: int):
        """
        Removes borrow event from book
        * self - Data
        * object_id - id of the book
        * event_id - id of the event
        """
        book = self.get_book(object_id)
        book.remove_borrowed(event_id)
        self.set_book(object_id, book)

    def add_client_borrowed(self, object_id: int, event_id: int):
        """
        Adds borrow event to client
        * self - Data
        * object_id - id of the client
        * event_id - id of the event
        """
        client = self.get_client(object_id)
        client.add_borrowed(event_id)
        self.set_client(object_id, client)

    def remove_client_borrowed(self, object_id: int, event_id: int):
        """
        Removes borrow event from client
        * self - Data
        * object_id - id of the client
        * event_id - id of the event
        """
        client = self.get_client(object_id)
        client.remove_borrowed(event_id)
        self.set_client(object_id, client)

    def add_event(self, event: event):
        """
        Adds an event object to the list
        Raises OperationException if the event already exists
        * self - Data
        * event - Event - Event to add
        """
        self.__events[event.id] = event

    def get_event(self, event_id: int) -> event:
        """
        Returns the event object with the corresponding id.
        Raises OperationException if event doesn't exit
        * self - Data
        * event_id - int(>=0) - id of the event
        """
        if not (event_id in self.__events):
            raise OperationException("Event doesn't exist")
        return self.__events[event_id]

    def get_new_event_id(self):
        """
        Returns an int representing the next id to add an event
        * self - Data
        """
        return len(self.__events) + 1
