class book:
    def __init__(self, id, title, desc, author):
        self.set_id(id)
        self.set_title(title)
        self.set_desc(desc)
        self.set_author(author)

    def get_id(self):
        return self._id

    def set_id(self, id):
        self._id = id

    def validate_id(id):
        if id < 0:
            raise ValueError

    def get_title(self):
        return self._title

    def set_title(self, title):
        self._title = title

    def validate_title(title):
        if len(title) == 0:
            raise ValueError

    def get_desc(self):
        return self._desc

    def set_desc(self, desc):
        self._desc = desc

    def validate_desc(desc):
        if len(desc) == 0:
            raise ValueError

    def get_author(self):
        return self._author

    def set_author(self, author):
        self._author = author

    def validate_author(author):
        if len(author) == 0:
            raise ValueError
