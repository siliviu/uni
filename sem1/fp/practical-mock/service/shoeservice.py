from repo.repo import *


class ShoeService:
    def __init__(self, repo: Repo):
        """Initialise shoe service

        Args:
            repo (Repo): Shoe Repo
        """
        self.__repo = repo

    def show_shoes(self, _name: str):
        """Show shoes with given name and following criteria

        Args:
            _name (str): shoe name

        Returns:
            list[shoe]: list of shoes as a result
        """
        s = self.__repo.get_shoes(lambda s: s.name == _name and s.pers)
        s.sort(key=lambda s: s.size)
        return s

    def get_shoe_size(self, _id: int):
        """Get shoes with same size as id and available

        Args:
            size (id): size to search
        """
        _size = self.__repo.get_shoes(lambda s: s.id == _id)[0].size
        return [x for x in self.__repo.get_shoes(lambda s:s.size == _size and s.number > 0)]

    def order(self, _id: int):
        """Order a pair of shoes. 

        Args:
            _id (int): if of the shoe to order

        Raises:
            ValueError: If shoe doesn't exist or no pair is left
        """
        s = self.__repo.get_shoes(lambda s: s.id == _id)
        if len(s) == 0:
            raise ValueError("Perechea de pantofi cu id-ul <"+str(_id)+"> nu exista")
        shoe = s[0]
        if shoe.number == 0:
            raise AssertionError("Ne pare rau. Nu mai avem acea pereche de pantofi")
        shoe.number -= 1
        self.__repo.modify_shoe(shoe.id, shoe)
        return shoe

    def get_all(self):
        """Get all shoes

        Returns:
            list[shoe]: list of all shoes
        """
        return [x for x in self.__repo.get_shoes()]
