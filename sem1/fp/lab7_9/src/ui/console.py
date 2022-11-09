from ui.util import *
from ui.modify_client import *
from ui.search_book import *
from ui.search_client import *

from ui.modify_book_console import *
from ui.modify_client_console import *


class Console:
    def __init__(self, ctrl):
        self.__ctrl = ctrl

    def run(self):
        """Main menu"""
        print("Welcome to the library app!\n")
        create_menu(
            "Choose a command to execute",
            [
                ("Modify the book collection", ModifyBookConsole),
                ("Modify the client list", ModifyClientConsole),
                ("Search for book", search_book_menu),
                ("Search for client", search_client_menu),
                ("Borrow book",),
                ("Return book",),
                ("Reports",),
            ],
            "Exit",
            "Unknown command. Please try again\n",
            self.__ctrl,
        )
        print("You have closed the app. Goodbye!\n")
