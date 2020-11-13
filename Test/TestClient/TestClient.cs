using System;
using System.Runtime.Remoting;
using System.Runtime.Remoting.Channels;
using System.Runtime.Remoting.Channels.Tcp;
using SySal.BasicTypes;
using SySal.DAQSystem;
using SySal.DAQSystem.Scanning;

namespace TestClient
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
			ChannelServices.RegisterChannel(new TcpChannel());
			SySal.DAQSystem.ScanServer Srv = (SySal.DAQSystem.ScanServer)RemotingServices.Connect(typeof(SySal.DAQSystem.ScanServer), "tcp://" + args[0] + ":1777/ScanServer.rem");

			do
			{
				string [] data = Console.ReadLine().Split(' ');
				if (data.Length == 9)
				{
					ZoneDesc zone;
					zone.Id.Part0 = Convert.ToInt32(data[0]);
					zone.Id.Part1 = Convert.ToInt32(data[1]);
					zone.Id.Part2 = Convert.ToInt32(data[2]);
					zone.Id.Part3 = Convert.ToInt32(data[3]);
					zone.MinX = Convert.ToSingle(data[4]);
					zone.MaxX = Convert.ToSingle(data[5]);
					zone.MinY = Convert.ToSingle(data[6]);
					zone.MaxY = Convert.ToSingle(data[7]);
					zone.Outname = data[8];
					Console.WriteLine("ScanResult: {0}", Srv.Scan(zone));
				}
				else if (data.Length == 5)
				{
					MountPlateDesc plate;
					plate.Id.Part0 = Convert.ToInt32(data[0]);
					plate.Id.Part1 = Convert.ToInt32(data[1]);
					plate.Id.Part2 = Convert.ToInt32(data[2]);
					plate.Id.Part3 = Convert.ToInt32(data[3]);
					plate.TextDesc = data[4];
					Console.WriteLine("LoadPlateResult: {0}", Srv.LoadPlate(plate));
				}
				else if (data.Length == 1)
				{
					Console.WriteLine("UnloadPlateResult: {0}", Srv.UnloadPlate());
				}
				else Console.WriteLine("Unknown command");
			}
			while (true);
		}
	}
}
