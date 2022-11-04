def get_current(lst):
    return lst[-1]

def add_new(lst, p):
    lst.append(p)

def undo(lst):
    """
    Undoes the last modification to the score list

    `lst`:
    * the list containing lists with scores from all versions
    """
    if len(lst) <= 1:
        raise ValueError
    lst.pop()
