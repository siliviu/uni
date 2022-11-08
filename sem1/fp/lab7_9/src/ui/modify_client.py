from ui.util import *
from domain.data import *


def print_clients(data):
    print("The clients in the list are: \n")
    for client in data.get_client_list():
        print(client)


def add_client(data):
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
    except TypeError as e:
        print(colored(e, "red"))
    finally:
        print()


def modify_client(data):
    try:
        id = int(input("Enter the id of the client you want to modify: "))
        client = data.get_client(id)
        ok = True
        create_menu(
            "Choose what to modify:",
            [
                ("Name of the client", lambda: client.set_name(input("Input name: "))),
                (
                    "UID of the client",
                    lambda: client.set_uid(input("Input UID: ")),
                ),
            ],
            "Go back\n",
            "Bad option. Please try again\n",
            persistent=False,
        )
        if not ok:
            return
        data.set_client(id, client)
        print("The client has been modified: ")
        print(data.get_client(id))
    except ValueError:
        bad_input()
    except TypeError as e:
        print(colored(e, "red"))
    finally:
        print()


def remove_client(data):
    try:
        id = int(input("Enter the id of the client you want to remove: "))
        print()
        data.remove_client(id)
        print("The client has been removed")
    except ValueError:
        bad_input()
    except TypeError as e:
        print(colored(e, "red"))
    finally:
        print()


def modify_client_menu(lst):
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
        lst,
    )
