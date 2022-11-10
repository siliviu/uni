from termcolor import colored
from domain.client_validator import *


class client:
    def __init__(self, id, name, uid):
        self.id = id
        self.name = name
        self.uid = uid
        self.__borrowed = {}

    @property
    def id(self):
        return self.__id

    @id.setter
    def id(self, id):
        client_validator.validate_id(id)
        self.__id = id

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, name):
        client_validator.validate_name(name)
        self.__name = name

    @property
    def uid(self):
        return self.__uid

    @uid.setter
    def uid(self, uid):
        client_validator.validate_uid(uid)
        self.__uid = uid

    def __str__(self):
        s = ""
        s += f"ID : {colored(str(self.id),'blue')}, "
        s += f"Name : {colored(self.name,'blue')}, "
        s += f"UID : {colored(str(self.uid),'blue')}"
        return s
