#include "StdAfx.h"
#include "GenesisClass.h"

// Internal Functions

#define PACKED_CYCLE (32 / PACKED_BLOCK)
#define DUP_PACKED_BLOCK 0x00080008
#define DUP_PACKED_CYCLE 0x00200020

int CGenesis::GetSegments(BYTE *ScanLine, unsigned Length, Segment *SegSpace, PrecompSegmentBlock *PrecData)
{
	/* 
		REGISTERS USAGE 

		EAX		->	32 Pixels block read (current in AL)		
		EBX		->	Current scan position (dword pointer) + Current position (unsigned, step = 8)
		EDX		->	computation register (loaded with offsets)
		ECX		->	number of precomputed segments (1 byte), 
						number of in-block cycles  = 32 / PACKED_BLOCK (1 byte),
						remaining cycles								
		ESI		->	PrecData base pointer
		EDI		->	Current segment position (quadword pointer)

	*/

	int NumberOfSegments;
	unsigned short sLength = Length / 32;

	union
	{
		BYTE *pScanLine;
		unsigned DupCurrPos;
		} Buff;
	
	Buff.pScanLine = ScanLine;

// Init all registers
	_asm
	{				
				xor esi, esi
				mov edi, dword ptr [SegSpace]
				mov cx, word ptr [sLength]
				xor edx, edx				
				cld
		};

// Start a 4 byte cycle with no open segment (as at startup)
CW:	_asm
	{
				xchg esi, dword ptr [Buff]
				lodsd
				xchg esi, dword ptr [Buff]
				cmp eax, 0xFFFFFFFF
				jz ZD
				ror ecx, 16
				mov ch, PACKED_CYCLE
		};

// Start a single byte cycle with no open segment
SW:	_asm
	{
				cmp al,0xFF
				jz ZB
				movzx ebx,al
				shl ebx,5
				add ebx, dword ptr [PrecData]
				mov cl, byte ptr [ebx]
		};

// 8 bit loop for segments
PW:	_asm
	{
				add ebx, 4
				mov edx, dword ptr [ebx]
				add edx, esi
				mov dword ptr [edi], edx				
				xor edx, edx
				mov dword ptr [edi + 4], edx
				add edi, 8
				dec cl
				jnz PW
				test al,0x80
				jz S1	
				ror eax, 8				
				add esi, DUP_PACKED_BLOCK
				dec ch
				jnz SW
				ror ecx,16
				dec cx
				jnz CW
				jmp End
		};

// Shortcut for zero byte (WARNING! INVERTED LOGIC!)
ZB:	_asm
	{
				ror eax, 8
				add esi, DUP_PACKED_BLOCK
				dec ch
				jnz SW
				ror ecx, 16
				dec cx
				jnz CW
				jmp End
		};

// Shortcut for zero dword (WARNING! INVERTED LOGIC!)
ZD:	_asm
	{
				add esi, DUP_PACKED_CYCLE
				dec cx
				jnz CW
				jmp End
		};
				
// Branch to enter 1 byte loop with open segment
S1:	_asm
	{
				ror eax,8
				add esi, DUP_PACKED_BLOCK
				dec ch
				jnz SB
				ror ecx,16
				dec cx
				jnz CB
				jmp End
		};

// Start a 4 byte cycle with an open segment
CB:	_asm
	{
				xchg esi, dword ptr [Buff]
				lodsd
				xchg esi, dword ptr [Buff]
				cmp eax, 0xFFFFFFFF
				jz ZD
				ror ecx, 16
				mov ch, PACKED_CYCLE
		};

// Start a single byte cycle with an open segment
SB:	_asm
	{
				cmp al,0xFF
				jz ZB
				movzx ebx,al
				shl ebx,5
				add ebx, dword ptr [PrecData]
				mov cl, byte ptr [ebx]
				test al,1
				jnz PW
				add ebx,4
				mov edx, dword ptr [ebx]
				add edx, esi
				shr edx,16
				mov word ptr [edi - 6], dx
				dec cl
				jnz PW
				test al,0x80
				jz S1
				ror eax,8
				add esi, DUP_PACKED_BLOCK
				dec ch
				jnz SW
				ror ecx,16
				dec cx
				jnz CW
				jmp End
		};

End:	
	_asm
	{
				sub edi, dword ptr [SegSpace];
				shr edi, 3
				mov dword ptr [NumberOfSegments], edi
		};

	return NumberOfSegments;
	};

