from termcolor import colored
from domain.book_validator import *


class book:
    def __init__(self, id, title, desc, author, copies):
        self.id = id
        self.title = title
        self.desc = desc
        self.author = author
        self.copies = copies
        self.__borrowed = set()

    @property
    def id(self):
        return self.__id

    @id.setter
    def id(self, id):
        book_validator.validate_id(id)
        self.__id = id

    @property
    def title(self):
        return self.__title

    @title.setter
    def title(self, title):
        book_validator.validate_title(title)
        self.__title = title

    @property
    def desc(self):
        return self.__desc

    @desc.setter
    def desc(self, desc):
        book_validator.validate_desc(desc)
        self.__desc = desc

    @property
    def author(self):
        return self.__author

    @author.setter
    def author(self, author):
        book_validator.validate_author(author)
        self.__author = author

    @property
    def copies(self):
        return self.__copies

    @copies.setter
    def copies(self, copies):
        book_validator.validate_copies(copies)
        self.__copies = copies

    @property
    def borrowers(self):
        return len(self.__borrowed)

    def add_borrowed(self, event_id):
        self.__borrowed.add(event_id)
        self.copies -= 1

    def remove_borrowed(self, event_id):
        self.__borrowed.remove(event_id)
        self.copies += 1

    def __eq__(self, other):
        return (
            self.id == other.id
            and self.title == other.title
            and self.desc == other.desc
            and self.author == other.author
            and self.copies == other.copies
            and self.__borrowed == other.__borrowed
        )

    def __str__(self):
        s = ""
        s += f"ID : {colored(str(self.id),'blue')}, "
        s += f"Title : {colored(self.title,'blue')}, "
        s += f"Description : {colored(self.desc,'blue')}, "
        s += f"Author : {colored(self.author,'blue')}, "
        s += f"Copies : {colored(str(self.copies),'blue')}"
        return s
