from logic.scores import *
from logic.history import *
from logic.participants import *


def validate_participant(lst, nr):
    """
    Throws a ValueError exception if the participant is invalid

    `nr`:
    * participant number
    """
    if nr < 0 or nr > get_current_length(lst):
        raise ValueError


def get_current_scores(lst, task=0):
    """
    Returns a list of integers with the current scores of all participants in a selected task

    `lst`:
    * a list containing lists with 11 items containing the scores from all versions

    `task`:
    * a number representing what scores to consider
    * `0 <= task <= 10`
    * `0` = sum of scores from all tasks, otherwise scores from task `i`
    """
    return [
        participant.get_score(task)
        for participant in get_all_participants(get_current_version(lst))
    ]


def get_current_participant(lst, nr):
    """
    Returns a list of integers with the all the scores of a participant

    `lst`:
    * a list containing lists with 11 items containing the scores from all versions

    `nr`:
    * an int representing the number of the participant
    """
    return get_participant(get_current_version(lst), nr).get_scores()


def get_current_length(lst):
    """
    Returns the current number of participants

    `lst`:
    * a list containing lists with 11 items containing the scores from all versions
    """
    return get_number_participants(get_current_version(lst))


def get_ordered_participants(lst, mode, task, score=None):
    """
    Returns a list of integers with the participants in a selected task ordered by score and a mode
    `mode`:
    * `mode = 1, 2, 3` depending on the mode
    1 = score order
    2 = participant order, scores smaller than `score`
    3 = score order, scores bigger than `score`

    `lst`:
    * the list containing lists with scores from all versions

    `task`:
    * an int representing the number of the task

    `score`:
    * an int representing the score
    """
    n = get_current_length(lst)
    nlst = get_current_scores(lst, task)
    plst = [i + 1 for i in range(n)]

    if mode == 2 or mode == 3:

        def criteria(x):
            if mode == 2:
                return nlst[x - 1] < score
            else:
                return nlst[x - 1] > score

        plst = list(filter(criteria, plst))
    if mode == 1 or mode == 3:

        def criteria(x):
            return nlst[x - 1]

        plst.sort(key=criteria)
    return plst


def get_filtered_participants(lst, mode, task, score=None):
    """
    Returns a list of integers with the participants in a selected task whose score don't respect a criteria
    * `mode = 1, 2` depending on the mode
    1 = filter out scores multiples of
    2 = filter out scores smaller than

    `lst`:
    * the list containing lists with scores from all versions

    `task`:
    * an int representing the number of the task

    `score`:
    * an int representing the score
    """

    n = get_current_length(lst)
    nlst = get_current_scores(lst, task)
    plst = [i + 1 for i in range(n)]

    def criteria(x):
        if mode == 1:
            return not (nlst[x - 1] % score == 0)
        else:
            return not (nlst[x - 1] < score)

    plst = list(filter(criteria, plst))
    return plst


def get_operation(lst, mode, task, left, right):
    """
    Returns the result of an operation applied on an interval
    `lst`:
    * the list containing lists with scores from all versions

    `mode`:
    * `mode = 1, 2, 3` depending on the mode
    1 = print average
    2 = print minimum
    3 = print participants with score a multiple of 10

    `task`:
    * an int representing the number of the task

    `left`:
    * an int representing the left endpoint of the interval of participants

    `right`:
    * an int representing the right endpoint of the interval of participants
    """
    nlst = get_current_scores(lst, task)
    nlst = nlst[left - 1 : right]
    if mode == 1:
        return sum(nlst) / len(nlst)
    elif mode == 2:
        return min(nlst)
    else:
        plst = [i for i in range(left, right + 1)]
        return list(filter(lambda x: nlst[x - left] % 10 == 0, plst))
