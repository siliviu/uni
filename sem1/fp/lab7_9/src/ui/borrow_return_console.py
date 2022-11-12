from ui.util import *
from service.book_controller import *
from service.client_controller import *
from service.event_controller import *


class BorrowReturnConsole:
    def __init__(self, book_ctrl, client_ctrl, event_ctrl, mode):
        self.__book_ctrl = book_ctrl
        self.__client_ctrl = client_ctrl
        self.__event_ctrl = event_ctrl
        self.__mode = mode
        self.dialog()

    def dialog(self):
        try:
            client_id = int(input("Enter the id of the client:"))
            book_id = int(input("Enter the id of the book"))
            if self.__mode == "b":
                self.__event_ctrl.borrow_book(client_id, book_id)
                print("The book has been successfully borrowed")
            else:
                self.__event_ctrl.return_book(client_id, book_id)
                print("The book has been successfully returned")
        except ValueError:
            bad_input()
        except Exception as e:
            print(colored(e, "red"))
        finally:
            print()
