from repo.repo import *
from service.utils import *


class Service:
    def __init__(self, repo: Repo):
        """Init service

        Args:
            repo (Repo): file repo
        """
        self.__repo = repo

    def add_tractor(self, id, name, price, model, expire):
        """Add tractor

        Args:
            id (int): id
            name (string): name
            price (int): price
            model (string): model
            expire (string): expiration date for revision
        """
        self.__repo.add_tractor(Tractor(id, name, price, model, expire))

    def remove_tractor(self, digit):
        """Remove tractors whose price contains the digit "digit"

        Args:
            digit (int, >=0, <10): given digit

        Returns number of tractors deleted
        """
        tractors = self.__repo.get_all()
        nr = 0
        deleted = []
        for tractor in tractors:
            if Utils.containts_digit(tractor.price, digit):
                deleted.append(tractor)
        self.__repo.remove_tractor(deleted)
        return len(deleted)

    def set_filter(self, name, nr):
        """Set current filter

        Args:
            name (str): _description_
            nr (int): _description_
        """
        self.__repo.set_filter(name, nr)

    def get_filter(self):
        """Returns curent filter
        Return type: (str, int) tuple corresponding to the text and number filter
        """
        return self.__repo.get_filter()

    def get_filtered(self) -> list[Tractor]:
        """Returns filtered list of tractors

        Returns:
            list[Tractor]: _description_
        """
        return self.__repo.get_filtered()

    def undo(self):
        """Undoes last add/remove operation
        """
        self.__repo.undo()
