using project_cs.domain;

namespace project_cs.repo;

public class UserDbRepository : IUserRepository {
    private static readonly log4net.ILog Log =
        log4net.LogManager.GetLogger(System.Reflection.MethodBase.GetCurrentMethod().DeclaringType);

    readonly IDictionary<String, string> _props;

    public UserDbRepository(IDictionary<string, string> props) {
        Log.Info("creating user repo ");
        this._props = props;
    }

    public User Add(User elem) {
        Log.Info("add user");
        var con = DbUtils.GetConnection(_props);
        using (var comm = con.CreateCommand()) {
            comm.CommandText = "INSERT INTO User (username, password) VALUES(@username, @password)";

            var paramUsername = comm.CreateParameter();
            paramUsername.ParameterName = "@username";
            paramUsername.Value = elem.username;
            comm.Parameters.Add(paramUsername);

            var paramPassword = comm.CreateParameter();
            paramPassword.ParameterName = "@password";
            paramPassword.Value = elem.hashedPassword;
            comm.Parameters.Add(paramPassword);
            comm.ExecuteNonQuery();
            
            var comm2 = con.CreateCommand();
            comm2.CommandText = "SELECT last_insert_rowid()";
            var id = (Int64)comm2.ExecuteScalar()!;
            elem.id = (int)id;
            return elem;
        }
    }

    public void Delete(int id) {
        Log.Info("delete User");
        var con = DbUtils.GetConnection(_props);
        using (var comm = con.CreateCommand()) {
            comm.CommandText = "DELETE FROM User WHERE ID=@id";
            var paramId = comm.CreateParameter();
            paramId.ParameterName = "@id";
            paramId.Value = id;
            comm.Parameters.Add(paramId);

            comm.ExecuteNonQuery();
        }
    }

    public void Update(User elem, int id) {
        Log.Info("update User");
        var con = DbUtils.GetConnection(_props);
        using (var comm = con.CreateCommand()) {
            comm.CommandText = "UPDATE User SET username=@username, password=@password WHERE ID=@id";
            var paramId = comm.CreateParameter();
            paramId.ParameterName = "@id";
            paramId.Value = elem.id;
            comm.Parameters.Add(paramId);

            var paramUsername = comm.CreateParameter();
            paramUsername.ParameterName = "@username";
            paramUsername.Value = elem.username;
            comm.Parameters.Add(paramUsername);

            var paramPassword = comm.CreateParameter();
            paramPassword.ParameterName = "@password";
            paramPassword.Value = elem.hashedPassword;
            comm.Parameters.Add(paramPassword);

            comm.ExecuteNonQuery();
        }
    }

    public User? GetById(int id) {
        Log.Info("get User ");
        var con = DbUtils.GetConnection(_props);
        User? u = null;
        using (var comm = con.CreateCommand()) {
            comm.CommandText = "SELECT username, password, id FROM User WHERE id=@id";
            var paramId = comm.CreateParameter();
            paramId.ParameterName = "@id";
            paramId.Value = id;
            comm.Parameters.Add(paramId);
            using (var dataR = comm.ExecuteReader()) {
                if (dataR.Read()) {
                    var username = dataR.GetString(0);
                    var password = dataR.GetString(1);
                    u = new User(username, password);
                    u.id = id;
                }
            }
        }

        return u;
    }

    public ICollection<User> GetAll() {
        Log.Info("get all from User");
        var con = DbUtils.GetConnection(_props);
        IList<User> users = new List<User>();
        using (var comm = con.CreateCommand()) {
            comm.CommandText = "SELECT username, password, id FROM User";

            using (var dataR = comm.ExecuteReader()) {
                while (dataR.Read()) {
                    var username = dataR.GetString(0);
                    var password = dataR.GetString(1);
                    var id = dataR.GetInt32(2);
                    var u = new User(username, password);
                    u.id = id;
                    users.Add(u);
                }
            }
        }

        return users;
    }

    public User? GetUserByUsername(string username) {
        Log.Info("get User ");
        var con = DbUtils.GetConnection(_props);
        User? u = null;
        using (var comm = con.CreateCommand()) {
            comm.CommandText = "SELECT username, password, id FROM User WHERE username=@username";
            var paramId = comm.CreateParameter();
            paramId.ParameterName = "@username";
            paramId.Value = username;
            comm.Parameters.Add(paramId);
            using (var dataR = comm.ExecuteReader()) {
                if (dataR.Read()) {
                    var password = dataR.GetString(1);
                    u = new User(username, password);
                    u.id = dataR.GetInt32(2);
                }
            }
        }

        return u;
    }
}