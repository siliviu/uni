from termcolor import colored

class event:
    def __init__(self, id, book, owner):
        self.__id = id
        self.__book = book
        self.__owner = owner

    @property
    def id(self):
        return self.__id

    @property
    def book(self):
        return self.__book

    @property
    def owner(self):
        return self.__owner

    def __str__(self):
        s = ""
        s += f"Event ID : {colored(str(self.id),'blue')}, "
        s += f"Borrower ID : {colored(str(self.owner),'blue')}, "
        s += f"Book ID : {colored(str(self.book),'blue')}"
        return s
