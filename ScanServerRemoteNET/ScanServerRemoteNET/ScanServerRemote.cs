using System;
using SySal;
using SySal.BasicTypes;

namespace ScanServerRemoteNET
{
	/// <summary>
	/// ScanServerRemoteClass: performs remote scanning according to requests.
	/// </summary>
	public class ScanServer : MarshalByRefObject
	{
		public ScanServer()
		{
			//
			// TODO: Add constructor logic here
			//
			throw new System.Exception("This is a stub only. Use remote activation.");
		}

		public override object InitializeLifetimeService()
		{
			return null;	
		}

		public bool Scan(Identifier id, float minx, float maxx, float miny, float maxy, string outname)
		{
			throw new System.Exception("This is a stub only. Use remote activation.");		
		}

		public bool LoadPlate(Identifier id, string textid)
		{
			throw new System.Exception("This is a stub only. Use remote activation.");		
		}

		public bool UnloadPlate()
		{
			throw new System.Exception("This is a stub only. Use remote activation.");		
		}

		public bool TestComm(int h)
		{
			throw new System.Exception("This is a stub only. Use remote activation.");		
		}
	}
}
