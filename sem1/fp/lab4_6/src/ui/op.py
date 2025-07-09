from ui.util import *
from logic.util_get import *


def do_op(mode, lst):
    """
    Handles the input and output for operations
    `mode`:
    * `mode = 1, 2, 3` depending on the mode
    1 = print average
    2 = print minimum
    3 = print participants with score a multiple of 10

    `lst`:
    * list containing the scores
    """
    if bail(lst):
        return
    nr = input_participant(lst)
    nr2 = input_participant(lst)
    if not (nr <= nr2):
        print(colored("Bad input", "red"))
        return
    task = input_task(False)
    result = get_operation(lst, mode, task, nr, nr2)
    if mode == 3:
        print_list(result)
    else:
        print(result)


def op_menu(lst):
    """Handles the menu for different operations"""
    create_menu(
        "Choose the type of score addition:",
        [
            ("Print average score in an interval", lambda lst: do_op(1, lst)),
            ("Print minimum score in an interval", lambda lst: do_op(2, lst)),
            (
                "Print participants in an interval whose score is a multiple of 10",
                lambda lst: do_op(3, lst),
            ),
        ],
        "Go back\n",
        "Bad option. Please try again\n",
        lst,
    )
    pass
