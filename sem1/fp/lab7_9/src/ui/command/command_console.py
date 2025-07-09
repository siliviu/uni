from ui.util_menu import *
from service.book_controller import *
from service.client_controller import *
from service.event_controller import *
from service.random_controller import *
from service.statistics_controller import *


class CommandConsole:
    def __init__(
            self, book_ctrl: BookController, client_ctrl: ClientController, event_ctrl: EventController,
            rand_ctrl: RandomController, stats_ctrl: StatisticsController):
        self.__book_ctrl = book_ctrl
        self.__client_ctrl = client_ctrl
        self.__event_ctrl = event_ctrl
        self.__rand_ctrl = rand_ctrl
        self.__stats_ctrl = stats_ctrl

    @staticmethod
    def print_help():
        print("""Available commands:
* book list | add <id> <title> <desc> <author> <copies> | delete <id> | edit <id> <title|desc|author|copies> <value> | search <id|title|author> <value> | populate <nr>
* client list | add <id> <name> <uid> | delete <id> | edit <id> <name|uid> <value> | search <id|name|uid> <value> | populate <nr>
* borrow <client_id> <book_id>
* return <evend_id>
* reports <1|2|3|4|5>
* exit
        """)

    def run(self):
        print("Welcome to the library app!\n")
        self.print_help()
        while True:
            command = input()
            splits = command.strip().split(' ')
            name = splits[0].strip().lower()
            args = splits[1:]

            try:
                nargs = []
                for arg in args:
                    arg = arg.strip()
                    if arg != "":
                        nargs.append(arg)
                args = nargs
                cur = ""
                nargs = []
                for arg in args:
                    if '\"' in arg:
                        if cur == "":
                            if arg.endswith('\"'):
                                nargs.append(arg[1:-1])
                            else:
                                cur += arg[1:] + ' '
                        else:
                            cur += arg
                            nargs.append(cur[:-1])
                            cur = ""
                    else:
                        if cur == "":
                            nargs.append(arg)
                        elif len(arg) > 0:
                            cur += arg + ' '
                args = nargs

            except:
                print("Command could not be parsed")

            try:
                if name == 'book':
                    if len(args) == 0:
                        raise CommandException
                    if args[0].lower() in ('print', 'list'):
                        if len(args) != 1:
                            raise CommandException
                        print("The books in the collection are: \n")
                        for b in self.__book_ctrl.get_book_list():
                            print(b)
                        print()
                    elif args[0].lower() == 'add':
                        if len(args) != 6:
                            raise CommandException
                        self.__book_ctrl.add_book(int(args[1]), args[2], args[3], args[4], int(args[5]))
                        print(colored("The book has been successfully added: ", "green"))
                        print(self.__book_ctrl.get_book(int(args[1])))
                    elif args[0].lower() in ('delete', 'remove'):
                        if len(args) != 2:
                            raise CommandException
                        self.__book_ctrl.remove_book(int(args[1]))
                        print(colored("The book has been successfully removed", "green"))
                    elif args[0].lower() in ('edit', 'modify'):
                        if len(args) != 4:
                            raise CommandException
                        options = {'title': book.title, 'desc': book.desc, 'author': book.author, 'copies': book.copies}
                        if args[2].lower() not in options:
                            raise CommandException
                        self.__book_ctrl.modify_book(
                            int(args[1]),
                            options[args[2].lower()],
                            args[3] if args[2].lower() in ('title', 'copies') else int(args[3]))
                        print(colored("The book has been successfully modified: ", "green"))
                        print(self.__book_ctrl.get_book(int(args[1])))
                    elif args[0].lower() == 'search':
                        if len(args) != 3:
                            CommandException
                        options = {'id': 0, 'title': 1, 'author': 2}
                        if args[1] not in options:
                            raise CommandException
                        Menu.print_results(
                            self.__book_ctrl.get_books_criteria(
                                options[args[1]],
                                int(args[2]) if args[1] == 'id' else args[2]))
                    elif args[0].lower() in 'populate':
                        if len(args) != 2:
                            raise CommandException
                        self.__rand_ctrl.generate_random_books(int(args[1]))
                    else:
                        raise CommandException
                elif name == 'client':
                    if len(args) == 0:
                        raise CommandException
                    if args[0].lower() in ('print', 'list'):
                        if len(args) != 1:
                            raise CommandException
                        print("The clients in the list are: \n")
                        for b in self.__client_ctrl.get_client_list():
                            print(b)
                        print()
                    elif args[0].lower() == 'add':
                        if len(args) != 4:
                            raise CommandException
                        self.__client_ctrl.add_client(int(args[1]), args[2], int(args[3]))
                        print(colored("The clients has been successfully added: \n", 'green'))
                        print(self.__client_ctrl.get_client(int(args[1])))
                    elif args[0].lower() in ('delete', 'remove'):
                        if len(args) != 2:
                            raise CommandException
                        self.__client_ctrl.remove_client(int(args[1]))
                        print(colored("The clients has been successfully removed\n", 'green'))
                    elif args[0].lower() in ('edit', 'modify'):
                        if len(args) != 4:
                            raise CommandException
                        options = {'name': client.name, 'uid': client.uid}
                        if args[2].lower() not in options:
                            raise CommandException
                        self.__client_ctrl.modify_client(
                            int(args[1]),
                            options[args[2].lower()],
                            args[3] if args[2].lower() == 'name' else int(args[3]))
                        print(colored("The clients has been successfully modified: \n", 'green'))
                        print(self.__client_ctrl.get_client(int(args[1])))
                    elif args[0].lower() == 'search':
                        if len(args) != 3:
                            raise
                        options = {'id': 0, 'name': 1, 'uid': 2}
                        if args[1] not in options:
                            raise CommandException
                        Menu.print_results(
                            self.__client_ctrl.get_clients_criteria(
                                options[args[1]],
                                int(args[2]) if args[1] in ('id', 'uid') else args[2]))
                    elif args[0].lower() in 'populate':
                        if len(args) != 2:
                            raise CommandException
                        self.__rand_ctrl.generate_random_clients(int(args[1]))
                    else:
                        raise CommandException
                elif name == 'borrow':
                    if len(args) != 2:
                        raise CommandException
                    event_id = self.__event_ctrl.borrow_book(int(args[0]), int(args[1]))
                    print(colored("\nThe book has been successfully borrowed", "green"))
                    print(f"Event ID: {colored(str(event_id),'blue')}")
                elif name == 'return':
                    if len(args) != 1:
                        raise CommandException
                    self.__event_ctrl.return_book(int(args[0]))
                    print(colored("\nThe book has been successfully returned", "green"))
                elif name == 'reports':
                    if len(args) != 1 and len(args) != 2:
                        raise CommandException
                    if args[0] not in ('1', '2', '3', '4', '5'):
                        raise CommandException
                    Menu.print_results(
                        self.__stats_ctrl.get_most_borrowed() if args[0] == '1'
                        else self.__stats_ctrl.get_borrowers(0, len(args) == 2) if args[0] == '2'
                        else self.__stats_ctrl.get_borrowers(1, len(args) == 2) if args[0] == '3'
                        else self.__stats_ctrl.get_20th_percentile_clients() if args[0] == '4'
                        else self.__stats_ctrl.get_20th_percentile_books()  # lab 9
                    )
                elif name == 'exit':
                    print("You have closed the app. Goodbye!\n")
                    return
                else:
                    raise CommandException
            except (ValueError, CommandException):
                Menu.bad_input()
                self.print_help()
            except Exception as e:
                print(colored(e, "red"))
            finally:
                print()
