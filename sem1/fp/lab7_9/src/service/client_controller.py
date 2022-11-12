from repo.data import *
from domain.book import *
from service.util import *


class ClientController:
    def __init__(self, data: Data):
        self.__data = data

    def get_client_list(self):
        return self.__data.get_client_list()

    def add_client(self, id, name, uid):
        b = client(id, name, uid)
        self.__data.add_client(b)

    def get_client(self, id):
        return self.__data.get_client(id)

    def remove_client(self, id):
        client_validator.validate_id(id)
        self.__data.remove_client(id)

    def modify_client(self, id, prop, val):
        prop.__set__(self.__data.get_client(id), val)

    def get_clients_criteria(self, mode, arg):
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
