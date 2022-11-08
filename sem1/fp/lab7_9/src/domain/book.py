class book:
    def __init__(self, id, title, desc, author, copies):
        self.set_id(id)
        self.set_title(title)
        self.set_desc(desc)
        self.set_author(author)
        self.set_copies(copies)
        self._borrowed={}

    def get_id(self):
        return self._id

    def set_id(self, id):
        book.validate_id(id)
        self._id = id

    def validate_id(id):
        if id < 0:
            raise TypeError("Id must be a natural number")

    def get_title(self):
        return self._title

    def set_title(self, title):
        book.validate_title(title)
        self._title = title

    def validate_title(title):
        if len(title) == 0:
            raise TypeError("Title must have at least a character")

    def get_desc(self):
        return self._desc

    def set_desc(self, desc):
        book.validate_desc(desc)
        self._desc = desc

    def validate_desc(desc):
        if len(desc) == 0:
            raise TypeError("Description must have at least a character")

    def get_author(self):
        return self._author

    def set_author(self, author):
        book.validate_author(author)
        self._author = author

    def validate_author(author):
        if len(author) == 0:
            raise TypeError("Author name must have at least a character")
    
    def get_copies(self):
        return self._copies

    def set_copies(self,copies):
        book.validate_copies(copies)
        self._copies=copies

    def validate_copies(copies):
        if copies <= 0:
            raise TypeError("There must be at least a copy in order to add the book")

    def add_borrowed(self, event_id):
        self._borrowed[event_id]

    def __str__(self):
        s = ""
        s += f"ID : {self.get_id()}, "
        s += f"Title : {self.get_title()}, "
        s += f"Description : {self.get_desc()}, "
        s += f"Author : {self.get_author()}, "
        s += f"Copies : {self.get_copies()}"
        return s

