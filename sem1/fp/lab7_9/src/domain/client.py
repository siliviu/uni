class client:
    def __init__(self, id, name, uid):
        self.set_id(id)
        self.set_name(name)
        self.set_uid(uid)
        self.__borrowed = {}

    def get_id(self):
        return self._id

    def set_id(self, id):
        client.validate_id(id)
        self._id = id

    def validate_id(id):
        if id < 0:
            raise TypeError("Id must be a natural number")

    def get_name(self):
        return self._name

    def set_name(self, name):
        client.validate_name(name)
        self._name = name

    def validate_name(title):
        if len(title) == 0:
            raise TypeError("Title must have at least a character")

    def get_uid(self):
        return self._uid

    def set_uid(self, uid):
        self._uid = uid

    def validate_uid(title):
        if len(title) == 0:
            raise TypeError("Title must have at least a character")
    
    def __str__(self):
        s = ""
        s += f"ID : {self.get_id()}, "
        s += f"Name : {self.get_name()}, "
        s += f"UID : {self.get_uid()}"
        return s
