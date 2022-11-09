from ui.util import *
from service.util import *
from domain.client import *


def search_client(db, mode):
    try:
        id = None
        name = None
        uid = None
        if mode == 0:
            id = int(input("Input ID: "))
            client_validator.validate_id(id)
        elif mode == 1:
            name = input("Input name: ")
            client_validator.validate_title(name)
        else:
            uid = int(input("Input UID: "))
            client_validator.validate_uid(uid)
        print()
        results = get_clients_criteria(
            db, mode, id if mode == 0 else name if mode == 1 else uid
        )
        print_results(results)
    except ValueError:
        bad_input()
    except ConstraintException as e:
        print(colored(e, "red"))
    finally:
        print()


def search_client_menu(db):
    """Handles the menu for searching a client
    * db: data class representing all the data
    """
    create_menu(
        "Choose the criteria for the search:",
        [
            ("ID", lambda db: search_client(db, 0)),
            ("Name", lambda db: search_client(db, 1)),
            ("UID", lambda db: search_client(db, 2)),
        ],
        "Go back\n",
        "Bad option. Please try again\n",
        db,
        persistent=False,
    )
