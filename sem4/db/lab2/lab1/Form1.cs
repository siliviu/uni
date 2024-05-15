using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Linq;

namespace lab1 {
	public partial class Form1 : Form {
		string ServerLocation, DatabaseName, ParentTableName, ChildTableName;
		string ParentKey, ChildKey;
		SqlDataAdapter dataAdapter = new SqlDataAdapter(), dataAdapter2 = new SqlDataAdapter();
		DataSet dataSet = new DataSet();
		SqlConnection conn;
		int lastRow = -1;
		public Form1() {
			InitializeComponent();
			Configuration configManager = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);
			KeyValueConfigurationCollection confCollection = configManager.AppSettings.Settings;
			ServerLocation = confCollection["server"].Value;
			DatabaseName = confCollection["database"].Value;
			ParentTableName = confCollection["parent"].Value;
			ChildTableName = confCollection["child"].Value;
			string connectionString = $@"Server={ServerLocation};Database={DatabaseName};Integrated Security=true;TrustServerCertificate=true";
			try {
				conn = new SqlConnection(connectionString);
			}
			catch (Exception e) {
				MessageBox.Show(e.Message);
				Close();
			}
			label1.Text = ParentTableName;
			label2.Text = ChildTableName;
			dataSet.Tables.Add("Parent");
			dataSet.Tables.Add("Child");
			InitParent();
			parentTable.DataSource = dataSet.Tables["Parent"];
			childTable.DataSource = dataSet.Tables["Child"];
			parentTable.Columns[ParentKey].Visible = false;
			childTable.UserDeletingRow += (sender, e) => Delete(null, null);
			childTable.RowHeadersVisible = false;
		}

		private void InitParent() {
			dataAdapter.SelectCommand = new SqlCommand($"SELECT * FROM {ParentTableName}", conn);
			dataSet.Tables["Parent"].Clear();
			dataAdapter.Fill(dataSet.Tables["Parent"]);
			dataAdapter.FillSchema(dataSet.Tables["Parent"], SchemaType.Mapped);
			ParentKey = dataSet.Tables["Parent"].PrimaryKey[0].ColumnName;
			parentTable.AllowUserToAddRows = false;
			parentTable.AllowUserToDeleteRows = false;
			parentTable.AllowUserToOrderColumns = false;
			parentTable.AllowUserToResizeColumns = false;
			parentTable.RowHeadersVisible = false;
			parentTable.ReadOnly = true;
		}

		private void Delete(object sender, EventArgs e) {
			dataAdapter.DeleteCommand = new SqlCommand($"DELETE FROM {ChildTableName} WHERE {ChildKey}=@ChildKey", conn);
			dataAdapter.DeleteCommand.Parameters.AddWithValue("@ChildKey", childTable[ChildKey, childTable.SelectedRows[0].Index].Value.ToString());
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
			if (!childTable.IsCurrentRowDirty)
				return;
			childTable.CommitEdit(DataGridViewDataErrorContexts.Commit);
			try {
				if (lastRow != -1) {
					string UpdateString = $"INSERT INTO {ChildTableName} (";
					foreach (DataGridViewColumn column in childTable.Columns) {
						string name = column.Name;
						if (name != ChildKey)
							UpdateString += $"{name},";
					}
					UpdateString = UpdateString.Substring(0, UpdateString.Length - 1) + $") VALUES(";
					foreach (DataGridViewColumn column in childTable.Columns) {
						string name = column.Name;
						if (name != ChildKey)
							UpdateString += $"@{name},";
					}
					UpdateString = UpdateString.Substring(0, UpdateString.Length - 1) + $")";
					dataAdapter.InsertCommand = new SqlCommand(UpdateString, conn);
					foreach (DataGridViewColumn column in childTable.Columns) {
						string name = column.Name;
						if (name != ChildKey && name != ParentKey)
							dataAdapter.InsertCommand.Parameters.AddWithValue($"@{name}", childTable[name, e.RowIndex].Value.ToString());
					}
					dataAdapter.InsertCommand.Parameters.AddWithValue($"@{ParentKey}", parentTable[ParentKey, parentTable.SelectedRows[0].Index].Value.ToString());
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
					string UpdateString = $"UPDATE {ChildTableName} SET ";
					foreach (DataGridViewColumn column in childTable.Columns) {
						string name = column.Name;
						if (name != ParentKey && name != ChildKey)
							UpdateString += $"{name}=@{name},";
					}
					UpdateString = UpdateString.Substring(0, UpdateString.Length - 1) + $" WHERE {ChildKey}=@{ChildKey}";
					dataAdapter.UpdateCommand = new SqlCommand(UpdateString, conn);
					foreach (DataGridViewColumn column in childTable.Columns) {
						string name = column.Name;
						if (name != ParentKey)
							dataAdapter.UpdateCommand.Parameters.AddWithValue($"@{name}", childTable[name, e.RowIndex].Value.ToString());
					}
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
			catch (Exception ex) {
				MessageBox.Show(ex.Message);
				dataSet.Tables["Child"].Clear();
				dataAdapter.Fill(dataSet.Tables["Child"]);
				dataAdapter.FillSchema(dataSet.Tables["Child"], SchemaType.Mapped);
				conn.Close();
			}
		}

		private void SelectParent(object sender, EventArgs e) {
			if (parentTable.SelectedRows.Count == 0 || parentTable.SelectedRows[0].IsNewRow)
				return;
			dataAdapter.SelectCommand = new SqlCommand($"SELECT * FROM {ChildTableName} WHERE {ParentKey}=@ParentKey", conn);
			dataAdapter.SelectCommand.Parameters.AddWithValue("@ParentKey", parentTable[ParentKey, parentTable.SelectedRows[0].Index].Value.ToString());
			dataSet.Tables["Child"].Clear();
			dataAdapter.Fill(dataSet.Tables["Child"]);
			dataAdapter.FillSchema(dataSet.Tables["Child"], SchemaType.Mapped);
			ChildKey = dataSet.Tables["Child"].PrimaryKey[0].ColumnName;
			childTable.Columns[ChildKey].Visible = false;
			childTable.Columns[ParentKey].Visible = false;
		}
	}
}
