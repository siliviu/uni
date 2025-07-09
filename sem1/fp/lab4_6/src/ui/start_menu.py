from ui.util import *
from logic.util_set import *


SEPARATOR = ";"


def command_error():
    print(colored("Wrong format for command", "red"))


def run_menu(lst):
    s = input()
    commands = s.split(SEPARATOR)
    for command in commands:
        splits = command.strip().split(" ")
        name = splits[0].upper().strip()
        args = splits[1:]
        for arg in args:
            arg = arg.strip()
        if name == "ADD":
            try:
                assert len(args) == 2
                task = int(args[0])
                validate_task(task, False)
                score = int(args[1])
                validate_score(score, False)
                push_score(lst, task, score)
                nr = get_current_length(lst)
                print(colored("Addition successful!\n", "green"))
                print(f"Participant {nr} now has: ")
                print_participant_scores(get_current_participant(lst, nr))
            except:
                command_error()
        elif name == "DELETE":
            nr, task
            score = 0
            try:
                assert len(args) == 2
                nr = int(args[0])
                validate_participant(lst, nr)
                task = int(args[1])
                validate_task(task, False)
            except:
                command_error()
            try:
                change_score(lst, nr, task, score, True)
                print(colored("Operation successful!\n", "green"))
                print(f"Participant {nr} now has: ")
                print_participant_scores(get_current_participant(lst, nr))
            except:
                print(colored("Error! The operation was not successful", "red"))
        elif name == "PRINT":
            try:
                assert len(args) == 1
                task = int(args[0])
                score = None
                validate_task(task, True)
                nlst = get_ordered_participants(lst, 1, task, score)
                print_list(nlst)
            except:
                command_error()
        elif name == "FILTER":
            try:
                assert len(args) == 2
                task = int(args[0])
                validate_task(task, True)
                score = int(args[1])
                validate_score(score, task == 0)
                nlst = get_filtered_participants(lst, 2, task, score)
                print_list(nlst)
            except:
                command_error()
        else:
            command_error()
        print()
