class Utils():
    @staticmethod
    def norm(s: str):
        return s.upper().strip()

    @staticmethod
    def get_books_criteria(db, mode, arg):
        books = db.get_book_list()
        results = []
        if mode == 0:
            results = [db.get_book(arg)]
        elif mode == 1:
            results = [book for book in books if Utils.norm(arg) in Utils.norm(book.get_title())]
        else:
            results = [book for book in books if Utils.norm(arg) in Utils.norm(book.get_author())]
        return results

    @staticmethod
    def get_clients_criteria(db, mode, arg):
        clients = db.get_client_list()
        results = []
        if mode == 0:
            results = [db.get_client(arg)]
        elif mode == 1:
            results = [client for client in clients if Utils.norm(arg) in Utils.norm(client.get_name())]
        else:
            results = [client for client in clients if arg == client.get_uid()]
        return results
