from domain.tractor import *


class Repo:
    def __init__(self, name):
        """Init file repo

        Args:
            name (string): file name
        """
        self.__name = name
        self.__namefilter = ""
        self.__nrfilter = -1
        self.__lastundotype = ""
        self.__lastundoobjects = []
        self.__objects = {}
        self.read()

    def save(self):
        """Save to file
        """
        with open(self.__name, "w") as f:
            for tractor in self.__objects.values():
                f.write(repr(tractor)+"\n")

    def read(self):
        """Read from file
        """
        with open(self.__name, "r") as f:
            for line in f:
                splits = line.strip().split('|')
                id = int(splits[0].strip())
                name = splits[1].strip()
                price = int(splits[2].strip())
                model = splits[3].strip()
                date = splits[4].strip()
                self.add_tractor(Tractor(id, name, price, model, date))

    def set_filter(self, name, nr):
        """Set current filter

        Args:
            name (str): _description_
            nr (int): _description_
        """
        self.__namefilter = name
        self.__nrfilter = nr

    def get_filter(self):
        """Returns curent filter
        Return type: (str, int) tuple corresponding to the text and number filter
        """
        return (self.__namefilter, self.__nrfilter)

    def add_tractor(self, tractor: Tractor):
        """Add tractor to repo
        tractor - Tractor - tractor to add
        """
        self.__objects[tractor.id] = tractor
        self.__lastundotype = 'A'
        self.__lastundoobjects = [tractor]
        self.save()

    def remove_tractor(self, tractors):
        """Remove list of tractors

        Args:
            tractors (list[Tractor]) - tractors to remove
        """
        self.__lastundotype = 'R'
        self.__lastundoobjects = tractors
        for tractor in tractors:
            del self.__objects[tractor.id]
        self.save()

    def get_all(self) -> list[Tractor]:
        """Gets all tractors

        Returns:
            list[Tractor]: all tractors
        """
        return [x for x in self.__objects.values()]

    def get_filtered(self) -> list[Tractor]:
        """Gets all tractors meeting the filter

        Returns:
            list[Tractor]: list of tractors filtered
        """
        return [x for x in self.__objects.values() if (self.__namefilter == '' or self.__namefilter in x.name)
                and (self.__nrfilter == -1 or x.price < self.__nrfilter)]

    def undo(self):
        """Undoes last add/remove operation"""
        if self.__lastundotype == 'A':
            self.remove_tractor(self.__lastundoobjects)
            return
        if self.__lastundotype == 'R':
            for tractor in self.__lastundoobjects:
                self.add_tractor(tractor)
            return
