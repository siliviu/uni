package repository;

import domain.Child;

public interface ChildRepository extends Repository<Child, Integer> {

	Child getChildByNameAge(String name, int Age);
}
