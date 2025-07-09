using System.Data.SQLite;
using System.Data;

namespace db_utils;

public class SqliteConnectionFactory : ConnectionFactory {
    public override IDbConnection CreateConnection(IDictionary<string, string> props) {
        //Mono Sqlite Connection

        // String connectionString = "DataSource=C:\\Users\\Liviu\\Documents\\p\\uni\\sem4\\mpp\\project.db,Version=3";
        var connectionString = props["ConnectionString"];
        Console.WriteLine("SQLite ---Se deschide o conexiune la  ... {0}", connectionString);
        return new SQLiteConnection(connectionString);

        // Windows SQLite Connection, fisierul .db ar trebuie sa fie in directorul debug/bin
        //String connectionString = "Data Source=tasks.db;Version=3";
        //return new SQLiteConnection(connectionString);
    }
}