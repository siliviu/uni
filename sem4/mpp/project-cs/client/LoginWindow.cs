namespace project_cs;

public partial class LoginWindow : Form {

	private readonly Controller _controller;
	public LoginWindow(Controller controller) {
		InitializeComponent();
		this._controller = controller;
	}

	private void Login(object sender, EventArgs e) {
		try {
			_controller.Login(textBox1.Text, textBox2.Text);
			var userForm = new UserWindow(_controller);
			userForm.Show();
			Hide();
		}
		catch (Exception ex) {
			MessageBox.Show("Could not login.\n" + ex.Message);
		}
	}

	private void Register(object sender, EventArgs e) {
		try {
			_controller.Register(textBox1.Text, textBox2.Text);
			MessageBox.Show("Registered successfully!");
		}
		catch (Exception ex) {
			MessageBox.Show("Could not register.\n" + ex.Message);
		}
	}
}