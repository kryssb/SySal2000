using System;
using SySal;
using SySal.BasicTypes;
using SySal.DAQSystem.Scanning;
using System.Runtime.Remoting;
using System.Runtime.Remoting.Channels;
using System.Runtime.Remoting.Channels.Tcp;

namespace CSTrackSearch
{
	/// <summary>
	/// Main executor class.
	/// </summary>
	class Exe
	{
		static public StripesFragLink2.StripesFragmentLinker SFL = new StripesFragLink2.StripesFragmentLinker();

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
			//
			// TODO: Add code to start application here
			//
			if (args.Length != 4)
			{
				Console.WriteLine("usage: CSTrackSearch <server> <input file> <link file> <output file>");
				return;
			}
			System.Runtime.Remoting.Channels.ChannelServices.RegisterChannel(new TcpChannel());
			SySal.DAQSystem.ScanServer Srv = (SySal.DAQSystem.ScanServer)System.Runtime.Remoting.RemotingServices.Connect(typeof(SySal.DAQSystem.ScanServer), "tcp://" + args[0] + ":1777/ScanServer.rem");
			System.IO.StreamReader inf = new System.IO.StreamReader(args[1]);
			SySal.DAQSystem.Scanning.MountPlateDesc mpd;
			mpd.Id.Part0 = mpd.Id.Part1 = mpd.Id.Part2 = mpd.Id.Part3 = 0;
			mpd.TextDesc = inf.ReadLine();
			Srv.LoadPlate(mpd);

			StripesFragLink2.StripesFragmentLinker sfl = new StripesFragLink2.StripesFragmentLinker();

			System.IO.FileStream sff = new System.IO.FileStream(args[2], System.IO.FileMode.Open, System.IO.FileAccess.Read);
			System.Xml.Serialization.XmlSerializer xmls = new System.Xml.Serialization.XmlSerializer(typeof(StripesFragLink2.Configuration));
			StripesFragLink2.Configuration sfc = (StripesFragLink2.Configuration)xmls.Deserialize(sff);
			SFL.Config = sfc;
			sff.Close();

			System.IO.StreamWriter outf = new System.IO.StreamWriter(args[3]);
			outf.AutoFlush = true;
			
			System.DateTime Start = System.DateTime.Now;
			Console.WriteLine("Batch started. Time: " + Start.ToString());

			string line;
			int pos;
			while ((line = inf.ReadLine()).Length > 0)
			{
				pos = 0;
				Identifier Id;
				double px, py, sx, sy, ptol, stol;
				int minpts;
				Id.Part0 = Convert.ToInt32(GetNextToken(line, ref pos));
				Id.Part1 = Convert.ToInt32(GetNextToken(line, ref pos));
				Id.Part2 = Convert.ToInt32(GetNextToken(line, ref pos));
				Id.Part3 = Convert.ToInt32(GetNextToken(line, ref pos));
				px = Convert.ToDouble(GetNextToken(line, ref pos)); 
				py = Convert.ToDouble(GetNextToken(line, ref pos));
				sx = Convert.ToDouble(GetNextToken(line, ref pos));
				sy = Convert.ToDouble(GetNextToken(line, ref pos));
				minpts = Convert.ToInt32(GetNextToken(line, ref pos));
				ptol = Convert.ToDouble(GetNextToken(line, ref pos));
				stol = Convert.ToDouble(GetNextToken(line, ref pos));
				SySal.DAQSystem.Scanning.ZoneDesc zd;
				zd.Id = Id;
				zd.MinX = px - ptol;
				zd.MaxX = px + ptol;
				zd.MinY = py - ptol;
				zd.MaxY = py + ptol;
				zd.Outname = GetNextToken(line, ref pos).Trim();
				bool success;
				Console.WriteLine("Zone {0}/{1}/{2}/{3} {4} {5} {6} {7} {8}", zd.Id.Part0, zd.Id.Part1, zd.Id.Part2, zd.Id.Part3, px, py, sx, sy, (success = Srv.Scan(zd)));
				if (success)
					new DataProcessor(zd.Id, zd.Outname, px, py, sx, sy, minpts, ptol, stol, outf).Process();
			}
			inf.Close();
			outf.Close();
			Console.WriteLine("Batch finished. Total time: " + (System.DateTime.Now - Start).ToString());
		}

