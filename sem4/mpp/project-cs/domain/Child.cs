namespace project_cs.domain;

public class Child : Identifiable<int> {
    public string name { get; set; }
    public int age { get; set; }

    public Child(string name, int age) {
        this.name = name;
        this.age = age;
    }

    public override string ToString() {
        return "Child: " + name + ", " + age;
    }

}