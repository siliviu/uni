from domain.exceptions import *


class book_validator:
    @staticmethod
    def validate_id(id):
        if type(id) != int or id < 0:
            raise ConstraintException("Id must be a natural number")

    @staticmethod
    def validate_title(title):
        if type(title) != str or len(title.strip()) == 0:
            raise ConstraintException("Title must have at least a character")

    @staticmethod
    def validate_desc(desc):
        if type(desc) != str or len(desc.strip()) == 0:
            raise ConstraintException("Description must have at least a character")

    @staticmethod
    def validate_author(author):
        if type(author) != str or len(author.strip()) == 0:
            raise ConstraintException("Author name must have at least a character")

    @staticmethod
    def validate_copies(copies):
        if type(copies) != int or copies <= 0:
            raise ConstraintException(
                "There must be at least a copy in order to add the book"
            )
