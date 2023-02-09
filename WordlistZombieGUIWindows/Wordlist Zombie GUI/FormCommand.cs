using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Wordlist_Zombie_GUI
{
    public partial class FormCommand : Form
    {
        public FormCommand()
        {
            InitializeComponent();
        }

        private void FormCommand_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (e.CloseReason == CloseReason.UserClosing)
            {
                e.Cancel = true;
                Hide();
            }
        }

        private void buttonCCopyToClipboard_Click(object sender, EventArgs e)
        {
            if (textBoxCommand.Text != "") Clipboard.SetText(textBoxCommand.Text);
        }

        private void buttonCClose_Click(object sender, EventArgs e)
        {
            Hide();
        }
    }
}
