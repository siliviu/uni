from domain.exceptions import *

class MemoryRepo:
    def __init__(self):
        """
        Initialise data object
        * self - Data
        """
        self.__objects = {}

    def get_list(self):
        """
        Returns a list of all objects
        * self - Data
        """
        return [obj for obj in self.__objects.values()]

    def get(self, obj_id: int):
        """
        Returns the object with the corresponding id.
        Raises OperationException if object doesn't exit
        * self - Data
        * obj_id - int(>=0) - id of the obj
        """
        if not (obj_id in self.__objects):
            raise OperationException("Object doesn't exist in collection")
        return self.__objects[obj_id]

    def set(self, obj_id: int, obj):
        """
        Sets the existing object with obj_id to a new object
        Raises OperationException if object doesn't exit
        * self - Data
        * obj_id - int (>=0) - id of the obj to modify
        * obj - modified version of obj
        """
        if not (obj_id in self.__objects):
            raise OperationException("Object doesn't exist in collection")
        self.__objects[obj_id] = obj

    def add(self, obj):
        """
        Adds an object to the list
        Raises OperationException if the object already exists
        * self - Data
        * obj - Object to add
        """
        if obj.id in self.__objects:
            raise OperationException("Object already exists in collection")
        self.__objects[obj.id] = obj

    def remove(self, obj_id: int):
        """
        Removes object with id obj_id from the list
        Raises OperationException if the object doesn't exist
        * self - Data
        * obj_id - int (>=0) - Id of the object to remove
        """
        if not (obj_id in self.__objects):
            raise OperationException("Object doesn't exist in collection")
        del self.__objects[obj_id]

    def get_length(self):
        """
        Returns an int representing the number of objects stored
        * self - Data
        """
        return len(self.__objects)