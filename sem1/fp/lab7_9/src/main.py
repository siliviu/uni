# 4 from https://www.cs.ubbcluj.ro/~istvanc/fp/lab/Lab7-9.pdf


from repo.data import *
from ui.console import *
from service.book_controller import *
from service.client_controller import *

if __name__ == "__main__":
    data = Data()
    book_controller = BookController(data)
    client_controller = ClientController(data)
    console = Console(book_controller, client_controller)
    console.run()
