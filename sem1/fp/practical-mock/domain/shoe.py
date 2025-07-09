class Shoe:
    def __init__(self, _id: int, _name: str, _size: int, _number: int, _price: int, _pers: bool):
        """Shoe constructor

        Args:
            _id (int): _description_
            _name (str): _description_
            _size (int): _description_
            _number (int): _description_
            _price (int): _description_
            _pers (bool): _description_
        """
        self.id = _id
        self.name = _name
        self.size = _size
        self.number = _number
        self.price = _price
        self.pers = _pers

    @property
    def id(self):
        return self.__id

    @id.setter
    def id(self, id):
        self.__id = id

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, name):
        self.__name = name

    @property
    def size(self):
        return self.__size

    @size.setter
    def size(self, size):
        self.__size = size

    @property
    def number(self):
        return self.__number

    @number.setter
    def number(self, number):
        self.__number = number

    @property
    def price(self):
        return self.__price

    @price.setter
    def price(self, price):
        self.__price = price

    @property
    def pers(self):
        return self.__pers

    @pers.setter
    def pers(self, pers):
        self.__pers = pers

    def __str__(self):
        """Converts shoe to string"""
        return ' '.join(
            [str(self.id),
             str(self.name),
             str(self.size),
             str(self.number),
             str(self.price),
             str(self.pers)])

    def __repr__(self):
        """Serialises object"""
        return ','.join(
            [str(self.id),
             str(self.name),
             str(self.size),
             str(self.number),
             str(self.price),
             str(self.pers)])
