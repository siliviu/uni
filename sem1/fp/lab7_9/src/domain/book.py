from termcolor import colored
from domain.book_validator import *


class book:
    def __init__(self, id, title, desc, author, copies):
        """
        Initialise book object. Raises ConstraintException if params are invalid
        self - book
        * id - int (>= 0)
        * title, desc, author - string (non empty)
        * copies - int (>= 0)
        """
        self.id = id
        self.title = title
        self.desc = desc
        self.author = author
        self.copies = copies
        self.__borrowed = set()

    @property
    def id(self):
        """
        Returns id (int) of the book
        * self - book
        """
        return self.__id

    @id.setter
    def id(self, id):
        """
        Sets id of the book. Raises ConstraintException if params are invalid
        self - book
        * id - int (>= 0)
        """
        book_validator.validate_id(id)
        self.__id = id

    @property
    def title(self):
        """
        Returns title (string) of the book
        * self - book
        """
        return self.__title

    @title.setter
    def title(self, title):
        """
        Sets title of the book. Raises ConstraintException if params are invalid
        * self - book
        * title - string (not empty)
        """
        book_validator.validate_title(title)
        self.__title = title

    @property
    def desc(self):
        """
        Returns desc (string) of the book
        * self - book
        """
        return self.__desc

    @desc.setter
    def desc(self, desc):
        """
        Sets title of the book. Raises ConstraintException if params are invalid
        * self - book
        * desc - string (not empty)
        """
        book_validator.validate_desc(desc)
        self.__desc = desc

    @property
    def author(self):
        """
        Returns author (string) of the book
        * self - book
        """
        return self.__author

    @author.setter
    def author(self, author):
        """
        Sets title of the book. Raises ConstraintException if params are invalid
        * self - book
        * author - string (not empty)
        """
        book_validator.validate_author(author)
        self.__author = author

    @property
    def copies(self):
        """
        Returns nr of copies (int) of the book
        * self - book
        """
        return self.__copies

    @copies.setter
    def copies(self, copies):
        """
        Sets nr of copies of the book. Raises ConstraintException if params are invalid
        * self - book
        * copies - int (>= 0)
        """
        book_validator.validate_copies(copies)
        self.__copies = copies

    @property
    def borrowers(self):
        """
        Returns an int, the number of borrowers of the book
        * self - book
        """
        return len(self.__borrowed)

    def add_borrowed(self, event_id):
        """
        Adds borrow event to book
        * self - book
        * event_id - int
        """
        self.__borrowed.add(event_id)
        self.copies -= 1

    def remove_borrowed(self, event_id):
        """
        Removes borrow event from book
        * self - book
        * event_id - int
        """
        self.__borrowed.remove(event_id)
        self.copies += 1

    def __eq__(self, other):
        """
        Returns true/false if two books are the same
        * self, other - book
        """
        return self.id == other.id and self.title == other.title and self.desc == other.desc and self.author == other.author and self.copies == other.copies and self.__borrowed == other.__borrowed

    def __str__(self):
        """
        Converts book to string
        self:book
        """
        s = ""
        s += f"ID : {colored(str(self.id),'blue')}, "
        s += f"Title : {colored(self.title,'blue')}, "
        s += f"Description : {colored(self.desc,'blue')}, "
        s += f"Author : {colored(self.author,'blue')}, "
        s += f"Copies : {colored(str(self.copies),'blue')}"
        return s
