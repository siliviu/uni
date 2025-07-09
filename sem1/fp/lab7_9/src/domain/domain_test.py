import unittest

from domain.book import *
from domain.client import *
from domain.event import *


class BookTests(unittest.TestCase):
    def test_init(self):
        b = book(12, "ab", "bc", "ef", 13)
        self.assertEqual(b.id, 12)
        self.assertEqual(b.title, "ab")
        self.assertEqual(b.desc, "bc")
        self.assertEqual(b.author, "ef")
        self.assertEqual(b.copies, 13)

    def test_setget(self):
        b = book(12, "ab", "bc", "ef", 13)
        b.id = 1
        self.assertEqual(b.id, 1)
        b.title = " a"
        self.assertEqual(b.title, " a")
        b.desc = "h "
        self.assertEqual(b.desc, "h ")
        b.author = " z "
        self.assertEqual(b.author, " z ")
        b.copies = 2
        self.assertEqual(b.copies, 2)

    def test_str(self):
        b = book(12, "ab", "bc", "ef", 13)
        self.assertEqual(
            str(b),
            f"ID : {colored('12','blue')}, Title : {colored('ab','blue')}, Description : {colored('bc','blue')}, Author : {colored('ef','blue')}, Copies : {colored('13','blue')}, Borrowers : {colored('0','blue')}",
        )

    def test_eq(self):
        b = book(12, "ab", "bc", "ef", 13)
        c = book(12, "ab", "bc", "ef", 13)
        d = book(12, "ab", "bc", " ef", 13)
        self.assertEqual(b, c)
        self.assertNotEqual(b, d)

    def test_exceptions(self):
        b = book(12, "ab", "bc", "ef", 13)
        with self.assertRaises(ConstraintException):
            b.id = -1
        with self.assertRaises(ConstraintException):
            b.id = "GA"
        with self.assertRaises(ConstraintException):
            b.desc = " "
        with self.assertRaises(ConstraintException):
            b.desc = 23
        with self.assertRaises(ConstraintException):
            b.title = ""
        with self.assertRaises(ConstraintException):
            b.author = "  "
        with self.assertRaises(ConstraintException):
            b.copies = -1
        self.assertRaises(ConstraintException, book, 3, "a", "b", "c", "haha")

    def test_borrowed(self):
        b = book(12, "ab", "bc", "ef", 13)
        self.assertEqual(b.copies, 13)
        b.add_borrowed(1)
        b.add_borrowed(2)
        self.assertEqual(b.borrowers, 2)
        self.assertEqual(b.copies, 11)
        b.remove_borrowed(1)
        self.assertEqual(b.borrowers, 1)
        self.assertEqual(b.copies, 12)


class ClientTests(unittest.TestCase):
    def test_init(self):
        c = client(1, "gigel", 2030)
        self.assertEqual(c.id, 1)
        self.assertEqual(c.name, "gigel")
        self.assertEqual(c.uid, 2030)

    def test_setget(self):
        c = client(1, "gigel", 2030)
        c.id = 44
        self.assertEqual(c.id, 44)
        c.name = "gigela"
        self.assertEqual(c.name, "gigela")
        c.uid = 3020
        self.assertEqual(c.uid, 3020)

    def test_str(self):
        c = client(1, "gigel", 2030)
        self.assertEqual(
            str(c),
            f"ID : {colored(str('1'),'blue')}, Name : {colored('gigel','blue')}, UID : {colored('2030','blue')}, Borrowed : {colored('0','blue')}",
        )

    def test_eq(self):
        b = client(12, "ef", 13)
        c = client(12, "ef", 13)
        d = client(12, " ef", 13)
        self.assertEqual(b, c)
        self.assertNotEqual(b, d)

    def test_exceptions(self):
        c = client(1, "gigel", 2030)
        with self.assertRaises(ConstraintException):
            c.id = "Ga"
        with self.assertRaises(ConstraintException):
            c.id = -4
        with self.assertRaises(ConstraintException):
            c.name = "   "
        with self.assertRaises(ConstraintException):
            c.name = 7
        with self.assertRaises(ConstraintException):
            c.uid = 0
        self.assertRaises(ConstraintException, client, -44, "haha", 2)

    def test_borrowed(self):
        c = client(1, "gigel", 2030)
        c.add_borrowed(1)
        c.add_borrowed(2)
        self.assertEqual(c.borrowed, 2)
        c.remove_borrowed(2)
        self.assertEqual(c.borrowed, 1)


class EventTests(unittest.TestCase):
    def test_init(self):
        e = event(1, 2, 3)
        self.assertEqual(e.id, 1)
        self.assertEqual(e.book, 2)
        self.assertEqual(e.owner, 3)

    def test_str(self):
        e = event(1, 2, 3)
        self.assertEqual(
            str(e),
            f"Event ID : {colored('1','blue')}, Borrower ID : {colored('3','blue')}, Book ID : {colored('2','blue')}"
        )
