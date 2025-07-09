from service.service import *
from service.utils import *


class ServiceTests:
    """Test service"""
    @staticmethod
    def test():
        "Service"
        r = Repo("test.txt")
        s = Service(r)
        assert s.get_filter() == ("", -1)
        assert len(s.get_filtered()) == 8
        s.set_filter("a", 500)
        assert s.get_filter() == ("a", 500)
        assert len(s.get_filtered()) == 2
        s.set_filter("", -1)
        s.add_tractor(10, "10", 100, "1000", "10:10:2040")
        assert len(r.get_all()) == 9
        s.undo()
        assert len(r.get_all()) == 8
        s.remove_tractor(2)
        assert len(r.get_all()) == 4
        s.undo()
        assert len(r.get_all()) == 8
        
        "Utils"
        assert Utils.containts_digit(1234, 2)
        assert not Utils.containts_digit(1234, 5)
        assert Utils.has_expired(date(2020, 2, 2))
        assert not Utils.has_expired(date(2024, 1, 1))
