def get_current_version(lst):
    """
    Returns the current version of the history

    `lst`:
    * the list containting all versions
    """
    return lst[-1]

def add_new_version(lst, p):
    """
    Adds a new version to the history

    `lst`:
    * the list containting all versions
    """
    lst.append(p)

def pop_version(lst):
    """
    Undoes the last modification to the history

    `lst`:
    * the list containting all versions
    """
    if len(lst) <= 1:
        raise ValueError
    lst.pop()
