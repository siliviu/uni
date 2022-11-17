# 4 from https://www.cs.ubbcluj.ro/~istvanc/fp/lab/Lab7-9.pdf


from repo.memory_repository import *
from ui.menu_console import *
from service.book_controller import *
from service.client_controller import *


def initiate_test_data(self):
    """
    Test helper function
    * self - Data
    """


if __name__ == "__main__":
    book_data = MemoryRepo()
    book_data.add(book(1, "Ana are mere", "Ana si mere", "Anuta Anisoara", 3))
    book_data.add(book(2, "Ana are mere 2", "Ana si mai multe mere", "Anuta Anisoara", 1))
    book_data.add(book(3, "Ana", "Doar ana", "Anica Anuta", 10))
    
    client_data = MemoryRepo()
    client_data.add(client(1, "Gigel", 128))
    client_data.add(client(2, "Gigelescu", 49))
    
    event_data = MemoryRepo()

    book_controller = BookController(book_data)
    client_controller = ClientController(client_data)
    event_controller = EventController(event_data, book_controller, client_controller)
    console = MenuConsole(book_controller, client_controller, event_controller)
    console.run()
