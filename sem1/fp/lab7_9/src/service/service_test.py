import unittest
from service.book_controller import *
from service.client_controller import *
from service.event_controller import *
from service.statistics_controller import *
from service.random_controller import *
from service.util import *


class ServiceTestBook(unittest.TestCase):
    def test_book(self):
        ctrl = BookController(Repo())
        ctrl.add_book(1, 'a', 'b', 'c', 2)
        ctrl.add_book(2, 'b', 'c', 'd', 10)
        self.assertEqual(ctrl.get_book_list(), [book(1, 'a', 'b', 'c', 2), book(2, 'b', 'c', 'd', 10)])
        self.assertEqual(ctrl.get_book(1), book(1, 'a', 'b', 'c', 2))
        ctrl.modify_book(1, book.desc, 'zaza')
        self.assertEqual(ctrl.get_book_list(), [book(1, 'a', 'zaza', 'c', 2), book(2, 'b', 'c', 'd', 10)])
        ctrl.remove_book(2)
        self.assertEqual(ctrl.get_book_list(), [book(1, 'a', 'zaza', 'c', 2)])

    def test_util(self):
        r = Repo()
        ctrl = BookController(r)
        stats = StatisticsController(r, Repo())
        ctrl.add_book(1, "Ana are mere", "Ana si mere", "Anuta Anisoara", 3)
        ctrl.add_book(2, "Ana are mere 2", "Ana si mai multe mere", "Anuta Anisoara", 1)
        ctrl.add_book(3, "Ana", "Doar ana", "Anica Anuta", 10)
        self.assertEqual(ctrl.get_books_criteria(0, 1), [book(1, "Ana are mere", "Ana si mere", "Anuta Anisoara", 3)])
        self.assertEqual(ctrl.get_books_criteria(1, "Ana"),
                         [book(1, "Ana are mere", "Ana si mere", "Anuta Anisoara", 3),
                         book(2, "Ana are mere 2", "Ana si mai multe mere", "Anuta Anisoara", 1),
                         book(3, "Ana", "Doar ana", "Anica Anuta", 10)])
        self.assertEqual(ctrl.get_books_criteria(1, " aRe MERe"),
                         [book(1, "Ana are mere", "Ana si mere", "Anuta Anisoara", 3),
                         book(2, "Ana are mere 2", "Ana si mai multe mere", "Anuta Anisoara", 1)])
        self.assertEqual(ctrl.get_books_criteria(2, "ANUTA"),
                         [book(1, "Ana are mere", "Ana si mere", "Anuta Anisoara", 3),
                         book(2, "Ana are mere 2", "Ana si mai multe mere", "Anuta Anisoara", 1),
                          book(3, "Ana", "Doar ana", "Anica Anuta", 10)])
        self.assertEqual(ctrl.get_books_criteria(2, "anica "), [book(3, "Ana", "Doar ana", "Anica Anuta", 10)])
        self.assertEqual(ctrl.get_books_criteria(2, "  anisoara  "),
                         [book(1, "Ana are mere", "Ana si mere", "Anuta Anisoara", 3),
                          book(2, "Ana are mere 2", "Ana si mai multe mere", "Anuta Anisoara", 1)])
        ctrl.add_book(4, 'a', 'b', 'c', 4)
        ctrl.add_book(5, 'a', 'b', 'c', 14)
        ctrl.add_book(6, 'a', 'b', 'c', 24)

        for _ in range(3):
            ctrl.change_borrow(1, book.add_borrowed, 1+_)
        ctrl.change_borrow(2, book.add_borrowed, 10)
        for _ in range(10):
            ctrl.change_borrow(3, book.add_borrowed, 20+_)
        for _ in range(4):
            ctrl.change_borrow(4, book.add_borrowed, 30+_)
        for _ in range(14):
            ctrl.change_borrow(5, book.add_borrowed, 40+_)
        for _ in range(24):
            ctrl.change_borrow(6, book.add_borrowed, 60+_)

        self.assertEqual(
            stats.get_most_borrowed(),
            [ctrl.get_book(6),
             ctrl.get_book(5),
             ctrl.get_book(3),
             ctrl.get_book(4),
             ctrl.get_book(1)])

        for _ in range(24):
            ctrl.change_borrow(6, book.remove_borrowed, 60+_)

        self.assertEqual(
            stats.get_most_borrowed(),
            [
                ctrl.get_book(5),
                ctrl.get_book(3),
                ctrl.get_book(4),
                ctrl.get_book(1),
                ctrl.get_book(2)])

    def test_exceptions(self):
        ctrl = BookController(Repo())
        ctrl.add_book(1, 'a', 'b', 'c', 2)
        ctrl.add_book(2, 'b', 'c', 'd', 10)
        self.assertRaises(OperationException, ctrl.add_book, 1, 'a', 'b', 'c', 2)
        self.assertRaises(OperationException, ctrl.get_book, 3)
        self.assertRaises(OperationException, ctrl.remove_book, 3)
        self.assertRaises(OperationException, ctrl.modify_book, 3, book.desc, 'zaza')
        self.assertRaises(ConstraintException, ctrl.get_books_criteria, 0, "b")


