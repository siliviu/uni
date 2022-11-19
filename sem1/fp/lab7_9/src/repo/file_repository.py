from repo.memory_repository import *
from domain.book import *
import pickle
import os.path


class FileRepo(Repo):
    def __init__(self, file, type):
        self.__file = os.path.dirname(__file__)+"\\file_"+file
        self.__type = type
        super().__init__()

    def load(self):
        if not os.path.exists(self.__file):
            self.save()
        with open(self.__file, 'r') as f:
            for line in f:
                self.add(self.__type.deserialise(line))

    def save(self):
        with open(self.__file, 'w') as f:
            for x in self.get_list():
                f.write(repr(x)+'\n')
