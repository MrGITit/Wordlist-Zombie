namespace Wordlist_Zombie_GUI
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.editWGNumber = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.buttonWGOutputFileBrowse = new System.Windows.Forms.Button();
            this.editWGOutputFile = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.buttonWGGenerate = new System.Windows.Forms.Button();
            this.buttonWGWordlistMapFileBrowse = new System.Windows.Forms.Button();
            this.editWGWordlistMapFile = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.buttonWGMarkovFileBrowse = new System.Windows.Forms.Button();
            this.editWGMarkovFile = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.buttonMCTGenerate = new System.Windows.Forms.Button();
            this.buttonMCTOutputBrowse = new System.Windows.Forms.Button();
            this.editMCTOutput = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.buttonMCTWordlistBrowse = new System.Windows.Forms.Button();
            this.editMCTWordlist = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.buttonWMGenerate = new System.Windows.Forms.Button();
            this.buttonWMOutputBrowse = new System.Windows.Forms.Button();
            this.editWMOutput = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.buttonWMWordlistBrowse = new System.Windows.Forms.Button();
            this.editWMWordlist = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.buttonSettingsResetToDefault = new System.Windows.Forms.Button();
            this.buttonSWordlistMapperBrowse = new System.Windows.Forms.Button();
            this.editSWordlistMapper = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.buttonSMarkovChainThingBrowse = new System.Windows.Forms.Button();
            this.editSMarkovChainThing = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.buttonSWordlistGeneratorBrowse = new System.Windows.Forms.Button();
            this.editSWordlistGenerator = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.openFileDialogWGMarkovFile = new System.Windows.Forms.OpenFileDialog();
            this.openFileDialogWGWordlistMapFile = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialogWGOutputFile = new System.Windows.Forms.SaveFileDialog();
            this.openFileDialogMCTWordlist = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialogMCTOutput = new System.Windows.Forms.SaveFileDialog();
            this.openFileDialogWMWordlist = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialogWMOutput = new System.Windows.Forms.SaveFileDialog();
            this.openFileDialogSWordlistGenerator = new System.Windows.Forms.OpenFileDialog();
            this.openFileDialogSMarkovChainThing = new System.Windows.Forms.OpenFileDialog();
            this.openFileDialogSWordlistMapper = new System.Windows.Forms.OpenFileDialog();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabPage3.SuspendLayout();
            this.tabPage4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Controls.Add(this.tabPage4);
            this.tabControl1.Location = new System.Drawing.Point(13, 123);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(534, 197);
            this.tabControl1.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.BackColor = System.Drawing.Color.Transparent;
            this.tabPage1.Controls.Add(this.editWGNumber);
            this.tabPage1.Controls.Add(this.label11);
            this.tabPage1.Controls.Add(this.buttonWGOutputFileBrowse);
            this.tabPage1.Controls.Add(this.editWGOutputFile);
            this.tabPage1.Controls.Add(this.label10);
            this.tabPage1.Controls.Add(this.buttonWGGenerate);
            this.tabPage1.Controls.Add(this.buttonWGWordlistMapFileBrowse);
            this.tabPage1.Controls.Add(this.editWGWordlistMapFile);
            this.tabPage1.Controls.Add(this.label8);
            this.tabPage1.Controls.Add(this.buttonWGMarkovFileBrowse);
            this.tabPage1.Controls.Add(this.editWGMarkovFile);
            this.tabPage1.Controls.Add(this.label9);
            this.tabPage1.Location = new System.Drawing.Point(4, 24);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(526, 169);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Wordlist Generator";
            // 
            // editWGNumber
            // 
            this.editWGNumber.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.editWGNumber.Location = new System.Drawing.Point(186, 96);
            this.editWGNumber.Name = "editWGNumber";
            this.editWGNumber.Size = new System.Drawing.Size(133, 23);
            this.editWGNumber.TabIndex = 20;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(16, 104);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(166, 15);
            this.label11.TabIndex = 19;
            this.label11.Text = "Number of words to generate:";
            // 
            // buttonWGOutputFileBrowse
            // 
            this.buttonWGOutputFileBrowse.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonWGOutputFileBrowse.Location = new System.Drawing.Point(492, 65);
            this.buttonWGOutputFileBrowse.Name = "buttonWGOutputFileBrowse";
            this.buttonWGOutputFileBrowse.Size = new System.Drawing.Size(24, 24);
            this.buttonWGOutputFileBrowse.TabIndex = 18;
            this.buttonWGOutputFileBrowse.Text = "...";
            this.buttonWGOutputFileBrowse.UseVisualStyleBackColor = true;
            this.buttonWGOutputFileBrowse.Click += new System.EventHandler(this.buttonWGOutputFileBrowse_Click);
            // 
            // editWGOutputFile
            // 
            this.editWGOutputFile.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.editWGOutputFile.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.editWGOutputFile.Location = new System.Drawing.Point(121, 66);
            this.editWGOutputFile.Name = "editWGOutputFile";
            this.editWGOutputFile.Size = new System.Drawing.Size(365, 23);
            this.editWGOutputFile.TabIndex = 17;
            this.editWGOutputFile.WordWrap = false;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(49, 74);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(69, 15);
            this.label10.TabIndex = 16;
            this.label10.Text = "Output File:";
            // 
            // buttonWGGenerate
            // 
            this.buttonWGGenerate.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.buttonWGGenerate.Location = new System.Drawing.Point(207, 125);
            this.buttonWGGenerate.Name = "buttonWGGenerate";
            this.buttonWGGenerate.Size = new System.Drawing.Size(112, 40);
            this.buttonWGGenerate.TabIndex = 15;
            this.buttonWGGenerate.Text = "Generate";
            this.buttonWGGenerate.UseVisualStyleBackColor = true;
            this.buttonWGGenerate.Click += new System.EventHandler(this.buttonWGGenerate_Click);
            // 
            // buttonWGWordlistMapFileBrowse
            // 
            this.buttonWGWordlistMapFileBrowse.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonWGWordlistMapFileBrowse.Location = new System.Drawing.Point(492, 36);
            this.buttonWGWordlistMapFileBrowse.Name = "buttonWGWordlistMapFileBrowse";
            this.buttonWGWordlistMapFileBrowse.Size = new System.Drawing.Size(24, 24);
            this.buttonWGWordlistMapFileBrowse.TabIndex = 13;
            this.buttonWGWordlistMapFileBrowse.Text = "...";
            this.buttonWGWordlistMapFileBrowse.UseVisualStyleBackColor = true;
            this.buttonWGWordlistMapFileBrowse.Click += new System.EventHandler(this.buttonWGWordlistMapFileBrowse_Click);
            // 
            // editWGWordlistMapFile
            // 
            this.editWGWordlistMapFile.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.editWGWordlistMapFile.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.editWGWordlistMapFile.Location = new System.Drawing.Point(121, 37);
            this.editWGWordlistMapFile.Name = "editWGWordlistMapFile";
            this.editWGWordlistMapFile.Size = new System.Drawing.Size(365, 23);
            this.editWGWordlistMapFile.TabIndex = 12;
            this.editWGWordlistMapFile.WordWrap = false;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(16, 45);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(102, 15);
            this.label8.TabIndex = 11;
            this.label8.Text = "Wordlist Map File:";
            // 
            // buttonWGMarkovFileBrowse
            // 
            this.buttonWGMarkovFileBrowse.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonWGMarkovFileBrowse.Location = new System.Drawing.Point(492, 9);
            this.buttonWGMarkovFileBrowse.Name = "buttonWGMarkovFileBrowse";
            this.buttonWGMarkovFileBrowse.Size = new System.Drawing.Size(24, 24);
            this.buttonWGMarkovFileBrowse.TabIndex = 10;
            this.buttonWGMarkovFileBrowse.Text = "...";
            this.buttonWGMarkovFileBrowse.UseVisualStyleBackColor = true;
            this.buttonWGMarkovFileBrowse.Click += new System.EventHandler(this.buttonWGMarkovFileBrowse_Click);
            // 
            // editWGMarkovFile
            // 
            this.editWGMarkovFile.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.editWGMarkovFile.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.editWGMarkovFile.Location = new System.Drawing.Point(121, 10);
            this.editWGMarkovFile.Name = "editWGMarkovFile";
            this.editWGMarkovFile.Size = new System.Drawing.Size(365, 23);
            this.editWGMarkovFile.TabIndex = 9;
            this.editWGMarkovFile.WordWrap = false;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(13, 18);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(105, 15);
            this.label9.TabIndex = 8;
            this.label9.Text = "Markov Chain File:";
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.buttonMCTGenerate);
            this.tabPage2.Controls.Add(this.buttonMCTOutputBrowse);
            this.tabPage2.Controls.Add(this.editMCTOutput);
            this.tabPage2.Controls.Add(this.label2);
            this.tabPage2.Controls.Add(this.buttonMCTWordlistBrowse);
            this.tabPage2.Controls.Add(this.editMCTWordlist);
            this.tabPage2.Controls.Add(this.label1);
            this.tabPage2.Location = new System.Drawing.Point(4, 24);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(526, 169);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Markov Chain Thing";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // buttonMCTGenerate
            // 
            this.buttonMCTGenerate.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.buttonMCTGenerate.Location = new System.Drawing.Point(207, 66);
            this.buttonMCTGenerate.Name = "buttonMCTGenerate";
            this.buttonMCTGenerate.Size = new System.Drawing.Size(112, 40);
            this.buttonMCTGenerate.TabIndex = 7;
            this.buttonMCTGenerate.Text = "Generate";
            this.buttonMCTGenerate.UseVisualStyleBackColor = true;
            this.buttonMCTGenerate.Click += new System.EventHandler(this.buttonMCTGenerate_Click);
            // 
            // buttonMCTOutputBrowse
            // 
            this.buttonMCTOutputBrowse.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonMCTOutputBrowse.Location = new System.Drawing.Point(492, 36);
            this.buttonMCTOutputBrowse.Name = "buttonMCTOutputBrowse";
            this.buttonMCTOutputBrowse.Size = new System.Drawing.Size(24, 24);
            this.buttonMCTOutputBrowse.TabIndex = 5;
            this.buttonMCTOutputBrowse.Text = "...";
            this.buttonMCTOutputBrowse.UseVisualStyleBackColor = true;
            this.buttonMCTOutputBrowse.Click += new System.EventHandler(this.buttonMCTOutputBrowse_Click);
            // 
            // editMCTOutput
            // 
            this.editMCTOutput.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.editMCTOutput.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.editMCTOutput.Location = new System.Drawing.Point(70, 37);
            this.editMCTOutput.Name = "editMCTOutput";
            this.editMCTOutput.Size = new System.Drawing.Size(416, 23);
            this.editMCTOutput.TabIndex = 4;
            this.editMCTOutput.WordWrap = false;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(16, 45);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(48, 15);
            this.label2.TabIndex = 3;
            this.label2.Text = "Output:";
            // 
            // buttonMCTWordlistBrowse
            // 
            this.buttonMCTWordlistBrowse.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonMCTWordlistBrowse.Location = new System.Drawing.Point(492, 9);
            this.buttonMCTWordlistBrowse.Name = "buttonMCTWordlistBrowse";
            this.buttonMCTWordlistBrowse.Size = new System.Drawing.Size(24, 24);
            this.buttonMCTWordlistBrowse.TabIndex = 2;
            this.buttonMCTWordlistBrowse.Text = "...";
            this.buttonMCTWordlistBrowse.UseVisualStyleBackColor = true;
            this.buttonMCTWordlistBrowse.Click += new System.EventHandler(this.buttonMCTWordlistBrowse_Click);
            // 
            // editMCTWordlist
            // 
            this.editMCTWordlist.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.editMCTWordlist.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.editMCTWordlist.Location = new System.Drawing.Point(70, 10);
            this.editMCTWordlist.Name = "editMCTWordlist";
            this.editMCTWordlist.Size = new System.Drawing.Size(416, 23);
            this.editMCTWordlist.TabIndex = 1;
            this.editMCTWordlist.WordWrap = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(10, 18);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(54, 15);
            this.label1.TabIndex = 0;
            this.label1.Text = "Wordlist:";
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.buttonWMGenerate);
            this.tabPage3.Controls.Add(this.buttonWMOutputBrowse);
            this.tabPage3.Controls.Add(this.editWMOutput);
            this.tabPage3.Controls.Add(this.label6);
            this.tabPage3.Controls.Add(this.buttonWMWordlistBrowse);
            this.tabPage3.Controls.Add(this.editWMWordlist);
            this.tabPage3.Controls.Add(this.label7);
            this.tabPage3.Location = new System.Drawing.Point(4, 24);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(526, 169);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "Wordlist Mapper";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // buttonWMGenerate
            // 
            this.buttonWMGenerate.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.buttonWMGenerate.Location = new System.Drawing.Point(207, 66);
            this.buttonWMGenerate.Name = "buttonWMGenerate";
            this.buttonWMGenerate.Size = new System.Drawing.Size(112, 40);
            this.buttonWMGenerate.TabIndex = 15;
            this.buttonWMGenerate.Text = "Generate";
            this.buttonWMGenerate.UseVisualStyleBackColor = true;
            this.buttonWMGenerate.Click += new System.EventHandler(this.buttonWMGenerate_Click);
            // 
            // buttonWMOutputBrowse
            // 
            this.buttonWMOutputBrowse.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonWMOutputBrowse.Location = new System.Drawing.Point(492, 37);
            this.buttonWMOutputBrowse.Name = "buttonWMOutputBrowse";
            this.buttonWMOutputBrowse.Size = new System.Drawing.Size(24, 24);
            this.buttonWMOutputBrowse.TabIndex = 13;
            this.buttonWMOutputBrowse.Text = "...";
            this.buttonWMOutputBrowse.UseVisualStyleBackColor = true;
            this.buttonWMOutputBrowse.Click += new System.EventHandler(this.buttonWMOutputBrowse_Click);
            // 
            // editWMOutput
            // 
            this.editWMOutput.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.editWMOutput.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.editWMOutput.Location = new System.Drawing.Point(70, 37);
            this.editWMOutput.Name = "editWMOutput";
            this.editWMOutput.Size = new System.Drawing.Size(416, 23);
            this.editWMOutput.TabIndex = 12;
            this.editWMOutput.WordWrap = false;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(16, 45);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(48, 15);
            this.label6.TabIndex = 11;
            this.label6.Text = "Output:";
            // 
            // buttonWMWordlistBrowse
            // 
            this.buttonWMWordlistBrowse.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonWMWordlistBrowse.Location = new System.Drawing.Point(492, 10);
            this.buttonWMWordlistBrowse.Name = "buttonWMWordlistBrowse";
            this.buttonWMWordlistBrowse.Size = new System.Drawing.Size(24, 24);
            this.buttonWMWordlistBrowse.TabIndex = 10;
            this.buttonWMWordlistBrowse.Text = "...";
            this.buttonWMWordlistBrowse.UseVisualStyleBackColor = true;
            this.buttonWMWordlistBrowse.Click += new System.EventHandler(this.buttonWMWordlistBrowse_Click);
            // 
            // editWMWordlist
            // 
            this.editWMWordlist.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.editWMWordlist.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.editWMWordlist.Location = new System.Drawing.Point(70, 10);
            this.editWMWordlist.Name = "editWMWordlist";
            this.editWMWordlist.Size = new System.Drawing.Size(416, 23);
            this.editWMWordlist.TabIndex = 9;
            this.editWMWordlist.WordWrap = false;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(10, 18);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(54, 15);
            this.label7.TabIndex = 8;
            this.label7.Text = "Wordlist:";
            // 
            // tabPage4
            // 
            this.tabPage4.Controls.Add(this.buttonSettingsResetToDefault);
            this.tabPage4.Controls.Add(this.buttonSWordlistMapperBrowse);
            this.tabPage4.Controls.Add(this.editSWordlistMapper);
            this.tabPage4.Controls.Add(this.label5);
            this.tabPage4.Controls.Add(this.buttonSMarkovChainThingBrowse);
            this.tabPage4.Controls.Add(this.editSMarkovChainThing);
            this.tabPage4.Controls.Add(this.label3);
            this.tabPage4.Controls.Add(this.buttonSWordlistGeneratorBrowse);
            this.tabPage4.Controls.Add(this.editSWordlistGenerator);
            this.tabPage4.Controls.Add(this.label4);
            this.tabPage4.Location = new System.Drawing.Point(4, 24);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Size = new System.Drawing.Size(526, 169);
            this.tabPage4.TabIndex = 3;
            this.tabPage4.Text = "Settings";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // buttonSettingsResetToDefault
            // 
            this.buttonSettingsResetToDefault.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.buttonSettingsResetToDefault.Location = new System.Drawing.Point(201, 127);
            this.buttonSettingsResetToDefault.Name = "buttonSettingsResetToDefault";
            this.buttonSettingsResetToDefault.Size = new System.Drawing.Size(125, 38);
            this.buttonSettingsResetToDefault.TabIndex = 16;
            this.buttonSettingsResetToDefault.Text = "Reset To Default";
            this.buttonSettingsResetToDefault.UseVisualStyleBackColor = true;
            this.buttonSettingsResetToDefault.Click += new System.EventHandler(this.buttonSettingsResetToDefault_Click);
            // 
            // buttonSWordlistMapperBrowse
            // 
            this.buttonSWordlistMapperBrowse.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonSWordlistMapperBrowse.Location = new System.Drawing.Point(493, 86);
            this.buttonSWordlistMapperBrowse.Name = "buttonSWordlistMapperBrowse";
            this.buttonSWordlistMapperBrowse.Size = new System.Drawing.Size(24, 24);
            this.buttonSWordlistMapperBrowse.TabIndex = 14;
            this.buttonSWordlistMapperBrowse.Text = "...";
            this.buttonSWordlistMapperBrowse.UseVisualStyleBackColor = true;
            this.buttonSWordlistMapperBrowse.Click += new System.EventHandler(this.buttonSWordlistMapperBrowse_Click);
            // 
            // editSWordlistMapper
            // 
            this.editSWordlistMapper.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.editSWordlistMapper.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.editSWordlistMapper.Location = new System.Drawing.Point(133, 87);
            this.editSWordlistMapper.Name = "editSWordlistMapper";
            this.editSWordlistMapper.Size = new System.Drawing.Size(354, 23);
            this.editSWordlistMapper.TabIndex = 13;
            this.editSWordlistMapper.WordWrap = false;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(29, 95);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(98, 15);
            this.label5.TabIndex = 12;
            this.label5.Text = "Wordlist Mapper:";
            // 
            // buttonSMarkovChainThingBrowse
            // 
            this.buttonSMarkovChainThingBrowse.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonSMarkovChainThingBrowse.Location = new System.Drawing.Point(493, 57);
            this.buttonSMarkovChainThingBrowse.Name = "buttonSMarkovChainThingBrowse";
            this.buttonSMarkovChainThingBrowse.Size = new System.Drawing.Size(24, 24);
            this.buttonSMarkovChainThingBrowse.TabIndex = 11;
            this.buttonSMarkovChainThingBrowse.Text = "...";
            this.buttonSMarkovChainThingBrowse.UseVisualStyleBackColor = true;
            this.buttonSMarkovChainThingBrowse.Click += new System.EventHandler(this.buttonSMarkovChainThingBrowse_Click);
            // 
            // editSMarkovChainThing
            // 
            this.editSMarkovChainThing.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.editSMarkovChainThing.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.editSMarkovChainThing.Location = new System.Drawing.Point(133, 58);
            this.editSMarkovChainThing.Name = "editSMarkovChainThing";
            this.editSMarkovChainThing.Size = new System.Drawing.Size(354, 23);
            this.editSMarkovChainThing.TabIndex = 10;
            this.editSMarkovChainThing.WordWrap = false;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(10, 66);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(117, 15);
            this.label3.TabIndex = 9;
            this.label3.Text = "Markov Chain Thing:";
            // 
            // buttonSWordlistGeneratorBrowse
            // 
            this.buttonSWordlistGeneratorBrowse.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonSWordlistGeneratorBrowse.Location = new System.Drawing.Point(493, 30);
            this.buttonSWordlistGeneratorBrowse.Name = "buttonSWordlistGeneratorBrowse";
            this.buttonSWordlistGeneratorBrowse.Size = new System.Drawing.Size(24, 24);
            this.buttonSWordlistGeneratorBrowse.TabIndex = 8;
            this.buttonSWordlistGeneratorBrowse.Text = "...";
            this.buttonSWordlistGeneratorBrowse.UseVisualStyleBackColor = true;
            this.buttonSWordlistGeneratorBrowse.Click += new System.EventHandler(this.buttonSWordlistGeneratorBrowse_Click);
            // 
            // editSWordlistGenerator
            // 
            this.editSWordlistGenerator.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.editSWordlistGenerator.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.editSWordlistGenerator.Location = new System.Drawing.Point(133, 31);
            this.editSWordlistGenerator.Name = "editSWordlistGenerator";
            this.editSWordlistGenerator.Size = new System.Drawing.Size(354, 23);
            this.editSWordlistGenerator.TabIndex = 7;
            this.editSWordlistGenerator.WordWrap = false;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(18, 39);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(109, 15);
            this.label4.TabIndex = 6;
            this.label4.Text = "Wordlist Generator:";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.pictureBox1.Image = global::Wordlist_Zombie_GUI.Properties.Resources.WordlistZombie;
            this.pictureBox1.Location = new System.Drawing.Point(12, 8);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(530, 107);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.pictureBox1.TabIndex = 1;
            this.pictureBox1.TabStop = false;
            // 
            // openFileDialogWGMarkovFile
            // 
            this.openFileDialogWGMarkovFile.FileName = "openFileDialog1";
            this.openFileDialogWGMarkovFile.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialogWGMarkovFile_FileOk);
            // 
            // openFileDialogWGWordlistMapFile
            // 
            this.openFileDialogWGWordlistMapFile.FileName = "openFileDialog2";
            this.openFileDialogWGWordlistMapFile.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialogWGWordlistMapFile_FileOk);
            // 
            // saveFileDialogWGOutputFile
            // 
            this.saveFileDialogWGOutputFile.FileOk += new System.ComponentModel.CancelEventHandler(this.saveFileDialogWGOutputFile_FileOk);
            // 
            // openFileDialogMCTWordlist
            // 
            this.openFileDialogMCTWordlist.FileName = "openFileDialog1";
            this.openFileDialogMCTWordlist.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialogMCTWordlist_FileOk);
            // 
            // saveFileDialogMCTOutput
            // 
            this.saveFileDialogMCTOutput.FileOk += new System.ComponentModel.CancelEventHandler(this.saveFileDialogMCTOutput_FileOk);
            // 
            // openFileDialogWMWordlist
            // 
            this.openFileDialogWMWordlist.FileName = "openFileDialog1";
            this.openFileDialogWMWordlist.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialogWMWordlist_FileOk);
            // 
            // saveFileDialogWMOutput
            // 
            this.saveFileDialogWMOutput.FileOk += new System.ComponentModel.CancelEventHandler(this.saveFileDialogWMOutput_FileOk);
            // 
            // openFileDialogSWordlistGenerator
            // 
            this.openFileDialogSWordlistGenerator.FileName = "openFileDialog1";
            this.openFileDialogSWordlistGenerator.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialogSWordlistGenerator_FileOk);
            // 
            // openFileDialogSMarkovChainThing
            // 
            this.openFileDialogSMarkovChainThing.FileName = "openFileDialog1";
            this.openFileDialogSMarkovChainThing.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialogSMarkovChainThing_FileOk);
            // 
            // openFileDialogSWordlistMapper
            // 
            this.openFileDialogSWordlistMapper.FileName = "openFileDialog1";
            this.openFileDialogSWordlistMapper.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialogSWordlistMapper_FileOk);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(556, 332);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.tabControl1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimumSize = new System.Drawing.Size(572, 371);
            this.Name = "Form1";
            this.Text = "Wordlist Zombie GUI 1.0";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.tabPage3.ResumeLayout(false);
            this.tabPage3.PerformLayout();
            this.tabPage4.ResumeLayout(false);
            this.tabPage4.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private TabControl tabControl1;
        private TabPage tabPage1;
        private TabPage tabPage2;
        private PictureBox pictureBox1;
        private TabPage tabPage3;
        private Button buttonMCTWordlistBrowse;
        private TextBox editMCTWordlist;
        private Label label1;
        private Button buttonMCTOutputBrowse;
        private TextBox editMCTOutput;
        private Label label2;
        private Button buttonMCTGenerate;
        private TabPage tabPage4;
        private Button buttonSMarkovChainThingBrowse;
        private TextBox editSMarkovChainThing;
        private Label label3;
        private Button buttonSWordlistGeneratorBrowse;
        private TextBox editSWordlistGenerator;
        private Label label4;
        private Button buttonSWordlistMapperBrowse;
        private TextBox editSWordlistMapper;
        private Label label5;
        private Button buttonSettingsResetToDefault;
        private Button buttonWMGenerate;
        private Button buttonWMOutputBrowse;
        private TextBox editWMOutput;
        private Label label6;
        private Button buttonWMWordlistBrowse;
        private TextBox editWMWordlist;
        private Label label7;
        private Button buttonWGOutputFileBrowse;
        private TextBox editWGOutputFile;
        private Label label10;
        private Button buttonWGGenerate;
        private Button buttonWGWordlistMapFileBrowse;
        private TextBox editWGWordlistMapFile;
        private Label label8;
        private Button buttonWGMarkovFileBrowse;
        private TextBox editWGMarkovFile;
        private Label label9;
        private OpenFileDialog openFileDialogWGMarkovFile;
        private OpenFileDialog openFileDialogWGWordlistMapFile;
        private SaveFileDialog saveFileDialogWGOutputFile;
        private OpenFileDialog openFileDialogMCTWordlist;
        private SaveFileDialog saveFileDialogMCTOutput;
        private OpenFileDialog openFileDialogWMWordlist;
        private SaveFileDialog saveFileDialogWMOutput;
        private OpenFileDialog openFileDialogSWordlistGenerator;
        private OpenFileDialog openFileDialogSMarkovChainThing;
        private OpenFileDialog openFileDialogSWordlistMapper;
        private TextBox editWGNumber;
        private Label label11;
    }
}