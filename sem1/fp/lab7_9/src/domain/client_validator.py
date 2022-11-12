from domain.exceptions import *


class client_validator:
    @staticmethod
    def validate_id(id):
        if type(id)!=int or id < 0:
            raise ConstraintException("ID must be a natural number")

    @staticmethod
    def validate_name(name):
        if type(name)!=str or len(name.strip()) == 0:
            raise ConstraintException("Name must have at least a character")

    @staticmethod
    def validate_uid(uid):
        if type(uid)!= int or uid <= 0:
            raise ConstraintException("UID must be a positive number")
