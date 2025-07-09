from ui.util import *
from logic.util_set import *


def undo_menu(lst):
    """
    Handles the undo action
    `lst`:
    * the list containing lists with scores from all versions
    """
    try:
        undo(lst)
        print(colored("Undo successful", "green"))
    except:
        print(colored("No more actions left to undo", "red"))