IntCluster *CGenesis::ChainSegments(Segment *Line1, Segment *Line2, unsigned short SegNum1,
	unsigned short SegNum2, unsigned short YLine, unsigned *PClusterNumber,
	IntCluster *NextFree)
{
	Segment *SegPointer1, *SegPointer2;
	Segment *SegEnd1, *SegEnd2, *Start1;
	IntCluster *ClusterPointer, *ClusterPointer2;
	unsigned int SegLength;
	unsigned int ClusterNumber = *PClusterNumber;
	unsigned int SX, XMax, XMin;	
	double XMaxD, XMinD;

	SegEnd1 = Line1 + SegNum1;
	SegEnd2 = Line2 + SegNum2;
	Start1 = Line1;
	for (SegPointer2 = Line2; (SegPointer2 < SegEnd2) && (NextFree); SegPointer2++)
	{  for (SegPointer1 = Start1; (SegPointer1 < SegEnd1) && (SegPointer2->Left > SegPointer1->Right); SegPointer1++);
		Start1 = SegPointer1;
		for (SegPointer1 = Start1; (SegPointer1 < SegEnd1) && (SegPointer2->Right >= SegPointer1->Left); SegPointer1++)
		{  if (!(SegPointer2->ClusterPointer))
			{	XMaxD = XMax = SegPointer2->Right + 1;
				XMinD = XMin = SegPointer2->Left;
				ClusterPointer = SegPointer2->ClusterPointer = SegPointer1->ClusterPointer;
				SegLength = XMax - XMin;
				ClusterPointer->Area += SegLength;
				ClusterPointer->YSum += YLine * SegLength;
				ClusterPointer->XSum += SX = (XMax * (XMax - 1) - XMin * (XMin - 1)) / 2;
				ClusterPointer->Inertia.IYY += YLine * YLine * SegLength;
				ClusterPointer->Inertia.IXY += YLine * SX;
				ClusterPointer->Inertia.IXX += (XMaxD * (1. + XMaxD * (3. + 2. * XMaxD)) - XMinD * (1. + XMinD * (3. + 2. * XMinD))) / 6.;
				}
			else
			{	ClusterPointer = SegPointer1->ClusterPointer;
				ClusterPointer2 = SegPointer2->ClusterPointer;
				if (ClusterPointer2 != ClusterPointer)
				{	ClusterPointer2->Area += ClusterPointer->Area;
					ClusterPointer2->XSum += ClusterPointer->XSum;
					ClusterPointer2->YSum += ClusterPointer->YSum;
					ClusterPointer2->Inertia.IXX += ClusterPointer->Inertia.IXX;
					ClusterPointer2->Inertia.IXY += ClusterPointer->Inertia.IXY;
					ClusterPointer2->Inertia.IYY += ClusterPointer->Inertia.IYY;
					Segment *Sweep;
					for (Sweep = Start1; Sweep < SegEnd1; Sweep++)
					{  if (Sweep->ClusterPointer == ClusterPointer)
							Sweep->ClusterPointer = ClusterPointer2;
						};
					for (Sweep = Line2; Sweep < SegPointer2; Sweep++)
					{  if (Sweep->ClusterPointer == ClusterPointer)
							Sweep->ClusterPointer = ClusterPointer2;
						};
					ClusterPointer->Area = 0;
					ClusterPointer->NextFree = NextFree;
					NextFree = ClusterPointer;
					ClusterNumber--;
					};
				};
			};
		if (!(SegPointer2->ClusterPointer))
		{  if (ClusterPointer = NextFree)
			{
				NextFree = ClusterPointer->NextFree;
				XMaxD = XMax = SegPointer2->Right + 1;
				XMinD = XMin = SegPointer2->Left;
				SegPointer2->ClusterPointer = ClusterPointer;
				SegLength = XMax - XMin;
				ClusterPointer->Area = SegLength;
				ClusterPointer->YSum = YLine * SegLength;
				ClusterPointer->XSum = SX = (XMax * (XMax - 1) - XMin * (XMin - 1)) / 2;
				ClusterPointer->Inertia.IYY = YLine * YLine * SegLength;
				ClusterPointer->Inertia.IXY = YLine * SX;
				ClusterPointer->Inertia.IXX = (XMaxD * (1. + XMaxD * (3. + 2. * XMaxD)) - XMinD * (1. + XMinD * (3. + 2. * XMinD))) / 6.;
				ClusterNumber++;
				};
			};
		};
	*PClusterNumber = ClusterNumber;
	return NextFree;
	};

