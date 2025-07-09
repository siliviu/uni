from ui.util import *
from logic.util_get import *



def print_menu(lst):
    """Handles the menu for printing a score"""
    create_menu(
        "Choose what to print",
        [
            (
                "Print all current scores in the order of participants",
                lambda lst: print_all(lst),
            ),
            (
                "Print all participants in order of score",
                lambda lst: print_participants(1, lst),
            ),
            (
                "Print all participants with scores smaller than",
                lambda lst: print_participants(2, lst),
            ),
            (
                "Print all participants with scores bigger than in order of score",
                lambda lst: print_participants(3, lst),
            ),
        ],
        "Go back\n",
        "Bad option. Please try again\n",
        lst,
    )


def print_all(lst):
    """
    Prints all current scores for all participants
    """
    for i in range(1, get_current_length(lst) + 1):
        print(f"Participant {i} has: ")
        print_participant_scores(get_current_participant(lst, i))
    print()


def print_participants(mode, lst):
    """Handles the input and output for printing ordered score
    `mode`:
    * `mode = 1, 2, 3` depending on the mode
    1 = score order
    2 = participant order, scores smaller than `score`
    3 = score order, scores bigger than `score`

    `lst`:
    * list containing the scores
    """
    task = input_task()
    score = None
    if mode in [2, 3]:
        score = input_score(task == 0)
    nlst = get_ordered_participants(lst, mode, task, score)
    print_list(nlst)
