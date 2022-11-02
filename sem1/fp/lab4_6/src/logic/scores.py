MIN_SCORE = 1
MAX_SCORE = 10
NR_TASKS = 10


def validate_score(score, all):
    """
    Throws a ValueError exception if the score is invalid

    `score`:
    * given score

    `all`:
    * boolean indicating if the sum of scores is considered
    """
    if (
        score < 1
        or (all and score > MAX_SCORE * NR_TASKS)
        or (not all and score > MAX_SCORE)
    ):
        raise ValueError


def validate_task(task, all):
    """
    Throws a ValueError exception if the task is invalid

    `task`:
    * given task number
    """
    if (all and task < 0) or (not all and task <= 0) or task > NR_TASKS:
        raise ValueError


def set_score(el, nr, score):
    """
    Set the score for task nr

    `el`:
    * Structure representing the scores'

    `nr`:
    * Number of task

    `score`:
    * Score to set
    """
    el[nr] = score


def get_new_score():
    """
    Get empty structure of scores
    """
    return {i: 0 for i in range(0, NR_TASKS + 1)}
    # return [0] * (NR_TASKS + 1)


def get_score(el, nr):
    """
    Get the score of participant

    `el`:
    * Structure representing the scores'

    `nr`:
    * Number of task

    """
    return el[nr]

def get_score_list(list):
    """
    Converts list of scores to structure with scores, to initialise data quickly

    `list`:
    * list of all scores
    """
    el = get_new_score()
    for i in range(NR_TASKS + 1):
        set_score(el, i, list[i])
    return el


