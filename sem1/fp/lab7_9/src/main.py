# 4 from https://www.cs.ubbcluj.ro/~istvanc/fp/lab/Lab7-9.pdf


from repo.data import *
from ui.console import *
from service.controller import *

def main():
    data = Data()
    controller = Controller(data)
    console = Console(controller)
    console.run()


if __name__ == "__main__":
    main()