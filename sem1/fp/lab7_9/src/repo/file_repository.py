from repo.memory_repository import *
from domain.book import *
import os.path


class FileRepo(Repo):
    def __init__(self, file:str, type):
        """
        Initialise file repo
        * self - Repo
        * file - name of file
        * type - class to be stored; must implement deserialise method
        """
        self.__file = os.path.dirname(__file__)+"\\file_"+file
        self.__type = type
        super().__init__()

    def load(self):
        """Load file"""
        if not os.path.exists(self.__file):
            self.save()
        with open(self.__file, 'r', encoding='utf-8') as f:
            for line in f:
                self.add(self.__type.deserialise(line))

    def save(self):
        """Save file"""
        with open(self.__file, 'w',encoding='utf-8') as f:
            for x in self.get_list():
                f.write(repr(x)+'\n')
