from termcolor import colored
from domain.client_validator import *


class client:
    def __init__(self, id: int, name: str, uid: int):
        """
        Initialise event object. Raises ConstraintException if params are invalid
        self - client
        * id, uid - int (>= 0)
        * name - string (non empty)
        """
        self.id = id
        self.name = name
        self.uid = uid
        self.__borrowed = set()

    @property
    def id(self):
        """
        Returns id (int) of the client
        * self - client
        """
        return self.__id

    @id.setter
    def id(self, id: int):
        """
        Sets id of the client. Raises ConstraintException if params are invalid
        * self - client
        * id - int (>= 0)
        """
        client_validator.validate_id(id)
        self.__id = id

    @property
    def name(self):
        """
        Returns name (string) of the client. Raises ConstraintException if params are invali
        * self - client
        """
        return self.__name

    @name.setter
    def name(self, name: str):
        """
        Sets name of the client. Raises ConstraintException if params are invalid
        * self - client
        * name - string (not empty)
        """
        client_validator.validate_name(name)
        self.__name = name

    @property
    def uid(self):
        """
        Returns uid (int) of the client
        * self - client
        """
        return self.__uid

    @uid.setter
    def uid(self, uid: int):
        """
        Sets uid of the client. Raises ConstraintException if params are invalid
        * self - client
        * id - int (>= 0)
        """
        client_validator.validate_uid(uid)
        self.__uid = uid

    @property
    def borrowed(self):
        """
        Returns number of borrowed books (int)
        """
        return len(self.__borrowed)

    def add_borrowed(self, event_id: int):
        """
        Adds borrow event to client
        * self - client
        * event_id - int
        """
        self.__borrowed.add(event_id)

    def remove_borrowed(self, event_id: int):
        """
        Remove borrow event to client
        * self - client
        * event_id - int
        """
        if event_id not in self.__borrowed:
            raise ConstraintException("Event already handled")
        self.__borrowed.remove(event_id)

    def __eq__(self, other):
        """
        Returns true/false if two clients are the same
        * self, other - client
        """
        return self.id == other.id and self.name == other.name and self.uid == other.uid and self.__borrowed == other.__borrowed

    def __str__(self):
        """
        Converts client to string
        * self:string
        """
        s = ""
        s += f"ID : {colored(str(self.id),'blue')}, "
        s += f"Name : {colored(self.name,'blue')}, "
        s += f"UID : {colored(str(self.uid),'blue')}, "
        s += f"Borrowed : {colored(str(self.borrowed),'blue')}"
        return s

    def __repr__(self):
        s = '\\'.join([str(self.id),self.name,str(self.uid)])+'|'
        for x in self.__borrowed:
            s += str(x) + ' '
        return s

    @staticmethod
    def deserialise(e):
        a, b = e.strip().split('|')
        args = a.strip().split('\\')
        args[0] = int(args[0])
        args[2] = int(args[2])
        r = client(*args)
        if b != '':
            events = b.strip().split(' ')
            for x in events:
                r.__borrowed.add(int(x))
        return r
