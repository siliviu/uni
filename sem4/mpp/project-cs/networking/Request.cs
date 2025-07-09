using Newtonsoft.Json;
using project_cs.domain;

namespace networking;

public enum RequestType {
    LOGIN, REGISTER, GET_CHILDREN, SIGN_UP_CHILD, LOGOUT
}

public class Request {
    public RequestType type { get; set; }
    public User user { get; set; }
    public SearchDto search { get; set; }
    public SignUpDto signup { get; set; }
}