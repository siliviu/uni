import unittest
from repo.data import *


class RepoTestBooks(unittest.TestCase):
    def test_add(self):
        d = Data()
        d.add_book(book(1, "2", "a", "4", 5))
        d.add_book(book(23, "va", "b", "nanana", 1))
        self.assertEqual(
            d.get_book_list(),
            [book(1, "2", "a", "4", 5), book(23, "va", "b", "nanana", 1)],
        )

    def test_setget(self):
        d = Data()
        d.add_book(book(1, "2", "a", "4", 5))
        d.add_book(book(23, "va", "b", "nanana", 1))
        self.assertEqual(d.get_book(1), book(1, "2", "a", "4", 5))
        d.set_book(23, book(24, "b", "wh", "th", 3))
        self.assertEqual(d.get_book(23), book(24, "b", "wh", "th", 3))

    def test_remove(self):
        d = Data()
        d.add_book(book(1, "2", "a", "4", 5))
        d.add_book(book(23, "va", "b", "nanana", 1))
        d.remove_book(23)
        self.assertEqual(d.get_book_list(), [book(1, "2", "a", "4", 5)])

    def test_exceptions(self):
        d = Data()
        d.add_book(book(1, "2", "a", "4", 5))
        self.assertRaises(OperationException, d.add_book, book(1, "3", "b", "4", 5))
        self.assertRaises(OperationException, d.get_book, 2)
        self.assertRaises(OperationException, d.remove_book, 2)
        self.assertRaises(OperationException, d.set_book, 2, book(2, "b", "c", "d", 4))

    def test_borrow(self):
        d = Data()
        d.add_book(book(1, "2", "a", "4", 5))
        d.add_book_borrowed(1, 1)
        self.assertEqual(d.get_book(1).borrowers, 1)
        d.add_book_borrowed(1, 2)
        self.assertEqual(d.get_book(1).borrowers, 2)
        d.remove_book_borrowed(1, 2)
        self.assertEqual(d.get_book(1).borrowers, 1)


class RepoTestClients(unittest.TestCase):
    def test_add(self):
        d = Data()
        d.add_client(client(1, "a", 5))
        d.add_client(client(23, "nanana", 1))
        self.assertEqual(
            d.get_client_list(),
            [client(1, "a", 5), client(23, "nanana", 1)],
        )

    def test_setget(self):
        d = Data()
        d.add_client(client(1, "a", 5))
        d.add_client(client(23, "nanana", 1))
        self.assertEqual(d.get_client(1), client(1, "a", 5))
        d.set_client(23, client(24, "b", 3))
        self.assertEqual(d.get_client(23), client(24, "b", 3))

    def test_remove(self):
        d = Data()
        d.add_client(client(1, "a", 5))
        d.add_client(client(23, "nanana", 1))
        d.remove_client(23)
        self.assertEqual(d.get_client_list(), [client(1, "a", 5)])

    def test_exceptions(self):
        d = Data()
        d.add_client(client(1, "a", 5))
        self.assertRaises(OperationException, d.add_client, client(1, "b", 5))
        self.assertRaises(OperationException, d.get_client, 2)
        self.assertRaises(OperationException, d.remove_client, 2)
        self.assertRaises(OperationException, d.set_client, 2, client(2, "b", 4))

    def test_borrow(self):
        d = Data()
        d.add_client(client(1, "b", 5))
        d.add_client_borrowed(1, 1)
        self.assertEqual(d.get_client(1).borrowed, 1)
        d.add_client_borrowed(1, 2)
        self.assertEqual(d.get_client(1).borrowed, 2)
        d.remove_client_borrowed(1, 1)
        self.assertEqual(d.get_client(1).borrowed, 1)


class RepoTestEvents(unittest.TestCase):
    def test_event(self):
        d = Data()
        d.add_event(event(1, 2, 3))
        d.add_event(event(2, 3, 2))
        self.assertEqual(d.get_event_list(), [event(1, 2, 3), event(2, 3, 2)])
        self.assertEqual(d.get_new_event_id(), 3)
        self.assertEqual(d.get_event(1), event(1, 2, 3))