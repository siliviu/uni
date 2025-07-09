using project_cs.domain;
using project_cs.service;
using project_cs.utils;

namespace project_cs {
    public partial class UserWindow : Form {
        private readonly Controller _controller;
        UserService _userService;


        public UserWindow(Controller controller) {
            InitializeComponent();
            _controller = controller;
            foreach (AgeGroup ageGroup in Enum.GetValues(typeof(AgeGroup)))
                comboBox1.Items.Add(EnumHandler.GetStringFromGroup(ageGroup));
            _controller.UpdateEvent += UserUpdate;
        }

        public void UserUpdate(object sender, EventArgs e) {
            dataGridView1.BeginInvoke(new UpdateCallback(UpdateTable));
        }

        private void UpdateTable() {
            if (comboBox1.SelectedItem == null || comboBox2.SelectedItem == null) return;
            dataGridView1.DataSource = null;
            var c = _controller.SearchChildren((string)comboBox1.SelectedItem, (string)comboBox2.SelectedItem);
            dataGridView1.DataSource = c;
            dataGridView1.Columns["Name"].DisplayIndex = 0;
            dataGridView1.Columns["Age"].DisplayIndex = 1;
            dataGridView1.Columns["Signups"].DisplayIndex = 2;
            dataGridView1.RowHeadersVisible = false;
            dataGridView1.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
        }

        public delegate void UpdateCallback();


        private void Logout(object sender, EventArgs e) {
            _controller.Logout();
            Application.Exit();
        }

        private void AgeSelect(object sender, EventArgs e) {
            comboBox2.Items.Clear();
            comboBox2.ResetText();
            var ageGroup = (AgeGroup)EnumHandler.GetGroupFromString((string)comboBox1.SelectedItem)!;
            foreach (var raceDistance in EnumHandler.GetRacesFromAge(ageGroup))
                comboBox2.Items.Add(EnumHandler.GetStringFromDistance(raceDistance));
        }

        private void RaceSelect(object sender, EventArgs e) {
            UpdateTable();
        }

        private void Signup(object sender, EventArgs e) {
            try {
                var raceDistanceList = new List<RaceDistance>();
                var ageValue = int.Parse(textBox2.Text);
                var ageGroup = EnumHandler.GetGroupFromAge(ageValue);
                if (ageGroup == null)
                    throw new Exception("Invalid age group");
                var i = 5;
                foreach (var raceDistance in EnumHandler.GetRacesFromAge(ageGroup.Value)) {
                    var checkBox = (CheckBox)panel2.Controls[i++];
                    if (checkBox.Checked)
                        raceDistanceList.Add(raceDistance);
                }

                if (raceDistanceList.Count > 2)
                    throw new Exception("Cannot sign up to more than two races.");
                foreach (var raceDistance in raceDistanceList)
                    _controller.SignUpChild(textBox1.Text, ageValue, raceDistance, ageGroup);
                // UpdateTable();
            }
            catch (Exception ex) {
                MessageBox.Show("Could not sign up child.\n" + ex.Message);
            }
        }

        private void UpdateList(object sender, EventArgs e) {
            try {
                while (panel2.Controls.Count > 5) {
                    panel2.Controls.RemoveAt(5);
                }

                var ageGroup = EnumHandler.GetGroupFromAge(int.Parse(textBox2.Text));
                if (ageGroup == null)
                    return;
                foreach (var raceDistance in EnumHandler.GetRacesFromAge(ageGroup.Value)) {
                    panel2.Controls.Add(new CheckBox {
                        Text = EnumHandler.GetStringFromDistance(raceDistance),
                        Location = new Point(label3.Left, panel2.Controls[panel2.Controls.Count - 1].Bottom + 10)
                    });
                }
            }
            catch (Exception ex) { }
        }
    }
}