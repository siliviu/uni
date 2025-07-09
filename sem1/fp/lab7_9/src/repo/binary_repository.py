from repo.memory_repository import *
import pickle
import os.path


class BinaryRepo(Repo):
    def __init__(self, file):
        self.__file = os.path.dirname(__file__)+"\\bin_"+file
        super().__init__()

    def load(self):
        if not os.path.exists(self.__file):
            self.save()
        with open(self.__file, 'rb') as f:
            self._objects = pickle.load(f)

    def save(self):
        with open(self.__file, 'wb') as f:
            pickle.dump(self._objects, f)
