from termcolor import colored
from logic.util_get import *


def print_list(lst):
    """
    Prints a list formatted
    lst - given list
    """
    print(
        f"The requested list has length {colored(str(len(lst)), 'blue')} and is: {colored(lst, 'blue')}\n"
    )


def print_participant_scores(lst):
    """
    Prints the scores for a participant
    lst - given list of scores for a participant
    """
    s = "Scores: "
    s += colored(str(lst[1:]), "blue")
    s += ", sum of scores: "
    s += colored(str(lst[0]), "blue")
    print(s)


def input_participant(lst):
    """
    Returns the participant number inputted by user
    lst - given list of scores
    """
    while True:
        try:
            s = "Enter the participant number ("
            s += f"{colored('1', 'blue')} - {colored(str(get_current_length(lst)), 'blue')})\n"
            nr = int(input(s))
            validate_participant(lst, nr)
            return nr
        except:
            print(colored("Invalid input\n", "red"))


def bail(lst):
    """
    Returns True if the list is empty and prints an error, false otherwise
    lst - list of all scores
    """
    if get_current_length(lst) == 0:
        print(colored("Error! The list is empty\n", "red"))
        return True
    return False

def input_task(all=True):
    """
    Returns the task for the scores inputted by user
    `all`:
    * True if the sum of scores is considered, False otherwise

    * `0 <= task <= 10`
    * `0` = sum of scores from all tasks, otherwise scores from task `i`
    """
    while True:
        try:
            s = f"Select the task ({colored('1', 'blue')} - {colored(str(NR_TASKS), 'blue')}) for which you want to interpret the scores"
            if all:
                s += f" or {colored('0', 'blue')} for the sum of scores for all tasks"
            s += "\n"
            nr = int(input(s))
            validate_task(nr, all)
            return nr
        except:
            print(colored("Invalid input\n", "red"))


def input_score(all=False):
    """
    Returns the score for a task inputted by user
    `all`:
    * True if the sum of scores is considered, False otherwise

    * `1 <= score <= 10`
    """
    while True:
        try:
            s = (
                "Enter a score for a task"
                + f" ({colored(str(MIN_SCORE), 'blue')} - {colored(str(NR_TASKS * MAX_SCORE if all else MAX_SCORE ), 'blue')})\n"
            )
            nr = int(input(s))
            validate_score(nr, all)
            return nr
        except:
            print(colored("Invalid input\n", "red"))


def create_menu(text, options, exit, bad_input, lst):
    """
    Helper function to create a console user menu with `len(options)+1` options, indexed from `1`. Last option is for quitting the menu.

    `text`:
    * string for the beginning of the menu

    `options` :
    * list of tuples `(message, fnc)` for each interaction
    * `message` : string corresponding to the message for an option
    * `fnc` : function called if the option is chosen
    * the `i` th element corresponds to the `i+1` th number inputted by the user`

    `exit`:
    * string for the exit message

    `bad_input`:
    * string to display if the input is wrong

    `lst`:
    * list containing the scores
    """
    command = ""
    nr = len(options)
    while command != str(nr + 1):
        print(text)
        print("Press one of the following keys:\n")
        for x in range(1, nr + 1):
            print(str(x) + ". " + options[x - 1][0])
        print(str(nr + 1) + ". " + exit + "\n")
        command = input()
        ok = False
        for x in range(1, nr + 1):
            if command == str(x):
                options[x - 1][1](lst)
                ok = True
                break
        if ok == False and command != str(nr + 1):
            print(colored(bad_input, "red"))
