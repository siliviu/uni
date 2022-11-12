from ui.util import *
from ui.modify_book_console import *
from ui.modify_client_console import *
from ui.search_book_console import *
from ui.search_client_console import *
from ui.borrow_return_console import *


class Console:
    def __init__(
        self,
        book_ctrl: BookController,
        client_ctrl: ClientController,
        event_ctrl: EventController,
    ):
        self.__book_ctrl = book_ctrl
        self.__client_ctrl = client_ctrl
        self.__event_ctrl = event_ctrl

    def run(self):
        """Main menu"""
        print("Welcome to the library app!\n")
        create_menu(
            "Choose a command to execute",
            [
                ("Modify the book collection", ModifyBookConsole, self.__book_ctrl),
                ("Modify the client list", ModifyClientConsole, self.__client_ctrl),
                ("Search for book", SearchBookConsole, self.__book_ctrl),
                ("Search for client", SearchClientConsole, self.__client_ctrl),
                (
                    "Borrow book",
                    BorrowReturnConsole,
                    self.__book_ctrl,
                    self.__client_ctrl,
                    self.__event_ctrl,
                    'b',
                ),
                (
                    "Return book",
                    BorrowReturnConsole,
                    self.__book_ctrl,
                    self.__client_ctrl,
                    self.__event_ctrl,
                    'r',
                ),
                ("Reports",),
            ],
            "Exit",
            "Unknown command. Please try again\n",
        )
        print("You have closed the app. Goodbye!\n")
