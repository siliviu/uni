package repository;

import domain.Medicine;

public interface MedicineRepository extends Repository<Medicine, Integer> {
	Medicine getMedicineByName(String name);
}
