MIN_SCORE = 1
MAX_SCORE = 10
NR_TASKS = 10


class scores:
    def __init__(self, nr=-1, score=-1):
        """
        Initialise scores object
        """
        'Change the data structure used to represent scores (lab 5)'
        # self.__score = {i: 0 for i in range(0, NR_TASKS + 1)}
        self.__score = [0] * (NR_TASKS + 1)
        if score != -1:
            self.set_score(nr, score)

    def get_score(self, nr):
        """
        Returns score for task `nr`
        """
        return self.__score[nr]

    def set_score(self, nr, score):
        """
        Set score for task `nr` to `score`
        """
        self.__score[0] += score - self.__score[nr]
        self.__score[nr] = score

    def get_scores(self):
        """
        Returns a list of integers with the all the scores
        """
        return [self.get_score(i) for i in range(NR_TASKS + 1)]

    def __eq__(self, other):
        """
        Helper function to test equality
        """
        return self.__score == other.__score

    def copy(self):
        """
        Helper function for shallow copy
        """
        n = scores()
        n.__score = self.__score.copy()
        return n


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


def get_score_list(list):
    """
    Converts list of scores to structure with scores, to initialise data quickly

    `list`:
    * list of all scores
    """
    el = scores()
    for i in range(1, NR_TASKS + 1):
        el.set_score(i, list[i])
    return el
