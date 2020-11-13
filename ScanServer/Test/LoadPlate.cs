using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace Test
{
	/// <summary>
	/// Summary description for LoadPlate.
	/// </summary>
	public class LoadPlate : System.Windows.Forms.Form
	{
		public long BrickId;

		public long PlateId;

		public string MapInitString;

		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox BrickText;
		private System.Windows.Forms.TextBox PlateText;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox MapInitText;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Button OkBtn;
		private System.Windows.Forms.Button CancelBtn;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public LoadPlate()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
			BrickText.Text = BrickId.ToString();
			PlateText.Text = PlateId.ToString();
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
			this.BrickText = new System.Windows.Forms.TextBox();
			this.PlateText = new System.Windows.Forms.TextBox();
			this.label2 = new System.Windows.Forms.Label();
			this.MapInitText = new System.Windows.Forms.TextBox();
			this.label3 = new System.Windows.Forms.Label();
			this.OkBtn = new System.Windows.Forms.Button();
			this.CancelBtn = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(8, 8);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(64, 24);
			this.label1.TabIndex = 0;
			this.label1.Text = "Brick #";
			this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// BrickText
			// 
			this.BrickText.Location = new System.Drawing.Point(72, 8);
			this.BrickText.Name = "BrickText";
			this.BrickText.Size = new System.Drawing.Size(48, 20);
			this.BrickText.TabIndex = 1;
			this.BrickText.Text = "";
			this.BrickText.Leave += new System.EventHandler(this.OnBrickLeave);
			// 
			// PlateText
			// 
			this.PlateText.Location = new System.Drawing.Point(232, 8);
			this.PlateText.Name = "PlateText";
			this.PlateText.Size = new System.Drawing.Size(48, 20);
			this.PlateText.TabIndex = 3;
			this.PlateText.Text = "";
			this.PlateText.Leave += new System.EventHandler(this.OnPlateLeave);
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(168, 8);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(64, 24);
			this.label2.TabIndex = 2;
			this.label2.Text = "Plate #";
			this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// MapInitText
			// 
			this.MapInitText.Location = new System.Drawing.Point(8, 64);
			this.MapInitText.Name = "MapInitText";
			this.MapInitText.Size = new System.Drawing.Size(272, 20);
			this.MapInitText.TabIndex = 5;
			this.MapInitText.Text = "";
			this.MapInitText.Leave += new System.EventHandler(this.OnMapInitLeave);
			// 
			// label3
			// 
			this.label3.Location = new System.Drawing.Point(8, 40);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(96, 24);
			this.label3.TabIndex = 4;
			this.label3.Text = "Map init string";
			this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// OkBtn
			// 
			this.OkBtn.Location = new System.Drawing.Point(8, 96);
			this.OkBtn.Name = "OkBtn";
			this.OkBtn.Size = new System.Drawing.Size(56, 24);
			this.OkBtn.TabIndex = 6;
			this.OkBtn.Text = "&Ok";
			this.OkBtn.Click += new System.EventHandler(this.OkBtn_Click);
			// 
			// CancelBtn
			// 
			this.CancelBtn.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.CancelBtn.Location = new System.Drawing.Point(224, 96);
			this.CancelBtn.Name = "CancelBtn";
			this.CancelBtn.Size = new System.Drawing.Size(56, 24);
			this.CancelBtn.TabIndex = 7;
			this.CancelBtn.Text = "&Cancel";
			// 
			// LoadPlate
			// 
			this.AcceptButton = this.OkBtn;
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.CancelButton = this.CancelBtn;
			this.ClientSize = new System.Drawing.Size(290, 128);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.CancelBtn,
																		  this.OkBtn,
																		  this.MapInitText,
																		  this.label3,
																		  this.PlateText,
																		  this.label2,
																		  this.BrickText,
																		  this.label1});
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
			this.Name = "LoadPlate";
			this.Text = "Load Plate parameters";
			this.ResumeLayout(false);

		}
		#endregion

		private void OnBrickLeave(object sender, System.EventArgs e)
		{
			try
			{
				BrickId = Convert.ToInt64(BrickText.Text);
			}
			catch (Exception)
			{
				BrickText.Text = BrickId.ToString();
			}
		}

		private void OnPlateLeave(object sender, System.EventArgs e)
		{
			try
			{
				PlateId = Convert.ToInt64(PlateText.Text);
			}
			catch (Exception)
			{
				PlateText.Text = PlateId.ToString();
			}		
		}

		private void OnMapInitLeave(object sender, System.EventArgs e)
		{
			MapInitString = MapInitText.Text;
		}

		private void OkBtn_Click(object sender, System.EventArgs e)
		{
			DialogResult = DialogResult.OK;
			Close();
		}
	}
}
