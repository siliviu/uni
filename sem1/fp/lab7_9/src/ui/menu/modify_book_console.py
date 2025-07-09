from ui.util_menu import *
from service.book_controller import *


class ModifyBookConsole:
    def __init__(self, ctrl: BookController):
        """Handles the menu for modifying books
        * db: data class representing all the data
        """
        self.__ctrl = ctrl
        Menu(
            "Choose what to do with the book collection:",
            [
                ("Print book collection", self.print_books),
                ("Add a new book to the collection", self.add_book),
                ("Modify a book from collection", self.modify_book),
                ("Delete book from collection", self.remove_book),
            ],
            "Go back\n",
            "Bad option. Please try again\n",
        )

    def print_books(self):
        """Prints all books
        * data: data class representing all the data
        """
        print("The books in the collection are: \n")
        for book in self.__ctrl.get_book_list():
            print(book)
        print()

    def add_book(self):
        """Handles the input & adding of a book
        * data: data class representing all the data
        """
        try:
            id = int(input("Input book id: "))
            title = input("Input title: ")
            desc = input("Input description: ")
            author = input("Input author: ")
            copies = int(input("Input number of copies available: "))
            print()
            self.__ctrl.add_book(id, title, desc, author, copies)
            print(colored("The book has been successfully added: ", "green"))
            print(self.__ctrl.get_book(id))
        except ValueError:
            Menu.bad_input()
        except Exception as e:
            print(colored(e, "red"))
        finally:
            print()

    def modify_book(self):
        """Handles the input & modifying of a book
        * data: data class representing all the data
        """
        try:
            id = int(input("Enter the id of the book you want to modify: "))
            Menu(
                "Choose what to modify:",
                [
                    (
                        "Title of the book",
                        lambda: self.__ctrl.modify_book(
                            id, book.title, input("Input title: ")
                        ),
                    ),
                    (
                        "Description of the book",
                        lambda: self.__ctrl.modify_book(
                            id, book.desc, input("Input description: ")
                        ),
                    ),
                    (
                        "Author of the book",
                        lambda: self.__ctrl.modify_book(
                            id, book.author, input("Input author: ")
                        ),
                    ),
                    (
                        "Total number of copies available",
                        lambda: self.__ctrl.modify_book(
                            id, book.copies, int(input("Input number of copies: "))
                        ),
                    ),
                ],
                "Go back\n",
                "Bad option. Please try again\n",
                persistent=False,
            )
            print(colored("The book has been successfully modified: ", "green"))
            print(self.__ctrl.get_book(id))
        except ValueError:
            Menu.bad_input()
        except Exception as e:
            print(colored(e, "red"))
        finally:
            print()

    def remove_book(self):
        """Handles the input & removing of a book
        * data: data class representing all the data
        """
        try:
            id = int(input("Enter the id of the book you want to remove: "))
            print()
            self.__ctrl.remove_book(id)
            print(colored("The book has been successfully removed", "green"))
        except ValueError:
            Menu.bad_input()
        except Exception as e:
            print(colored(e, "red"))
        finally:
            print()
