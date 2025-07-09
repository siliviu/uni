package domain;

import java.util.Objects;

public class Student {

    private float mark;
    private String name;

    public Student( String nume,float medie) {
        this.mark = medie;
        this.name = nume;
    }

    @Override
    public String toString() {
        return "Student{" +
                "name=" + name +
                ", mark='" + mark + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Student student = (Student) o;
        return Float.compare(mark, student.mark) == 0 && Objects.equals(name, student.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(mark, name);
    }

    public float getMark() {
        return mark;
    }

    public void setMark(float mark) {
        this.mark = mark;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

}
