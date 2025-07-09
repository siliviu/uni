using project_cs.domain;

namespace project_cs.repo;

public interface ISignupRepository : IRepository<Signup, int> {
    public ICollection<Child> GetChildrenByRace(AgeGroup ageGroup, RaceDistance raceDistance);

    public int GetChildSignups(int id);
}