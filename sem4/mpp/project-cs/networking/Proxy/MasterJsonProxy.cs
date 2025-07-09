using project_cs.domain;
using project_cs.utils;

namespace networking.Proxy;

public class MasterJsonProxy : AbstractJsonProxy, IMasterService {
    private IUserObserver user;

    public MasterJsonProxy(string host, int port) : base(host, port) { }

    protected override bool IsUpdate(Response response) {
        return response.type == ResponseType.UPDATE_CHILDREN;
    }

    protected override void HandleUpdate(Response response) {
        if (response.type == ResponseType.UPDATE_CHILDREN)
            user.NotifySignup();
    }

    public void Register(string username, string password) {
        InitializeConnection();
        var req = new Request {
            user = new User(username, password),
            type = RequestType.REGISTER
        };
        SendRequest(req);
        var response = GetResponse();
        if (response.type == ResponseType.ERROR) {
//			closeConnection();
            var err = response.errorMessage;
            throw new Exception(err);
        }
    }

    public void Login(string username, string password, IUserObserver user) {
        InitializeConnection();
        var req = new Request {
            user = new User(username, password),
            type = RequestType.LOGIN
        };
        SendRequest(req);
        var response = GetResponse();
        if (response.type == ResponseType.OK) {
            this.user = user;
            return;
        }

        if (response.type == ResponseType.ERROR) {
//			closeConnection();
            var err = response.errorMessage;
            throw new Exception(err);
        }
    }

    public void Logout(IUserObserver user) {
        var req = new Request {
            type = RequestType.LOGOUT
        };
        SendRequest(req);
        CloseConnection();
    }

    public List<ChildDto> SearchChildren(RaceDistance raceDistance, AgeGroup ageGroup) {
        var req = new Request() {
            search = new SearchDto(raceDistance, ageGroup),
            type = RequestType.GET_CHILDREN
        };
        SendRequest(req);
        var response = GetResponse();
        if (response.type == ResponseType.ERROR) {
//			closeConnection();
            var err = response.errorMessage;
            throw new Exception(err);
        }

        return response.children;
    }

    public void SignUpChild(string name, int age, RaceDistance raceDistance, AgeGroup? ageGroup) {
        var req = new Request {
            signup = new SignUpDto(name, age, raceDistance, (AgeGroup)ageGroup!),
            type = RequestType.SIGN_UP_CHILD
        };
        SendRequest(req);
        var response = GetResponse();
        if (response.type == ResponseType.ERROR) {
//			closeConnection();
            var err = response.errorMessage;
            throw new Exception(err);
        }
    }
}