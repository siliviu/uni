namespace project_cs.domain;

public class User : Identifiable<int> {
    public string username { get; set; }
    public string hashedPassword { get; set; }
    public User(string username, string hashedPassword) {
        this.username = username;
        this.hashedPassword = hashedPassword;
    }

    public override string ToString() {
        return "User: " + username + ", " + hashedPassword;
    }

}