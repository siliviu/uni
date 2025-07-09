package networking;


import domain.User;
import domain.dto.SearchDTO;
import domain.dto.SignUpDTO;

public class Request {
    private RequestType type;
    private User user;
    private SearchDTO search;
    private SignUpDTO signup;

    public Request(){}
    public RequestType getType() {
        return type;
    }

    public void setType(RequestType type) {
        this.type = type;
    }

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }

    public SearchDTO getSearch() {
        return search;
    }

    public void setSearch(SearchDTO search) {
        this.search = search;
    }

    public SignUpDTO getSignup() {
        return signup;
    }

    public void setSignup(SignUpDTO signup) {
        this.signup = signup;
    }

    @Override
    public String toString() {
        return "Request{" +
                "type=" + type +
                ", user=" + user +
                ", search=" + search +
                ", signup=" + signup +
                '}';
    }
}
