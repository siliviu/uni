from ui.util_menu import *
from ui.menu.modify_book_console import *
from ui.menu.modify_client_console import *
from ui.menu.search_book_console import *
from ui.menu.search_client_console import *
from ui.menu.borrow_return_console import *
from ui.menu.reports_console import *
from service.random_controller import *


class MenuConsole:
    def __init__(
        self,
        book_ctrl: BookController,
        client_ctrl: ClientController,
        event_ctrl: EventController,
        random_ctrl: RandomController,
        stats_ctrl: StatisticsController
    ):
        self.__book_ctrl = book_ctrl
        self.__client_ctrl = client_ctrl
        self.__event_ctrl = event_ctrl
        self.__random_ctrl = random_ctrl
        self.__stats_ctrl = stats_ctrl

    def run(self):
        """Main menu"""
        print("Welcome to the library app!\n")
        Menu(
            "Choose a command to execute",
            [
                ("Book collection", ModifyBookConsole, self.__book_ctrl),
                ("Client list", ModifyClientConsole, self.__client_ctrl),
                ("Search for book", SearchBookConsole, self.__book_ctrl),
                ("Search for client", SearchClientConsole, self.__client_ctrl),
                ("Borrow book", BorrowReturnConsole, self.__event_ctrl, 'b',),
                ("Return book", BorrowReturnConsole, self.__event_ctrl, 'r',),
                ("Reports", ReportsConsole, self.__stats_ctrl),
            ],
            "Exit",
            "Unknown command. Please try again\n",
        )
        print("You have closed the app. Goodbye!\n")
