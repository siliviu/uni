from datetime import *


class Utils:
    @staticmethod
    def containts_digit(nr, digit):
        """Helper function to check if number cointains digit

        Args:
            nr (int): _description_
            digit (int): _description_

        Returns:
            bool: True or false
        """
        while nr > 0:
            if nr % 10 == digit:
                return True
            nr //= 10
        return False

    @staticmethod
    def has_expired(date):
        """Check if date is past today

        Args:
            date (date): date to check

        Returns:
            bool: True or False
        """
        return date < datetime.today().date()