DWORD CGenesis::GetClusters(BYTE *ImageBuffer, PrecompSegmentBlock *PrecompData, Cluster *pSpace, int *pMaxNumber, 
	unsigned short Width, unsigned short Height, unsigned short OffX, unsigned short OffY, unsigned short WinWidth, 
	unsigned short WinHeight)
{
	if ((!(VP.SegPointer1)) || (!(VP.SegPointer2)))
	{
		*pMaxNumber = 0;
		return S_FALSE;
		};
	unsigned int ClusterCount = 0;
	unsigned int TempClusterCount;
	unsigned short int YLine;
	Segment *SegmentArray[2];
	Segment *SegSwap;
	unsigned short int SegNum[2];
	IntCluster *ClusterScan, *ClusterEnd, *NextFree, *Dummy;
	float Area;
	int MaxNumber = *pMaxNumber;

	byte *LineBuffer;

	ClusterEnd = ((IntCluster *)pSpace) + MaxNumber - 1;
	for (ClusterScan = ((IntCluster *)pSpace); ClusterScan < ClusterEnd; ClusterScan++)
	{  
		ClusterScan->Area = 0;
		ClusterScan->NextFree = ClusterScan + 1;
		};
	ClusterEnd->Area = 0;
	ClusterEnd->NextFree = 0;
	NextFree = (IntCluster *)pSpace;

	SegmentArray[0] = VP.SegPointer1;
	SegmentArray[1] = VP.SegPointer2;
	SegNum[0] = 0;	
	LineBuffer = ImageBuffer + (Width*(unsigned int)OffY + OffX) / PACKED_BLOCK;
	for (YLine = 0; (YLine < WinHeight) && (NextFree); YLine++)
	{  
		SegNum[1] = GetSegments(LineBuffer, WinWidth, SegmentArray[1], PrecompData);
		NextFree = ChainSegments(SegmentArray[0], SegmentArray[1], SegNum[0],
			SegNum[1], YLine, &ClusterCount, NextFree);
		SegSwap = SegmentArray[0];
		SegmentArray[0] = SegmentArray[1];
		SegmentArray[1] = SegSwap;
		SegNum[0] = SegNum[1];
		LineBuffer += Width / PACKED_BLOCK;
		};

	if (!NextFree) 
	{
		*pMaxNumber = -1;
		return S_FALSE;
		};
	TempClusterCount = 0;
	for (ClusterScan = ((IntCluster *)pSpace); TempClusterCount < ClusterCount; ClusterScan++)
	{	if (ClusterScan->Area)
		{  	Area = ClusterScan->Area;
			ClusterScan->X = ((float)ClusterScan->XSum) / Area;
			ClusterScan->Y = ((float)ClusterScan->YSum) / Area;
			ClusterScan->Inertia.IXY = Area * ClusterScan->X++ * ClusterScan->Y - ClusterScan->Inertia.IXY;
			ClusterScan->Inertia.IXX -= Area * ClusterScan->X * ClusterScan->X;
			ClusterScan->Inertia.IYY -= Area * ClusterScan->Y * ClusterScan->Y;
			ClusterScan->X += OffX;
			ClusterScan->Y += OffY;
			ClusterScan->GrayLevel = ((float)(ClusterScan->GrayLevelSum)) / Area;
			TempClusterCount++;
			};
		};
	ClusterEnd = ((IntCluster *)pSpace + ClusterCount);
	for (ClusterScan = Dummy = (IntCluster *)pSpace; ClusterScan < ClusterEnd;)
		if (Dummy->Area)
		{  *ClusterScan++ = *Dummy++; }
		else
		{  Dummy++; };
	*pMaxNumber = ClusterCount;
	return S_OK;
	};
