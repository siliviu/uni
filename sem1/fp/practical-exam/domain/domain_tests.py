from domain.tractor import *


class DomainTests:
    """Test domain"""
    @staticmethod
    def test():
        t = Tractor(12, "ba", 234, "gaa", "20:10:2010")
        assert repr(t) == "12|ba|234|gaa|20:10:2010"
        assert str(t) =="ba, 234, gaa, 20:10:2010 | Id = 12"
        assert t.id == 12
        t.id = 13
        assert t.id == 13
        assert t.name == "ba"
        t.name = "hga"
        assert t.name == "hga"
        assert t.price == 234
        t.price = 4411
        assert t.price == 4411
        assert t.expire == date(2010, 10, 20)
        t.expire = "21:11:2011"
        assert t.expire == date(2011, 11, 21)
