using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace SySal.Executables.VertigoScan6Server_Win
{
    public partial class MainForm : Form
    {
        class ServerEntry
        {
            public string Name;

            public SySal.DAQSystem.TrackingServer Server;

            public ServerEntry(string name)
            {
                Name = name;
                Server = new SySal.DAQSystem.TrackingServer(new SySal.DAQSystem.dNotifyCall(NotifyCall), new SySal.DAQSystem.dNotifyTracks(NotifyTracks), new SySal.DAQSystem.dNotifyError(NotifyError));
                LastDuration = System.TimeSpan.FromMinutes(100.0);
            }

            public System.DateTime LastStart;

            public System.TimeSpan LastDuration;

            public int Calls = 0;

            public int TotalMilliSeconds = 0;

            public int CallsLastMinute = 0;

            public int MilliSecondsLastMinute = 0;

            public int CallsThisMinute = 0;

            public int MilliSecondsThisMinute = 0;

            public long Tracks = 0;

            public long TracksLastMinute = 0;

            public long TracksThisMinute = 0;

            public string LastError = "";

            void NotifyCall(int milliseconds) { CallsThisMinute++; Calls++; TotalMilliSeconds += milliseconds; MilliSecondsThisMinute += milliseconds; }

            void NotifyTracks(int ntracks) { TracksThisMinute += ntracks; Tracks += ntracks;  }

            void NotifyError(string err) { LastError = System.DateTime.Now.ToShortTimeString() +" : " + err; }
        }

        ServerEntry[] m_Servers = null;

        public MainForm()
        {
            InitializeComponent();
            System.Runtime.Remoting.Channels.ChannelServices.RegisterChannel(new System.Runtime.Remoting.Channels.Tcp.TcpChannel(1808), false);
            SySal.OperaDb.OperaDbConnection conn = SySal.OperaDb.OperaDbCredentials.CreateFromRecord().Connect();
            conn.Open();
            System.Data.DataSet ds = new System.Data.DataSet();
            new SySal.OperaDb.OperaDbDataAdapter("SELECT NAME FROM TB_MACHINES WHERE ID_SITE = (SELECT TO_NUMBER(VALUE) FROM OPERA.LZ_SITEVARS WHERE NAME = 'ID_SITE') AND ISSCANNINGSERVER = 1 ORDER BY NAME", conn, null).Fill(ds);
            conn.Close();
            m_Servers = new ServerEntry[ds.Tables[0].Rows.Count];
            int i;
            for (i = 0; i < ds.Tables[0].Rows.Count; i++)
            {
                m_Servers[i] = new ServerEntry(ds.Tables[0].Rows[i][0].ToString());
                System.Runtime.Remoting.RemotingServices.Marshal(m_Servers[i].Server, "TrackServer_" + m_Servers[i].Name + ".rem");
                System.Windows.Forms.ListViewItem lvi = TrackerList.Items.Add(m_Servers[i].Name);
                lvi.SubItems.Add("0");
                lvi.SubItems.Add("0");
                lvi.SubItems.Add("0");
                lvi.SubItems.Add("0");
                lvi.SubItems.Add("0");
                lvi.SubItems.Add("0");
                lvi.SubItems.Add("");
            }
            m_TF = new TestForm();
        }

        private void OnLoad(object sender, EventArgs e)
        {
            RefreshTimer.Enabled = true;
        }

        private void OnRefresh(object sender, EventArgs e)
        {
            int i;
            TrackerList.BeginUpdate();
            System.DateTime current = System.DateTime.Now;            
            for (i = 0; i < m_Servers.Length; i++)
            {
                System.Windows.Forms.ListViewItem lvi = TrackerList.Items[i];
                ServerEntry entry = m_Servers[i];
                lvi.SubItems[1].Text = entry.Calls.ToString();
                lvi.SubItems[2].Text = (entry.TotalMilliSeconds * 0.001f).ToString("F3");
                lvi.SubItems[3].Text = (entry.CallsLastMinute / entry.LastDuration.TotalMinutes).ToString("F0");
                lvi.SubItems[4].Text = (entry.MilliSecondsLastMinute / (600 * entry.LastDuration.TotalMinutes)).ToString("F0");
                lvi.SubItems[5].Text = entry.Tracks.ToString();
                lvi.SubItems[6].Text = (entry.TracksLastMinute / entry.LastDuration.TotalMinutes).ToString("F0");
                lvi.SubItems[7].Text = entry.LastError;
                if ((current - entry.LastStart).TotalSeconds > 60)
                {
                    entry.CallsLastMinute = entry.CallsThisMinute;
                    entry.CallsThisMinute = 0;
                    entry.MilliSecondsLastMinute = entry.MilliSecondsThisMinute;
                    entry.MilliSecondsThisMinute = 0;
                    entry.TracksLastMinute = entry.TracksThisMinute;
                    entry.TracksThisMinute = 0;
                    entry.LastDuration = current - entry.LastStart;
                    entry.LastStart = current;
                }
            }
            TrackerList.EndUpdate();            
        }

        private void CloseButton_Click(object sender, EventArgs e)
        {
            Close();
        }

        TestForm m_TF;

        private void TestButton_Click(object sender, EventArgs e)
        {
            if (m_TF.Visible) return;
            if (TrackerList.SelectedIndices.Count != 1) return;
            m_TF.Server = m_Servers[TrackerList.SelectedIndices[0]].Server;
            m_TF.Show();        
        }

        private void ClearErrButton_Click(object sender, EventArgs e)
        {
            if (TrackerList.SelectedIndices.Count != 1) return;
            m_Servers[TrackerList.SelectedIndices[0]].LastError = "";
            OnRefresh(this, null);
        }
    }
}