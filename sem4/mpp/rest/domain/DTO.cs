namespace project_cs.domain;

public class ChildDto {
    public string name { get; set; }
    public int age { get; set; }
    public int signups { get; set; }

    public ChildDto(string name, int age, int signups) {
        this.name = name;
        this.age = age;
        this.signups = signups;
    }
}

public class SearchDto {
    public RaceDistance raceDistance { get; }
    public AgeGroup ageGroup { get; }

    public SearchDto(RaceDistance raceDistance, AgeGroup ageGroup) {
        this.raceDistance = raceDistance;
        this.ageGroup = ageGroup;
    }
}

public class SignUpDto {
    public string name { get; }
    public int age { get; }
    public RaceDistance raceDistance { get; }
    public AgeGroup ageGroup { get; }
    public SignUpDto(string name, int age, RaceDistance raceDistance, AgeGroup ageGroup) {
        this.name = name;
        this.age = age;
        this.raceDistance = raceDistance;
        this.ageGroup = ageGroup;
    }
}