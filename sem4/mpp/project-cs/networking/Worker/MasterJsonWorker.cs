using System.Net.Sockets;
using project_cs.domain;
using project_cs.utils;

namespace networking.Worker;

public class MasterJsonWorker : AbstractJsonWorker, IUserObserver {
    private IMasterService Service;

    public MasterJsonWorker(IMasterService service, TcpClient connection) : base(connection) {
        Service = service;
    }

    protected override Response HandleRequest(Request request) {
        Response response = null;
        Console.WriteLine(request);
        switch (request.type) {
            case RequestType.LOGIN: {
                Console.WriteLine("Login request ...");
                var user = request.user;
                try {
                    Service.Login(user.username, user.hashedPassword, this);
                    return okResponse;
                }
                catch (Exception e) {
//				connected = false;
                    response = new Response {
                        type = ResponseType.ERROR,
                        errorMessage = e.Message
                    };
                    return response;
                }
            }
            case RequestType.REGISTER: {
                Console.WriteLine("Register request ...");
                var user = request.user;
                try {
                    Service.Register(user.username, user.hashedPassword);
                    return okResponse;
                }
                catch (Exception e) {
//				connected = false;
                    response = new Response {
                        type = ResponseType.ERROR,
                        errorMessage = e.Message
                    };
                    return response;
                }
            }
            case RequestType.GET_CHILDREN: {
                Console.WriteLine("Children request ...");
                var search = request.search;
                try {
                    return new Response {
                        type = ResponseType.CHILDREN_LIST,
                        children = Service.SearchChildren(search.raceDistance, search.ageGroup)
                    };
                }
                catch (Exception e) {
//				connected = false;
                    response = new Response {
                        type = ResponseType.ERROR,
                        errorMessage = e.Message
                    };
                    return response;
                }
            }
            case RequestType.SIGN_UP_CHILD: {
                Console.WriteLine("Sign up");
                var signUp = request.signup;
                try {
                    Service.SignUpChild(signUp.name, signUp.age, signUp.raceDistance, signUp.ageGroup);
                    return okResponse;
                }
                catch (Exception e) {
//				connected = false;
                    response = new Response {
                        type = ResponseType.ERROR,
                        errorMessage = e.Message
                    };
                    return response;
                }
            }
            case RequestType.LOGOUT:
                connected = false;
                Service.Logout(this);
                break;
        }

        return response;
    }

    public void NotifySignup() {
        var response = new Response {
            type = ResponseType.UPDATE_CHILDREN
        };
        Console.WriteLine("Received signup notification");
        try {
            SendResponse(response);
        }
        catch (Exception e) {
            Console.WriteLine(e.StackTrace);
        }
    }
}