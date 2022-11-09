from ui.util import *
from service.util import *
from domain.book import *


def search_book(db, mode):
    try:
        id = None
        title = None
        author = None
        if mode == 0:
            id = int(input("Input ID: "))
            book_validator.validate_id(id)
        elif mode == 1:
            title = input("Input title: ")
            book_validator.validate_title(title)
        else:
            author = input("Input author: ")
            book_validator.validate_author(author)
        print()
        results = get_books_criteria(
            db, mode, id if mode == 0 else title if mode == 1 else author
        )
        print_results(results)
    except ValueError:
        bad_input()
    except ConstraintException as e:
        print(colored(e, "red"))
    finally:
        print()


def search_book_menu(db):
    """Handles the menu for searching a book
    * db: data class representing all the data
    """
    create_menu(
        "Choose the criteria for the search:",
        [
            ("ID", lambda db: search_book(db, 0)),
            ("Title", lambda db: search_book(db, 1)),
            ("Author", lambda db: search_book(db, 2)),
        ],
        "Go back\n",
        "Bad option. Please try again\n",
        db,
        persistent=False,
    )
