using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab1 {
	public partial class Form1 : Form {
		SqlDataAdapter dataAdapter = new SqlDataAdapter();
		DataSet dataSet = new DataSet();
		SqlConnection conn;
		int lastRow = -1;
		public Form1() {
			InitializeComponent();

			string connectionString = @"Server=DESKTOP-9M0I8IV\SQLEXPRESS;Database=LanguageCentre;Integrated Security=true;TrustServerCertificate=true";
			try {
				conn = new SqlConnection(connectionString);
			}
			catch (Exception e) {
				MessageBox.Show(e.Message);
				Close();
			}
			dataSet.Tables.Add("Parent");
			dataSet.Tables.Add("Child");
			InitParent();
			parentTable.DataSource = dataSet.Tables["Parent"];
			childTable.DataSource = dataSet.Tables["Child"];
			parentTable.Columns[0].Visible = false;
			childTable.UserDeletingRow += (sender, e) => Delete(null, null);
			childTable.RowHeadersVisible = false;
		}

		private void InitParent() {
			dataAdapter.SelectCommand = new SqlCommand("SELECT * FROM Languages", conn);
			dataSet.Tables["Parent"].Clear();
			dataAdapter.Fill(dataSet.Tables["Parent"]);
			parentTable.AllowUserToAddRows = false;
			parentTable.AllowUserToDeleteRows = false;
			parentTable.AllowUserToOrderColumns = false;
			parentTable.AllowUserToResizeColumns = false;
			parentTable.RowHeadersVisible = false;
			parentTable.ReadOnly = true;
		}

		private void Delete(object sender, EventArgs e) {
			dataAdapter.DeleteCommand = new SqlCommand("DELETE FROM Courses WHERE course_id=@course_id", conn);
			dataAdapter.DeleteCommand.Parameters.AddWithValue("@course_id", childTable[0, childTable.SelectedRows[0].Index].Value.ToString());
			conn.Open();
			dataAdapter.DeleteCommand.ExecuteNonQuery();
			conn.Close();
			if (sender != null) {
				childTable.Rows.RemoveAt(childTable.SelectedRows[0].Index);
			}
		}


		private void childTable_UserAddedRow(object sender, DataGridViewRowEventArgs e) {
			lastRow = e.Row.Index - 1;
		}

		private void childTable_RowLeave(object sender, DataGridViewCellEventArgs e) {
			childTable.CommitEdit(DataGridViewDataErrorContexts.Commit);
			if (lastRow != -1) {
				dataAdapter.InsertCommand = new SqlCommand("INSERT INTO Courses(name, description, length, difficulty, language_id) values (@name,@desc,@len,@diff,@language_id)", conn);
				dataAdapter.InsertCommand.Parameters.AddWithValue("@name", childTable[1, lastRow].Value.ToString());
				dataAdapter.InsertCommand.Parameters.AddWithValue("@desc", childTable[2, lastRow].Value.ToString());
				dataAdapter.InsertCommand.Parameters.AddWithValue("@len", childTable[3, lastRow].Value.ToString());
				dataAdapter.InsertCommand.Parameters.AddWithValue("@diff", childTable[4, lastRow].Value.ToString());
				dataAdapter.InsertCommand.Parameters.AddWithValue("@language_id", parentTable[0, parentTable.SelectedRows[0].Index].Value.ToString());
				conn.Open();
				try {
					dataAdapter.InsertCommand.ExecuteNonQuery();
				}
				catch (Exception ee) {
					MessageBox.Show(ee.Message);
					dataSet.Tables["Child"].Clear();
					dataAdapter.Fill(dataSet.Tables["Child"]);
				}
				conn.Close();
				lastRow = -1;
			}
			else {
				dataAdapter.UpdateCommand = new SqlCommand("UPDATE Courses SET name=@name, description=@desc, length=@len, difficulty=@diff WHERE course_id=@course_id", conn);
				dataAdapter.UpdateCommand.Parameters.AddWithValue("@name", childTable[1, e.RowIndex].Value.ToString());
				dataAdapter.UpdateCommand.Parameters.AddWithValue("@desc", childTable[2, e.RowIndex].Value.ToString());
				dataAdapter.UpdateCommand.Parameters.AddWithValue("@len", childTable[3, e.RowIndex].Value.ToString());
				dataAdapter.UpdateCommand.Parameters.AddWithValue("@diff", childTable[4, e.RowIndex].Value.ToString());
				dataAdapter.UpdateCommand.Parameters.AddWithValue("@course_id", childTable[0, e.RowIndex].Value.ToString());
				conn.Open();
				try {
					dataAdapter.UpdateCommand.ExecuteNonQuery();
				}
				catch (Exception ee) {
					MessageBox.Show(ee.Message);
					dataSet.Tables["Child"].Clear();
					dataAdapter.Fill(dataSet.Tables["Child"]);
				}
				conn.Close();
			}
		}

		private void SelectParent(object sender, EventArgs e) {
			if (parentTable.SelectedRows.Count == 0 || parentTable.SelectedRows[0].IsNewRow)
				return;

			dataAdapter.SelectCommand = new SqlCommand("SELECT * FROM Courses WHERE language_id=@language_id", conn);
			dataAdapter.SelectCommand.Parameters.AddWithValue("@language_id", parentTable[0, parentTable.SelectedRows[0].Index].Value.ToString());
			dataSet.Tables["Child"].Clear();
			dataAdapter.Fill(dataSet.Tables["Child"]);
			childTable.Columns[0].Visible = false;
			childTable.Columns[childTable.Columns.Count - 1].Visible = false;
		}
	}
}
