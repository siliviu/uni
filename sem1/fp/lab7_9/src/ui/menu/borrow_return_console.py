from ui.util_menu import *
from service.book_controller import *
from service.client_controller import *
from service.event_controller import *


class BorrowReturnConsole:
    def __init__(self, event_ctrl: EventController, mode):
        self.__event_ctrl = event_ctrl
        self.__mode = mode
        self.dialog()

    def dialog(self):
        try:
            if self.__mode == "b":
                client_id = int(input("Enter the id of the client: "))
                book_id = int(input("Enter the id of the book: "))
                event_id = self.__event_ctrl.borrow_book(client_id, book_id)
                print(colored("\nThe book has been successfully borrowed", "green"))
                print(f"Event ID: {colored(str(event_id),'blue')}")
            else:
                event_id = int(input("Enter the id of the event: "))
                self.__event_ctrl.return_book(event_id)
                print(colored("\nThe book has been successfully returned", "green"))
        except ValueError:
            Menu.bad_input()
        except Exception as e:
            print(colored(e, "red"))
        finally:
            print()
