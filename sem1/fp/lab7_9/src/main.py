from ui.util import *

def main():
    lst = []
    print("Welcome to the library app!\n")
    create_menu(
        "Choose a command to execute",
        [
            ("Modify the book collection", ),
            ("Modify the client list", ),
            ("Search for book", ),
            ("Search for client", ),
            ("Borrow/return book", ),
            ("Reports")
        ],
        "Exit",
        "Unknown command. Please try again\n",
        lst,
    )
    print("You have closed the app. Goodbye!\n")

if __name__ == "__main__":
    main()