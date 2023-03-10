using System;
using System.Diagnostics;
using System.Security.Policy;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace Wordlist_Zombie_GUI
{
    public partial class Form1 : Form
    {
        FormCommand commandDlg = new FormCommand();

        public Form1()
        {
            InitializeComponent();
            LoadSettings();
        }

        private void openFileDialogWGMarkovFile_FileOk(object sender, System.ComponentModel.CancelEventArgs e)
        {
            editWGMarkovFile.Text = openFileDialogWGMarkovFile.FileName;
        }

        private void openFileDialogWGWordlistMapFile_FileOk(object sender, System.ComponentModel.CancelEventArgs e)
        {
            editWGWordlistMapFile.Text = openFileDialogWGWordlistMapFile.FileName;
        }

        private void saveFileDialogWGOutputFile_FileOk(object sender, System.ComponentModel.CancelEventArgs e)
        {
            editWGOutputFile.Text = saveFileDialogWGOutputFile.FileName;
        }

        private void buttonWGMarkovFileBrowse_Click(object sender, EventArgs e)
        {
            openFileDialogWGMarkovFile.ShowDialog();
        }

        private void buttonWGWordlistMapFileBrowse_Click(object sender, EventArgs e)
        {
            openFileDialogWGWordlistMapFile.ShowDialog();
        }

        private void buttonWGOutputFileBrowse_Click(object sender, EventArgs e)
        {
            saveFileDialogWGOutputFile.ShowDialog();
        }

        private void openFileDialogMCTWordlist_FileOk(object sender, System.ComponentModel.CancelEventArgs e)
        {
            editMCTWordlist.Text = openFileDialogMCTWordlist.FileName;
        }

        private void saveFileDialogMCTOutput_FileOk(object sender, System.ComponentModel.CancelEventArgs e)
        {
            editMCTOutput.Text = saveFileDialogMCTOutput.FileName;
        }

        private void buttonMCTWordlistBrowse_Click(object sender, EventArgs e)
        {
            openFileDialogMCTWordlist.ShowDialog();
        }

        private void buttonMCTOutputBrowse_Click(object sender, EventArgs e)
        {
            saveFileDialogMCTOutput.ShowDialog();
        }

        private void openFileDialogWMWordlist_FileOk(object sender, System.ComponentModel.CancelEventArgs e)
        {
            editWMWordlist.Text = openFileDialogWMWordlist.FileName;
        }

        private void saveFileDialogWMOutput_FileOk(object sender, System.ComponentModel.CancelEventArgs e)
        {
            editWMOutput.Text = saveFileDialogWMOutput.FileName;
        }

        private void buttonWMWordlistBrowse_Click(object sender, EventArgs e)
        {
            openFileDialogWMWordlist.ShowDialog();
        }

        private void buttonWMOutputBrowse_Click(object sender, EventArgs e)
        {
            saveFileDialogWMOutput.ShowDialog();
        }

        private void openFileDialogSWordlistGenerator_FileOk(object sender, System.ComponentModel.CancelEventArgs e)
        {
            editSWordlistGenerator.Text = openFileDialogSWordlistGenerator.FileName;
        }

        private void openFileDialogSMarkovChainThing_FileOk(object sender, System.ComponentModel.CancelEventArgs e)
        {
            editSMarkovChainThing.Text = openFileDialogSMarkovChainThing.FileName;
        }

        private void openFileDialogSWordlistMapper_FileOk(object sender, System.ComponentModel.CancelEventArgs e)
        {
            editSWordlistMapper.Text = openFileDialogSWordlistMapper.FileName;
        }

        private void buttonSWordlistGeneratorBrowse_Click(object sender, EventArgs e)
        {
            openFileDialogSWordlistGenerator.ShowDialog();
        }

        private void buttonSMarkovChainThingBrowse_Click(object sender, EventArgs e)
        {
            openFileDialogSMarkovChainThing.ShowDialog();
        }

        private void buttonSWordlistMapperBrowse_Click(object sender, EventArgs e)
        {
            openFileDialogSWordlistMapper.ShowDialog();
        }

        private void SaveSettings()
        {
            JsonSyncSettings jss = new JsonSyncSettings();

            jss.jsonEditWGMarkovFile = editWGMarkovFile.Text;
            jss.jsonEditWGWordlistMapFile = editWGWordlistMapFile.Text;
            jss.jsonEditWGOutputFile = editWGOutputFile.Text;
            jss.jsonEditWGNumber = editWGNumber.Text;
            jss.jsonEditWGThreads = editWGThreads.Text;
            jss.jsonCheckboxWGMinWordLength = checkboxWGMinWordLength.Checked;
            jss.jsonCheckboxWGMaxWordLength = checkboxWGMaxWordLength.Checked;
            jss.jsonEditWGMinWordLength = editWGMinWordLength.Text;
            jss.jsonEditWGMaxWordLength = editWGMaxWordLength.Text;
            jss.jsonRadioButtonWeightedOutput = radioButtonWeightedOutput.Checked;
            jss.jsonRadioButtonHalfWeightedOutput = radioButtonHalfWeightedOutput.Checked;
            jss.jsonRadioButtonUnweightedOutput = radioButtonUnweightedOutput.Checked;
            jss.jsonEditMCTWordlist = editMCTWordlist.Text;
            jss.jsonEditMCTOutput = editMCTOutput.Text;
            jss.jsonEditWMWordlist = editWMWordlist.Text;
            jss.jsonEditWMOutput = editWMOutput.Text;
            jss.jsonEditSWordlistGenerator = editSWordlistGenerator.Text;
            jss.jsonEditSMarkovChainThing = editSMarkovChainThing.Text;
            jss.jsonEditSWordlistMapper = editSWordlistMapper.Text;


            string fileName = Path.GetDirectoryName(Application.ExecutablePath) + @"\settings.json"; //Could also use AppDomain.CurrentDomain.BaseDirectory

            using (FileStream fs = File.Create(fileName))
            {
                byte[] jsonUtf8Bytes;
                var options = new JsonSerializerOptions
                {
                    WriteIndented = true
                };
                jsonUtf8Bytes = JsonSerializer.SerializeToUtf8Bytes(jss, options);

                fs.Write(jsonUtf8Bytes, 0, jsonUtf8Bytes.Length);
                //InfoUpdate("Settings saved successfully.");
            }
        }

        private void LoadSettings()
        {
            string fileName = Path.GetDirectoryName(Application.ExecutablePath) + @"\settings.json"; //Could also use AppDomain.CurrentDomain.BaseDirectory

            if (File.Exists(fileName))
            {
                using (FileStream fs = File.OpenRead(fileName))
                {
                    FileInfo FileProps = new FileInfo(fileName);
                    byte[] jsonUtf8Bytes = new byte[FileProps.Length];
                    fs.Read(jsonUtf8Bytes, 0, jsonUtf8Bytes.Length);

                    var readOnlySpan = new ReadOnlySpan<byte>(jsonUtf8Bytes);
                    JsonSyncSettings jss = new JsonSyncSettings();
                    jss = JsonSerializer.Deserialize<JsonSyncSettings>(readOnlySpan);

                    editWGMarkovFile.Text = jss.jsonEditWGMarkovFile;
                    editWGWordlistMapFile.Text = jss.jsonEditWGWordlistMapFile;
                    editWGOutputFile.Text = jss.jsonEditWGOutputFile;
                    editWGNumber.Text = jss.jsonEditWGNumber;
                    editWGThreads.Text = jss.jsonEditWGThreads;
                    checkboxWGMinWordLength.Checked = jss.jsonCheckboxWGMinWordLength;
                    checkboxWGMaxWordLength.Checked = jss.jsonCheckboxWGMaxWordLength;
                    editWGMinWordLength.Text = jss.jsonEditWGMinWordLength;
                    editWGMaxWordLength.Text = jss.jsonEditWGMaxWordLength;
                    radioButtonWeightedOutput.Checked = jss.jsonRadioButtonWeightedOutput;
                    radioButtonHalfWeightedOutput.Checked = jss.jsonRadioButtonHalfWeightedOutput;
                    radioButtonUnweightedOutput.Checked = jss.jsonRadioButtonUnweightedOutput;
                    editMCTWordlist.Text = jss.jsonEditMCTWordlist;
                    editMCTOutput.Text = jss.jsonEditMCTOutput;
                    editWMWordlist.Text = jss.jsonEditWMWordlist;
                    editWMOutput.Text = jss.jsonEditWMOutput;
                    editSWordlistGenerator.Text = jss.jsonEditSWordlistGenerator;
                    editSMarkovChainThing.Text = jss.jsonEditSMarkovChainThing;
                    editSWordlistMapper.Text = jss.jsonEditSWordlistMapper;
                }
            }
            else
            {
                editSWordlistGenerator.Text = Path.GetDirectoryName(Application.ExecutablePath) + @"\WordlistGenerator.exe";
                editSMarkovChainThing.Text = Path.GetDirectoryName(Application.ExecutablePath) + @"\MarkovChainThing.exe";
                editSWordlistMapper.Text = Path.GetDirectoryName(Application.ExecutablePath) + @"\WordlistMapper.exe";
            }
        }

        private void buttonSettingsResetToDefault_Click(object sender, EventArgs e)
        {
            editSWordlistGenerator.Text = Path.GetDirectoryName(Application.ExecutablePath) + @"\WordlistGenerator.exe";
            editSMarkovChainThing.Text = Path.GetDirectoryName(Application.ExecutablePath) + @"\MarkovChainThing.exe";
            editSWordlistMapper.Text = Path.GetDirectoryName(Application.ExecutablePath) + @"\WordlistMapper.exe";
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            SaveSettings();
        }

        private void buttonWGGenerate_Click(object sender, EventArgs e)
        {
            Process p = new Process();
            p.StartInfo.UseShellExecute = true;

            string weight = "";
            if (radioButtonUnweightedOutput.Checked == true) weight = " --unweighted";
            else if (radioButtonHalfWeightedOutput.Checked == true) weight = " --halfweighted";

            string threads = "";
            if ((editWGThreads.Text != "50") && (editWGThreads.Text != "")) threads = " --threads " + editWGThreads.Text;

            string minWordLength = "";
            if ((checkboxWGMinWordLength.Checked == true) && (editWGMinWordLength.Text != "")) minWordLength = " --minwordlength " + editWGMinWordLength.Text;

            string maxWordLength = "";
            if ((checkboxWGMaxWordLength.Checked == true) && (editWGMaxWordLength.Text != "")) maxWordLength = " --maxwordlength " + editWGMaxWordLength.Text;

            p.StartInfo.Arguments = "/K \"\"" + editSWordlistGenerator.Text + "\" --number " + editWGNumber.Text + " --markov \"" + editWGMarkovFile.Text + "\" --wordmap \"" + editWGWordlistMapFile.Text + "\" --output \"" + editWGOutputFile.Text + "\"" + weight + threads + minWordLength + maxWordLength + "\"";
            p.StartInfo.FileName = "cmd";
            p.Start();
        }

        private void buttonMCTGenerate_Click(object sender, EventArgs e)
        {
            Process p = new Process();
            p.StartInfo.UseShellExecute = true;
            p.StartInfo.Arguments = "/K \"\"" + editSMarkovChainThing.Text + "\" --wordlist \"" + editMCTWordlist.Text + "\" --output \"" + editMCTOutput.Text + "\"\"";
            p.StartInfo.FileName = "cmd";
            p.Start();
        }

        private void buttonWMGenerate_Click(object sender, EventArgs e)
        {
            Process p = new Process();
            p.StartInfo.UseShellExecute = true;
            p.StartInfo.Arguments = "/K \"\"" + editSWordlistMapper.Text + "\" --wordlist \"" + editWMWordlist.Text + "\" --output \"" + editWMOutput.Text + "\"\"";
            p.StartInfo.FileName = "cmd";
            p.Start();
        }

        private void checkboxMinWordLength_CheckedChanged(object sender, EventArgs e)
        {
            if (checkboxWGMinWordLength.Checked == true) editWGMinWordLength.Enabled = true;
            else editWGMinWordLength.Enabled = false;
        }

        private void checkboxWGMaxWordLength_CheckedChanged(object sender, EventArgs e)
        {
            if (checkboxWGMaxWordLength.Checked == true) editWGMaxWordLength.Enabled = true;
            else editWGMaxWordLength.Enabled = false;
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            Process.Start(new ProcessStartInfo { FileName = "https://github.com/MrGITit/Wordlist-Zombie", UseShellExecute = true });
        }

        private void buttonWGCommand_Click(object sender, EventArgs e)
        {
            Point p = new Point(this.Left + this.Width / 2 - commandDlg.Width / 2, this.Top + this.Height / 2 - commandDlg.Height / 2);
            commandDlg.Location = p;

            string weight = "";
            if (radioButtonUnweightedOutput.Checked == true) weight = " --unweighted";
            else if (radioButtonHalfWeightedOutput.Checked == true) weight = " --halfweighted";

            string threads = "";
            if ((editWGThreads.Text != "50") && (editWGThreads.Text != "")) threads = " --threads " + editWGThreads.Text;

            string minWordLength = "";
            if ((checkboxWGMinWordLength.Checked == true) && (editWGMinWordLength.Text != "")) minWordLength = " --minwordlength " + editWGMinWordLength.Text;

            string maxWordLength = "";
            if ((checkboxWGMaxWordLength.Checked == true) && (editWGMaxWordLength.Text != "")) maxWordLength = " --maxwordlength " + editWGMaxWordLength.Text;

            commandDlg.textBoxCommand.Text = "\"" + editSWordlistGenerator.Text + "\" --number " + editWGNumber.Text + " --markov \"" + editWGMarkovFile.Text + "\" --wordmap \"" + editWGWordlistMapFile.Text + "\" --output \"" + editWGOutputFile.Text + "\"" + weight + threads + minWordLength + maxWordLength;

            commandDlg.Show();
        }

        private void buttonMCCommand_Click(object sender, EventArgs e)
        {
            Point p = new Point(this.Left + this.Width / 2 - commandDlg.Width / 2, this.Top + this.Height / 2 - commandDlg.Height / 2);
            commandDlg.Location = p;

            commandDlg.textBoxCommand.Text = "\"" + editSMarkovChainThing.Text + "\" --wordlist \"" + editMCTWordlist.Text + "\" --output \"" + editMCTOutput.Text + "\"";

            commandDlg.Show();
        }

        private void buttonWMCommand_Click(object sender, EventArgs e)
        {
            Point p = new Point(this.Left + this.Width / 2 - commandDlg.Width / 2, this.Top + this.Height / 2 - commandDlg.Height / 2);
            commandDlg.Location = p;

            commandDlg.textBoxCommand.Text = "\"" + editSWordlistMapper.Text + "\" --wordlist \"" + editWMWordlist.Text + "\" --output \"" + editWMOutput.Text + "\"";

            commandDlg.Show();
        }
    }

    public class JsonSyncSettings
    {
        public string jsonEditWGMarkovFile { get; set; }
        public string jsonEditWGWordlistMapFile { get; set; }
        public string jsonEditWGOutputFile { get; set; }
        public string jsonEditWGNumber { get; set; }
        public string jsonEditWGThreads { get; set; }
        public bool jsonCheckboxWGMinWordLength { get; set; }
        public bool jsonCheckboxWGMaxWordLength { get; set; }
        public string jsonEditWGMinWordLength { get; set; }
        public string jsonEditWGMaxWordLength { get; set; }
        public bool jsonRadioButtonWeightedOutput { get; set; }
        public bool jsonRadioButtonHalfWeightedOutput { get; set; }
        public bool jsonRadioButtonUnweightedOutput { get; set; }
        public string jsonEditMCTWordlist { get; set; }
        public string jsonEditMCTOutput { get; set; }
        public string jsonEditWMWordlist { get; set; }
        public string jsonEditWMOutput { get; set; }
        public string jsonEditSWordlistGenerator { get; set; }
        public string jsonEditSMarkovChainThing { get; set; }
        public string jsonEditSWordlistMapper { get; set; }
    }
}