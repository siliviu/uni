class client:
    def __init__(self, id, name, uid):
        self.set_id(id)
        self.set_name(name)
        self.set_uid(uid)

    def get_id(self):
        return self._id

    def set_id(self, id):
        self._id = id

    def get_name(self):
        return self._name

    def set_name(self, name):
        self._name = name

    def get_uid(self):
        return self._uid

    def set_uid(self, uid):
        self._uid = uid
