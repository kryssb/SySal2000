using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Runtime.Remoting;
using System.Runtime.Remoting.Channels.Tcp;

namespace Test
{
	/// <summary>
	/// Summary description for ExeForm.
	/// </summary>
	public class ExeForm : System.Windows.Forms.Form
	{
		private System.Windows.Forms.TextBox IPBox;
		private System.Windows.Forms.Button SetScanLayoutButton;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public ExeForm()
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
				if (components != null) 
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
			this.IPBox = new System.Windows.Forms.TextBox();
			this.SetScanLayoutButton = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// IPBox
			// 
			this.IPBox.Location = new System.Drawing.Point(8, 8);
			this.IPBox.Name = "IPBox";
			this.IPBox.Size = new System.Drawing.Size(384, 20);
			this.IPBox.TabIndex = 0;
			this.IPBox.Text = "localhost";
			// 
			// SetScanLayoutButton
			// 
			this.SetScanLayoutButton.Location = new System.Drawing.Point(8, 32);
			this.SetScanLayoutButton.Name = "SetScanLayoutButton";
			this.SetScanLayoutButton.Size = new System.Drawing.Size(96, 24);
			this.SetScanLayoutButton.TabIndex = 1;
			this.SetScanLayoutButton.Text = "Set Scan Layout";
			this.SetScanLayoutButton.Click += new System.EventHandler(this.SetScanLayoutButton_Click);
			// 
			// ExeForm
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(400, 62);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.SetScanLayoutButton,
																		  this.IPBox});
			this.Name = "ExeForm";
			this.Text = "Test";
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			System.Runtime.Remoting.Channels.ChannelServices.RegisterChannel(new TcpChannel());
			Application.Run(new ExeForm());
		}

		private void SetScanLayoutButton_Click(object sender, System.EventArgs e)
		{
			try
			{
				SySal.DAQSystem.ScanServer Srv = (SySal.DAQSystem.ScanServer)System.Runtime.Remoting.RemotingServices.Connect(typeof(SySal.DAQSystem.ScanServer), "tcp://" + IPBox.Text + ":" + (int)SySal.DAQSystem.OperaPort.ScanServer + "/ScanServer.rem");
				OpenFileDialog odlg = new OpenFileDialog();
				odlg.CheckFileExists = true;
				odlg.Filter = "XML files (*.xml)|*.xml";
				if (odlg.ShowDialog() == DialogResult.OK)
				{
					System.IO.StreamReader r = new System.IO.StreamReader(odlg.FileName);
					string xmlstring = r.ReadToEnd();
					r.Close();
					MessageBox.Show("Result: " + Srv.SetScanLayout(xmlstring).ToString());
				}
			}
			catch (Exception x)
			{
				MessageBox.Show(x.ToString(), "Error");
			}
		}
	}
}
