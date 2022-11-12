# 4 from https://www.cs.ubbcluj.ro/~istvanc/fp/lab/Lab7-9.pdf


from repo.data import *
from ui.console import *
from service.book_controller import *
from service.client_controller import *

if __name__ == "__main__":
    data = Data()
    data.initiate_test_data()
    book_controller = BookController(data)
    client_controller = ClientController(data)
    event_controller = EventController(data)
    console = Console(book_controller, client_controller, event_controller)
    console.run()
