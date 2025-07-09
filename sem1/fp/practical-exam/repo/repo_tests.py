from repo.repo import *


class RepoTests:
    @staticmethod
    def test():
        """Test repo
        """
        r = Repo("test.txt")
        assert len(r.get_all()) == 8
        assert r.get_filtered() == r.get_all()
        assert r.get_filter() == ("", -1)
        r.set_filter("a", 500)
        assert r.get_filter() == ("a", 500)
        assert len(r.get_filtered()) == 2
        r.add_tractor(Tractor(10,"10",100,"1000","10:10:2040"))
        assert len(r.get_all()) == 9
        r.undo()
        assert len(r.get_all()) == 8
        r.add_tractor(Tractor(10,"10",100,"1000","10:10:2040"))
        r.remove_tractor([Tractor(10,"10",100,"1000","10:10:2040")])
        assert len(r.get_all()) == 8
        r.undo()
        assert len(r.get_all()) == 9
        r.remove_tractor([Tractor(10,"10",100,"1000","10:10:2040")])

