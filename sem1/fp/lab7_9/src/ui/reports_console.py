from ui.menu import *
from service.book_controller import *
from service.client_controller import *
from service.event_controller import *


class ReportsConsole:
    def __init__(self, book_ctrl: BookController, client_ctrl: ClientController):
        self.__book_ctrl = book_ctrl
        self.__client_ctrl = client_ctrl
        Menu(
            "Choose the report type:",
            [
                ("Print most borrowed books", self.__book_ctrl),
                ("Print clients who borrowed books ordered by name, number of borrowed books", self.__client_ctrl),
                ("Print the most active 20% clients ", self.__client_ctrl),
            ],
            "Go back\n",
            "Bad option. Please try again\n",
        )
