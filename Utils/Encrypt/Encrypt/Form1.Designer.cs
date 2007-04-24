namespace Encrypt
{
    partial class EncryptProjectForm
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
          this.ProgressBar = new System.Windows.Forms.ProgressBar();
          this.EncryptProjectButton = new System.Windows.Forms.Button();
          this.CreateBackupCheckBox = new System.Windows.Forms.CheckBox();
          this.EncryptPGMFilesCheckBox = new System.Windows.Forms.CheckBox();
          this.EncryptRCTFilesCheckBox = new System.Windows.Forms.CheckBox();
          this.EncryptDXFFiles = new System.Windows.Forms.CheckBox();
          this.ProjectListBox = new System.Windows.Forms.ListBox();
          this.ProjectsLabel = new System.Windows.Forms.Label();
          this.SuspendLayout();
          // 
          // ProgressBar
          // 
          this.ProgressBar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                      | System.Windows.Forms.AnchorStyles.Right)));
          this.ProgressBar.Location = new System.Drawing.Point(12, 186);
          this.ProgressBar.Maximum = 0;
          this.ProgressBar.Name = "ProgressBar";
          this.ProgressBar.Size = new System.Drawing.Size(476, 11);
          this.ProgressBar.Step = 1;
          this.ProgressBar.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
          this.ProgressBar.TabIndex = 0;
          // 
          // EncryptProjectButton
          // 
          this.EncryptProjectButton.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                      | System.Windows.Forms.AnchorStyles.Right)));
          this.EncryptProjectButton.Location = new System.Drawing.Point(12, 142);
          this.EncryptProjectButton.Name = "EncryptProjectButton";
          this.EncryptProjectButton.Size = new System.Drawing.Size(476, 23);
          this.EncryptProjectButton.TabIndex = 1;
          this.EncryptProjectButton.Text = "Encrypt Project";
          this.EncryptProjectButton.UseVisualStyleBackColor = true;
          this.EncryptProjectButton.Click += new System.EventHandler(this.EncryptProjectButton_Click);
          // 
          // CreateBackupCheckBox
          // 
          this.CreateBackupCheckBox.Checked = true;
          this.CreateBackupCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
          this.CreateBackupCheckBox.Location = new System.Drawing.Point(12, 12);
          this.CreateBackupCheckBox.Name = "CreateBackupCheckBox";
          this.CreateBackupCheckBox.Size = new System.Drawing.Size(97, 17);
          this.CreateBackupCheckBox.TabIndex = 2;
          this.CreateBackupCheckBox.Text = "Create Backup";
          this.CreateBackupCheckBox.UseVisualStyleBackColor = true;
          // 
          // EncryptPGMFilesCheckBox
          // 
          this.EncryptPGMFilesCheckBox.AutoSize = true;
          this.EncryptPGMFilesCheckBox.Checked = true;
          this.EncryptPGMFilesCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
          this.EncryptPGMFilesCheckBox.Location = new System.Drawing.Point(142, 12);
          this.EncryptPGMFilesCheckBox.Name = "EncryptPGMFilesCheckBox";
          this.EncryptPGMFilesCheckBox.Size = new System.Drawing.Size(113, 17);
          this.EncryptPGMFilesCheckBox.TabIndex = 3;
          this.EncryptPGMFilesCheckBox.Text = "Encrypt PGM Files";
          this.EncryptPGMFilesCheckBox.UseVisualStyleBackColor = true;
          // 
          // EncryptRCTFilesCheckBox
          // 
          this.EncryptRCTFilesCheckBox.AutoSize = true;
          this.EncryptRCTFilesCheckBox.Checked = true;
          this.EncryptRCTFilesCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
          this.EncryptRCTFilesCheckBox.Location = new System.Drawing.Point(261, 12);
          this.EncryptRCTFilesCheckBox.Name = "EncryptRCTFilesCheckBox";
          this.EncryptRCTFilesCheckBox.Size = new System.Drawing.Size(111, 17);
          this.EncryptRCTFilesCheckBox.TabIndex = 4;
          this.EncryptRCTFilesCheckBox.Text = "Encrypt RCT Files";
          this.EncryptRCTFilesCheckBox.UseVisualStyleBackColor = true;
          // 
          // EncryptDXFFiles
          // 
          this.EncryptDXFFiles.AutoSize = true;
          this.EncryptDXFFiles.Checked = true;
          this.EncryptDXFFiles.CheckState = System.Windows.Forms.CheckState.Checked;
          this.EncryptDXFFiles.Location = new System.Drawing.Point(378, 12);
          this.EncryptDXFFiles.Name = "EncryptDXFFiles";
          this.EncryptDXFFiles.Size = new System.Drawing.Size(110, 17);
          this.EncryptDXFFiles.TabIndex = 5;
          this.EncryptDXFFiles.Text = "Encrypt DXF Files";
          this.EncryptDXFFiles.UseVisualStyleBackColor = true;
          // 
          // ProjectListBox
          // 
          this.ProjectListBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                      | System.Windows.Forms.AnchorStyles.Right)));
          this.ProjectListBox.FormattingEnabled = true;
          this.ProjectListBox.HorizontalScrollbar = true;
          this.ProjectListBox.Location = new System.Drawing.Point(12, 67);
          this.ProjectListBox.Name = "ProjectListBox";
          this.ProjectListBox.Size = new System.Drawing.Size(476, 69);
          this.ProjectListBox.TabIndex = 6;
          // 
          // ProjectsLabel
          // 
          this.ProjectsLabel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                      | System.Windows.Forms.AnchorStyles.Right)));
          this.ProjectsLabel.AutoSize = true;
          this.ProjectsLabel.Location = new System.Drawing.Point(12, 51);
          this.ProjectsLabel.Name = "ProjectsLabel";
          this.ProjectsLabel.Size = new System.Drawing.Size(48, 13);
          this.ProjectsLabel.TabIndex = 7;
          this.ProjectsLabel.Text = "Projects:";
          // 
          // EncryptProjectForm
          // 
          this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
          this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
          this.ClientSize = new System.Drawing.Size(500, 209);
          this.Controls.Add(this.ProjectsLabel);
          this.Controls.Add(this.ProjectListBox);
          this.Controls.Add(this.EncryptDXFFiles);
          this.Controls.Add(this.EncryptRCTFilesCheckBox);
          this.Controls.Add(this.EncryptPGMFilesCheckBox);
          this.Controls.Add(this.CreateBackupCheckBox);
          this.Controls.Add(this.EncryptProjectButton);
          this.Controls.Add(this.ProgressBar);
          this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
          this.Name = "EncryptProjectForm";
          this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
          this.Text = "Encrypt Project";
          this.Load += new System.EventHandler(this.EncryptProjectForm_Load);
          this.ResumeLayout(false);
          this.PerformLayout();

        }

        #endregion

      private System.Windows.Forms.ProgressBar ProgressBar;
      private System.Windows.Forms.Button EncryptProjectButton;
      private System.Windows.Forms.CheckBox CreateBackupCheckBox;
      private System.Windows.Forms.CheckBox EncryptPGMFilesCheckBox;
      private System.Windows.Forms.CheckBox EncryptRCTFilesCheckBox;
      private System.Windows.Forms.CheckBox EncryptDXFFiles;
      private System.Windows.Forms.ListBox ProjectListBox;
      private System.Windows.Forms.Label ProjectsLabel;
    }
}

