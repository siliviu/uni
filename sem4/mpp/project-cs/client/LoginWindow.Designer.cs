namespace project_cs;

partial class LoginWindow {
	/// <summary>
	///  Required designer variable.
	/// </summary>
	private System.ComponentModel.IContainer components = null;

	/// <summary>
	///  Clean up any resources being used.
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
	///  Required method for Designer support - do not modify
	///  the contents of this method with the code editor.
	/// </summary>
	private void InitializeComponent() {
		textBox1 = new TextBox();
		textBox2 = new TextBox();
		label1 = new Label();
		label2 = new Label();
		button1 = new Button();
		button2 = new Button();
		SuspendLayout();
		// 
		// textBox1
		// 
		textBox1.Location = new Point(136, 44);
		textBox1.Name = "textBox1";
		textBox1.Size = new Size(150, 31);
		textBox1.TabIndex = 0;
		// 
		// textBox2
		// 
		textBox2.Location = new Point(136, 106);
		textBox2.Name = "textBox2";
		textBox2.PasswordChar = '*';
		textBox2.Size = new Size(150, 31);
		textBox2.TabIndex = 1;
		// 
		// label1
		// 
		label1.AutoSize = true;
		label1.Location = new Point(39, 44);
		label1.Name = "label1";
		label1.Size = new Size(91, 25);
		label1.TabIndex = 2;
		label1.Text = "Username";
		// 
		// label2
		// 
		label2.AutoSize = true;
		label2.Location = new Point(39, 106);
		label2.Name = "label2";
		label2.Size = new Size(87, 25);
		label2.TabIndex = 3;
		label2.Text = "Password";
		// 
		// button1
		// 
		button1.Location = new Point(39, 184);
		button1.Name = "button1";
		button1.Size = new Size(112, 34);
		button1.TabIndex = 4;
		button1.Text = "Register";
		button1.UseVisualStyleBackColor = true;
		button1.Click += Register;
		// 
		// button2
		// 
		button2.Location = new Point(174, 184);
		button2.Name = "button2";
		button2.Size = new Size(112, 34);
		button2.TabIndex = 5;
		button2.Text = "Login";
		button2.UseVisualStyleBackColor = true;
		button2.Click += Login;
		// 
		// LoginForm
		// 
		AutoScaleDimensions = new SizeF(10F, 25F);
		AutoScaleMode = AutoScaleMode.Font;
		ClientSize = new Size(332, 249);
		Controls.Add(button2);
		Controls.Add(button1);
		Controls.Add(label2);
		Controls.Add(label1);
		Controls.Add(textBox2);
		Controls.Add(textBox1);
		Name = "LoginWindow";
		Text = "Form1";
		ResumeLayout(false);
		PerformLayout();
	}

	#endregion

	private TextBox textBox1;
	private TextBox textBox2;
	private Label label1;
	private Label label2;
	private Button button1;
	private Button button2;
}