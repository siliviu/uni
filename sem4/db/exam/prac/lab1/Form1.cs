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

			string connectionString = @"Server=DESKTOP-9M0I8IV\SQLEXPRESS;Database=S16;Integrated Security=true;TrustServerCertificate=true";
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
			dataAdapter.SelectCommand = new SqlCommand("SELECT * FROM Echipe", conn);
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
			try {
				dataAdapter.DeleteCommand = new SqlCommand("DELETE FROM Premii WHERE Pid=@Pid", conn);
				dataAdapter.DeleteCommand.Parameters.AddWithValue("@Pid", childTable[0, childTable.SelectedRows[0].Index].Value.ToString());
				conn.Open();
				dataAdapter.DeleteCommand.ExecuteNonQuery();
				conn.Close();
				if (sender != null) {
					childTable.Rows.RemoveAt(childTable.SelectedRows[0].Index);
				}
			}
			catch (Exception) {
			}
		}


		private void childTable_UserAddedRow(object sender, DataGridViewRowEventArgs e) {
			lastRow = e.Row.Index - 1;
		}

		private void childTable_RowLeave(object sender, DataGridViewCellEventArgs e) {
			childTable.CommitEdit(DataGridViewDataErrorContexts.Commit);
			if (lastRow != -1) {
				dataAdapter.InsertCommand = new SqlCommand("INSERT INTO Premii(Denumire, Descriere, Valoare, Eid, Tid) values (@Denumire,@Descriere,@Valoare,@Eid, @Tid)", conn);
				dataAdapter.InsertCommand.Parameters.AddWithValue("@Denumire", childTable[1, lastRow].Value.ToString());
				dataAdapter.InsertCommand.Parameters.AddWithValue("@Descriere", childTable[2, lastRow].Value.ToString());
				dataAdapter.InsertCommand.Parameters.AddWithValue("@Valoare", childTable[3, lastRow].Value.ToString());
				dataAdapter.InsertCommand.Parameters.AddWithValue("@Tid", childTable[5, lastRow].Value.ToString());
				dataAdapter.InsertCommand.Parameters.AddWithValue("@Eid", parentTable[0, parentTable.SelectedRows[0].Index].Value.ToString());
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
				dataAdapter.UpdateCommand = new SqlCommand("UPDATE Premii SET Denumire=@Denumire, Descriere=@Descriere, Valoare=@Valoare, Tid=@Tid WHERE Pid=@Pid", conn);
				dataAdapter.UpdateCommand.Parameters.AddWithValue("@Denumire", childTable[1, e.RowIndex].Value.ToString());
				dataAdapter.UpdateCommand.Parameters.AddWithValue("@Descriere", childTable[2, e.RowIndex].Value.ToString());
				dataAdapter.UpdateCommand.Parameters.AddWithValue("@Valoare", childTable[3, e.RowIndex].Value.ToString());
				dataAdapter.UpdateCommand.Parameters.AddWithValue("@Tid", childTable[5, e.RowIndex].Value.ToString());
				dataAdapter.UpdateCommand.Parameters.AddWithValue("@Pid", childTable[0, e.RowIndex].Value.ToString());
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

			dataAdapter.SelectCommand = new SqlCommand("SELECT * FROM Premii WHERE Eid=@Eid", conn);
			dataAdapter.SelectCommand.Parameters.AddWithValue("@Eid", parentTable[0, parentTable.SelectedRows[0].Index].Value.ToString());
			dataSet.Tables["Child"].Clear();
			dataAdapter.Fill(dataSet.Tables["Child"]);
			childTable.Columns[0].Visible = false;
			childTable.Columns[4].Visible = false;
		}

		private void label1_Click(object sender, EventArgs e) {

		}
	}
}
