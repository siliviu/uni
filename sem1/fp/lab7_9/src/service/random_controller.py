# lab 8

from service.book_controller import *
from service.client_controller import *
from service.util import *
from repo.memory_repository import *
from random import *


class RandomController:
    def __init__(self, book_data: Repo, client_data: Repo):
        """
        Initialises random controller
        * self - RandomController
        * data - Data
        """
        self.__book_data = book_data
        self.__client_data = client_data

    def generate_random_books(self, nr: int):
        """
        Generate random books
        * nr - int - number of books to generate
        """
        for _ in range(nr):
            try:
                self.__book_data.add(book(
                    randint(1, 250),
                    Utils.rand_string(12),
                    Utils.rand_string(20),
                    Utils.rand_string(15),
                    randint(1, 50)))
            except:
                pass

    def recursive_generate_random_books(self, nr: int):
        """
        Generate random books
        * nr - int - number of books to generate
        """
        if nr == 0:
            return
        try:
            self.__book_data.add(book(
                randint(1, 250),
                Utils.rand_string(12),
                Utils.rand_string(20),
                Utils.rand_string(15),
                randint(1, 50)))
            self.recursive_generate_random_books(nr - 1)
        except:
            pass

    def generate_random_clients(self, nr: int):
        """
        Generate random clients
        * nr - int - number of clients to generate
        """
        for _ in range(nr):
            try:
                self.__client_data.add(client(randint(1, 500), Utils.rand_string(15), randint(1, 10000000)))
            except:
                pass

    def recursive_generate_random_clients(self, nr: int):
        """
        Generate random clients
        * nr - int - number of clients to generate
        """
        if nr == 0:
            return
        try:
            self.__client_data.add(client(randint(1, 500), Utils.rand_string(15), randint(1, 10000000)))
            self.recursive_generate_random_clients(nr - 1)
        except:
            pass
