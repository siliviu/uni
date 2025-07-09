from domain.shoe import *
import os.path

class Repo:
    def __init__(self, name):
        """Initialise repo
        Args:
            name (string): File name to read from
        """
        self.__name = os.path.dirname(__file__)+f"\\{name}"
        self.__objects = {}
        self.load()

    def get_shoes(self, cond=lambda Shoe: True):
        """Get shoes from repo

        Args:
            cond (Condition to filter shoes, optional): Function for filtering. Defaults to lambda:True.

        Returns:
            list[Shoe]: List of shoes
        """
        return [shoe for shoe in self.__objects.values() if cond(shoe)]

    def modify_shoe(self, id: int, shoe: Shoe):
        """Modifies shoe

        Args:
            id (int): id of shoe
            shoe (Shoe): new shoe object
        """
        self.__objects[id] = shoe
        self.save()

    def add_shoe(self, obj: Shoe):
        """Add shoe to memory

        Args:
            obj (Shoe): shoe object
        """
        self.__objects[obj.id] = obj

    def load(self):
        """Load data from file"""
        with open(self.__name, "r") as f:
            for line in f:
                values = line.strip().split(',')
                id = int(values[0].strip())
                name = values[1].strip()
                size = int(values[2].strip())
                number = int(values[3].strip())
                price = int(values[4].strip())
                pers = True if values[5].strip() == 'True' else False
                self.add_shoe(Shoe(id, name, size, number, price, pers))

    def save(self):
        """Saves data to file"""
        with open(self.__name, "w") as f:
            for shoe in self.__objects.values():
                f.write(repr(shoe)+'\n')
