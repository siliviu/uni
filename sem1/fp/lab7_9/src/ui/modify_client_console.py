from ui.util import *
from service.controller import *


class ModifyClientConsole:
    def __init__(self, ctrl: Controller):
        """Handles the menu for modifying clients"""
        self.__ctrl = ctrl
        create_menu(
            "Choose what to do with the client list:",
            [
                ("Print client list", self.print_clients),
                ("Add a new client to the list", self.add_client),
                ("Modify a client from the list", self.modify_client),
                ("Delete a client from the list", self.remove_client),
            ],
            "Go back\n",
            "Bad option. Please try again\n",
        )

    def print_clients(self):
        """Prints all clients
        * data: data class representing all the data
        """
        print("The clients in the list are: \n")
        for client in self.__ctrl.get_client_list():
            print(client)
        print()

    def add_client(self):
        """Handles the input & adding of a client
        * data: data class representing all the data
        """
        try:
            id = int(input("Input client id: "))
            name = input("Input name: ")
            uid = int(input("Input client UID: "))
            print()
            self.__ctrl.add_client(id, name, uid)
            print("The client has been added: ")
            print(self.__ctrl.get_client(id))
        except ValueError:
            bad_input()
        except ConstraintException as e:
            print(colored(e, "red"))
        finally:
            print()

    def modify_client(self):
        """Handles the input & modifying of a client
        * data: data class representing all the data
        """
        try:
            id = int(input("Enter the id of the client you want to modify: "))
            create_menu(
                "Choose what to modify:",
                [
                    (
                        "Name of the client",
                        lambda: self.__ctrl.modify_client(
                            id, client.name, input("Input name: ")
                        ),
                    ),
                    (
                        "UID of the client",
                        lambda: self.__ctrl.modify_client(
                            id, client.uid, int(input("Input UID: "))
                        ),
                    ),
                ],
                "Go back\n",
                "Bad option. Please try again\n",
                persistent=False,
            )
            print("The client has been modified: ")
            print(self.__ctrl.get_client(id))
        except ValueError:
            bad_input()
        except ConstraintException as e:
            print(colored(e, "red"))
        finally:
            print()

    def remove_client(self):
        """Handles the input & removing of a client
        * data: data class representing all the data
        """
        try:
            id = int(input("Enter the id of the client you want to remove: "))
            print()
            self.__ctrl.remove_client(id)
            print("The client has been removed")
        except ValueError:
            bad_input()
        except ConstraintException as e:
            print(colored(e, "red"))
        finally:
            print()
