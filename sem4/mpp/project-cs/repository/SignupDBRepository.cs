using project_cs.domain;

namespace project_cs.repo;

public class SignupDbRepository : ISignupRepository {
    private static readonly log4net.ILog Log =
        log4net.LogManager.GetLogger(System.Reflection.MethodBase.GetCurrentMethod().DeclaringType);

    private readonly IChildRepository _childRepository;
    readonly IDictionary<String, string> _props;

    public SignupDbRepository(IDictionary<string, string> props) {
        Log.Info("creating signup repo ");
        this._props = props;
        _childRepository = new ChildDbRepository(props);
    }

    public Signup Add(Signup elem) {
        Log.Info("add signup");
        var con = DbUtils.GetConnection(_props);
        using (var comm = con.CreateCommand()) {
            comm.CommandText =
                "INSERT INTO Signup (child_id, age_group, race_distance) VALUES (@child_id, @age_group, @race_distance)";

            var paramChild = comm.CreateParameter();
            paramChild.ParameterName = "@child_id";
            paramChild.Value = elem.child.id;
            comm.Parameters.Add(paramChild);

            var paramAge = comm.CreateParameter();
            paramAge.ParameterName = "@age_group";
            paramAge.Value = elem.ageGroup.ToString();
            comm.Parameters.Add(paramAge);

            var paramDistance = comm.CreateParameter();
            paramDistance.ParameterName = "@race_distance";
            paramDistance.Value = elem.raceDistance.ToString();
            comm.Parameters.Add(paramDistance);
            comm.ExecuteNonQuery();

            var comm2 = con.CreateCommand();
            comm2.CommandText = "SELECT last_insert_rowid()";
            var id = (Int64)comm2.ExecuteScalar()!;
            elem.id = (int)id;
            return elem;
        }
    }

    public void Delete(int id) {
        Log.Info("delete signup");
        var con = DbUtils.GetConnection(_props);
        using (var comm = con.CreateCommand()) {
            comm.CommandText = "DELETE FROM Signup WHERE ID=@id";
            var paramId = comm.CreateParameter();
            paramId.ParameterName = "@id";
            paramId.Value = id;
            comm.Parameters.Add(paramId);
            comm.ExecuteNonQuery();
        }
    }

    public void Update(Signup elem, int id) {
        Log.Info("update signup");
        var con = DbUtils.GetConnection(_props);
        using var comm = con.CreateCommand();
        comm.CommandText =
            "UPDATE Signup SET child_id=@child_id, age_group=@age_group, race_distance=@race_distance WHERE id=@id";
        var paramId = comm.CreateParameter();
        paramId.ParameterName = "@id";
        paramId.Value = id;
        comm.Parameters.Add(paramId);

        var paramChild = comm.CreateParameter();
        paramChild.ParameterName = "@child_id";
        paramChild.Value = elem.child.id;
        comm.Parameters.Add(paramChild);

        var paramAge = comm.CreateParameter();
        paramAge.ParameterName = "@age_group";
        paramAge.Value = elem.ageGroup.ToString();
        comm.Parameters.Add(paramAge);

        var paramDistance = comm.CreateParameter();
        paramDistance.ParameterName = "@race_distance";
        paramDistance.Value = elem.raceDistance.ToString();
        comm.Parameters.Add(paramDistance);

        comm.ExecuteNonQuery();
    }

    public Signup? GetById(int id) {
        Log.Info("get signup");
        var con = DbUtils.GetConnection(_props);
        Signup? s = null;
        using (var comm = con.CreateCommand()) {
            comm.CommandText = "SELECT child_id, age_group, race_distance, id FROM Signup WHERE id=@id";
            var paramId = comm.CreateParameter();
            paramId.ParameterName = "@id";
            paramId.Value = id;
            comm.Parameters.Add(paramId);
            using (var dataR = comm.ExecuteReader()) {
                if (dataR.Read()) {
                    var child = _childRepository.GetById(dataR.GetInt32(0))!;
                    Enum.TryParse(dataR.GetString(1), out AgeGroup ageGroup);
                    Enum.TryParse(dataR.GetString(2), out RaceDistance raceDistance);
                    s = new Signup(child, ageGroup, raceDistance);
                    s.id = id;
                }
            }
        }

        return s;
    }

    public ICollection<Signup> GetAll() {
        Log.Info("get all from signup");
        var con = DbUtils.GetConnection(_props);
        IList<Signup> signups = new List<Signup>();
        using (var comm = con.CreateCommand()) {
            comm.CommandText = "SELECT child_id, age_group, race_distance, id FROM Signup";

            using (var dataR = comm.ExecuteReader()) {
                while (dataR.Read()) {
                    var child = _childRepository.GetById(dataR.GetInt32(0))!;
                    Enum.TryParse(dataR.GetString(1), out AgeGroup ageGroup);
                    Enum.TryParse(dataR.GetString(2), out RaceDistance raceDistance);
                    var s = new Signup(child, ageGroup, raceDistance);
                    s.id = dataR.GetInt32(3);
                    signups.Add(s);
                }
            }
        }

        return signups;
    }

    public ICollection<Child> GetChildrenByRace(AgeGroup age, RaceDistance distance) {
        Log.Info("get children by race");
        var con = DbUtils.GetConnection(_props);
        IList<Child> children = new List<Child>();
        using (var comm = con.CreateCommand()) {
            comm.CommandText =
                "SELECT child_id, age_group, race_distance, id FROM Signup WHERE age_group=@age_group AND race_distance=@race_distance";
            var paramAgeGroup = comm.CreateParameter();
            paramAgeGroup.ParameterName = "@age_group";
            paramAgeGroup.Value = age.ToString();
            comm.Parameters.Add(paramAgeGroup);
            var paramRaceDistance = comm.CreateParameter();
            paramRaceDistance.ParameterName = "@race_distance";
            paramRaceDistance.Value = distance.ToString();
            comm.Parameters.Add(paramRaceDistance);
            using (var dataR = comm.ExecuteReader()) {
                while (dataR.Read()) {
                    var c = _childRepository.GetById(dataR.GetInt32(0))!;
                    children.Add(c);
                }
            }
        }

        return children;
    }

    public int GetChildSignups(int id) {
        Log.Info("get no of signups");
        var con = DbUtils.GetConnection(_props);
        using (var comm = con.CreateCommand()) {
            comm.CommandText = "SELECT COUNT(*) FROM Signup WHERE child_id=@child_id";
            var paramChildId = comm.CreateParameter();
            paramChildId.ParameterName = "@child_id";
            paramChildId.Value = id;
            comm.Parameters.Add(paramChildId);
            var dataR = comm.ExecuteScalar();
            return Convert.ToInt32(dataR!.ToString());
        }
    }
}