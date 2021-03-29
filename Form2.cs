using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _idTechEngine8
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Rendering in 4k");
            MessageBox.Show("Rendering in 2k");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Rendering in 1080p");
            MessageBox.Show("Rendering in 720p");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Rendering in 420p");
            MessageBox.Show("Rendering in 360p");
        }

        private void button4_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Rendering in 144p");
            MessageBox.Show("Rendering in 1000 BITS");
        }

        private void button5_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Initiating Format");
            MessageBox.Show("Formatting");
            MessageBox.Show("Done");
        }
    }
}
