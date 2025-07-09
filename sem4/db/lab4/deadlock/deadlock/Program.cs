using System.Data;
using System.Data.Common;
using System.Data.SqlClient;
using System.Transactions;

namespace deadlock {
	internal class Program {
		static void Main(string[] args) {
			const int MAX_RETRIES = 5;
			string connectionString = @"Server=DESKTOP-9M0I8IV\SQLEXPRESS;Database=LanguageCentre;Integrated Security=true;TrustServerCertificate=true";
			try {

				Console.WriteLine("Connected successfully!");
				new Thread(() => {
					SqlConnection conn = new SqlConnection(connectionString);
					SqlDataAdapter dataAdapter1 = new SqlDataAdapter();

					for (int i = 0; i < MAX_RETRIES; ++i)
						try {
							Console.WriteLine("Starting 1");
							conn.Open();
							SqlTransaction transaction = conn.BeginTransaction();
							dataAdapter1.UpdateCommand = new SqlCommand("UPDATE Languages SET name='RoRoEnglish' WHERE language_id=159", conn);
							dataAdapter1.UpdateCommand.Transaction = transaction;
							dataAdapter1.UpdateCommand.ExecuteNonQuery();
							Console.WriteLine("Update Languages 1");

							Thread.Sleep(1000);

							dataAdapter1.UpdateCommand = new SqlCommand("UPDATE Courses SET name='Course Course' WHERE course_id=57", conn);
							dataAdapter1.UpdateCommand.Transaction = transaction;
							dataAdapter1.UpdateCommand.ExecuteNonQuery();
							Console.WriteLine("Update Courses 1");
							transaction.Commit();
							conn.Close();
							Console.WriteLine("Success 1");
							break;
						}
						catch (Exception ex) {
							Console.WriteLine("Error 1:");
							Console.WriteLine(ex.Message);
							conn.Close();
						}
				}).Start();
				new Thread(() => {
					SqlConnection conn2 = new SqlConnection(connectionString);
					SqlDataAdapter dataAdapter2 = new SqlDataAdapter();

					for (int i = 0; i < MAX_RETRIES; ++i)
						try {
							Console.WriteLine("Starting 2");
							conn2.Open();
							SqlTransaction transaction2 = conn2.BeginTransaction();
							dataAdapter2.UpdateCommand = new SqlCommand("UPDATE Courses SET name='Course Course Course' WHERE course_id=57", conn2);
							dataAdapter2.UpdateCommand.Transaction = transaction2;
							dataAdapter2.UpdateCommand.ExecuteNonQuery();
							Console.WriteLine("Update Courses 2");

							Thread.Sleep(1000);

							dataAdapter2.UpdateCommand = new SqlCommand("UPDATE Languages SET name='RoRoRoEnglish' WHERE language_id=159", conn2);
							dataAdapter2.UpdateCommand.Transaction = transaction2;
							dataAdapter2.UpdateCommand.ExecuteNonQuery();
							Console.WriteLine("Update Languages 2");
							transaction2.Commit();
							conn2.Close();
							Console.WriteLine("Success 2");
							break;
						}
						catch (Exception ex) {
							Console.WriteLine("Error 2:");
							Console.WriteLine(ex.Message);
							conn2.Close();
						}
				}).Start();
			}
			catch (Exception e) {
				Console.WriteLine(e.Message);
				return;
			}
		}
	}
}