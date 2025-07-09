from logic.scores import *
from logic.history import *
from logic.participants import *


def change_score(lst, nr, task, score, change):
    """
    Changes the score of a participant for a specific task

    `lst`:
    * the list containing lists with scores from all versions

    `nr`:
    * an int representing the number of the participant

    `task`:
    * an int representing the number of the task

    `score`:
    * an int representing the score we want to set

    `change`:
    * boolean representing whether we want to add or modify a score
    """
    change_scores(lst,nr,nr,task,score,change)

def change_scores(lst, left, right, task, score, change):
    """
    Changes the score of a interval of participant for a specific task

    `lst`:
    * the list containing lists with scores from all versions

    `left`:
    * an int representing the left endpoint of the interval of participants
    * left <= right

    `right`:
    * an int representing the right endpoint of the interval of participants

    `task`:
    * an int representing the number of the task

    `score`:
    * an int representing the score we want to set

    `change`:
    * boolean representing whether we want to add or modify a score
    """
    participants = get_current_version(lst).copy()
    for nr in range(left, right + 1):
        if not ((get_participant(participants, nr).get_score(task) != 0) == change):
            raise ValueError
        scores = get_participant(participants, nr).copy()
        scores.set_score(task, score)
        set_participant(participants, nr, scores)
    add_new_version(lst, participants)


def push_score(lst, task, score):
    """
    Adds a new participant with a score for a given task
    `lst`:
    * the list containing lists with scores from all versions

    `task`:
    * an int representing the number of the task

    `score`:
    * an int representing the score

    """
    participants = get_current_version(lst).copy()
    add_participant(participants, scores(task, score))
    add_new_version(lst, participants)


def undo(lst):
    """
    Undoes the last modification to the score list

    `lst`:
    * the list containing lists with scores from all versions
    """
    pop_version(lst)
