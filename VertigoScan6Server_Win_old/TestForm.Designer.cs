namespace SySal.Executables.VertigoScan6Server_Win
{
    partial class TestForm
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
            this.RWDFileSaveDialog = new System.Windows.Forms.SaveFileDialog();
            this.OutRWDButton = new System.Windows.Forms.Button();
            this.RWDFileText = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.DoButton = new System.Windows.Forms.Button();
            this.HideButton = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.ClassList = new System.Windows.Forms.ListView();
            this.columnHeader1 = new System.Windows.Forms.ColumnHeader();
            this.ConfigList = new System.Windows.Forms.ListView();
            this.columnHeader2 = new System.Windows.Forms.ColumnHeader();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.PickTrkTButton = new System.Windows.Forms.Button();
            this.PickFitTButton = new System.Windows.Forms.Button();
            this.PickFitBButton = new System.Windows.Forms.Button();
            this.TrkTText = new System.Windows.Forms.TextBox();
            this.FitTText = new System.Windows.Forms.TextBox();
            this.FitBText = new System.Windows.Forms.TextBox();
            this.TrkBText = new System.Windows.Forms.TextBox();
            this.PickTrkBButton = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.GrainsText = new System.Windows.Forms.TextBox();
            this.SaveGrainsCheck = new System.Windows.Forms.CheckBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // RWDFileSaveDialog
            // 
            this.RWDFileSaveDialog.Filter = "RWD files|*.rwd|Batched rwd files|*.rwd.????????";
            // 
            // OutRWDButton
            // 
            this.OutRWDButton.Location = new System.Drawing.Point(427, 15);
            this.OutRWDButton.Name = "OutRWDButton";
            this.OutRWDButton.Size = new System.Drawing.Size(30, 20);
            this.OutRWDButton.TabIndex = 0;
            this.OutRWDButton.Text = "...";
            this.OutRWDButton.UseVisualStyleBackColor = true;
            this.OutRWDButton.Click += new System.EventHandler(this.OutRWDButton_Click);
            // 
            // RWDFileText
            // 
            this.RWDFileText.Location = new System.Drawing.Point(111, 15);
            this.RWDFileText.Name = "RWDFileText";
            this.RWDFileText.Size = new System.Drawing.Size(310, 20);
            this.RWDFileText.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 18);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(93, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Output RWD path";
            // 
            // DoButton
            // 
            this.DoButton.Location = new System.Drawing.Point(482, 14);
            this.DoButton.Name = "DoButton";
            this.DoButton.Size = new System.Drawing.Size(38, 20);
            this.DoButton.TabIndex = 3;
            this.DoButton.Text = "Do!";
            this.DoButton.UseVisualStyleBackColor = true;
            this.DoButton.Click += new System.EventHandler(this.DoButton_Click);
            // 
            // HideButton
            // 
            this.HideButton.Location = new System.Drawing.Point(691, 15);
            this.HideButton.Name = "HideButton";
            this.HideButton.Size = new System.Drawing.Size(59, 20);
            this.HideButton.TabIndex = 4;
            this.HideButton.Text = "Hide";
            this.HideButton.UseVisualStyleBackColor = true;
            this.HideButton.Click += new System.EventHandler(this.HideButton_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.ClassList);
            this.groupBox1.Location = new System.Drawing.Point(15, 51);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(218, 238);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Classes";
            // 
            // ClassList
            // 
            this.ClassList.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1});
            this.ClassList.FullRowSelect = true;
            this.ClassList.GridLines = true;
            this.ClassList.HideSelection = false;
            this.ClassList.Location = new System.Drawing.Point(6, 19);
            this.ClassList.Name = "ClassList";
            this.ClassList.Size = new System.Drawing.Size(206, 213);
            this.ClassList.TabIndex = 6;
            this.ClassList.UseCompatibleStateImageBehavior = false;
            this.ClassList.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "Name";
            this.columnHeader1.Width = 600;
            // 
            // ConfigList
            // 
            this.ConfigList.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader2});
            this.ConfigList.FullRowSelect = true;
            this.ConfigList.GridLines = true;
            this.ConfigList.HideSelection = false;
            this.ConfigList.Location = new System.Drawing.Point(6, 19);
            this.ConfigList.Name = "ConfigList";
            this.ConfigList.Size = new System.Drawing.Size(206, 213);
            this.ConfigList.TabIndex = 6;
            this.ConfigList.UseCompatibleStateImageBehavior = false;
            this.ConfigList.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "Name";
            this.columnHeader2.Width = 600;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.ConfigList);
            this.groupBox2.Location = new System.Drawing.Point(246, 51);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(218, 238);
            this.groupBox2.TabIndex = 6;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Configs";
            // 
            // PickTrkTButton
            // 
            this.PickTrkTButton.Location = new System.Drawing.Point(482, 70);
            this.PickTrkTButton.Name = "PickTrkTButton";
            this.PickTrkTButton.Size = new System.Drawing.Size(131, 23);
            this.PickTrkTButton.TabIndex = 7;
            this.PickTrkTButton.Text = "Pick Tracker Top";
            this.PickTrkTButton.UseVisualStyleBackColor = true;
            this.PickTrkTButton.Click += new System.EventHandler(this.PickTrkTButton_Click);
            // 
            // PickFitTButton
            // 
            this.PickFitTButton.Location = new System.Drawing.Point(482, 180);
            this.PickFitTButton.Name = "PickFitTButton";
            this.PickFitTButton.Size = new System.Drawing.Size(131, 23);
            this.PickFitTButton.TabIndex = 8;
            this.PickFitTButton.Text = "Pick Fitter Top";
            this.PickFitTButton.UseVisualStyleBackColor = true;
            this.PickFitTButton.Click += new System.EventHandler(this.PickFitTButton_Click);
            // 
            // PickFitBButton
            // 
            this.PickFitBButton.Location = new System.Drawing.Point(482, 239);
            this.PickFitBButton.Name = "PickFitBButton";
            this.PickFitBButton.Size = new System.Drawing.Size(131, 23);
            this.PickFitBButton.TabIndex = 9;
            this.PickFitBButton.Text = "Pick Fitter Bottom";
            this.PickFitBButton.UseVisualStyleBackColor = true;
            this.PickFitBButton.Click += new System.EventHandler(this.PickFitBButton_Click);
            // 
            // TrkTText
            // 
            this.TrkTText.Location = new System.Drawing.Point(484, 99);
            this.TrkTText.Name = "TrkTText";
            this.TrkTText.ReadOnly = true;
            this.TrkTText.Size = new System.Drawing.Size(266, 20);
            this.TrkTText.TabIndex = 10;
            // 
            // FitTText
            // 
            this.FitTText.Location = new System.Drawing.Point(482, 213);
            this.FitTText.Name = "FitTText";
            this.FitTText.ReadOnly = true;
            this.FitTText.Size = new System.Drawing.Size(266, 20);
            this.FitTText.TabIndex = 11;
            // 
            // FitBText
            // 
            this.FitBText.Location = new System.Drawing.Point(482, 269);
            this.FitBText.Name = "FitBText";
            this.FitBText.ReadOnly = true;
            this.FitBText.Size = new System.Drawing.Size(266, 20);
            this.FitBText.TabIndex = 12;
            // 
            // TrkBText
            // 
            this.TrkBText.Location = new System.Drawing.Point(484, 154);
            this.TrkBText.Name = "TrkBText";
            this.TrkBText.ReadOnly = true;
            this.TrkBText.Size = new System.Drawing.Size(266, 20);
            this.TrkBText.TabIndex = 14;
            // 
            // PickTrkBButton
            // 
            this.PickTrkBButton.Location = new System.Drawing.Point(482, 125);
            this.PickTrkBButton.Name = "PickTrkBButton";
            this.PickTrkBButton.Size = new System.Drawing.Size(131, 23);
            this.PickTrkBButton.TabIndex = 13;
            this.PickTrkBButton.Text = "Pick Tracker Bottom";
            this.PickTrkBButton.UseVisualStyleBackColor = true;
            this.PickTrkBButton.Click += new System.EventHandler(this.PickTrkBButton_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(528, 17);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(68, 13);
            this.label2.TabIndex = 15;
            this.label2.Text = "Grains/Layer";
            // 
            // GrainsText
            // 
            this.GrainsText.Location = new System.Drawing.Point(602, 16);
            this.GrainsText.Name = "GrainsText";
            this.GrainsText.Size = new System.Drawing.Size(69, 20);
            this.GrainsText.TabIndex = 16;
            this.GrainsText.Text = "2000";
            this.GrainsText.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.GrainsText.Leave += new System.EventHandler(this.OnGrainsLeave);
            // 
            // SaveGrainsCheck
            // 
            this.SaveGrainsCheck.AutoSize = true;
            this.SaveGrainsCheck.Location = new System.Drawing.Point(485, 39);
            this.SaveGrainsCheck.Name = "SaveGrainsCheck";
            this.SaveGrainsCheck.Size = new System.Drawing.Size(82, 17);
            this.SaveGrainsCheck.TabIndex = 17;
            this.SaveGrainsCheck.Text = "Save grains";
            this.SaveGrainsCheck.UseVisualStyleBackColor = true;
            // 
            // TestForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(762, 301);
            this.ControlBox = false;
            this.Controls.Add(this.SaveGrainsCheck);
            this.Controls.Add(this.GrainsText);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.PickTrkTButton);
            this.Controls.Add(this.TrkTText);
            this.Controls.Add(this.TrkBText);
            this.Controls.Add(this.PickTrkBButton);
            this.Controls.Add(this.FitBText);
            this.Controls.Add(this.FitTText);
            this.Controls.Add(this.PickFitBButton);
            this.Controls.Add(this.PickFitTButton);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.HideButton);
            this.Controls.Add(this.DoButton);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.RWDFileText);
            this.Controls.Add(this.OutRWDButton);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "TestForm";
            this.Text = "Test parameters";
            this.VisibleChanged += new System.EventHandler(this.OnVisible);
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.SaveFileDialog RWDFileSaveDialog;
        private System.Windows.Forms.Button OutRWDButton;
        private System.Windows.Forms.TextBox RWDFileText;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button DoButton;
        private System.Windows.Forms.Button HideButton;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ListView ClassList;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ListView ConfigList;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button PickTrkTButton;
        private System.Windows.Forms.Button PickFitTButton;
        private System.Windows.Forms.Button PickFitBButton;
        private System.Windows.Forms.TextBox TrkTText;
        private System.Windows.Forms.TextBox FitTText;
        private System.Windows.Forms.TextBox FitBText;
        private System.Windows.Forms.TextBox TrkBText;
        private System.Windows.Forms.Button PickTrkBButton;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox GrainsText;
        private System.Windows.Forms.CheckBox SaveGrainsCheck;
    }
}