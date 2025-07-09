from repo.repo import *
from service.shoeservice import *
from ui.console import *
from tests import *

if __name__ == "__main__":
    Tests.test_all()
    r = Repo("pantof.txt")
    s = ShoeService(r)
    c = Console(s)
    c.run()
