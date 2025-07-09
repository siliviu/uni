from logic.util_get import *
from logic.util_set import *


def get_test_list():
    """Starting list"""
    history = []
    participants = []
    add_participant(participants, get_score_list([16, 2, 10, 4, 0, 0, 0, 0, 0, 0, 0]))
    add_participant(participants, get_score_list([24, 7, 9, 8, 0, 0, 0, 0, 0, 0, 0]))
    add_participant(participants, get_score_list([19, 5, 6, 0, 0, 0, 0, 0, 8, 0, 0]))
    add_new_version(history, participants)
    return history

def test_util():
    """Test helper"""
    lst = get_test_list()
    assert get_current_length(lst) == 3
    assert get_current_scores(lst, 0) == [16, 24, 19]
    assert get_current_scores(lst, 3) == [4, 8, 0]
    assert get_current_participant(lst, 1) == [16, 2, 10, 4, 0, 0, 0, 0, 0, 0, 0]
    assert get_current_participant(lst, 2) == [24, 7, 9, 8, 0, 0, 0, 0, 0, 0, 0]

    """History"""
    add_new_version(
        lst,
        [
            get_score_list([16, 2, 10, 4, 0, 0, 0, 0, 0, 0, 0]),
            get_score_list([24, 7, 9, 8, 0, 0, 0, 0, 0, 0, 0]),
            get_score_list([19, 5, 6, 0, 0, 0, 0, 0, 8, 0, 0]),
        ],
    )
    assert get_current_version(lst) == [
        get_score_list([16, 2, 10, 4, 0, 0, 0, 0, 0, 0, 0]),
        get_score_list([24, 7, 9, 8, 0, 0, 0, 0, 0, 0, 0]),
        get_score_list([19, 5, 6, 0, 0, 0, 0, 0, 8, 0, 0]),
    ]


def test_get():
    """Test print, filter, operations"""
    lst = get_test_list()
    # print
    assert get_ordered_participants(lst, 1, 0) == [1, 3, 2]
    assert get_ordered_participants(lst, 1, 2) == [3, 2, 1]
    assert get_ordered_participants(lst, 2, 0, 20) == [1, 3]
    assert get_ordered_participants(lst, 2, 1, 10) == [1, 2, 3]
    assert get_ordered_participants(lst, 3, 0, 16) == [3, 2]
    assert get_ordered_participants(lst, 3, 3, 0) == [1, 2]

    # filter
    assert get_filtered_participants(lst, 1, 2, 10) == [2, 3]
    assert get_filtered_participants(lst, 2, 0, 20) == [2]

    # operations
    assert get_operation(lst, 1, 0, 1, 3) == 59 / 3
    assert get_operation(lst, 2, 1, 1, 3) == 2
    assert get_operation(lst, 3, 2, 1, 3) == [1]


def test_add():
    """Test add"""
    lst = get_test_list()
    push_score(lst, 1, 10)
    assert get_current_length(lst) == 4
    assert get_current_participant(lst, 4) == [10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    change_score(lst, 4, 2, 8, False)
    assert get_current_participant(lst, 4) == [18, 10, 8, 0, 0, 0, 0, 0, 0, 0, 0]
    try:
        change_score(lst, 1, 1, 5, False)
        assert False
    except ValueError:
        pass


def test_change():
    """Test change"""
    lst = get_test_list()
    change_score(lst, 1, 1, 6, True)
    assert get_current_participant(lst, 1) == [20, 6, 10, 4, 0, 0, 0, 0, 0, 0, 0]
    try:
        change_score(lst, 1, 10, 5, True)
        assert False
    except ValueError:
        pass
    change_scores(lst, 1, 3, 2, 5, True)
    assert get_current_participant(lst, 1) == [15, 6, 5, 4, 0, 0, 0, 0, 0, 0, 0]
    assert get_current_participant(lst, 2) == [20, 7, 5, 8, 0, 0, 0, 0, 0, 0, 0]
    assert get_current_participant(lst, 3) == [18, 5, 5, 0, 0, 0, 0, 0, 8, 0, 0]
    try:
        change_scores(lst, 1, 3, 10, 5, True)
        assert False
    except ValueError:
        pass


def test_undo():
    """Test undo"""
    lst = get_test_list()
    change_score(lst, 1, 1, 6, True)
    undo(lst)
    assert lst == get_test_list()
    try:
        undo(lst)
        assert False
    except ValueError:
        pass


def test_all():
    """Test all non ui functions"""
    test_util()
    test_get()
    test_add()
    test_change()
    test_undo()
