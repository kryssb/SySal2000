#ifndef _SYSAL_TOTAL_SCAN_RECONSTRUCTION_MANAGER_
#define _SYSAL_TOTAL_SCAN_RECONSTRUCTION_MANAGER_

#define USE_MIDL_INCOMPATIBLE_STRUCTS
#include "..\Common\datastructs.h"
#include "..\Common\Vectors.h"
#include "Vectors2.h"
#include "TSReconData.h"

#define POS_ALIGN_DATA_LEN 7

class TSReconstructionManager
{
	public:

		typedef void (*ActionProgressCallBack)(void *pContext, char *Text, float Percent);

		TSReconstructionManager();
		~TSReconstructionManager();
		
		void SetReconstructionData(TSReconData *pTSRD);
		void GetReconstructionData(TSReconData *pTSRD);

		void ClearTracks();

		bool Reconstruct(void *pContext = 0, TSReconstructionManager::ActionProgressCallBack ProgressMonitor = 0, CString *pNotes = 0);
		bool CheckTopology(void *pContext = 0, TSReconstructionManager::ActionProgressCallBack ProgressMonitor = 0, CString *pNotes = 0);

		IO_TS_Reconstruction *AccessReconstruction();
		bool LoadReconstruction(IO_TS_Reconstruction *pTSRec);

		bool StartAdding(int StartSheet, int MaxLayers, Identifier Id, Vector Pos);
		bool AddLayer(TS_LayerInfo *pLayer, bool bResetDepth, bool bAlignSlopes);
		void EndAdding();

		bool SegPtrToIndices(TS_Segment *pSeg, int *i, int *s);

		
	protected:
		bool RefineAlignment(void *pContext = 0, TSReconstructionManager::ActionProgressCallBack ProgressMonitor = 0, CString *pNotes = 0);
		bool CheckTopologicalConsistency();
		void CompactTracks();
		void KillVertex(TS_Vertex *pVtx);
		bool ComputeMultiTrackCrossing(TS_Vertex *pVtx);

		IO_TS_Reconstruction *pTSReconstruction;

		struct Crossing
		{
			Vector Pos;
			TS_Track *pTracks[2];
			bool IsDownstream[2];
			};

		void ResetDepth(TS_LayerInfo *pLayer);
		void AlignSlopes(TS_LayerInfo *pLayer);
		bool IsRemeasure(TS_RawTrack *pTracks, TS_Segment *pSeg1, TS_Segment *pSeg2);	
		bool FormSegments(TS_LayerInfo *pLayer, int Side);
		bool LinkSegments(int BottomLayer, int BottomSide, int TopLayer, int TopSide, bool OptimizeAlignment);
		bool FitTrack(TS_Track *pTSTrack, bool FitEdges = false);
		bool LocalFit(TS_Segment *pStart, int Count, Vector2 *pSlope);

		bool MakeCrossing(TS_Track *T1, TS_Track *T2, Crossing *pC);
		bool MergeCrossings(int Count, Crossing *pC);

		bool Adding;
		int NextLayer;
		
		TSReconData TSRD;
		
	};

#endif