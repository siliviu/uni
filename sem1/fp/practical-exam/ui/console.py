from service.service import *


class Console:
    def __init__(self, service: Service):
        """Init console

        Args:
            service (Service): linked service
        """
        self.__service = service

    def print_filtered(self):
        """Prints list of filtered tractors
        """
        print(f"\nList of tractors following filter criteria ({self.__service.get_filter()}):\n")
        for x in self.__service.get_filtered():
            if Utils.has_expired(x.expire):
                print("*", end="")
            print(x)
        print()

    def run(self):
        """Running the console itself
        """
        print("""
Welcome to the tractor app
Commands available:
add - add tractor
remove - remove tractor whose price containts digit
filter - filter tractors by price and number
undo - undo last add/remove operation
exit - exit the app
        """)
        self.print_filtered()
        while True:
            command = input().strip()
            if command == "add":
                id = int(input("Enter id: "))
                name = input("Enter name: ")
                price = int(input("Enter price: "))
                model = input("Enter model: ")
                expire = input("Enter expiration date (day:month:year): ")
                self.__service.add_tractor(id, name, price, model, expire)
                self.print_filtered()
            elif command == "remove":
                digit = int(input("Enter price: "))
                print(f"{self.__service.remove_tractor(digit)} tractors have been removed")
                self.print_filtered()
            elif command == "filter":
                text = input("Enter text filter (nothing if none): ")
                nr = int(input("Enter number (-1 if ignored): "))
                self.__service.set_filter(text, nr)
                print("Current filter is ", self.__service.get_filter())
                self.print_filtered()
            elif command == "undo":
                self.__service.undo()
                self.print_filtered()
            elif command == "exit":
                return
            else:
                print("Wrong command. try again")
