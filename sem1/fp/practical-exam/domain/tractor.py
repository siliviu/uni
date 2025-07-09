from datetime import *


class Tractor:
    def __init__(self, _id, _name, _price, _model, _expire):
        """Init tractor

        Args:
            _id (int): id
            _name (string): name
            _price (int): price
            _model (string): model
            _expire (date): date of expiration
        """
        self.id = _id
        self.name = _name
        self.price = _price
        self.model = _model
        self.expire = _expire

    @property
    def id(self):
        """Init id

        Returns: id(int)
        """
        return self.__id

    @id.setter
    def id(self, id):
        """Set id

        Args:
            id (int):
        """
        self.__id = id

    @property
    def name(self):
        """Get Name

        Returns:
            name(string)
        """
        return self.__name

    @name.setter
    def name(self, name):
        """Set name

        Args:
            name (string)
        """
        self.__name = name

    @property
    def price(self):
        """Get price

        Returns:
            price(int)
        """
        return self.__price

    @price.setter
    def price(self, price):
        """Set price

        Args:
            price (int)
        """
        self.__price = price

    @property
    def model(self):
        """Get model

        Returns:
            model(string)
        """
        return self.__model

    @model.setter
    def model(self, model):
        """Set model

        Args:
            model (string)
        """
        self.__model = model

    @property
    def expire(self):
        """Get expiration date

        Returns:
            expire (date)
        """
        return self.__expire

    @expire.setter
    def expire(self, expire):
        """Set expire

        Args:
            expire (date)
        """
        self.__expire = datetime.strptime(expire, "%d:%m:%Y").date()

    def __repr__(self):
        """Serialise object"""
        return str(self.id)+"|"+self.name+"|"+str(self.price)+"|"+self.model+"|"+str(self.expire.day)+":"+str(self.expire.month)+":"+str(self.expire.year)

    def __str__(self):
        """Format for printing
        """
        return self.name+", "+str(self.price)+", "+self.model+", "+str(self.expire.day)+":"+str(self.expire.month)+":"+str(self.expire.year)+" | Id = "+str(self.id)
