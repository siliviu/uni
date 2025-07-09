using project_cs.domain;

namespace project_cs.utils;

public interface IMasterService {
    public void Register(string username, string password);
    public void Login(string username, string password, IUserObserver user);
    public void Logout(IUserObserver user);
    public List<ChildDto> SearchChildren(RaceDistance raceDistance, AgeGroup ageGroup);
    public void SignUpChild(string name, int age, RaceDistance raceDistance, AgeGroup? ageGroup);
}