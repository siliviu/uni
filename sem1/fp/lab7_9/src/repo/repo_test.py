import unittest
import os
from repo.memory_repository import *
from repo.binary_repository import *
from repo.file_repository import *
from domain.book import *


class MemoryRepoTest(unittest.TestCase):
    def test_add(self):
        d = Repo()
        d.add(book(1, "2", "a", "4", 5))
        d.add(book(23, "va", "b", "nanana", 1))
        self.assertEqual(d.get_length(), 2)
        self.assertEqual(
            d.get_list(),
            [book(1, "2", "a", "4", 5), book(23, "va", "b", "nanana", 1)],
        )

    def test_blackbox_add(self):
        d = Repo()
        d.add(book(1, "2", "a", "4", 5))
        d.add(book(23, "va", "b", "nanana", 1))
        self.assertEqual(d.get_length(), 2)
        self.assertEqual(
            d.get_list(),
            [book(1, "2", "a", "4", 5), book(23, "va", "b", "nanana", 1)],
        )
        self.assertRaises(OperationException, d.add, book(1, "4", "5", "6", 7))

    def test_setget(self):
        d = Repo()
        d.add(book(1, "2", "a", "4", 5))
        d.add(book(23, "va", "b", "nanana", 1))
        self.assertEqual(d.get(1), book(1, "2", "a", "4", 5))
        d.set(23, book(24, "b", "wh", "th", 3))
        self.assertEqual(d.get(23), book(24, "b", "wh", "th", 3))

    def test_remove(self):
        d = Repo()
        d.add(book(1, "2", "a", "4", 5))
        d.add(book(23, "va", "b", "nanana", 1))
        d.remove(23)
        self.assertEqual(d.get_list(), [book(1, "2", "a", "4", 5)])

    def test_exceptions(self):
        d = Repo()
        d.add(book(1, "2", "a", "4", 5))
        self.assertRaises(OperationException, d.add, book(1, "3", "b", "4", 5))
        self.assertRaises(OperationException, d.get, 2)
        self.assertRaises(OperationException, d.remove, 2)
        self.assertRaises(OperationException, d.set, 2, book(2, "b", "c", "d", 4))


class PersistencyRepoTest(unittest.TestCase):
    def test_binary(self):
        d = BinaryRepo('binrepo.test')
        d.add(book(1, "2", "a", "4", 5))
        d.add(book(23, "va", "b", "nanana", 1))
        e = BinaryRepo('binrepo.test')
        self.assertEqual(
            e.get_list(),
            [book(1, "2", "a", "4", 5), book(23, "va", "b", "nanana", 1)],
        )
        os.remove(os.path.dirname(__file__)+'\\bin_binrepo.test')

    def test_file(self):
        d = FileRepo('filerepo.test', book)
        d.add(book(1, "2", "a", "4", 5))
        d.add(book(23, "va", "b", "nanana", 1))
        e = FileRepo('filerepo.test', book)
        self.assertEqual(
            e.get_list(),
            [book(1, "2", "a", "4", 5), book(23, "va", "b", "nanana", 1)],
        )
        os.remove(os.path.dirname(__file__)+'\\file_filerepo.test')
