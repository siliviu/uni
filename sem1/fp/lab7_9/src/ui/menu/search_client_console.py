from ui.util_menu import *
from service.client_controller import *


class SearchClientConsole:
    def __init__(self, ctrl: ClientController):
        """Handles the menu for searching a client
        * db: data class representing all the data
        """
        self.__ctrl = ctrl
        Menu(
            "Choose the criteria for the search:",
            [
                ("ID", lambda: self.search_client(0)),
                ("Name", lambda: self.search_client(1)),
                ("UID", lambda: self.search_client(2)),
            ],
            "Go back\n",
            "Bad option. Please try again\n",
            persistent=False,
        )

    def search_client(self, mode):
        try:
            Menu.print_results(self.__ctrl.get_clients_criteria(
                mode,
                int(input("Input ID: ")) if mode == 0
                else input("Input name: ") if mode == 1
                else int(input("Input UID: "))))
        except ValueError:
            Menu.bad_input()
        except Exception as e:
            print(colored(e, "red"))
        finally:
            print()
