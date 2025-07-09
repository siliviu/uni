from domain.shoe import *


class DomainTest:
    @staticmethod
    def Test():
        s1 = Shoe(1, "a", 2, 3, 4, False)
        assert s1.id == 1 and s1.name == "a" and s1.size == 2 and s1.number == 3 and s1.price == 4 and not s1.pers
        s2 = Shoe(2, "baba", 3, 4, 5, True)
        assert s2.id == 2 and s2.name == "baba" and s2.size == 3 and s2.number == 4 and s2.price == 5 and s2.pers
        s2.id = 4
        s2.name='sa'
        s2.size=5
        s2.number=6
        s2.price=7
        s2.pers=False
        assert s2.id==4 and s2.name=='sa' and s2.size==5 and s2.number==6 and s2.price==7 and not s2.pers
        assert str(s1)=='1 a 2 3 4 False'
        assert repr(s1)=='1,a,2,3,4,False'
