using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace Test
{
	/// <summary>
	/// Summary description for ScanZone.
	/// </summary>
	public class ScanZone : System.Windows.Forms.Form
	{
		public SySal.DAQSystem.Scanning.ZoneDesc Zone = new SySal.DAQSystem.Scanning.ZoneDesc();

		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox SeriesText;
		private System.Windows.Forms.TextBox OutnameText;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox MinXText;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.TextBox MaxXText;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.TextBox MaxYText;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.TextBox MinYText;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.Button OkBtn;
		private System.Windows.Forms.Button CancelBtn;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public ScanZone()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if(components != null)
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.label1 = new System.Windows.Forms.Label();
			this.SeriesText = new System.Windows.Forms.TextBox();
			this.OutnameText = new System.Windows.Forms.TextBox();
			this.label2 = new System.Windows.Forms.Label();
			this.MinXText = new System.Windows.Forms.TextBox();
			this.label3 = new System.Windows.Forms.Label();
			this.MaxXText = new System.Windows.Forms.TextBox();
			this.label4 = new System.Windows.Forms.Label();
			this.MaxYText = new System.Windows.Forms.TextBox();
			this.label5 = new System.Windows.Forms.Label();
			this.MinYText = new System.Windows.Forms.TextBox();
			this.label6 = new System.Windows.Forms.Label();
			this.OkBtn = new System.Windows.Forms.Button();
			this.CancelBtn = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(8, 8);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(48, 24);
			this.label1.TabIndex = 0;
			this.label1.Text = "Series";
			this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// SeriesText
			// 
			this.SeriesText.Location = new System.Drawing.Point(64, 8);
			this.SeriesText.Name = "SeriesText";
			this.SeriesText.Size = new System.Drawing.Size(56, 20);
			this.SeriesText.TabIndex = 1;
			this.SeriesText.Text = "";
			this.SeriesText.Leave += new System.EventHandler(this.OnSeriesLeave);
			// 
			// OutnameText
			// 
			this.OutnameText.Location = new System.Drawing.Point(192, 8);
			this.OutnameText.Name = "OutnameText";
			this.OutnameText.Size = new System.Drawing.Size(176, 20);
			this.OutnameText.TabIndex = 3;
			this.OutnameText.Text = "";
			this.OutnameText.Leave += new System.EventHandler(this.OnOutnameLeave);
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(128, 8);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(56, 24);
			this.label2.TabIndex = 2;
			this.label2.Text = "Outname";
			this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// MinXText
			// 
			this.MinXText.Location = new System.Drawing.Point(64, 40);
			this.MinXText.Name = "MinXText";
			this.MinXText.Size = new System.Drawing.Size(56, 20);
			this.MinXText.TabIndex = 5;
			this.MinXText.Text = "";
			this.MinXText.Leave += new System.EventHandler(this.OnMinXLeave);
			// 
			// label3
			// 
			this.label3.Location = new System.Drawing.Point(8, 40);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(48, 24);
			this.label3.TabIndex = 4;
			this.label3.Text = "MinX";
			this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// MaxXText
			// 
			this.MaxXText.Location = new System.Drawing.Point(64, 72);
			this.MaxXText.Name = "MaxXText";
			this.MaxXText.Size = new System.Drawing.Size(56, 20);
			this.MaxXText.TabIndex = 7;
			this.MaxXText.Text = "";
			this.MaxXText.Leave += new System.EventHandler(this.OnMaxXLeave);
			// 
			// label4
			// 
			this.label4.Location = new System.Drawing.Point(8, 72);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(48, 24);
			this.label4.TabIndex = 6;
			this.label4.Text = "MaxX";
			this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// MaxYText
			// 
			this.MaxYText.Location = new System.Drawing.Point(192, 72);
			this.MaxYText.Name = "MaxYText";
			this.MaxYText.Size = new System.Drawing.Size(56, 20);
			this.MaxYText.TabIndex = 11;
			this.MaxYText.Text = "";
			this.MaxYText.Leave += new System.EventHandler(this.OnMaxYLeave);
			// 
			// label5
			// 
			this.label5.Location = new System.Drawing.Point(136, 72);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(48, 24);
			this.label5.TabIndex = 10;
			this.label5.Text = "MaxY";
			this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// MinYText
			// 
			this.MinYText.Location = new System.Drawing.Point(192, 40);
			this.MinYText.Name = "MinYText";
			this.MinYText.Size = new System.Drawing.Size(56, 20);
			this.MinYText.TabIndex = 9;
			this.MinYText.Text = "";
			this.MinYText.Leave += new System.EventHandler(this.OnMinYLeave);
			// 
			// label6
			// 
			this.label6.Location = new System.Drawing.Point(136, 40);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(48, 24);
			this.label6.TabIndex = 8;
			this.label6.Text = "MinY";
			this.label6.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// OkBtn
			// 
			this.OkBtn.Location = new System.Drawing.Point(280, 40);
			this.OkBtn.Name = "OkBtn";
			this.OkBtn.Size = new System.Drawing.Size(88, 24);
			this.OkBtn.TabIndex = 12;
			this.OkBtn.Text = "&Ok";
			this.OkBtn.Click += new System.EventHandler(this.OkBtn_Click);
			// 
			// CancelBtn
			// 
			this.CancelBtn.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.CancelBtn.Location = new System.Drawing.Point(280, 72);
			this.CancelBtn.Name = "CancelBtn";
			this.CancelBtn.Size = new System.Drawing.Size(88, 24);
			this.CancelBtn.TabIndex = 13;
			this.CancelBtn.Text = "&Cancel";
			// 
			// ScanZone
			// 
			this.AcceptButton = this.OkBtn;
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.CancelButton = this.CancelBtn;
			this.ClientSize = new System.Drawing.Size(386, 104);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.CancelBtn,
																		  this.OkBtn,
																		  this.MaxYText,
																		  this.label5,
																		  this.MinYText,
																		  this.label6,
																		  this.MaxXText,
																		  this.label4,
																		  this.MinXText,
																		  this.label3,
																		  this.OutnameText,
																		  this.label2,
																		  this.SeriesText,
																		  this.label1});
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
			this.Name = "ScanZone";
			this.Text = "ScanZone";
			this.ResumeLayout(false);

		}
		#endregion

		private void OnSeriesLeave(object sender, System.EventArgs e)
		{
			try
			{
				Zone.Series = Convert.ToInt64(SeriesText.Text);
			}
			catch (Exception)
			{
				SeriesText.Text = Zone.Series.ToString();
			}
		}

		private void OnMinXLeave(object sender, System.EventArgs e)
		{
			try
			{
				Zone.MinX = Convert.ToDouble(MinXText.Text);
			}
			catch (Exception)
			{
				MinXText.Text = Zone.MinX.ToString();
			}		
		}

		private void OnMaxXLeave(object sender, System.EventArgs e)
		{
			try
			{
				Zone.MaxX = Convert.ToDouble(MaxXText.Text);
			}
			catch (Exception)
			{
				MaxXText.Text = Zone.MaxX.ToString();
			}				
		}

		private void OnMinYLeave(object sender, System.EventArgs e)
		{
			try
			{
				Zone.MinY = Convert.ToDouble(MinYText.Text);
			}
			catch (Exception)
			{
				MinYText.Text = Zone.MinY.ToString();
			}				
		}

		private void OnMaxYLeave(object sender, System.EventArgs e)
		{
			try
			{
				Zone.MaxY = Convert.ToDouble(MaxYText.Text);
			}
			catch (Exception)
			{
				MaxYText.Text = Zone.MaxY.ToString();
			}				
		}

		private void OnOutnameLeave(object sender, System.EventArgs e)
		{
			Zone.Outname = OutnameText.Text;
		}

		private void OkBtn_Click(object sender, System.EventArgs e)
		{
			DialogResult = DialogResult.OK;
			Close();
		}
	}
}
