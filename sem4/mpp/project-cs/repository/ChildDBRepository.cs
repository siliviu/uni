using project_cs.domain;
using log4net;


namespace project_cs.repo;

public class ChildDbRepository : IChildRepository {
    private static readonly ILog Log =
        LogManager.GetLogger(System.Reflection.MethodBase.GetCurrentMethod().DeclaringType);

    readonly IDictionary<String, string> _props;

    public ChildDbRepository(IDictionary<string, string> props) {
        Log.Info("creating child repo ");
        this._props = props;
    }

    public Child Add(Child elem) {
        Log.Info("add child");
        var con = DbUtils.GetConnection(_props);
        using (var comm = con.CreateCommand()) {
            comm.CommandText = "INSERT INTO Child (name, age) VALUES(@name, @age)";
            var paramName = comm.CreateParameter();
            paramName.ParameterName = "@name";
            paramName.Value = elem.name;
            comm.Parameters.Add(paramName);

            var paramAge = comm.CreateParameter();
            paramAge.ParameterName = "@age";
            paramAge.Value = elem.age;
            comm.Parameters.Add(paramAge);
            comm.ExecuteNonQuery();

            var comm2 = con.CreateCommand();
            comm2.CommandText = "SELECT last_insert_rowid()";
            var id = (Int64)comm2.ExecuteScalar()!;
            elem.id = (int)id;
            return elem;
        }
    }

    public void Delete(int id) {
        Log.Info("delete child");
        var con = DbUtils.GetConnection(_props);
        using (var comm = con.CreateCommand()) {
            comm.CommandText = "DELETE FROM Child WHERE ID=@id";
            var paramId = comm.CreateParameter();
            paramId.ParameterName = "@id";
            paramId.Value = id;
            comm.Parameters.Add(paramId);

            comm.ExecuteNonQuery();
        }
    }

    public void Update(Child elem, int id) {
        Log.Info("update child");
        var con = DbUtils.GetConnection(_props);
        using (var comm = con.CreateCommand()) {
            comm.CommandText = "UPDATE Child SET name=@name, age=@age WHERE ID=@id";
            var paramId = comm.CreateParameter();
            paramId.ParameterName = "@id";
            paramId.Value = id;
            comm.Parameters.Add(paramId);

            var paramName = comm.CreateParameter();
            paramName.ParameterName = "@name";
            paramName.Value = elem.name;
            comm.Parameters.Add(paramName);

            var paramAge = comm.CreateParameter();
            paramAge.ParameterName = "@age";
            paramAge.Value = elem.age;
            comm.Parameters.Add(paramAge);

            comm.ExecuteNonQuery();
        }
    }

    public Child? GetById(int id) {
        Log.Info("get child");
        var con = DbUtils.GetConnection(_props);
        Child? c = null;
        using (var comm = con.CreateCommand()) {
            comm.CommandText = "SELECT name, age, id FROM child WHERE id=@id";
            var paramId = comm.CreateParameter();
            paramId.ParameterName = "@id";
            paramId.Value = id;
            comm.Parameters.Add(paramId);
            using (var dataR = comm.ExecuteReader()) {
                if (dataR.Read()) {
                    var name = dataR.GetString(0);
                    var age = dataR.GetInt32(1);
                    c = new Child(name, age);
                    c.id = id;
                }
            }
        }

        return c;
    }

    public ICollection<Child> GetAll() {
        Log.Info("get all from child");
        var con = DbUtils.GetConnection(_props);
        IList<Child> children = new List<Child>();
        using (var comm = con.CreateCommand()) {
            comm.CommandText = "SELECT name, age, id FROM child";

            using (var dataR = comm.ExecuteReader()) {
                while (dataR.Read()) {
                    var name = dataR.GetString(0);
                    var age = dataR.GetInt32(1);
                    var id = dataR.GetInt32(2);
                    var c = new Child(name, age);
                    c.id = id;
                    children.Add(c);
                }
            }
        }

        return children;
    }

    public Child? GetChildByNameAge(string name, int age) {
        Log.Info("get child");
        var con = DbUtils.GetConnection(_props);
        Child? c = null;
        using (var comm = con.CreateCommand()) {
            comm.CommandText = "SELECT name, age, id FROM child WHERE name=@name AND age=@age";
            var paramName = comm.CreateParameter();
            paramName.ParameterName = "@name";
            paramName.Value = name;
            comm.Parameters.Add(paramName);
            var paramAge = comm.CreateParameter();
            paramAge.ParameterName = "@age";
            paramAge.Value = age;
            comm.Parameters.Add(paramAge);
            using (var dataR = comm.ExecuteReader()) {
                if (dataR.Read()) {
                    c = new Child(name, age);
                    c.id = dataR.GetInt32(2);
                }
            }
        }

        return c;
    }
}