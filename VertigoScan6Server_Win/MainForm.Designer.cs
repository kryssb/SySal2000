namespace SySal.Executables.VertigoScan6Server_Win
{
    partial class MainForm
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
            this.components = new System.ComponentModel.Container();
            this.TrackerList = new System.Windows.Forms.ListView();
            this.columnHeader1 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader2 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader7 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader3 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader8 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader4 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader5 = new System.Windows.Forms.ColumnHeader();
            this.columnHeader6 = new System.Windows.Forms.ColumnHeader();
            this.TestButton = new System.Windows.Forms.Button();
            this.CloseButton = new System.Windows.Forms.Button();
            this.RefreshTimer = new System.Windows.Forms.Timer(this.components);
            this.ClearErrButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // TrackerList
            // 
            this.TrackerList.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2,
            this.columnHeader7,
            this.columnHeader3,
            this.columnHeader8,
            this.columnHeader4,
            this.columnHeader5,
            this.columnHeader6});
            this.TrackerList.FullRowSelect = true;
            this.TrackerList.GridLines = true;
            this.TrackerList.HideSelection = false;
            this.TrackerList.Location = new System.Drawing.Point(12, 12);
            this.TrackerList.Name = "TrackerList";
            this.TrackerList.Size = new System.Drawing.Size(851, 392);
            this.TrackerList.TabIndex = 0;
            this.TrackerList.UseCompatibleStateImageBehavior = false;
            this.TrackerList.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "Trackers";
            this.columnHeader1.Width = 148;
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "Calls";
            this.columnHeader2.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.columnHeader2.Width = 76;
            // 
            // columnHeader7
            // 
            this.columnHeader7.Text = "Total time (s)";
            this.columnHeader7.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.columnHeader7.Width = 90;
            // 
            // columnHeader3
            // 
            this.columnHeader3.Text = "Calls/min";
            this.columnHeader3.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.columnHeader3.Width = 88;
            // 
            // columnHeader8
            // 
            this.columnHeader8.Text = "Time %";
            this.columnHeader8.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // columnHeader4
            // 
            this.columnHeader4.Text = "Tracks";
            this.columnHeader4.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.columnHeader4.Width = 94;
            // 
            // columnHeader5
            // 
            this.columnHeader5.Text = "Tracks/min";
            this.columnHeader5.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.columnHeader5.Width = 92;
            // 
            // columnHeader6
            // 
            this.columnHeader6.Text = "Last error";
            this.columnHeader6.Width = 600;
            // 
            // TestButton
            // 
            this.TestButton.Location = new System.Drawing.Point(12, 421);
            this.TestButton.Name = "TestButton";
            this.TestButton.Size = new System.Drawing.Size(75, 23);
            this.TestButton.TabIndex = 1;
            this.TestButton.Text = "Test";
            this.TestButton.UseVisualStyleBackColor = true;
            this.TestButton.Click += new System.EventHandler(this.TestButton_Click);
            // 
            // CloseButton
            // 
            this.CloseButton.Location = new System.Drawing.Point(788, 421);
            this.CloseButton.Name = "CloseButton";
            this.CloseButton.Size = new System.Drawing.Size(75, 23);
            this.CloseButton.TabIndex = 2;
            this.CloseButton.Text = "Close";
            this.CloseButton.UseVisualStyleBackColor = true;
            this.CloseButton.Click += new System.EventHandler(this.CloseButton_Click);
            // 
            // RefreshTimer
            // 
            this.RefreshTimer.Interval = 2000;
            this.RefreshTimer.Tick += new System.EventHandler(this.OnRefresh);
            // 
            // ClearErrButton
            // 
            this.ClearErrButton.Location = new System.Drawing.Point(93, 421);
            this.ClearErrButton.Name = "ClearErrButton";
            this.ClearErrButton.Size = new System.Drawing.Size(142, 23);
            this.ClearErrButton.TabIndex = 3;
            this.ClearErrButton.Text = "Clear Error State";
            this.ClearErrButton.UseVisualStyleBackColor = true;
            this.ClearErrButton.Click += new System.EventHandler(this.ClearErrButton_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(875, 459);
            this.Controls.Add(this.ClearErrButton);
            this.Controls.Add(this.CloseButton);
            this.Controls.Add(this.TestButton);
            this.Controls.Add(this.TrackerList);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "MainForm";
            this.Text = "VertigoScan6 Server";
            this.Load += new System.EventHandler(this.OnLoad);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListView TrackerList;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.ColumnHeader columnHeader4;
        private System.Windows.Forms.ColumnHeader columnHeader5;
        private System.Windows.Forms.Button TestButton;
        private System.Windows.Forms.Button CloseButton;
        private System.Windows.Forms.Timer RefreshTimer;
        private System.Windows.Forms.ColumnHeader columnHeader6;
        private System.Windows.Forms.Button ClearErrButton;
        private System.Windows.Forms.ColumnHeader columnHeader7;
        private System.Windows.Forms.ColumnHeader columnHeader8;
    }
}

