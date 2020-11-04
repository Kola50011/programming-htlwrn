using System;
using System.Windows.Forms;

namespace StackRechner
{
    public partial class Rechner : Form
    {
        private string _currentText;
        private StackRechner _rechner;

        public Rechner(StackRechner rechner)
        {
            InitializeComponent();
            _rechner = rechner;
            _currentText = "";
            textBox1.AcceptsReturn = true;
            textBox1.ScrollBars = ScrollBars.Vertical;
        }

        private void UpdateTextArea()
        {
            StackToText();
            textBox1.Text += _currentText;
        }

        private void StackToText()
        {
            textBox1.Text = "";
            foreach (double text in _rechner.Stack)
                textBox1.Text += text + Environment.NewLine;
        }

        private void PushIfNotEmtpy()
        {
            if (_currentText != null)
            {
                _rechner.Push(_currentText);
                _currentText = "";
                UpdateTextArea();
            }
        }

        private void Number7_Click(object sender, EventArgs e)
        {
            _currentText += @"7";
            UpdateTextArea();
        }

        private void Number8_Click(object sender, EventArgs e)
        {
            _currentText += @"8";
            UpdateTextArea();
        }

        private void Number9_Click(object sender, EventArgs e)
        {
            _currentText += @"9";
            UpdateTextArea();
        }

        private void Number6_Click(object sender, EventArgs e)
        {
            _currentText += @"6";
            UpdateTextArea();
        }

        private void Rechner_Load(object sender, EventArgs e)
        {
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
        }

        private void Number0_Click(object sender, EventArgs e)
        {
            _currentText += @"0";
            UpdateTextArea();
        }

        private void Number1_Click(object sender, EventArgs e)
        {
            _currentText += @"1";
            UpdateTextArea();
        }

        private void Number2_Click(object sender, EventArgs e)
        {
            _currentText += @"2";
            UpdateTextArea();
        }

        private void Number3_Click(object sender, EventArgs e)
        {
            _currentText += @"3";
            UpdateTextArea();
        }

        private void Number4_Click(object sender, EventArgs e)
        {
            _currentText += @"4";
            UpdateTextArea();
        }

        private void Number5_Click(object sender, EventArgs e)
        {
            _currentText += @"5";
            UpdateTextArea();
        }

        private void NumberDot_Click(object sender, EventArgs e)
        {
            _currentText += @",";
            UpdateTextArea();
        }

        private void OperationEnter_Click(object sender, EventArgs e)
        {
            _rechner.Push(_currentText);
            _currentText = "";
            UpdateTextArea();
        }

        private void OperationMult_Click(object sender, EventArgs e)
        {
            PushIfNotEmtpy();
            _rechner.Push("*");
            UpdateTextArea();
        }

        private void OperationDiv_Click(object sender, EventArgs e)
        {
            PushIfNotEmtpy();
            _rechner.Push("/");
            UpdateTextArea();
        }

        private void OperationPlus_Click(object sender, EventArgs e)
        {
            PushIfNotEmtpy();
            _rechner.Push("+");
            UpdateTextArea();
        }

        private void OperationMinus_Click(object sender, EventArgs e)
        {
            PushIfNotEmtpy();
            _rechner.Push("-");
            UpdateTextArea();
        }

        private void OperationExp_Click(object sender, EventArgs e)
        {
            PushIfNotEmtpy();
            _rechner.Push("^");
            UpdateTextArea();
        }

        private void OperationRoot_Click(object sender, EventArgs e)
        {
            PushIfNotEmtpy();
            _rechner.Push("sqr");
            UpdateTextArea();
        }

        private void OperationDelete_Click(object sender, EventArgs e)
        {
            _currentText = _currentText.Remove(_currentText.Length - 1);
            UpdateTextArea();
        }

        private void OperationClear_Click(object sender, EventArgs e)
        {
            _currentText = "";
            _rechner = new StackRechner();
            UpdateTextArea();
        }

        private void OperationE_Click(object sender, EventArgs e)
        {
            PushIfNotEmtpy();
            _rechner.Push("e");
            UpdateTextArea();
        }
    }
}