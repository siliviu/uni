from ui.util import *
from repo.data import *
from domain.book import *
from domain.client import *


def print_clients(data):
    """Prints all clients
    * data: data class representing all the data
    """
    print("The clients in the list are: \n")
    for client in data.get_client_list():
        print(client)


def add_client(data):
    """Handles the input & adding of a client
    * data: data class representing all the data
    """
    try:
        id = int(input("Input client id: "))
        name = input("Input name: ")
        uid = int(input("Input client UID: "))
        print()
        new_client = client(id, name, uid)
        data.add_client(new_client)
        print("The client has been added: ")
        print(data.get_client(id))
    except ValueError:
        bad_input()
    except ConstraintException as e:
        print(colored(e, "red"))
    finally:
        print()


def modify_client(data: Data):
    """Handles the input & modifying of a client
    * data: data class representing all the data
    """
    try:
        id = int(input("Enter the id of the client you want to modify: "))
        crt_client = data.get_client(id)

        def handle_name():
            crt_client.name = input("Input name: ")

        def handle_uid():
            crt_client.uid = int(input("Input UID: "))

        create_menu(
            "Choose what to modify:",
            [
                ("Name of the client", handle_name),
                ("UID of the client", handle_uid),
            ],
            "Go back\n",
            "Bad option. Please try again\n",
            persistent=False,
        )
        data.set_client(id, crt_client)
        print("The client has been modified: ")
        print(data.get_client(id))
    except ValueError:
        bad_input()
    except ConstraintException as e:
        print(colored(e, "red"))
    finally:
        print()


def remove_client(data):
    """Handles the input & removing of a client
    * data: data class representing all the data
    """
    try:
        id = int(input("Enter the id of the client you want to remove: "))
        print()
        data.remove_client(id)
        print("The client has been removed")
    except ValueError:
        bad_input()
    except ConstraintException as e:
        print(colored(e, "red"))
    finally:
        print()


def modify_client_menu(db):
    """Handles the menu for modifying clients"""
    create_menu(
        "Choose what to do with the client list:",
        [
            ("Print client list", print_clients),
            ("Add a new client to the list", add_client),
            ("Modify a client from the list", modify_client),
            ("Delete a client from the list", remove_client),
        ],
        "Go back\n",
        "Bad option. Please try again\n",
        db,
    )
