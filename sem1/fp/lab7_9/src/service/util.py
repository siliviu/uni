import string
import random

class Utils():
    @staticmethod
    def norm(s: str) -> str:
        """Returns a string capitalised and stripped, normalising it for comparison"""
        return s.upper().strip()

    @staticmethod
    def rand_string(l: int) -> str:
        """Returns a string of length l"""
        letters = string.ascii_lowercase
        return ''.join(random.choice(letters) for i in range(l))