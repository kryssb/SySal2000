using System;
using System.Runtime.Remoting;
using System.Runtime.Remoting.Channels;
using System.Runtime.Remoting.Channels.Tcp;

namespace ListScan
{
	/// <summary>
	/// Main executor.
	/// </summary>
	class Exe
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
			if (args.Length != 3)
			{
				Console.WriteLine("ListScan: <scanserver address> <zone list file> <XML scanning configuration file>");
				Console.WriteLine("Zone list file syntax: ");
				Console.WriteLine("  Plate line: <brick>,<plate>,<map init string>");
				Console.WriteLine("  Zone line: <id>,<minx>,<maxx>,<miny>,<maxy>,<output name>");
                Console.WriteLine("  Note: first line must be a Plate line ");
				return;
			}
			System.IO.StreamReader r = new System.IO.StreamReader(args[2]);
			string config = r.ReadToEnd();
			r.Close();

			System.Runtime.Remoting.Channels.ChannelServices.RegisterChannel( new TcpChannel());
			SySal.DAQSystem.ScanServer ScanSrv = (SySal.DAQSystem.ScanServer)System.Runtime.Remoting.RemotingServices.Connect(typeof(SySal.DAQSystem.ScanServer), "tcp://" + args[0] + ":" + ((int)SySal.DAQSystem.OperaPort.ScanServer).ToString() + "/ScanServer.rem");
			ScanSrv.SetScanLayout(config);

            SySal.DAQSystem.Scanning.MountPlateDesc plated = new SySal.DAQSystem.Scanning.MountPlateDesc();
			r = new System.IO.StreamReader(args[1]);

 		//	bool isloaded = false;
            
           
            string line = r.ReadLine() ;
            string [] tokens = line.Split(',');
            if ( tokens.Length != 3 )
            {
					Console.WriteLine("First Line must be a Plate line" );
					return ;
            }

            do
            {
                tokens = line.Split(',');
                if ( ! (tokens.Length == 6 || tokens.Length == 3 ) )
                {
                    Console.WriteLine("Plate line must be in the format:\n<brick>,<plate>,<map init string>");
                    Console.WriteLine("Zone line must be in the format:\n<id>,<minx>,<maxx>,<miny>,<maxy>,<output name>");
                    Console.WriteLine("Skipping line: " + line);
                    continue;
                }
                try
                {
                    if (tokens.Length == 3)
                    {
                        plated.BrickId = Convert.ToInt32(tokens[0]);
                        plated.PlateId = Convert.ToInt32(tokens[1]);
                        plated.MapInitString = tokens[2];
                        plated.TextDesc = "";

                        Console.WriteLine("Load Plate: " + plated.PlateId );
                        if (!ScanSrv.LoadPlate(plated))
                        {
                            Console.WriteLine("ERROR: Unable to LOAD PLATE");
                            return;
                        }

                    } 
                    else if (tokens.Length == 6)
                    {
                        int id;
                        double minx, maxx, miny, maxy;
                        id = Convert.ToInt32(tokens[0]);
                        minx = Convert.ToDouble(tokens[1]);
                        maxx = Convert.ToDouble(tokens[2]);
                        miny = Convert.ToDouble(tokens[3]);
                        maxy = Convert.ToDouble(tokens[4]);
                        Console.WriteLine("  scan zone: " + id + " ( " + minx + ", " + maxx + ", " + miny + ", " + maxx + ", " + minx +")" );
                        SySal.DAQSystem.Scanning.ZoneDesc zd = new SySal.DAQSystem.Scanning.ZoneDesc();
                        zd.Series = id;
                        zd.MinX = minx;
                        zd.MaxX = maxx;
                        zd.MinY = miny;
                        zd.MaxY = maxy;
                        zd.Outname = tokens[5];
                        ScanSrv.Scan(zd);
                    }

                }
                catch (Exception x)
                {
                    Console.WriteLine("Error \n" + x.Message + "\nat line: " + line);
                    Console.WriteLine("Line skipped");
                }
            } while ((line = r.ReadLine()) != null && line.Length > 0);

			Console.WriteLine("List scan complete");
		}

        private static object Exception(string p)
        {
            throw new Exception("The method or operation is not implemented.");
        }
	}
}
