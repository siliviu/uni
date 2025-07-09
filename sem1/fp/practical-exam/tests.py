from domain.domain_tests import *
from repo.repo_tests import *
from service.service_tests import *

class Tests():
    """Test everything
    """
    @staticmethod
    def test_all():
        DomainTests.test()
        RepoTests.test()
        ServiceTests.test()
