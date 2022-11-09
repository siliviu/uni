from repo.data import *
from domain.book import *


class Controller:
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
        self.__data.remove_book(id)

    def modify_book(self, id, prop, val):
        prop.__set__(self.__data.get_book(id), val)
    
    def get_client_list(self):
        return self.__data.get_client_list()

    def add_client(self, id, name, uid):
        b = client(id, name, uid)
        self.__data.add_client(b)

    def get_client(self, id):
        return self.__data.get_client(id)

    def remove_client(self, id):
        self.__data.remove_client(id)

    def modify_client(self, id, prop, val):
        prop.__set__(self.__data.get_client(id), val)
