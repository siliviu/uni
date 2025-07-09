from ui.util import *
from logic.util_get import *


def filter_menu(lst):
    """Handles the menu for filtering scores"""
    create_menu(
        "Choose what to filter out",
        [
            ("Filter out scores multiple of", lambda lst: filter_participants(1, lst)),
            ("Filter out scores smaller than", lambda lst: filter_participants(2, lst)),
        ],
        "Go back\n",
        "Bad option. Please try again\n",
        lst,
    )


def filter_participants(mode, lst):
    """
    Handles the input and output for filtering score
    * `mode = 1, 2` depending on the mode
    1 = filter out scores multiples of
    2 = filter out scores smaller than

    `lst`:
    * list containing the scores
    """
    task = input_task()
    score = input_score(task == 0)
    nlst = get_filtered_participants(lst, mode, task, score)
    print_list(nlst)
