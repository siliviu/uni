using System.Data;

namespace project_cs.repo;

public class DbUtils {
    private static IDbConnection _instance = null;


    public static IDbConnection GetConnection(IDictionary<string,string> props)
    {
        if (_instance == null || _instance.State == ConnectionState.Closed)
        {
            _instance = GetNewConnection(props);
            _instance.Open();
        }
        return _instance;
    }

    private static IDbConnection GetNewConnection(IDictionary<string,string> props)
    {
			
        return db_utils.ConnectionFactory.GetInstance().CreateConnection(props);


    }

}