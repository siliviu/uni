from domain.exceptions import *


class client_validator:
    @staticmethod
    def validate_id(id):
        """
        Raises ConstraintException if id isn't a natural number >= 0
        * id : int, client id
        """
        if type(id) != int or id < 0:
            raise ConstraintException("ID must be a natural number")

    @staticmethod
    def validate_name(name):
        """
        Raises ConstraintException if name is empty or only has white space characters
        * name : string, client name
        """
        if type(name) != str or len(name.strip()) == 0:
            raise ConstraintException("Name must have at least a character")

    @staticmethod
    def validate_uid(uid):
        """
        Raises ConstraintException if uid isn't a natural number >= 1
        * uid : int, client uid
        """
        if type(uid) != int or uid <= 0:
            raise ConstraintException("UID must be a positive number")
