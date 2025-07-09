from termcolor import colored


class event:
    def __init__(self, id: int, book: int, owner: int):
        """
        Initialises event object
        * self - event
        * id, book, owner - int
        """
        self.__id = id
        self.__book = book
        self.__owner = owner

    @property
    def id(self):
        """
        Returns id (int) of the event
        """
        return self.__id

    @property
    def book(self):
        """
        Returns id (int) of the book
        """
        return self.__book

    @property
    def owner(self):
        """
        Returns id (int) of the client
        """
        return self.__owner

    def __eq__(self, other):
        """
        Returns true/false if two events are the same
        * self, other - event
        """
        return self.id == other.id and self.book == other.book and self.owner == other.owner

    def __str__(self):
        """
        Converts event to string
        self:event
        """
        s = ""
        s += f"Event ID : {colored(str(self.id),'blue')}, "
        s += f"Borrower ID : {colored(str(self.owner),'blue')}, "
        s += f"Book ID : {colored(str(self.book),'blue')}"
        return s

    def __repr__(self):
        return '\\'.join([str(self.id), str(self.book), str(self.owner)])

    @staticmethod
    def deserialise(e):
        args = e.strip().split('\\')
        r = event(int(args[0]), int(args[1]), int(args[2]))
        return r
