using project_cs.domain;
using project_cs.repo;

namespace project_cs.service;

public class UserService {
    private readonly IChildRepository _childRepository;
    private readonly ISignupRepository _signupRepository;

    private const int MaxSignups = 2;

    public UserService(IChildRepository childRepository, ISignupRepository signupRepository) {
        this._childRepository = childRepository;
        this._signupRepository = signupRepository;
    }

    public List<ChildDto> SearchChildren(RaceDistance raceDistance, AgeGroup ageGroup) {
        return _signupRepository.GetChildrenByRace(ageGroup, raceDistance)
            .Select(c => new ChildDto(c.name, c.age, _signupRepository.GetChildSignups(c.id)))
            .ToList<ChildDto>();
    }

    public void SignUpChild(string name, int age, RaceDistance raceDistance, AgeGroup? ageGroup) {
        if (ageGroup == null)
            throw new Exception("Invalid age group");
        var child = _childRepository.GetChildByNameAge(name, age);
        if (child == null)
            child = _childRepository.Add(new Child(name, age));
        if (_signupRepository.GetChildSignups(child.id) >= MaxSignups)
            throw new Exception("Child has signed up to the maximum of " + MaxSignups + " races already.");
        _signupRepository.Add(new Signup(child, (AgeGroup)ageGroup, raceDistance));
    }
}