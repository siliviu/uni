from repo.data import *
from domain.book import *
from domain.client import *
from domain.event import *
from service.util import *
from service.book_controller import *
from service.client_controller import *


class EventController:
    def __init__(
        self, data: Data, book_ctrl: BookController, client_ctrl: ClientController
    ):
        self.__data = data
        self.__book_ctrl = book_ctrl
        self.__client_ctrl = client_ctrl
        
    def borrow_book(self):
        pass

    def return_book(self):
        pass
