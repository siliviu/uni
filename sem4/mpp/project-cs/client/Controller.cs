using project_cs.domain;
using project_cs.utils;

namespace project_cs;

public class Controller : IUserObserver {
    public event EventHandler<EventArgs> UpdateEvent;
    private readonly IMasterService _service;

    public Controller(IMasterService service) {
        _service = service;
    }

    public void NotifySignup() {
        Console.WriteLine("Update Event called");
        UpdateEvent(this, null);
    }

    public void Login(string name, string password) {
        _service.Login(name, password, this);
    }

    public void Register(string name, string password) {
        _service.Register(name, password);
    }

    public void Logout() {
        _service.Logout(null!);
    }

    public List<ChildDto> SearchChildren(string raceS, string ageS) {
        var ageGroup = (AgeGroup)EnumHandler.GetGroupFromString(raceS)!;
        var raceDistance = (RaceDistance)EnumHandler.GetRaceFromString(ageS)!;
        return _service.SearchChildren(raceDistance, ageGroup);
    }

    public void SignUpChild(string name, int ageValue, RaceDistance raceDistance, AgeGroup? ageGroup) {
        _service.SignUpChild(name, ageValue, raceDistance, ageGroup);
    }
}