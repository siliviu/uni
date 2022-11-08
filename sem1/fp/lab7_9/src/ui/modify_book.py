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
        new_book = book(id,title,desc,author,copies)
        data.add_book(new_book)
        print("The book has been added: ")
        print(data.get_book(id))
    except ValueError:
        bad_input()
    except TypeError as e:
        print(colored(e,"red"))
    finally:
        print()

def modify_book(data):
    pass
    
def remove_book(data):
    pass 

def modify_book_menu(lst):
    """Handles the menu for modifying books"""
    create_menu(
        "Choose what to do with the book collection:",
        [
            ("Print book collection", lambda lst: print_books(lst)),
            ("Add a new book to the collection", lambda lst: add_book(lst)),
            ("Modify a book from collection", lambda lst: modify_book(lst)),
            ("Delete book from collection", lambda lst: remove_book(lst))

        ],
        "Go back\n",
        "Bad option. Please try again\n",
        lst,
    )
