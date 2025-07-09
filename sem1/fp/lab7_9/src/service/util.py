import string
import random
import math


class Utils():
    @staticmethod
    def norm(s: str) -> str:
        """Returns a string capitalised and stripped, normalising it for comparison"""
        return s.upper().strip()

    @staticmethod
    def rand_string(l: int) -> str:
        """Returns a string of length l"""
        letters = string.ascii_lowercase
        return ''.join(random.choice(letters) for _ in range(l))

    @staticmethod
    def insert_sort(l: list, *, key=None, cmp=None, reverse=False):
        """Sorts list using insertion sort

        Args:
            l (list): list to be sorted
            key (_type_, optional): Key for comparison. Defaults to None.
            reverse (bool, optional): Sort in decreasing order. Defaults to False.
        """
        def smaller(x, y):
            if key != None:
                x = key(x)
                y = key(y)
            if reverse:
                x, y = y, x
            if cmp != None:
                return cmp(x, y) < 0
            return x < y
        for i in range(1, len(l)):
            j = i
            while j > 0 and smaller(l[j], l[j-1]):
                l[j], l[j-1] = l[j-1], l[j]
                j -= 1

    @staticmethod
    def comb_sort(l: list, *, key=None, cmp=None, reverse=False):
        """Sorts list using comb sort

        Args:
            l (list): list to be sorted
            key (_type_, optional): Key for comparison. Defaults to None.
            reverse (bool, optional): Sort in decreasing order. Defaults to False.
        """
        SHRINK_FACTOR = 1.3

        def smaller(x, y):
            if key != None:
                x = key(x)
                y = key(y)
            if reverse:
                x, y = y, x
            if cmp != None:
                return cmp(x, y) < 0
            return x < y
        gap = len(l)
        sorted = False
        while not sorted:
            gap = math.floor(gap/SHRINK_FACTOR)
            if gap <= 1:
                gap = 1
                sorted = True
            for i in range(len(l)-gap):
                if smaller(l[i+gap], l[i]):
                    l[i], l[i+gap] = l[i+gap], l[i]
                    sorted = False
