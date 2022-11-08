# 4 from https://www.cs.ubbcluj.ro/~istvanc/fp/lab/Lab7-9.pdf

from ui.util import *
from ui.modify_book import *
from ui.modify_client import *
from domain.data import *

def main():
    db = data()
    print("Welcome to the library app!\n")
    create_menu(
        "Choose a command to execute",
        [
            ("Modify the book collection", modify_book_menu),
            ("Modify the client list", modify_client_menu),
            ("Search for book", ),
            ("Search for client", ),
            ("Borrow book", ),
            ("Return book", ),
            ("Reports", )
        ],
        "Exit",
        "Unknown command. Please try again\n",
        db,
    )
    print("You have closed the app. Goodbye!\n")


if __name__ == "__main__":
    main()