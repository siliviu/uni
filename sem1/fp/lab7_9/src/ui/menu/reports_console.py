from ui.util_menu import *
from service.book_controller import *
from service.client_controller import *
from service.event_controller import *


class ReportsConsole:
    def __init__(self, book_ctrl: BookController, client_ctrl: ClientController):
        self.__book_ctrl = book_ctrl
        self.__client_ctrl = client_ctrl
        Menu(
            "Choose the report type:",
            [("Print most borrowed books", lambda: Menu.print_results(self.__book_ctrl.get_most_borrowed())),
             ("Print clients who borrowed books ordered by name", lambda: Menu.print_results(
                 self.__client_ctrl.get_borrowers(0))),
             ("Print clients who borrowed books ordered by number of borrowed books", lambda: Menu.print_results(
                 self.__client_ctrl.get_borrowers(1))),
             ("Print the most active 20% clients ", lambda: Menu.print_results(
                 self.__client_ctrl.get_20th_percentile())),
             ("Print the most borrowed 20% books ", lambda: Menu.print_results(
                 self.__book_ctrl.get_20th_percentile())), ],
            "Go back\n", "Bad option. Please try again\n",)
