namespace lab1 {
	partial class Form1 {
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing) {
			if (disposing && (components != null)) {
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent() {
			this.parentTable = new System.Windows.Forms.DataGridView();
			this.childTable = new System.Windows.Forms.DataGridView();
			this.button1 = new System.Windows.Forms.Button();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			((System.ComponentModel.ISupportInitialize)(this.parentTable)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.childTable)).BeginInit();
			this.SuspendLayout();
			// 
			// parentTable
			// 
			this.parentTable.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
			this.parentTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.parentTable.Location = new System.Drawing.Point(57, 88);
			this.parentTable.Name = "parentTable";
			this.parentTable.RowHeadersWidth = 62;
			this.parentTable.RowTemplate.Height = 28;
			this.parentTable.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
			this.parentTable.Size = new System.Drawing.Size(1072, 552);
			this.parentTable.TabIndex = 0;
			this.parentTable.SelectionChanged += new System.EventHandler(this.SelectParent);
			// 
			// childTable
			// 
			this.childTable.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
			this.childTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.childTable.Location = new System.Drawing.Point(57, 722);
			this.childTable.Name = "childTable";
			this.childTable.RowHeadersWidth = 62;
			this.childTable.RowTemplate.Height = 28;
			this.childTable.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
			this.childTable.Size = new System.Drawing.Size(1072, 499);
			this.childTable.TabIndex = 2;
			this.childTable.RowLeave += new System.Windows.Forms.DataGridViewCellEventHandler(this.childTable_RowLeave);
			this.childTable.UserAddedRow += new System.Windows.Forms.DataGridViewRowEventHandler(this.childTable_UserAddedRow);
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(57, 1239);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(113, 52);
			this.button1.TabIndex = 3;
			this.button1.Text = "Delete";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new System.EventHandler(this.Delete);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label1.Location = new System.Drawing.Point(47, 21);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(0, 55);
			this.label1.TabIndex = 4;
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label2.Location = new System.Drawing.Point(47, 664);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(0, 46);
			this.label2.TabIndex = 5;
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(1189, 1329);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.button1);
			this.Controls.Add(this.childTable);
			this.Controls.Add(this.parentTable);
			this.Name = "Form1";
			this.Text = "Form1";
			this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
			((System.ComponentModel.ISupportInitialize)(this.parentTable)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.childTable)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.DataGridView parentTable;
		private System.Windows.Forms.DataGridView childTable;
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
	}
}

