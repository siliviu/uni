package org.example;

import domain.Student;

import java.util.HashSet;
import java.util.TreeSet;

public class Main {
	public static void main(String[] args) {
		Student s1 = new Student("Dan", 4.5f);
		Student s2 = new Student("Ana", 8.5f);
		Student s3 = new Student("Dan", 4.5f);
		Student s4 = new Student("Ion", 5.5f);

//		TreeSet<Student> treeSet = new TreeSet<>(new StudentComparator());
		TreeSet<Student> treeSet = new TreeSet<>((Student a, Student b)->{return a.getName().compareTo(b.getName());});
		treeSet.add(s1);
		treeSet.add(s2);
		treeSet.add(s3);
		treeSet.add(s4);
		treeSet.forEach(System.out::println);
		System.out.println();


		treeSet = new TreeSet<>((Student a, Student b)->{return (int)(a.getMark()-b.getMark());});
		treeSet.add(s1);
		treeSet.add(s2);
		treeSet.add(s3);
		treeSet.add(s4);
        treeSet.forEach(System.out::println);
		System.out.println();

		HashSet<Student> hashSet = new HashSet<Student>();
		hashSet.add(s1);
		hashSet.add(s2);
		hashSet.add(s3);
		hashSet.forEach(System.out::println);

	}
}