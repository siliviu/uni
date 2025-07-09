namespace project_cs {
	partial class UserWindow {
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
			button1 = new Button();
			label1 = new Label();
			label2 = new Label();
			comboBox1 = new ComboBox();
			comboBox2 = new ComboBox();
			dataGridView1 = new DataGridView();
			panel1 = new Panel();
			panel2 = new Panel();
			label3 = new Label();
			label4 = new Label();
			textBox1 = new TextBox();
			textBox2 = new TextBox();
			button2 = new Button();
			((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
			panel1.SuspendLayout();
			panel2.SuspendLayout();
			SuspendLayout();
			// 
			// button1
			// 
			button1.Location = new Point(18, 28);
			button1.Name = "button1";
			button1.Size = new Size(112, 34);
			button1.TabIndex = 0;
			button1.Text = "Logout";
			button1.UseVisualStyleBackColor = true;
			button1.Click += Logout;
			// 
			// label1
			// 
			label1.AutoSize = true;
			label1.Location = new Point(3, 42);
			label1.Name = "label1";
			label1.Size = new Size(99, 25);
			label1.TabIndex = 1;
			label1.Text = "Age Group";
			// 
			// label2
			// 
			label2.AutoSize = true;
			label2.Location = new Point(3, 78);
			label2.Name = "label2";
			label2.Size = new Size(121, 25);
			label2.TabIndex = 2;
			label2.Text = "Race Distance";
			// 
			// comboBox1
			// 
			comboBox1.FormattingEnabled = true;
			comboBox1.Location = new Point(143, 34);
			comboBox1.Name = "comboBox1";
			comboBox1.Size = new Size(182, 33);
			comboBox1.TabIndex = 3;
			comboBox1.SelectedIndexChanged += AgeSelect;
			// 
			// comboBox2
			// 
			comboBox2.FormattingEnabled = true;
			comboBox2.Location = new Point(143, 73);
			comboBox2.Name = "comboBox2";
			comboBox2.Size = new Size(182, 33);
			comboBox2.TabIndex = 4;
			comboBox2.SelectedIndexChanged += RaceSelect;
			// 
			// dataGridView1
			// 
			dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			dataGridView1.Location = new Point(403, 89);
			dataGridView1.Name = "dataGridView1";
			dataGridView1.RowHeadersWidth = 62;
			dataGridView1.Size = new Size(771, 561);
			dataGridView1.TabIndex = 5;
			// 
			// panel1
			// 
			panel1.Controls.Add(label1);
			panel1.Controls.Add(label2);
			panel1.Controls.Add(comboBox2);
			panel1.Controls.Add(comboBox1);
			panel1.Location = new Point(18, 89);
			panel1.Name = "panel1";
			panel1.Size = new Size(353, 150);
			panel1.TabIndex = 6;
			// 
			// panel2
			// 
			panel2.Controls.Add(label3);
			panel2.Controls.Add(label4);
			panel2.Controls.Add(textBox1);
			panel2.Controls.Add(textBox2);
			panel2.Controls.Add(button2);
			panel2.Location = new Point(21, 273);
			panel2.Name = "panel2";
			panel2.Size = new Size(350, 377);
			panel2.TabIndex = 7;
			// 
			// label3
			// 
			label3.AutoSize = true;
			label3.Location = new Point(3, 12);
			label3.Name = "label3";
			label3.Size = new Size(59, 25);
			label3.TabIndex = 0;
			label3.Text = "Name";
			// 
			// label4
			// 
			label4.AutoSize = true;
			label4.Location = new Point(3, 49);
			label4.Name = "label4";
			label4.Size = new Size(44, 25);
			label4.TabIndex = 1;
			label4.Text = "Age";
			// 
			// textBox1
			// 
			textBox1.Location = new Point(140, 9);
			textBox1.Name = "textBox1";
			textBox1.Size = new Size(182, 31);
			textBox1.TabIndex = 2;
			// 
			// textBox2
			// 
			textBox2.Location = new Point(140, 46);
			textBox2.Name = "textBox2";
			textBox2.Size = new Size(182, 31);
			textBox2.TabIndex = 3;
			textBox2.TextChanged += UpdateList;
			// 
			// button2
			// 
			button2.Location = new Point(3, 88);
			button2.Name = "button2";
			button2.Size = new Size(118, 34);
			button2.TabIndex = 4;
			button2.Text = "Add signup";
			button2.UseVisualStyleBackColor = true;
			button2.Click += Signup;
			// 
			// UserForm
			// 
			AutoScaleDimensions = new SizeF(10F, 25F);
			AutoScaleMode = AutoScaleMode.Font;
			ClientSize = new Size(1222, 688);
			Controls.Add(panel2);
			Controls.Add(panel1);
			Controls.Add(dataGridView1);
			Controls.Add(button1);
			Name = "UserWindow";
			Text = "User Menu";
			((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
			panel1.ResumeLayout(false);
			panel1.PerformLayout();
			panel2.ResumeLayout(false);
			panel2.PerformLayout();
			ResumeLayout(false);
		}

		#endregion

		private Button button1;
		private Label label1;
		private Label label2;
		private ComboBox comboBox1;
		private ComboBox comboBox2;
		private DataGridView dataGridView1;
		private Panel panel1;
		private Panel panel2;
		private Button button2;
		private TextBox textBox2;
		private TextBox textBox1;
		private Label label4;
		private Label label3;
	}
}