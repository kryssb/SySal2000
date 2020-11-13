#ifndef _SYSAL_ROOT_INTERFACE_STRUCTS_
#define _SYSAL_ROOT_INTERFACE_STRUCTS_ 1

	struct TLGHeader
	{
		Int_t Id0;
		Int_t Id1;
		Int_t Id2;
		Int_t Id3;
		Double_t CenterX;
		Double_t CenterY;
		Double_t MinX;
		Double_t MaxX;
		Double_t MinY;
		Double_t MaxY;
		Int_t TopTracks;
		Int_t BottomTracks;
		Int_t BaseTracks;
		Int_t Fields;
		Double_t TopExt;
		Double_t TopInt;
		Double_t BottomInt;
		Double_t BottomExt;
	};

	struct TLGBaseTrack
	{
		Int_t AreaSum;
		Int_t Grains;
		Double_t InterceptX;
		Double_t InterceptY;
		Double_t InterceptZ;
		Double_t SlopeX;
		Double_t SlopeY;
		Double_t Sigma;
		Int_t Id;
		Int_t IdT;
		Int_t IdB;
	};

	struct TLGEmulsionTrack
	{
		Int_t Id;
		Int_t Field;
		Int_t AreaSum;
		Int_t Grains;
		Double_t InterceptX;
		Double_t InterceptY;
		Double_t InterceptZ;
		Double_t SlopeX;
		Double_t SlopeY;
		Double_t Sigma;
		Double_t TopZ;
		Double_t BottomZ;
	};

	struct TLGEmulsionTrackRawData
	{
		Int_t Fragment;
		Int_t View;
		Int_t Track;
	};

	struct RWDHeader
	{
		Int_t Id0;
		Int_t Id1;
		Int_t Id2;
		Int_t Id3;
		Int_t Index;
		Int_t StartView;
		Int_t Views;
		Int_t CodingMode;
		Int_t TopLayers;
		Int_t BottomLayers;
		Int_t TopTracks;
		Int_t BottomTracks;
		Int_t TopGrains;
		Int_t BottomGrains;
	};

	struct RWDView
	{
		Int_t Id;
		Int_t TileX;
		Int_t TileY;
		Int_t TopTracks;
		Int_t BottomTracks;
		Int_t TopFlags;
		Int_t BottomFlags;
		Int_t TopLayers;
		Int_t BottomLayers;
	};

	struct RWDViewMap
	{
		Double_t TopExt;
		Double_t TopInt;
		Double_t BottomInt;
		Double_t BottomExt;
		Double_t TopPosX;
		Double_t TopPosY;
		Double_t TopMapPosX;
		Double_t TopMapPosY;
		Double_t TopMapMXX;
		Double_t TopMapMXY;
		Double_t TopMapMYX;
		Double_t TopMapMYY;
		Double_t BottomPosX;
		Double_t BottomPosY;
		Double_t BottomMapPosX;
		Double_t BottomMapPosY;
		Double_t BottomMapMXX;
		Double_t BottomMapMXY;
		Double_t BottomMapMYX;
		Double_t BottomMapMYY;
	};

	struct RWDLayer
	{
		Int_t Id;
		Int_t Grains;
		Double_t Z;
	};

	struct RWDEmulsionTrack
	{
		Int_t AreaSum;
		Int_t Grains;
		Double_t InterceptX;
		Double_t InterceptY;
		Double_t InterceptZ;
		Double_t SlopeX;
		Double_t SlopeY;
		Double_t Sigma;
		Double_t TopZ;
		Double_t BottomZ;
		Int_t Id;
		Int_t View;
		Int_t Fragment;
		Int_t FirstGrain;
	};

	struct RWDGrain
	{
		Double_t X;
		Double_t Y;
		Double_t Z;
		Int_t Area;
		Int_t Id;
	};
	
	struct TSRHeader
	{
		Int_t Id0;
		Int_t Id1;
		Int_t Id2;
		Int_t Id3;
		Double_t MinX;
		Double_t MaxX;
		Double_t MinY;
		Double_t MaxY;
		Double_t MinZ;
		Double_t MaxZ;
		Int_t Sheets;
		Int_t Tracks;
		Int_t Vertices;
		Int_t MaxTracksInSegment;
		Double_t RefCenterX;
		Double_t RefCenterY;
		Double_t RefCenterZ;
		Int_t Segments;
	};

	struct TSRLayer
	{
		Int_t Id;
		Int_t SheetId;
		Double_t DownstreamExt;
		Double_t DownstreamInt;
		Double_t UpstreamInt;
		Double_t UpstreamExt;
		Double_t RefCenterX;
		Double_t RefCenterY;
		Double_t RefCenterZ;
		Int_t Segments;
		Int_t FirstSegment;
	};

	struct TSRAlignment
	{
		Double_t DeformationXX;
		Double_t DeformationXY;
		Double_t DeformationYX;
		Double_t DeformationYY;
		Double_t TranslationX;
		Double_t TranslationY;
		Double_t TranslationZ;
		Double_t DeltaSlopeX;
		Double_t DeltaSlopeY;
		Double_t DeltaShrinkX;
		Double_t DeltaShrinkY;
	};

	struct TSRSegment
	{
		Int_t AreaSum;
		Int_t Grains;
		Double_t InterceptX;
		Double_t InterceptY;
		Double_t InterceptZ;
		Double_t SlopeX;
		Double_t SlopeY;
		Double_t Sigma;
		Double_t TopZ;
		Double_t BottomZ;
		Int_t BaseTrackId;
		Int_t LayerOwnerId;
		Int_t LayerId;
		Int_t TrackOwnerId;
		Int_t TrackId;
		Int_t TrackLength;
	};

	struct TSRTrack
	{
		Double_t DownstreamZeroX;
		Double_t DownstreamZeroY;
		Double_t DownstreamSlopeX;
		Double_t DownstreamSlopeY;
		Double_t UpstreamZeroX;
		Double_t UpstreamZeroY;
		Double_t UpstreamSlopeX;
		Double_t UpstreamSlopeY;
		Int_t Id;
		Int_t Segments;
		Int_t FirstSegment;
		Int_t UpstreamVertexId;
		Int_t DownstreamVertexId;
	};

	struct TSRTrackSegment
	{
		Int_t LayerOwnerId;
		Int_t LayerId;
	};

	struct TSRVertexTrack
	{
		Int_t TrackId;
		Int_t IsUpstream;
	};

	struct TSRVertex
	{
		Double_t X;
		Double_t Y;
		Double_t Z;
		Double_t AverageDistance;
		Double_t DeltaX;
		Double_t DeltaY;
		Int_t Id;
		Int_t Tracks;
		Int_t FirstTrack;
	};


#endif
