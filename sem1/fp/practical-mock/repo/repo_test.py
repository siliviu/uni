from repo.repo import *


class RepoTest:
    @staticmethod
    def Test():
        r = Repo('test.txt')
        r.add_shoe(Shoe(1, '2', 3, 4, 5, False))
        r.add_shoe(Shoe(2, '3', 4, 5, 6, True))
        a = r.get_shoes()
        assert len(a) == 2 and a[0].id == 1 and not a[0].pers and a[1].id == 2 and a[1].pers
        a = r.get_shoes(lambda s: s.id == 1)
        assert len(a) == 1 and a[0].id == 1 and not a[0].pers and a[0].name == '2'
        r.modify_shoe(1, Shoe(1, 'zaza', 3, 4, 5, False))
        a = r.get_shoes(lambda s: s.id == 1)
        assert len(a) == 1 and a[0].id == 1 and not a[0].pers and a[0].name == 'zaza'
        rr = Repo('test.txt')
        a = rr.get_shoes(lambda s: s.id == 1)
        assert len(a) == 1 and a[0].id == 1 and not a[0].pers and a[0].name == 'zaza'