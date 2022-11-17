import unittest
from repo.memory_repository import *
from domain.book import *

class MemoryRepoTest(unittest.TestCase):
    def test_add(self):
        d = MemoryRepo()
        d.add(book(1, "2", "a", "4", 5))
        d.add(book(23, "va", "b", "nanana", 1))
        self.assertEqual(d.get_length(),2)
        self.assertEqual(
            d.get_list(),
            [book(1, "2", "a", "4", 5), book(23, "va", "b", "nanana", 1)],
        )

    def test_setget(self):
        d = MemoryRepo()
        d.add(book(1, "2", "a", "4", 5))
        d.add(book(23, "va", "b", "nanana", 1))
        self.assertEqual(d.get(1), book(1, "2", "a", "4", 5))
        d.set(23, book(24, "b", "wh", "th", 3))
        self.assertEqual(d.get(23), book(24, "b", "wh", "th", 3))

    def test_remove(self):
        d = MemoryRepo()
        d.add(book(1, "2", "a", "4", 5))
        d.add(book(23, "va", "b", "nanana", 1))
        d.remove(23)
        self.assertEqual(d.get_list(), [book(1, "2", "a", "4", 5)])

    def test_exceptions(self):
        d = MemoryRepo()
        d.add(book(1, "2", "a", "4", 5))
        self.assertRaises(OperationException, d.add, book(1, "3", "b", "4", 5))
        self.assertRaises(OperationException, d.get, 2)
        self.assertRaises(OperationException, d.remove, 2)
        self.assertRaises(OperationException, d.set, 2, book(2, "b", "c", "d", 4))