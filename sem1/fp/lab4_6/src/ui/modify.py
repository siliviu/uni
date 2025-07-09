from ui.util import *
from logic.util_set import *


def modify_score(mode, lst):
    """
    Handles the input and output for modifying score
    `mode`:
    * `mode = 1, 2, 3` depending on the mode
    1 = delete score of participant
    2 = delete score of participants in interval
    3 = modify score of participant

    `lst`:
    * list containing the scores
    """
    if bail(lst):
        return
    nr = input_participant(lst)
    nr2 = nr
    if mode == 2:
        nr2 = input_participant(lst)
    if not (nr <= nr2):
        print(colored("Bad input", "red"))
        return
    task = input_task(False)
    score = 0
    if mode == 3:
        score = input_score(False)
    try:
        if mode == 2:
            change_scores(lst, nr, nr2, task, score, True)
        else:
            change_score(lst, nr, task, score, True)
        print(colored("Operation successful!\n", "green"))
        for nr in range(nr, nr2 + 1):
            print(f"Participant {nr} now has: ")
            print_participant_scores(get_current_participant(lst, nr))
    except:
        print(colored("Error! The operation was not successful", "red"))


def modify_menu(lst):
    """Handles the menu for modifying a score"""
    create_menu(
        "Choose the type of score modification:",
        [
            ("Delete score of a participant", lambda lst: modify_score(1, lst)),
            (
                "Delete score of an interval of participants",
                lambda lst: modify_score(2, lst),
            ),
            ("Modify score of a participant", lambda lst: modify_score(3, lst)),
        ],
        "Go back\n",
        "Bad option. Please try again\n",
        lst,
    )
