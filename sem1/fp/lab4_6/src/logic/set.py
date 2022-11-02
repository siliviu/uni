from logic.scores import *


def push_change(lst, el):
    """
    Adds a new version of the scores list to the list of all versions

    `lst`:
    * the list containing lists with scores from all versions

    `el`
    * current list of scores to be added
    """
    lst.append(el)


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
    el = lst[-1].copy()
    el[nr - 1] = lst[-1][nr - 1].copy()
    prev_score = get_score(el[nr - 1], task)
    if not((prev_score != 0) == change):
        raise ValueError
    set_score(el[nr - 1], 0, score + get_score(el[nr - 1], 0) - prev_score)
    set_score(el[nr - 1], task, score)
    push_change(lst, el)


def change_scores(lst, left, right, task, score, change):
    """
    Changes the score of a interval of participant for a specific task

    `lst`:
    * the list containing lists with scores from all versions

    `left`:
    * an int representing the left endpoint of the interval of participants

    `right`:
    * an int representing the right endpoint of the interval of participants

    `task`:
    * an int representing the number of the task

    `score`:
    * an int representing the score we want to set

    `change`:
    * boolean representing whether we want to add or modify a score
    """
    el = lst[-1].copy()
    for nr in range(left, right + 1):
        el[nr - 1] = lst[-1][nr - 1].copy()
        prev_score = get_score(el[nr - 1], task)
        if not((prev_score != 0) == change):
            raise ValueError
        set_score(el[nr - 1], 0, score + get_score(el[nr - 1], 0) - prev_score)
        set_score(el[nr - 1], task, score)
    push_change(lst, el)


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
    c = get_new_score()
    set_score(c, 0, score)
    set_score(c, task, score)
    el = lst[-1].copy()
    el.append(c)
    push_change(lst, el)


def undo(lst):
    """
    Undoes the last modification to the score list

    `lst`:
    * the list containing lists with scores from all versions
    """
    if len(lst) <= 1:
        raise ValueError
    lst.pop()
