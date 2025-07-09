from ui.util_menu import *
from service.book_controller import *


class SearchBookConsole:
    def __init__(self, ctrl: BookController):
        """Handles the menu for searching a book
        * db: data class representing all the data
        """
        self.__ctrl = ctrl
        Menu(
            "Choose the criteria for the search:",
            [
                ("ID", lambda: self.search_book(0)),
                ("Title", lambda: self.search_book(1)),
                ("Author", lambda: self.search_book(2)),
            ],
            "Go back\n",
            "Bad option. Please try again\n",
            persistent=False,
        )

    def search_book(self, mode):
        try:
            Menu.print_results(self.__ctrl.get_books_criteria(
                mode,
                int(input("Input ID: ")) if mode == 0
                else input("Input title: ") if mode == 1
                else input("Input author: ")))
        except ValueError:
            Menu.bad_input()
        except Exception as e:
            print(colored(e, "red"))
        finally:
            print()
