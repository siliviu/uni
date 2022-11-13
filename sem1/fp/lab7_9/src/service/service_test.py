import unittest
from service.book_controller import *
from service.client_controller import *
from service.event_controller import *
from service.util import *


class ServiceTestBook(unittest.TestCase):
    pass


class ServiceTestClient(unittest.TestCase):
    pass


class ServiceTestEvent(unittest.TestCase):
    pass


class ServiceTestUtil(unittest.TestCase):
    def test(self):
        self.assertEqual(Utils.norm(" aBCdEFg  h   "), "ABCDEFG  H")
        self.assertEqual(Utils.norm("       "), "")
