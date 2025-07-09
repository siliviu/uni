from ui.util import *
from logic.util_set import *


def add_score(mode, lst):
    """
    Handles inputting the score and adds it
    `mode`:
    * mode = 0 or 1 depending on whether you add a new participant or an existing one

    `lst`:
    * list containing the scores
    """
    nr = 0
    if mode == 1:
        if bail(lst):
            return
        nr = input_participant(lst)
        task = input_task(False)
        score = input_score()
        try:
            change_score(lst, nr, task, score, False)
        except:
            print(
                colored(
                    "Error! The participant already has a score for that task", "red"
                )
            )
            return
    else:
        task = input_task(False)
        score = input_score()
        push_score(lst, task, score)
        nr = get_current_length(lst)
    print(colored("Addition successful!\n", "green"))
    print(f"Participant {nr} now has: ")
    print_participant_scores(get_current_participant(lst, nr))


def add_menu(lst):
    """Handles the menu for adding a score"""
    create_menu(
        "Choose the type of score addition:",
        [
            ("Add score of a new participant", lambda lst: add_score(0, lst)),
            ("Add score for an existing participant", lambda lst: add_score(1, lst)),
        ],
        "Go back\n",
        "Bad option. Please try again\n",
        lst,
    )
