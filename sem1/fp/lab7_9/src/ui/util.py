from termcolor import colored
from domain.book import *


def bad_input():
    print(colored("Bad input", "red"))


def create_menu(text, options, exit, bad_input, *args, persistent=True):
    """
    Helper function to create a console user menu with `len(options)+1` options, indexed from `1`. Last option is for quitting the menu.

    `text`:
    * string for the beginning of the menu

    `options` :
    * list of tuples `(message, fnc)` for each interaction
    * `message` : string corresponding to the message for an option
    * `fnc` : function called if the option is chosen
    * the `i` th element corresponds to the `i+1` th number inputted by the user`

    `exit`:
    * string for the exit message

    `bad_input`:
    * string to display if the input is wrong

    `args`:
    * all other arguments to be passed on
    """
    command = ""
    nr = len(options)
    while command != str(nr + 1):
        print(text)
        print("Press one of the following keys:\n")
        for x in range(1, nr + 1):
            print(str(x) + ". " + options[x - 1][0])
        print(str(nr + 1) + ". " + exit + "\n")
        command = input()
        ok = False
        for x in range(1, nr + 1):
            if command == str(x):
                options[x - 1][1](*args)
                ok = True
                break
        if ok == False and command != str(nr + 1):
            print(colored(bad_input, "red"))
        if not persistent:
            return
