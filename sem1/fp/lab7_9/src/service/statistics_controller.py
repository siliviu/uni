from service.book_controller import *
from service.client_controller import *
from service.util import *
from repo.memory_repository import *
import math
import os.path
import re


class StatisticsController:
    def __init__(self, book_data: Repo, client_data: Repo):
        """
        Initialises statistics controller
        * self - StatisticsController
        * book_data - Book Data
        * client_data - Client Data
        """
        self.__book_data = book_data
        self.__client_data = client_data

    def get_most_borrowed(self):
        """
        Gets list of most borrowed 5 books.
        self - StatisticsController
        """
        books = self.__book_data.get_list().copy()

        def comp(a: book, b: book):
            if a.borrowers != b.borrowers:
                return a.borrowers - b.borrowers
            return a.copies - b.copies
        Utils.comb_sort(books, cmp=comp,reverse=True)
        # books.sort(key=lambda b: -b.borrowers)
        books = books[:5]
        return books

    def get_20th_percentile_books(self) -> list[(str, int)]:
        """
        Returns a list of pairs [name, nr of books borrowed] for the 20th percentile of clients
        * self - StatisticsController
        """
        books = self.__book_data.get_list().copy()
        Utils.insert_sort(books, key=lambda c: -c.borrowers)
        # books.sort(key=lambda c: -c.borrowers)
        books = books[:math.ceil(len(books)/5)]
        return [(book.title, book.borrowers) for book in books]

    def get_borrowers(self, mode: int, file: bool = False):
        """s
        Returns list with clients who borrowed books (and not returned them)
        * self - StatisticsController
        * mode - int = 0 if ordered by name, 1 if ordered by number of books
        """
        clients = self.__client_data.get_list()
        clients = list(filter(lambda c: c.borrowed != 0, clients))
        Utils.comb_sort(clients, key=lambda c: c.name if mode == 0 else -c.borrowed)
        # clients.sort(clients, key=lambda c: c.name if mode == 0 else -c.borrowed)
        # lab 10
        if file:
            with open(os.path.dirname(__file__)+'\\results.txt', 'w', encoding='utf-8') as f:
                for x in clients:
                    f.write(re.sub('\[[0-9;]+[a-zA-Z]?', ' ', str(x)+'\n'))
        return clients

    def get_20th_percentile_clients(self) -> list[(str, int)]:
        """
        Returns a list of pairs [name, nr of books borrowed] for the 20th percentile of clients
        * self - StatisticsController
        """
        clients = self.__client_data.get_list()
        Utils.insert_sort(clients, key=lambda c: -c.borrowed)
        # clients.sort(clients, key=lambda c: -c.borrowed)
        clients = clients[:math.ceil(len(clients)/5)]
        return [(client.name, client.borrowed) for client in clients]
