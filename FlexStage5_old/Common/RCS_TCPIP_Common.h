#ifndef _SYSAL_REMOTE_CONTROL_SERVER_TCPIP_COMMON_STRUCTS_
#define _SYSAL_REMOTE_CONTROL_SERVER_TCPIP_COMMON_STRUCTS_

#pragma pack(push)
#pragma pack(1)

namespace RemCtlSrvTCPIP
{
	struct Token
	{
		public:

			unsigned Code;
			unsigned Length;
			unsigned Parity;

		protected:

			unsigned ComputeParity(DWORD *pData = 0) 
			{
				if (!pData) pData = (DWORD *)&Parity + 1;
				unsigned par = Code ^ Length;
				int i;
				for (i = 0; i < Length; i++) par ^= pData[i];
				return ~par;
				};

		};

#define RCS_TCPIP_TOKEN_NULL			0
#define RCS_TCPIP_TOKEN_ACK				0xA1
#define RCS_TCPIP_TOKEN_CFG_S			0xA2
#define RCS_TCPIP_TOKEN_CFG_R			0xA3
#define RCS_TCPIP_TOKEN_GO				0xB1
#define RCS_TCPIP_TOKEN_POS_S			0xB3
#define RCS_TCPIP_TOKEN_POS_R			0xB4
#define RCS_TCPIP_TOKEN_STOP			0xB5
#define RCS_TCPIP_TOKEN_IMG_S			0xC1
#define RCS_TCPIP_TOKEN_IMG_R			0xC2
#define RCS_TCPIP_TOKEN_OVR_S			0xC3
#define RCS_TCPIP_TOKEN_OVR_R			0xC4
#define RCS_TCPIP_TOKEN_SCAN_S			0xD1
#define RCS_TCPIP_TOKEN_SCAN_R			0xD2

#define RCS_TCPIP_ACKSTRING "REM_CNTRL_TCPIP"

	struct Acknowledge : public Token
	{
		char AckString[16];

		Acknowledge()
		{
			Code = RCS_TCPIP_TOKEN_ACK;
			Length = (sizeof(AckString) + sizeof(unsigned) - 1) / sizeof(unsigned);
			strcpy(AckString, RCS_TCPIP_ACKSTRING);
			Parity = ComputeParity();
			};
		};

	struct ConfigureSend : public Token
	{
		ConfigureSend()
		{
			Code = RCS_TCPIP_TOKEN_CFG_S; 
			Length = 0;
			Parity = ComputeParity();
			};
		};

	struct ConfigureReply : public Token
	{
		unsigned ImageWidth;
		unsigned ImageHeight;
		unsigned ImageFormat;
		unsigned ImageOverlayColors;

		ConfigureReply(unsigned imw, unsigned imh, unsigned imfmt, unsigned imovrcol) 
		{
			Code = RCS_TCPIP_TOKEN_CFG_R;
			Length = 4;
			ImageWidth = imw;
			ImageHeight = imh;
			ImageFormat = imfmt;
			ImageOverlayColors = imovrcol;
			Parity = ComputeParity();
			};
		};

	struct Go : public Token
	{
		unsigned Axis;
		float Pos;
		float Speed;
		float Acc;

		Go(unsigned axis, float pos, float speed, float acc) 
		{
			Code = RCS_TCPIP_TOKEN_GO;
			Length = 4;
			Axis = axis;
			Pos = pos;
			Speed = speed;
			Acc = acc;
			Parity = ComputeParity();
			};
		};

	struct PosSend : public Token
	{
		unsigned Axis;

		PosSend(unsigned axis)
		{
			Code = RCS_TCPIP_TOKEN_POS_S;
			Length = 1;
			Axis = axis;
			Parity = ComputeParity();
			};
		};

	struct PosReply : public Token
	{
		unsigned Axis;
		float Pos;

		PosReply(unsigned axis, float pos)
		{
			Code = RCS_TCPIP_TOKEN_POS_R;
			Length = 2;
			Axis = axis;
			Pos = pos;
			Parity = ComputeParity();
			};
		};

	struct Stop : public Token
	{
		unsigned Axis;

		Stop(unsigned axis) 
		{
			Code = RCS_TCPIP_TOKEN_STOP;
			Length = 1;
			Axis = axis;
			Parity = ComputeParity();
			};
		};

	struct ImageSend : public Token
	{
		ImageSend()
		{
			Code = RCS_TCPIP_TOKEN_IMG_S;
			Length = 0;
			Parity = ComputeParity();
			};
		};
	
	struct ImageReply : public Token
	{
		BYTE *pData;

		ImageReply(BYTE *pdata, unsigned length) 
		{
			Code = RCS_TCPIP_TOKEN_IMG_R;
			Length = (length + sizeof(unsigned) - 1) / sizeof(unsigned);
			pData = pdata;
			Parity = ComputeParity((DWORD *)pData);
			};
		};

	struct OverlaySend : public Token
	{
		OverlaySend() 
		{
			Code = RCS_TCPIP_TOKEN_OVR_S;
			Length = 0;
			Parity = ComputeParity();
			};
		};
	
	struct OverlayReply : public Token
	{
		RemCtl_Graphics *pData;

		OverlayReply(RemCtl_Graphics *pdata, unsigned length) 
		{
			Code = RCS_TCPIP_TOKEN_OVR_R;
			Length = length;
			pData = pdata;
			Parity = ComputeParity((DWORD *)pData);
			};
		};

	struct ScanSend : public Token
	{
		float StartZ;
		float EndZ;
		unsigned Frames;
		ScanSend(float startz, float endz, unsigned frames) 
		{
			Code = RCS_TCPIP_TOKEN_SCAN_S;
			Length = 3;
			StartZ = startz;
			EndZ = endz;
			Frames = frames;
			Parity = ComputeParity();
			};
		};

	struct ScanReply : public Token
	{
		unsigned Layer;
		float Z;
		BYTE *pData;

		ScanReply(BYTE *pdata, unsigned length, unsigned layer, float z) 
		{
			Code = RCS_TCPIP_TOKEN_SCAN_R;
			Length = (length + sizeof(unsigned) - 1) / sizeof(unsigned) + 2;
			pData = pdata;
			Layer = layer;
			Z = z;
			Parity = ~ComputeParity((DWORD *)pData);
			Parity ^= Layer;
			Parity ^= *(unsigned *)&Z;
			Parity = ~Parity;
			};
		};

	};

#pragma pack(pop)

#endif