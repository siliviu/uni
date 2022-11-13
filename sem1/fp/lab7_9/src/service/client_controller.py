from repo.data import *
from domain.book import *
from service.util import *


class ClientController:
    def __init__(self, data: Data):
        """
        Initialises client controller
        * self - ClientController
        * data - Data
        """
        self.__data = data

    def get_client_list(self):
        """
        Returns a list of all client objects
        * self - ClientController
        """
        return self.__data.get_client_list()

    def add_client(self, id: int, name: str, uid: int):
        """
        Adds client to list
        Raises operation exception if the client is a duplicate
        self - ClientController
        * id - (int >=0) - id of the client
        * name - (nonempty) - name of client
        * uid - (int >=0) - uid of the client
        """
        b = client(id, name, uid)
        self.__data.add_client(b)

    def get_client(self, id: int):
        """
        Gets client from list by id
        Raises operation exception if there's no client with id
        * self - ClientController
        * id - (int >= 0) - id of the client to search
        """
        return self.__data.get_client(id)

    def remove_client(self, id: int):
        """
        Removes client from list by id
        Raises operation exception if there's no client with id
        * self - ClientController
        * id - (int >= 0) - id of the client to remove
        """
        client_validator.validate_id(id)
        self.__data.remove_client(id)

    def modify_client(self, id: int, prop: property, val: int | str):
        """
        Modifies client from list by id
        Raises OperationException if there's no client with id or ConstraintException if val is invalid
        * self - ClientController
        * id - (int >= 0) - id of the client to modify
        * prop - property - property to modify
        * val - int | string - value to modify
        """
        client = self.__data.get_client(id)
        prop.__set__(client, val)
        self.__data.set_client(id, client)

    def get_clients_criteria(self, mode: int, arg: int | str):
        """
        Gets clients meeting criteria for search
        Raises ConstraintException if the search arg is invalid
        * self - ClientController
        * mode - int -
            * 0 if searching by id
            * 1 if searching by name
            * 2 if searching by uid
        * arg - int | string - search argument
        """
        clients = self.__data.get_client_list()
        if mode == 0:
            client_validator.validate_id(arg)
            return [self.__data.get_client(arg)]
        elif mode == 1:
            client_validator.validate_name(arg)
            return [client for client in clients if Utils.norm(arg) in Utils.norm(client.name)]
        else:
            client_validator.validate_uid(arg)
            return [client for client in clients if arg == client.uid]
