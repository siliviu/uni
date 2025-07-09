using project_cs.domain;
using project_cs.utils;

namespace project_cs.service;

public class MasterService : IMasterService {
    private readonly LoginService _loginService;
    private readonly UserService _userService;
    private readonly Dictionary<String, IUserObserver> _loggedClients;

    public MasterService(LoginService loginService, UserService userService) {
        _loginService = loginService;
        _userService = userService;
        _loggedClients = new Dictionary<string, IUserObserver>();
    }

    public void Register(string username, string password) {
        _loginService.Register(username, password);
    }

    public void Login(string username, string password, IUserObserver user) {
        if (_loggedClients.ContainsKey(username))
            throw new Exception("User already logged in");
        _loginService.Login(username, password);
        _loggedClients[username] = user;
    }

    public void Logout(IUserObserver user) {
        String? username = null;
        foreach(var item in _loggedClients)
            if (item.Value == user)
                username = item.Key;
        _loggedClients.Remove(username!);
    }

    public List<ChildDto> SearchChildren(RaceDistance raceDistance, AgeGroup ageGroup) {
        return _userService.SearchChildren(raceDistance, ageGroup);
    }

    public void SignUpChild(string name, int age, RaceDistance raceDistance, AgeGroup? ageGroup) {
        _userService.SignUpChild(name, age, raceDistance, ageGroup);
        NotifySignup();
    }

    private void NotifySignup() {
        foreach (var item in _loggedClients)
            Task.Run(() => item.Value.NotifySignup());
    }
}