from domain.domain_test import *
from repo.repo_test import *
from service.service_test import *

class Tests:
    @staticmethod
    def test_all():
        DomainTest.Test()
        RepoTest.Test()
        ServiceTest.Test()