		static string GetNextToken(string s, ref int pos)
		{
			string n = "";
			while (pos < s.Length && (s[pos] == ' ' || s[pos] == '\t')) n += s[pos++];
			while (pos < s.Length && (s[pos] != ' ' && s[pos] != '\t')) n += s[pos++];
			return n;
		}
	}

	class DataProcessor
	{
		string BaseName;
		double Px, Py, Sx, Sy, PTol, STol;
		Identifier Id;
		int MinPts;
		System.IO.StreamWriter OutF;
		public DataProcessor(Identifier id, string basename, double px, double py, double sx, double sy, int minpts, double ptol, double stol, System.IO.StreamWriter outf)
		{
			BaseName = basename;
			Px = px;
			Py = py;
			Sx = sx;
			Sy = sy;
			PTol = ptol;
			STol = stol;
			OutF = outf;
			Id = id;
			MinPts = minpts;
		}

		public SySal.Scanning.Plate.IO.OPERA.RawData.Fragment LoadFragment(uint index)
		{
			System.IO.FileStream f;
			f = new System.IO.FileStream(BaseName + ".rwd." + Convert.ToString(index, 16).PadLeft(8, '0'), System.IO.FileMode.Open, System.IO.FileAccess.Read);
			SySal.Scanning.Plate.IO.OPERA.RawData.Fragment Frag = new SySal.Scanning.Plate.IO.OPERA.RawData.Fragment(f);
			f.Close();
			return Frag;
		}		

		public void Process()
		{
			System.IO.FileStream f = new System.IO.FileStream(BaseName + ".rwc", System.IO.FileMode.Open, System.IO.FileAccess.Read);
			SySal.Scanning.Plate.IO.OPERA.RawData.Catalog Cat = new SySal.Scanning.Plate.IO.OPERA.RawData.Catalog(f);
			f.Close();
			Exe.SFL.Load = new SySal.Scanning.PostProcessing.dLoadFragment(LoadFragment);
			SySal.Scanning.Plate.IO.OPERA.LinkedZone lz = Exe.SFL.Link(Cat);
			System.IO.FileStream g = new System.IO.FileStream(BaseName + ".tlg", System.IO.FileMode.Create, System.IO.FileAccess.Write);
			lz.Save(g);
			g.Flush();
			g.Close();
			double bestdlink = STol;
			SySal.Scanning.MIPBaseTrack besttrack = null;
			int i;
			for (i = 0; i < lz.Length; i++)
			{
				if (lz[i].Info.Count >= MinPts)
				{
					double dsx, dsy, dlink;
					dsx = lz[i].Info.Slope.X - Sx;
					dsy = lz[i].Info.Slope.Y - Sy;
					dlink = Math.Sqrt(dsx * dsx + dsy * dsy);
					if (dlink < bestdlink)
					{
						besttrack = lz[i];
						bestdlink = dlink;
					}
				}
			}
			if (besttrack != null)
				OutF.WriteLine("{0} {1} {2} {3} {4} {5} {6} {7} {8} {9} 1 {10} {11} {12} {13} {14} {15} {16} {17}",
					Id.Part0, Id.Part1, Id.Part2, Id.Part3, Px, Py, Sx, Sy, PTol, STol,
					besttrack.Info.Intercept.X, besttrack.Info.Intercept.Y, besttrack.Info.Slope.X, besttrack.Info.Slope.Y,
					besttrack.Info.Intercept.X - Px, besttrack.Info.Intercept.Y - Py, besttrack.Info.Slope.X - Sx, besttrack.Info.Slope.Y - Sy);
			else
				OutF.WriteLine("{0} {1} {2} {3} {4} {5} {6} {7} {8} {9} 0 0 0 0 0 0 0 0 0",
					Id.Part0, Id.Part1, Id.Part2, Id.Part3, Px, Py, Sx, Sy, PTol, STol);
		}
	}
}
