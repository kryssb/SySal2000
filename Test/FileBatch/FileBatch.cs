using System;
using SySal.BasicTypes;
using System.Runtime.Remoting;
using System.Runtime.Remoting.Channels;
using System.Runtime.Remoting.Channels.Tcp;

namespace FileBatch
{
	/// <summary>
	/// Summary description for Exe.
	/// </summary>
	class Exe
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
			//
			// TODO: Add code to start application here
			//
			if (args.Length != 3)
			{
				Console.WriteLine("usage: filebatch <serveraddress> <inputfile> <outputfile>");
				return;
			}
			ChannelServices.RegisterChannel(new TcpChannel());
			SySal.DAQSystem.ScanServer Srv = (SySal.DAQSystem.ScanServer)RemotingServices.Connect(typeof(SySal.DAQSystem.ScanServer), "tcp://" + args[0] + ":" + ((int)(SySal.DAQSystem.OperaPort.ScanServer)).ToString() + "/ScanServer.rem");

			System.IO.StreamReader r = new System.IO.StreamReader(args[1]);
			System.IO.StreamWriter w = new System.IO.StreamWriter(args[2]);
			w.AutoFlush = true;

			int count = 0;
			try
			{
				string [] data = r.ReadLine().Split(' ');
				if (data.Length != 5) throw new Exception("Invalid header");

				SySal.DAQSystem.Scanning.MountPlateDesc mpd = new SySal.DAQSystem.Scanning.MountPlateDesc();
				mpd.Id.Part0 = Convert.ToInt32(data[0]);
				mpd.Id.Part1 = Convert.ToInt32(data[1]);
				mpd.Id.Part2 = Convert.ToInt32(data[2]);
				mpd.Id.Part3 = Convert.ToInt32(data[3]);
				mpd.TextDesc = data[4];
				mpd.MapInitString = r.ReadLine();
				bool ret;
				w.WriteLine("LoadPlate: {0} {1} {2} {3} {4} - Result: {5}", data[0], data[1], data[2], data[3], data[4], (ret = Srv.LoadPlate(mpd)));
				if (ret == false) throw new Exception("Plate not loaded");
				while(true)
				{
					string line;
					line = r.ReadLine();
					if (line == null) break;
					data = line.Split(' ');
					if (data.Length != 9) throw new Exception("Invalid prediction");

					SySal.DAQSystem.Scanning.ZoneDesc zd = new SySal.DAQSystem.Scanning.ZoneDesc();

					zd.Id.Part0 = Convert.ToInt32(data[0]);
					zd.Id.Part1 = Convert.ToInt32(data[1]);
					zd.Id.Part2 = Convert.ToInt32(data[2]);
					zd.Id.Part3 = Convert.ToInt32(data[3]);
					zd.MinX = Convert.ToSingle(data[4]);
					zd.MaxX = Convert.ToSingle(data[5]);
					zd.MinY = Convert.ToSingle(data[6]);
					zd.MaxY = Convert.ToSingle(data[7]);
					zd.Outname = data[8];
					w.WriteLine("Scan: {0} {1} {2} {3} {4} {5} {6} {7} {8} - Result: {9} - at {10}", 
						data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8],
						Srv.Scan(zd), System.DateTime.Now);
					Console.WriteLine("Prediction {0} complete", ++count);
				}
				w.WriteLine("UnloadPlate: - Result: {0}", Srv.UnloadPlate());
			}
			catch (Exception x)
			{
				w.WriteLine("Batch Interrupted at {0}", System.DateTime.Now);
				w.WriteLine("Reason: {0}", x.Message);
				w.WriteLine("Details: {0}", x.ToString()); 
			}
			Console.WriteLine("Batch finished");
			w.Close();
			r.Close();
		}
	}
}
