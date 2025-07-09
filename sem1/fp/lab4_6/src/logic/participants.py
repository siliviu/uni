from logic.scores import scores

def get_number_participants(lst):
    """
    Returns number of participants

    `lst`:
    * list of participants
    """
    return len(lst)


def add_participant(lst, scores:scores):
    """
    Add a new participant to the list of participants

    `lst`:
    * list of participants

    `scores:
    * scores object for scores of a participant
    """
    lst.append(scores)


def get_participant(lst, nr):
    """
    Returns the scores object of a participant

    `lst`:
    * list of participants

    `nr:
    * number of participant
    """
    return lst[nr - 1]


def set_participant(lst, nr, scores:scores):
    """
    Sets the scores object of a participant

    `lst`:
    * list of participants

    `nr:
    * number of participant

    `scores:
    * structure object for scores of a participant
    """
    lst[nr - 1] = scores


def get_all_participants(lst):
    """
    Helper function to get a *list* of all participants

    `lst`:
    * list of participants
    """
    return [x for x in lst]
