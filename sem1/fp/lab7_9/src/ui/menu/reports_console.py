from ui.util_menu import *
from service.statistics_controller import *


class ReportsConsole:
    def __init__(self, stats_ctrl: StatisticsController):
        self.__stats_ctrl = stats_ctrl
        Menu(
            "Choose the report type:",
            [("Print most borrowed books", lambda: Menu.print_results(self.__stats_ctrl.get_most_borrowed())),
             ("Print clients who borrowed books ordered by name", lambda: Menu.print_results(
                 self.__stats_ctrl.get_borrowers(0))),
             ("Print clients who borrowed books ordered by number of borrowed books", lambda: Menu.print_results(
                 self.__stats_ctrl.get_borrowers(1))),
             ("Print the most active 20% clients ", lambda: Menu.print_results(
                 self.__stats_ctrl.get_20th_percentile_clients())),
             ("Print the most borrowed 20% books ", lambda: Menu.print_results(
                 self.__stats_ctrl.get_20th_percentile_books())), ],
            "Go back\n", "Bad option. Please try again\n",)
