using Microsoft.Data.SqlClient;

namespace sem1 {
	internal class Program {
		static void Main(string[] args) {
			Console.WriteLine("Hello, World!");
			try {
				string connectionString = @"Server=DESKTOP-9M0I8IV\SQLEXPRESS;Database=SGBDIR;Integrated Security=true;TrustServerCertificate=true";
				using (SqlConnection connection = new SqlConnection(connectionString)) {
					Console.WriteLine(connection.State);
					connection.Open();
					Console.WriteLine(connection.State);
					SqlCommand insertCommand = new SqlCommand("INSERT INTO Cadouri (descriere, posesor, pret) VALUES " +
						"(@desc1, @posesor1, @pret1), " +
						"(@desc2, @posesor2, @pret2), " +
						"(@desc3, @posesor3, @pret3);",
						connection);
					insertCommand.Parameters.AddWithValue("@desc1", "carbuni");
					insertCommand.Parameters.AddWithValue("@posesor1", "tata");
					insertCommand.Parameters.AddWithValue("@pret1", "5");
					insertCommand.Parameters.AddWithValue("@desc2", "gratar");
					insertCommand.Parameters.AddWithValue("@posesor2", "unchiul");
					insertCommand.Parameters.AddWithValue("@pret2", "10");
					insertCommand.Parameters.AddWithValue("@desc3", "mici");
					insertCommand.Parameters.AddWithValue("@posesor3", "eu");
					insertCommand.Parameters.AddWithValue("@pret3", "15");
					int insertRowCount = insertCommand.ExecuteNonQuery();
					Console.WriteLine(insertRowCount);

					SqlCommand selectCommand = new SqlCommand("SELECT descriere, posesor, pret FROM Cadouri", connection);
					SqlDataReader reader = selectCommand.ExecuteReader();
					if (reader.HasRows) {
						Console.WriteLine("Stuff");
						while (reader.Read()) {
							Console.WriteLine("{0} {1} {2}", reader.GetString(0), reader.GetString(1), reader.GetFloat(2));
						}
					}
					else
						Console.WriteLine("No stuff");
					reader.Close();
				
					SqlCommand updateCommand = new SqlCommand("UPDATE Cadouri SET pret=@pretnou WHERE descriere=@desc", connection);
					updateCommand.Parameters.AddWithValue("@pretnou", 9.99);
					updateCommand.Parameters.AddWithValue("@desc", "mici");
					int updateRowCount = updateCommand.ExecuteNonQuery();
					Console.WriteLine(updateRowCount);

					SqlCommand deleteCommand = new SqlCommand("DELETE FROM Cadouri WHERE descriere=@desc", connection);
					deleteCommand.Parameters.AddWithValue("@desc", "carbuni");
					int deleteRowCount = deleteCommand.ExecuteNonQuery();
					Console.WriteLine(deleteRowCount);

					reader = selectCommand.ExecuteReader();
					if (reader.HasRows) {
						Console.WriteLine("Stuff");
						while (reader.Read()) {
							Console.WriteLine("{0} {1} {2}", reader.GetString(0), reader.GetString(1), reader.GetFloat(2));
						}
					}
					else
						Console.WriteLine("No stuff");
					reader.Close();
				}
			}
			catch (Exception ex) {
				Console.WriteLine("Exception with message {0}", ex.Message);
			}
		}
	}
}