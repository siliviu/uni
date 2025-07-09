# 2 from https://www.cs.ubbcluj.ro/~istvanc/fp/lab/Lab4-6.pdf

from ui.util import *
from ui.add import *
from ui.print import *
from ui.filter import *
from ui.modify import *
from ui.undo import *
from ui.op import *
from ui.start_menu import *
from tests import *


def main():
    """Main menu of the app"""
    test_all()
    scorelist = get_test_list()
    'test if initial list is empty'
    # scorelist = [[]] 
    print("Welcome to the score management app!\n")
    'run commands from string menu (lab 6)'
    # run_menu(scorelist)
    create_menu(
        "Choose a command to execute",
        [
            ("Add a score for a participant", add_menu),
            ("Modify the score of a participant", modify_menu),
            ("Print a list of participants", print_menu),
            ("Operations on a subset of participants", op_menu),
            ("Filter the list", filter_menu),
            ("Undo", undo_menu),
        ],
        "Exit",
        "Unknown command. Please try again\n",
        scorelist,
    )
    print("You have closed the app. Goodbye!\n")


if __name__ == "__main__":
    main()
