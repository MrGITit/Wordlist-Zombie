namespace Wordlist_Zombie_GUI
{
    partial class FormCommand
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxCommand = new System.Windows.Forms.TextBox();
            this.buttonCCopyToClipboard = new System.Windows.Forms.Button();
            this.buttonCClose = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Segoe UI", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.label1.Location = new System.Drawing.Point(225, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(149, 37);
            this.label1.TabIndex = 0;
            this.label1.Text = "Command";
            // 
            // textBoxCommand
            // 
            this.textBoxCommand.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBoxCommand.Location = new System.Drawing.Point(15, 51);
            this.textBoxCommand.Multiline = true;
            this.textBoxCommand.Name = "textBoxCommand";
            this.textBoxCommand.ReadOnly = true;
            this.textBoxCommand.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBoxCommand.Size = new System.Drawing.Size(568, 78);
            this.textBoxCommand.TabIndex = 1;
            // 
            // buttonCCopyToClipboard
            // 
            this.buttonCCopyToClipboard.Location = new System.Drawing.Point(237, 135);
            this.buttonCCopyToClipboard.Name = "buttonCCopyToClipboard";
            this.buttonCCopyToClipboard.Size = new System.Drawing.Size(124, 23);
            this.buttonCCopyToClipboard.TabIndex = 2;
            this.buttonCCopyToClipboard.Text = "Copy To Clipboard";
            this.buttonCCopyToClipboard.UseVisualStyleBackColor = true;
            this.buttonCCopyToClipboard.Click += new System.EventHandler(this.buttonCCopyToClipboard_Click);
            // 
            // buttonCClose
            // 
            this.buttonCClose.Location = new System.Drawing.Point(508, 135);
            this.buttonCClose.Name = "buttonCClose";
            this.buttonCClose.Size = new System.Drawing.Size(75, 23);
            this.buttonCClose.TabIndex = 3;
            this.buttonCClose.Text = "Close";
            this.buttonCClose.UseVisualStyleBackColor = true;
            this.buttonCClose.Click += new System.EventHandler(this.buttonCClose_Click);
            // 
            // FormCommand
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(598, 164);
            this.Controls.Add(this.buttonCClose);
            this.Controls.Add(this.buttonCCopyToClipboard);
            this.Controls.Add(this.textBoxCommand);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormCommand";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Wordlist Zombie GUI";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormCommand_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Label label1;
        public TextBox textBoxCommand;
        private Button buttonCCopyToClipboard;
        private Button buttonCClose;
    }
}