
from service.shoeservice import *


class Console:
    def __init__(self, srv: ShoeService):
        """Initialise console

        Args:
            srv (ShoeService): Shoe service
        """
        self.__srv = srv

    def run(self):
        print("""Welcome! Available commands are:
        * show <shoe_name> 
        * order <shoe_id> 
        """)
        while True:
            s = input("Enter a command:\n")
            splits = s.strip().split(' ')
            command = splits[0].strip()
            if command == 'show':
                name = ' '.join(splits[1:])
                for x in self.__srv.show_shoes(name):
                    print(x)
            elif command == 'order':
                id = int(splits[1])
                try:
                    print(self.__srv.order(id))
                except ValueError as e:
                    print(e)
                except AssertionError as e:
                    print(e)
                    for x in self.__srv.get_shoe_size(id):
                        print(x)
            elif command == 'list':
                for x in self.__srv.get_all():
                    print(x)
