from service.shoeservice import *


class ServiceTest:
    @staticmethod
    def Test():
        r = Repo("test.txt")
        s = ShoeService(r)
        result = s.show_shoes('3')
        assert len(result) == 1
        assert result[0].id == 2
        result = s.show_shoes('zaza')
        assert len(result) == 0
        result = s.get_shoe_size(1)
        assert len(result) == 1
        assert result[0].size == 3 and result[0].number == 4
        result = s.order(1)
        assert result.number == 3