class ServiceTestClient(unittest.TestCase):
    def test_client(self):
        ctrl = ClientController(Repo())
        ctrl.add_client(1, 'a',  2)
        ctrl.add_client(2, 'b',  10)
        self.assertEqual(ctrl.get_client_list(), [client(1, 'a', 2), client(2, 'b',  10)])
        self.assertEqual(ctrl.get_client(1), client(1, 'a', 2))
        ctrl.modify_client(2, client.name, 'zaza')
        self.assertEqual(ctrl.get_client_list(),  [client(1, 'a', 2), client(2, 'zaza',  10)])
        ctrl.remove_client(1)
        self.assertEqual(ctrl.get_client_list(), [client(2, 'zaza', 10)])

    def test_util(self):
        r = Repo()
        ctrl = ClientController(r)
        stats = StatisticsController(Repo(), r)
        ctrl.add_client(1, "Gigel", 128)
        ctrl.add_client(2, "Gigelescu", 49)
        self.assertEqual(ctrl.get_clients_criteria(0, 1), [client(1, "Gigel", 128)])
        self.assertEqual(ctrl.get_clients_criteria(1, "gigeL "), [client(1, "Gigel", 128), client(2, "Gigelescu", 49)])
        self.assertEqual(ctrl.get_clients_criteria(1, " GIGELESCU"), [client(2, "Gigelescu", 49)])
        self.assertEqual(ctrl.get_clients_criteria(2, 49), [client(2, "Gigelescu", 49)])
        ctrl.add_client(3, "Marcel", 125)
        ctrl.add_client(4, "Ionel", 68)
        ctrl.add_client(5, "Viorel", 44)
        for _ in range(12):
            ctrl.change_borrow(1, client.add_borrowed, 1+_)
        for _ in range(4):
            ctrl.change_borrow(2, client.add_borrowed, 20+_)
        for _ in range(6):
            ctrl.change_borrow(3, client.add_borrowed, 30+_)
        for _ in range(14):
            ctrl.change_borrow(5, client.add_borrowed, 40+_)
        self.assertEqual(
            stats.get_borrowers(0), [ctrl.get_client(1), ctrl.get_client(2), ctrl.get_client(3), ctrl.get_client(5)])
        self.assertEqual(
            stats.get_borrowers(1), [ctrl.get_client(5), ctrl.get_client(1), ctrl.get_client(3), ctrl.get_client(2)])
        self.assertEqual(stats.get_20th_percentile_clients(), [("Viorel", 14)])
        for _ in range(1):
            ctrl.change_borrow(5, client.remove_borrowed, 40+_)
        self.assertEqual(stats.get_20th_percentile_clients(), [("Viorel", 13)])

    def test_exceptions(self):
        ctrl = ClientController(Repo())
        ctrl.add_client(1, 'a', 2)
        ctrl.add_client(2, 'b', 10)
        self.assertRaises(OperationException, ctrl.add_client, 1, 'a', 2)
        self.assertRaises(OperationException, ctrl.get_client, 3)
        self.assertRaises(OperationException, ctrl.remove_client, 3)
        self.assertRaises(OperationException, ctrl.modify_client, 3, client.name, 'zaza')
        self.assertRaises(ConstraintException, ctrl.get_clients_criteria, 0, "b")


class ServiceTestEvent(unittest.TestCase):
    def test_service(self):
        book_repo = Repo()
        client_repo = Repo()
        event_ctrl = EventController(Repo(), book_repo, client_repo)
        book_repo.add(book(1, 'a', 'b', 'c', 1))
        client_repo.add(client(1, 'a', 2))
        self.assertEqual(event_ctrl.borrow_book(1, 1), 1)
        self.assertEqual(book_repo.get(1).copies, 0)
        self.assertEqual(book_repo.get(1).borrowers, 1)
        self.assertEqual(client_repo.get(1).borrowed, 1)
        event_ctrl.return_book(1)
        self.assertEqual(book_repo.get(1).copies, 1)
        self.assertEqual(book_repo.get(1).borrowers, 0)
        self.assertEqual(client_repo.get(1).borrowed, 0)

    def test_exceptions(self):
        book_repo = Repo()
        client_repo = Repo()
        event_ctrl = EventController(Repo(), book_repo, client_repo)
        book_repo.add(book(1, 'a', 'b', 'c', 1))
        client_repo.add(client(1, 'a', 2))
        self.assertRaises(OperationException, event_ctrl.borrow_book, 1, 2)
        self.assertRaises(OperationException, event_ctrl.borrow_book, 2, 1)
        self.assertRaises(OperationException, event_ctrl.return_book, 1)
        event_ctrl.borrow_book(1, 1)
        event_ctrl.return_book(1)
        self.assertRaises(ConstraintException, event_ctrl.return_book, 1)

class ServiceTestRandom(unittest.TestCase):
    def test(self):
        book_repo=Repo()
        client_repo=Repo()
        r = RandomController(book_repo,client_repo)
        r.recursive_generate_random_books(4)
        self.assertEqual(book_repo.get_length(),4)
        r.recursive_generate_random_clients(3)
        self.assertEqual(client_repo.get_length(),3)

class ServiceTestUtil(unittest.TestCase):
    def test(self):
        self.assertEqual(Utils.norm(" aBCdEFg  h   "), "ABCDEFG  H")
        self.assertEqual(Utils.norm("       "), "")
    