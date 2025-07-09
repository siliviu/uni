from domain.exceptions import *

class Repo:
    def __init__(self):
        """
        Initialise memory repo
        * self - Repo
        """
        self._objects = {}
        self.load()

    def load(self):
        """Loads data (if not stored in memory)"""
        pass

    def save(self):
        """Loads data (if not stored in memory)"""
        pass

    def get_list(self):
        """
        Returns a list of all objects
        * self - Repo
        Best case = Worst case = Average case 
        T(n) ~ n -> θ(n), where n = number of objects in repo  
        """
        return [obj for obj in self._objects.values()]

    def get_length(self):
        """
        Returns an int representing the number of objects stored
        * self - Repo
        """
        return len(self._objects)

    def get(self, obj_id: int):
        """
        Returns the object with the corresponding id.
        Raises OperationException if object doesn't exit
        * self - Repo
        * obj_id - int(>=0) - id of the obj
        """
        if not (obj_id in self._objects):
            raise OperationException("Object doesn't exist in collection")
        return self._objects[obj_id]

    def set(self, obj_id: int, obj):
        """
        Sets the existing object with obj_id to a new object
        Raises OperationException if object doesn't exit
        * self - Repo
        * obj_id - int (>=0) - id of the obj to modify
        * obj - modified version of obj
        """
        if not (obj_id in self._objects):
            raise OperationException("Object doesn't exist in collection")
        self._objects[obj_id] = obj
        self.save()

    def add(self, obj):
        """
        Adds an object to the list
        Raises OperationException if the object already exists
        * self - Repo
        * obj - Object to add
        """
        if obj.id in self._objects:
            raise OperationException("Object already exists in collection")
        self._objects[obj.id] = obj
        self.save()

    def remove(self, obj_id: int):
        """
        Removes object with id obj_id from the list
        Raises OperationException if the object doesn't exist
        * self - Repo
        * obj_id - int (>=0) - Id of the object to remove
        """
        if not (obj_id in self._objects):
            raise OperationException("Object doesn't exist in collection")
        del self._objects[obj_id]
        self.save()

