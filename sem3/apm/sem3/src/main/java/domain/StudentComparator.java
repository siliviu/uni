package domain;

import java.util.Comparator;

public class StudentComparator implements Comparator<Student> {

    public int compare(Student a,Student b)
    {
        return a.getName().compareTo(b.getName());
    }
}
