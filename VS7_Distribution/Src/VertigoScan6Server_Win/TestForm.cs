using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace SySal.Executables.VertigoScan6Server_Win
{
    public partial class TestForm : Form
    {
        string trackerclsid_t = "";
        string trackerclsid_b = "";
        string fitterclsid_t = "";
        string fitterclsid_b = "";
        string trackerconfig_t = "";
        string trackerconfig_b = "";
        string fitterconfig_t = "";
        string fitterconfig_b = "";
        uint grains = 2000;

        internal SySal.DAQSystem.TrackingServer Server = null;

        public TestForm()
        {
            InitializeComponent();
        }

        private void OutRWDButton_Click(object sender, EventArgs e)
        {
            RWDFileSaveDialog.FileName = RWDFileText.Text;
            if (RWDFileSaveDialog.ShowDialog() == DialogResult.OK)
            {
                RWDFileText.Text = RWDFileSaveDialog.FileName;
            }
        }

        private void HideButton_Click(object sender, EventArgs e)
        {
            Visible = false;
        }

        private void OnVisible(object sender, EventArgs e)
        {
            try
            {
                Microsoft.Win32.RegistryKey rk_classes = Microsoft.Win32.RegistryKey.OpenRemoteBaseKey(Microsoft.Win32.RegistryHive.LocalMachine, "").OpenSubKey("Software\\SySal2\\Classes");
                string[] classes = rk_classes.GetSubKeyNames();
                rk_classes.Close();
                ClassList.Items.Clear();
                foreach (string s1 in classes)
                    ClassList.Items.Add(s1);
                rk_classes.Close();
                Microsoft.Win32.RegistryKey rk_configs = Microsoft.Win32.RegistryKey.OpenRemoteBaseKey(Microsoft.Win32.RegistryHive.LocalMachine, "").OpenSubKey("Software\\SySal2\\Configs");
                string[] configs = rk_configs.GetSubKeyNames();
                rk_configs.Close();
                ConfigList.Items.Clear();
                foreach (string s2 in configs)
                    ConfigList.Items.Add(s2);
                rk_configs.Close();
            }
            catch (Exception) { }
        }

        private void PickTrkTButton_Click(object sender, EventArgs e)
        {
            if (ClassList.SelectedItems.Count != 1) return;
            if (ConfigList.SelectedItems.Count != 1) return;
            TrkTText.Text = (trackerclsid_t = ClassList.SelectedItems[0].Text) + " [" + (trackerconfig_t = ConfigList.SelectedItems[0].Text) + "]";
        }

        private void PickTrkBButton_Click(object sender, EventArgs e)
        {
            if (ClassList.SelectedItems.Count != 1) return;
            if (ConfigList.SelectedItems.Count != 1) return;
            TrkBText.Text = (trackerclsid_b = ClassList.SelectedItems[0].Text) + " [" + (trackerconfig_b = ConfigList.SelectedItems[0].Text) + "]";
        }

        private void PickFitTButton_Click(object sender, EventArgs e)
        {
            if (ClassList.SelectedItems.Count != 1) return;
            if (ConfigList.SelectedItems.Count != 1) return;
            FitTText.Text = (fitterclsid_t = ClassList.SelectedItems[0].Text) + " [" + (fitterconfig_t = ConfigList.SelectedItems[0].Text) + "]";
        }

        private void PickFitBButton_Click(object sender, EventArgs e)
        {
            if (ClassList.SelectedItems.Count != 1) return;
            if (ConfigList.SelectedItems.Count != 1) return;
            FitBText.Text = (fitterclsid_b = ClassList.SelectedItems[0].Text) + " [" + (fitterconfig_b = ConfigList.SelectedItems[0].Text) + "]";
        }

        private bool GetByteStreams(string classname, string configname, out byte[] clsid_stream, out byte[] config_stream)
        {
            clsid_stream = null;
            config_stream = null;
            Microsoft.Win32.RegistryKey rk_class = Microsoft.Win32.RegistryKey.OpenRemoteBaseKey(Microsoft.Win32.RegistryHive.LocalMachine, "").OpenSubKey("Software\\SySal2\\Classes\\" + classname);
            string clsidstr = rk_class.GetValue("CLSID").ToString();
            rk_class.Close();
            try
            {
                GuidConverter g = new GuidConverter();
                Guid clsid = (Guid)g.ConvertFromString(clsidstr);
                clsid_stream = clsid.ToByteArray();
                Microsoft.Win32.RegistryKey rk_config = Microsoft.Win32.RegistryKey.OpenRemoteBaseKey(Microsoft.Win32.RegistryHive.LocalMachine, "").OpenSubKey("Software\\SySal2\\Configs\\" + configname);
                string[] names = rk_config.GetValueNames();
                config_stream = new byte[4 + names.Length * 128];
                config_stream[0] = Convert.ToByte(names.Length & 0xff);
                config_stream[1] = Convert.ToByte((names.Length >> 8) & 0xff);
                config_stream[2] = Convert.ToByte((names.Length >> 16) & 0xff);
                config_stream[3] = Convert.ToByte((names.Length >> 24) & 0xff);
                int i, j;
                for (i = 0; i < names.Length; i++)
                {
                    for (j = 0; j < 64 && j < names[i].Length; j++)
                        config_stream[4 + i * 128 + j] = (byte)names[i][j];
                    while (j < 64)
                        config_stream[4 + i * 128 + j++] = (byte)0;
                    string value = rk_config.GetValue(names[i]).ToString();
                    for (j = 0; j < 64 && j < value.Length; j++)
                        config_stream[68 + i * 128 + j] = (byte)value[j];
                    while (j < 64)
                        config_stream[68 + i * 128 + j++] = (byte)0;
                }
                rk_config.Close();
            }
            catch (Exception)
            {
                return false;
            }
            return true;       
        }

        static byte[] CamSpecStream = InitCamSpecStream();

        static byte[] InitCamSpecStream()
        {
            System.IO.MemoryStream memstr = new System.IO.MemoryStream();
            System.IO.BinaryWriter b = new System.IO.BinaryWriter(memstr);
            b.Write((int)1280);
            b.Write((int)1024);
            b.Write((int)8);
            b.Write((int)8);
            b.Write((int)1264);
            b.Write((int)1008);
            b.Write(0.400f);
            b.Write(0.400f);
            b.Write(1.0f);
            b.Flush();
            b.Close();
            return memstr.ToArray();
        }

        private void DoButton_Click(object sender, EventArgs e)
        {
            if (Server == null) return;
            byte[] trackerclsid_stream_t;
            byte[] trackerconfig_stream_t;
            byte[] trackerclsid_stream_b;
            byte[] trackerconfig_stream_b;
            byte[] fitterclsid_stream_t;
            byte[] fitterconfig_stream_t;
            byte[] fitterclsid_stream_b;
            byte[] fitterconfig_stream_b;
            if (!GetByteStreams(trackerclsid_t, trackerconfig_t, out trackerclsid_stream_t, out trackerconfig_stream_t))
            {
                MessageBox.Show("Incorrect top tracker class/config.", "Configuration error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            if (!GetByteStreams(trackerclsid_b, trackerconfig_b, out trackerclsid_stream_b, out trackerconfig_stream_b))
            {
                MessageBox.Show("Incorrect bottom tracker class/config.", "Configuration error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            if (!GetByteStreams(fitterclsid_t, fitterconfig_t, out fitterclsid_stream_t, out fitterconfig_stream_t))
            {
                MessageBox.Show("Incorrect top fitter class/config.", "Configuration error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            if (!GetByteStreams(fitterclsid_b, fitterconfig_b, out fitterclsid_stream_b, out fitterconfig_stream_b))
            {
                MessageBox.Show("Incorrect bottom fitter class/config.", "Configuration error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            const int nviews = 10;
            const int nlayers = 15;
            Server.OpenFragment(RWDFileText.Text, 1, 0, nviews, CamSpecStream, trackerconfig_stream_t, trackerclsid_stream_t, trackerconfig_stream_b, trackerclsid_stream_b, fitterconfig_stream_t, fitterclsid_stream_t, fitterconfig_stream_b, fitterclsid_stream_b, 10000, SaveGrainsCheck.Checked, false, 0.0f, 0.0f, 0.0f, 0.0f);
            int i, j, h;            
            bool sideistop = true;
            float [] Z = new float[nlayers];
            do
            {
                for (i = 0; i < nviews; i++)
                {
                    System.IO.MemoryStream grainstream = new System.IO.MemoryStream((int)nlayers * (sizeof(int) + (sizeof(float) * 2 + sizeof(int)) * (int)grains));
                    System.IO.BinaryWriter w = new System.IO.BinaryWriter(grainstream);
                    for (h = 0; h < nlayers; h++)
                    {
                        w.Write(grains);
                        Z[h] = 245.0f * (sideistop ? 1 : 0) - 3.0f * h;
                        for (j = 0; j < grains; j++)
                        {
                            w.Write(((float)(Rnd.NextDouble() * 1264.0 + 8)));
                            w.Write(((float)(Rnd.NextDouble() * 1008.0 + 8)));
                            w.Write(Rnd.Next(5) + 4);
                        }
                    }
                    w.Flush();
                    w.Close();
                    Server.SendViewSide(i, i, 0, i * 400.0f, 0.0f, i * 400.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, Z, grainstream.ToArray(), sideistop, 245.0f * (sideistop ? 1 : 0), 245.0f * (sideistop ? 1 : 0) - 245.0f, (sideistop ? 0.0f : -200.0f), 1.0f);  
                }
                sideistop = !sideistop;
            }
            while (sideistop == false);            
                
        }

        static System.Random Rnd = new Random();

        private void OnGrainsLeave(object sender, EventArgs e)
        {
            try
            {
                grains = Convert.ToUInt32(GrainsText.Text);
            }
            catch (Exception)
            {
                GrainsText.Text = grains.ToString();
            }
        }
    }
}