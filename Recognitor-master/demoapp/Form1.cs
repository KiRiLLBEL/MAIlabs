using System;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

namespace demoapp
{
    public partial class Form1 : Form, IView
    {
        private double[] _inputPixels = new double[15] { 0d, 0d, 0d, 0d, 0d, 0d, 0d, 0d, 0d, 0d, 0d, 0d, 0d, 0d, 0d };
        public double[] InputPixels { get => _inputPixels; }

        public double[] NetOutput { set => MessageBox.Show(value.ToList().IndexOf(value.Max()).ToString()); }

        public event EventHandler<EventArgs> GotResult;

        public Form1() => InitializeComponent();
        private void Form1_Load(object sender, EventArgs e) { }

        private void recognizebutton_Click(object sender, EventArgs e) => GotResult?.Invoke(this, EventArgs.Empty);
        private void ChangeState(Button b, int index)
        {
            if (b.BackColor == Color.Black)
            {
                b.BackColor = Color.White;
                _inputPixels[index] = 1d;
            }
            else if (b.BackColor == Color.White)
            {
                b.BackColor = Color.Black;
                _inputPixels[index] = 0d;
            }
        }
        private void button1_Click(object sender, EventArgs e) => ChangeState(button1, 0);
        private void button2_Click(object sender, EventArgs e) => ChangeState(button2, 1);
        private void button3_Click(object sender, EventArgs e) => ChangeState(button3, 2);
        private void button4_Click(object sender, EventArgs e) => ChangeState(button4, 3);
        private void button5_Click(object sender, EventArgs e) => ChangeState(button5, 4);
        private void button6_Click(object sender, EventArgs e) => ChangeState(button6, 5);
        private void button7_Click(object sender, EventArgs e) => ChangeState(button7, 6);
        private void button8_Click(object sender, EventArgs e) => ChangeState(button8, 7);
        private void button9_Click(object sender, EventArgs e) => ChangeState(button9, 8);
        private void button10_Click(object sender, EventArgs e) => ChangeState(button10, 9);
        private void button11_Click(object sender, EventArgs e) => ChangeState(button11, 10);
        private void button12_Click(object sender, EventArgs e) => ChangeState(button12, 11);
        private void button13_Click(object sender, EventArgs e) => ChangeState(button13, 12);
        private void button14_Click(object sender, EventArgs e) => ChangeState(button14, 13);
        private void button15_Click(object sender, EventArgs e) => ChangeState(button15, 14);
    }
}
