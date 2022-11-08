from ui.util import *
from domain.data import *


def print_books(data):
    print("The books in the collection are: \n")
    for book in data.get_book_list():
        print(book)


def add_book(data):
    try:
        id = int(input("Input book id: "))
        title = input("Input title: ")
        desc = input("Input description: ")
        author = input("Input author: ")
        copies = int(input("Input number of copies available: "))
        print()
        new_book = book(id, title, desc, author, copies)
        data.add_book(new_book)
        print("The book has been added: ")
        print(data.get_book(id))
    except ValueError:
        bad_input()
    except TypeError as e:
        print(colored(e, "red"))
    finally:
        print()


def modify_book(data):
    try:
        id = int(input("Enter the id of the book you want to modify: "))
        book = data.get_book(id)
        ok = True
        create_menu(
            "Choose what to modify:",
            [
                ("Title of the book", lambda: book.set_title(input("Input title: "))),
                (
                    "Description of the book",
                    lambda: book.set_desc(input("Input description: ")),
                ),
                (
                    "Author of the book",
                    lambda: book.set_author(input("Input author: ")),
                ),
                (
                    "Total number of copies available",
                    lambda: book.set_copies(int(input("Input number of copies: "))),
                ),
            ],
            "Go back\n",
            "Bad option. Please try again\n",
            persistent=False,
        )
        if not ok:
            return
        data.set_book(id, book)
        print("The book has been modified: ")
        print(data.get_book(id))
    except ValueError:
        bad_input()
    except TypeError as e:
        print(colored(e, "red"))
    finally:
        print()


def remove_book(data):
    try:
        id = int(input("Enter the id of the book you want to remove: "))
        print()
        data.remove_book(id)
        print("The book has been removed")
    except ValueError:
        bad_input()
    except TypeError as e:
        print(colored(e, "red"))
    finally:
        print()


def modify_book_menu(lst):
    """Handles the menu for modifying books"""
    create_menu(
        "Choose what to do with the book collection:",
        [
            ("Print book collection", print_books),
            ("Add a new book to the collection", add_book),
            ("Modify a book from collection", modify_book),
            ("Delete book from collection", remove_book),
        ],
        "Go back\n",
        "Bad option. Please try again\n",
        lst,
    )
