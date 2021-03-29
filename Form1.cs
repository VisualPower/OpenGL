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
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Rendering Proxy 4k");
            MessageBox.Show("Rendering Proxy 1440p");
            MessageBox.Show("Rendering Proxy 1080p");
            MessageBox.Show("Rendering Proxy 720p");

            MessageBox.Show("60FPS Template");
            MessageBox.Show("30FPS Template");

            MessageBox.Show("Rendering Bits 128-BIT");
            MessageBox.Show("Rendering Bits 64-BIT");
            MessageBox.Show("Rendering Bits 32-BIT");
            MessageBox.Show("Rendering Bits 16-BIT");

            MessageBox.Show("Presenting Rendered Specimen in Highest quality");

            MessageBox.Show("________________");
            MessageBox.Show("|              |");
            MessageBox.Show("|              |");
            MessageBox.Show("|              |");
            MessageBox.Show("|              |");
            MessageBox.Show("|              |");
            MessageBox.Show("----------------");

        }
        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Counts Vertticies");
            MessageBox.Show("Modifying Physics");
            MessageBox.Show("Creating Print");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Grid Calculation");
            MessageBox.Show("Adjusting Components Accoding to Grind");
            MessageBox.Show("FPS + 55");
        }

        private void button5_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Adding latest Animations for each objects");
            MessageBox.Show("Adding latest Physics for each objects to imply the Anim");
        }

        private void button4_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Lastlime renders");
        }

        private void button6_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Making GFX accoding scripts");
        }

        private void button7_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Opening scripting panel");
        }

        private void progressBar2_Click(object sender, EventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void progressBar3_Click(object sender, EventArgs e)
        {

        }

        private void progressBar4_Click(object sender, EventArgs e)
        {

        }

        private void progressBar5_Click(object sender, EventArgs e)
        {

        }

        private void button17_Click(object sender, EventArgs e)
        {

        }

        private void button18_Click(object sender, EventArgs e)
        {

        }

        private void button19_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Insert Preset 1");
        }

        private void button20_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Insert Preset 2");
        }

        private void button21_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Insert Preset 3");
        }

        private void button22_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Insert Preset 4");
        }

        private void button23_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Insert Preset 5");
        }

        private void button24_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Insert Preset 6");
        }

        private void button25_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Insert Preset 7");
        }

        private void button26_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Insert Preset 8");
        }

        private void button27_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Insert Preset 9");
        }

        private void button28_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Insert Preset 10");
        }

        private void button31_Click(object sender, EventArgs e)
        {

        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {

        }

        private void button36_Click(object sender, EventArgs e)
        {
            MessageBox.Show("EXCUTING RENDERING PROCESS");

            var newForm = new Form2();
            newForm.Show();
        }

        private void button37_Click(object sender, EventArgs e)
        {
            var newForm = new APIService();
            newForm.Show();
        }
    }
}
