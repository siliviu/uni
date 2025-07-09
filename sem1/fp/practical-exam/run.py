from ui.console import *
from tests import *

if __name__ == "__main__":
    """Skeleton"""
    Tests.test_all()
    repo = Repo("file.txt")
    service = Service(repo)
    console = Console(service)
    console.run()