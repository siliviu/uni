namespace project_cs.domain;

public class Signup : Identifiable<int> {
    public Child child { get; set; }
    public AgeGroup ageGroup { get; set; }
    public RaceDistance raceDistance { get; set; }
    public Signup(Child child, AgeGroup ageGroup, RaceDistance raceDistance) {
        this.child = child;
        this.ageGroup = ageGroup;
        this.raceDistance = raceDistance;
    }

    public override string ToString() {
        return "Signup: " + child + ", " + ageGroup + ", " + raceDistance;
    }

}