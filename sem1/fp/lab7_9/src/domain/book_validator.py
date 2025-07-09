from domain.exceptions import *


class book_validator:
    @staticmethod
    def validate_id(id):
        """
        Raises ConstraintException if id isn't a natural number >= 0
        * id : int, book id
        """
        if type(id) != int or id < 0:
            raise ConstraintException("Id must be a natural number")

    @staticmethod
    def validate_title(title):
        """
        Raises ConstraintException if title is empty or only has white space characters
        * title : string, book title
        """
        if type(title) != str or len(title.strip()) == 0:
            raise ConstraintException("Title must have at least a character")

    @staticmethod
    def validate_desc(desc):
        """
        Raises ConstraintException if desc is empty or only has white space characters
        * desc : string, book desc
        """
        if type(desc) != str or len(desc.strip()) == 0:
            raise ConstraintException("Description must have at least a character")

    @staticmethod
    def validate_author(author):
        """
        Raises ConstraintException if author is empty or only has white space characters
        * author : string, book author
        """
        if type(author) != str or len(author.strip()) == 0:
            raise ConstraintException("Author name must have at least a character")

    @staticmethod
    def validate_copies(copies):
        """
        Raises ConstraintException if copies isn't a natural number >= 0
        * copies : int, nr of book copies
        """
        if type(copies) != int or copies < 0:
            raise ConstraintException("No copies left to borrow or the number of copies is invalid")
    