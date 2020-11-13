#include "SySalROOT.h"
#include <stdio.h>
#include <stdlib.h>

char ReadByte(FILE *f)
{
	char ret; fread(&ret, 1, 1, f); return ret;
}

void WriteData(char b, FILE *f)
{
	fwrite(&b, 1, 1, f);
}

short int ReadShort(FILE *f)
{
	short int ret; fread(&ret, 2, 1, f); return ret;
}

void WriteData(short s, FILE *f)
{
	fwrite(&s, 2, 1, f);
}

int ReadInt(FILE *f)
{
	int ret; fread(&ret, 4, 1, f); return ret;
}

void WriteData(int i, FILE *f)
{
	fwrite(&i, 4, 1, f);
}

float ReadSingle(FILE *f)
{
	float ret; fread(&ret, 4, 1, f); return ret;
}

void WriteData(float s, FILE *f)
{
	fwrite(&s, 4, 1, f);
}

double ReadDouble(FILE *f)
{
	double ret; fread(&ret, 8, 1, f); return ret;
}

void WriteData(double d, FILE *f)
{
	fwrite(&d, 8, 1, f);
}

double ReadSingleAsDouble(FILE *f)
{
	float ret; fread(&ret, 4, 1, f); return (double)ret;
}

//----------------- TSySalTLG

TSySalTLG::TSySalTLG(TFile *pfile) : pFile(pfile)
{
	pHeader = new TTree("TLGHeader", "TLGHeader"); pHeader->SetDirectory(pFile);
	pBaseTracks = new TTree("TLGBaseTracks", "TLGBaseTracks"); pBaseTracks->SetDirectory(pFile);
	pTopTracks = new TTree("TLGTopTracks", "TLGTopTracks"); pTopTracks->SetDirectory(pFile);
	pBottomTracks = new TTree("TLGBottomTracks", "TLGBottomTracks"); pBottomTracks->SetDirectory(pFile);
};

TSySalTLG::~TSySalTLG()
{
	delete pHeader;
	delete pBaseTracks;
	delete pTopTracks;
	delete pBottomTracks;
}

bool TSySalTLG::LoadTLG(char *tlgfilename)
{
	TLGHeader Header;
	TLGBaseTrack BaseTrack;
	TLGEmulsionTrack EmulsionTrack;
	TLGEmulsionTrackRawData EmulsionTrackIndex;

	FILE *f = 0;
	try
	{
		int i;
		f = fopen(tlgfilename, "rb");
		if (!pHeader->GetBranch("Data")) pHeader->Branch("Data", &Header, "Id0/I:Id1/I:Id2/I:Id3/I:CenterX/D:CenterY/D:MinX/D:MaxX/D:MinY/D:MaxY/D:TopTracks/I:BottomTracks/I:BaseTracks/I:Fields/I:TopExt/D:TopInt/D:BottomInt/D:BottomExt/D");
		char infotype;
		infotype = ReadByte(f);
		short headerformat;
		headerformat = ReadShort(f);
		if (infotype != 0x41) throw 0;
		switch (headerformat)
		{
			case tlgFmtNormalDoubleWithIndex:	break;
			case tlgFmtNormalWithIndex:	break;
			case tlgFmtNormal:	break;
			case tlgFmtNoExtents:	break;
			case tlgFmtOld:	break;
			case tlgFmtOld2: break;

			default: throw 0;
		}
		if (headerformat == tlgFmtOld)
		{
			Header.Id3 = ReadInt(f);
			Header.Id0 = Header.Id1 = Header.Id2 = Header.Id3 = 0;
		}
		else
		{
			Header.Id0 = ReadInt(f);
			Header.Id1 = ReadInt(f);
			Header.Id2 = ReadInt(f);
			Header.Id3 = ReadInt(f);
		}

		if (headerformat == tlgFmtNormalDoubleWithIndex)
		{
			Header.CenterX = ReadDouble(f);
			Header.CenterY = ReadDouble(f);
			Header.MinX = ReadDouble(f);
			Header.MaxX = ReadDouble(f);
			Header.MinY = ReadDouble(f);
			Header.MaxY = ReadDouble(f);
			ReadSingle(f);
			Header.TopTracks = ReadInt(f);
			Header.BottomTracks = ReadInt(f);
			Header.BaseTracks = ReadInt(f);
			Header.Fields = ReadInt(f);
			Header.TopExt = ReadDouble(f);
			Header.TopInt = ReadDouble(f);
			Header.BottomInt = ReadDouble(f);
			Header.BottomExt = ReadDouble(f);
			pHeader->Fill();
			for (i = 0; i < 2 * Header.Fields; i++)
				ReadByte(f);


			TTree *pEmu = pTopTracks;
			int tkcount = Header.TopTracks;
			while (true)
			{
				if (!pEmu->GetBranch("Data")) pEmu->Branch("Data", &EmulsionTrack, "Id/I:Field/I:AreaSum/I:Grains/I:InterceptX/D:InterceptY/D:InterceptZ/D:SlopeX/D:SlopeY/D:Sigma/D:TopZ/D:BottomZ/D");
				for (i = 0; i < tkcount; i++)
				{
					EmulsionTrack.Field = ReadInt(f);
					EmulsionTrack.AreaSum = ReadInt(f);
					EmulsionTrack.Grains = ReadInt(f);
					EmulsionTrack.Id = i;
					EmulsionTrack.InterceptX = ReadDouble(f);
					EmulsionTrack.InterceptY = ReadDouble(f);
					EmulsionTrack.InterceptZ = ReadDouble(f);
					EmulsionTrack.SlopeX = ReadDouble(f);
					EmulsionTrack.SlopeY = ReadDouble(f);
					ReadDouble(f);
					EmulsionTrack.Sigma = ReadDouble(f);
					EmulsionTrack.TopZ = ReadDouble(f);
					EmulsionTrack.BottomZ = ReadDouble(f);
					pEmu->Fill();
				}
				if (pEmu == pTopTracks)
				{
					pEmu = pBottomTracks;
					tkcount = Header.BottomTracks;
				}
				else break;
			}

			if (!pBaseTracks->GetBranch("Data")) pBaseTracks->Branch("Data", &BaseTrack, "AreaSum/I:Grains/I:InterceptX/D:InterceptY/D:InterceptZ/D:SlopeX/D:SlopeY/D:Sigma/D:Id/I:IdT/I:IdB/I");
			for (i = 0; i < Header.BaseTracks; i++)
			{
				BaseTrack.AreaSum = ReadInt(f);
				BaseTrack.Grains = ReadInt(f);
				BaseTrack.InterceptX = ReadDouble(f);
				BaseTrack.InterceptY = ReadDouble(f);
				BaseTrack.InterceptZ = ReadDouble(f);
				BaseTrack.SlopeX = ReadDouble(f);
				BaseTrack.SlopeY = ReadDouble(f);
				ReadDouble(f);
				BaseTrack.Sigma = ReadDouble(f);
				BaseTrack.IdT = ReadInt(f);
				BaseTrack.IdB = ReadInt(f);
				BaseTrack.Id = i;
				pBaseTracks->Fill();
			}

			pEmu = pTopTracks;
			tkcount = Header.TopTracks;
			while (true)
			{
				TBranch *tb = pEmu->GetBranch("Index");
				if (!tb) tb = pEmu->Branch("Index", &EmulsionTrackIndex, "Fragment/I:View/I:Track/I");
				for (i = 0; i < tkcount; i++)
				{
					EmulsionTrackIndex.Fragment = ReadInt(f);
					EmulsionTrackIndex.View = ReadInt(f);
					EmulsionTrackIndex.Track = ReadInt(f);
					tb->Fill();
				}
				if (pEmu == pTopTracks)
				{
					pEmu = pBottomTracks;
					tkcount = Header.BottomTracks;
				}
				else break;
			}
		}
	}
	catch (...)
	{
		if (f) fclose(f);
		return false;
	}
	fclose(f);
	return true;
};

bool TSySalTLG::SaveTLG(char *tlgfilename, int number)
{
	TLGHeader Header;
	TLGBaseTrack BaseTrack;
	TLGEmulsionTrack EmulsionTrack;
	TLGEmulsionTrackRawData EmulsionTrackIndex;
	int btbase = 0, tbase = 0, bbase = 0;
	int i;

	FILE *f = 0;
	try
	{
		pHeader->GetBranch("Data")->SetAddress(&Header);
		Header.BaseTracks = 0;
		Header.TopTracks = 0;
		Header.BottomTracks = 0;
		for (i = 0; i <= number; i++)
		{
			btbase += Header.BaseTracks;
			tbase += Header.TopTracks;
			bbase += Header.BottomTracks;
			pHeader->GetEntry(i);
		}
		f = fopen(tlgfilename, "wb");
		WriteData((char)0x41, f);
		WriteData((short)tlgFmtNormalDoubleWithIndex, f);
		WriteData(Header.Id0, f);
		WriteData(Header.Id1, f);
		WriteData(Header.Id2, f);
		WriteData(Header.Id3, f);
		WriteData(Header.CenterX, f);
		WriteData(Header.CenterY, f);
		WriteData(Header.MinX, f);
		WriteData(Header.MaxX, f);
		WriteData(Header.MinY, f);
		WriteData(Header.MaxY, f);
		WriteData((float)0.0f, f);
		WriteData(Header.TopTracks, f);
		WriteData(Header.BottomTracks, f);
		WriteData(Header.BaseTracks, f);
		WriteData(Header.Fields, f);
		WriteData(Header.TopExt, f);
		WriteData(Header.TopInt, f);
		WriteData(Header.BottomInt, f);
		WriteData(Header.BottomExt, f);
		for (i = 0; i < 2 * Header.Fields; i++)
			WriteData((char)0, f);

		TTree *pEmu = pTopTracks;
		int tkcount = Header.TopTracks;
		int base = tbase;
		while (true)
		{
			pEmu->GetBranch("Data")->SetAddress(&EmulsionTrack);
			for (i = 0; i < tkcount; i++)
			{
				pEmu->GetEntry(tbase + i);
				WriteData(EmulsionTrack.Field, f);
				WriteData(EmulsionTrack.AreaSum, f);
				WriteData(EmulsionTrack.Grains, f);
				WriteData(EmulsionTrack.InterceptX, f);
				WriteData(EmulsionTrack.InterceptY, f);
				WriteData(EmulsionTrack.InterceptZ, f);
				WriteData(EmulsionTrack.SlopeX, f);
				WriteData(EmulsionTrack.SlopeY, f);
				WriteData((double)1.0, f);
				WriteData(EmulsionTrack.Sigma, f);
				WriteData(EmulsionTrack.TopZ, f);
				WriteData(EmulsionTrack.BottomZ, f);
			}
			if (pEmu == pTopTracks)
			{
				pEmu = pBottomTracks;
				tkcount = Header.BottomTracks;
				base = bbase;
			}
			else break;
		}

		pBaseTracks->GetBranch("Data")->SetAddress(&BaseTrack);
		for (i = 0; i < Header.BaseTracks; i++)
		{
			pBaseTracks->GetEntry(btbase + i);
			WriteData(BaseTrack.AreaSum, f);
			WriteData(BaseTrack.Grains, f);
			WriteData(BaseTrack.InterceptX, f);
			WriteData(BaseTrack.InterceptY, f);
			WriteData(BaseTrack.InterceptZ, f);
			WriteData(BaseTrack.SlopeX, f);
			WriteData(BaseTrack.SlopeY, f);
			WriteData((double)1.0, f);
			WriteData(BaseTrack.Sigma, f);
			WriteData(BaseTrack.IdT, f);
			WriteData(BaseTrack.IdB, f);
		}

		pEmu = pTopTracks;
		tkcount = Header.TopTracks;
		base = tbase;
		while (true)
		{
			pEmu->GetBranch("Index")->SetAddress(&EmulsionTrackIndex);
			for (i = 0; i < tkcount; i++)
			{
				pEmu->GetEntry(base + i);
				WriteData(EmulsionTrackIndex.Fragment, f);
				WriteData(EmulsionTrackIndex.View, f);
				WriteData(EmulsionTrackIndex.Track, f);
			}
			if (pEmu == pTopTracks)
			{
				pEmu = pBottomTracks;
				tkcount = Header.BottomTracks;
				base = bbase;
			}
			else break;
		}
	}
	catch (...)
	{
		if (f) fclose(f);
		return false;
	}
	fclose(f);
	return true;
};

//----------------- TSySalRWD

TSySalRWD::TSySalRWD(TFile *pfile) : pFile(pfile)
{
	pHeader = new TTree("RWDHeader", "RWDHeader"); pHeader->SetDirectory(pFile);
	pViews = new TTree("RWDViews", "RWDViews"); pViews->SetDirectory(pFile);
	pTopLayers = new TTree("RWDTopLayers", "RWDTopLayers"); pTopLayers->SetDirectory(pFile);
	pBottomLayers = new TTree("RWDBottomLayers", "RWDBottomLayers"); pBottomLayers->SetDirectory(pFile);
	pTopTracks = new TTree("RWDTopTracks", "RWDTopTracks"); pTopTracks->SetDirectory(pFile);
	pBottomTracks = new TTree("RWDBottomTracks", "RWDBottomTracks"); pBottomTracks->SetDirectory(pFile);
	pTopGrains = new TTree("RWDTopGrains", "RWDTopGrains"); pTopGrains->SetDirectory(pFile);
	pBottomGrains = new TTree("RWDBottomGrains", "RWDBottomGrains"); pBottomGrains->SetDirectory(pFile);
}

TSySalRWD::~TSySalRWD()
{
	delete pHeader;
	delete pViews;
	delete pTopLayers;
	delete pBottomLayers;
	delete pTopTracks;
	delete pBottomTracks;
	delete pTopGrains;
	delete pBottomGrains;
}

bool TSySalRWD::LoadRWD(char *rwdfilename)
{
	RWDHeader Header;
	RWDView View;
	RWDViewMap ViewMap;
	RWDLayer Layer;
	RWDEmulsionTrack Track;
	RWDGrain Grain;

	struct t_tv
	{
		Int_t toptks;
		Int_t bottomtks;
		Int_t topgrs;
		Int_t bottomgrs;
		Int_t toplayers;
		Int_t bottomlayers;
	};

	t_tv *pTempViews = 0;

	FILE *f = 0;
	try
	{
		int i, j, k;
		int topgrcount = 0;
		int bottomgrcount = 0;
		f = fopen(rwdfilename, "rb");
		if (!pHeader->GetBranch("Data")) pHeader->Branch("Data", &Header, "Id0/I:Id1/I:Id2/I:Id3/I:Index/I:StartView/I:Views/I:FragmentCoding/I:TopLayers/I:BottomLayers/I:TopTracks/I:BottomTracks/I:TopGrains/I:BottomGrains/I");
		char infotype;
		infotype = ReadByte(f);
		short headerformat;
		headerformat = ReadShort(f);
		if (infotype != 0x66) throw 0;
		if (headerformat != rwdFmtNormalDouble && headerformat != rwdFmtNormal) throw 0;
		Header.Id0 = ReadInt(f);
		Header.Id1 = ReadInt(f);
		Header.Id2 = ReadInt(f);
		Header.Id3 = ReadInt(f);
		Header.Index = ReadInt(f);
		Header.StartView = ReadInt(f);
		Header.Views = ReadInt(f);
		ReadInt(f);
		Header.CodingMode = ReadInt(f);
		switch(Header.CodingMode)
		{
			case rwdGCNull:
			case rwdGCSuppressed: break;

			default: throw 1;
		}
		for (i = 0; i < 256; i++)
			ReadByte(f);
		Header.TopLayers = Header.BottomLayers = Header.TopTracks = Header.BottomTracks = Header.TopGrains = Header.BottomGrains = 0;

		double (*pReadDouble)(FILE *) = (headerformat == rwdFmtNormalDouble) ? ReadDouble : ReadSingleAsDouble;

		if (headerformat == rwdFmtNormalDouble || headerformat == rwdFmtNormal)
		{
			pTempViews = new t_tv[Header.Views];
			if (!pViews->GetBranch("Data")) pViews->Branch("Data", &View, "Id/I:TileX/I:TileY/I:TopTracks/I:BottomTracks/I:TopFlags/I:BottomFlags/I:TopLayers/I:BottomLayers/I");
			if (!pViews->GetBranch("Map")) pViews->Branch("Map", &ViewMap, "TopExt/D:TopInt/D:BottomInt/D:BottomExt/D:TopPosX/D:TopPosY/D:TopMapPosX/D:TopMapPosY/D:TopMapMXX/D:TopMapMXY/D:TopMapMYX/D:TopMapMYY/D:BottomPosX/D:BottomPosY/D:BottomMapPosX/D:BottomMapPosY/D:BottomMapMXX/D:BottomMapMXY/D:BottomMapMYX/D:BottomMapMYY/D");
			if (!pTopLayers->GetBranch("Data")) pTopLayers->Branch("Data", &Layer, "Id/I:Grains/i:Z/D");
			if (!pBottomLayers->GetBranch("Data")) pBottomLayers->Branch("Data", &Layer, "Id/I:Grains/i:Z/D");
			if (!pTopTracks->GetBranch("Data")) pTopTracks->Branch("Data",&Track, "AreaSum/I:Grains/I:InterceptX/D:InterceptY/D:InterceptZ/D:SlopeX/D:SlopeY/D:Sigma/D:TopZ/D:BottomZ/D:Id/I:View/I:Fragment/I:FirstGrain/I");
			if (!pBottomTracks->GetBranch("Data")) pBottomTracks->Branch("Data",&Track, "AreaSum/I:Grains/I:InterceptX/D:InterceptY/D:InterceptZ/D:SlopeX/D:SlopeY/D:Sigma/D:TopZ/D:BottomZ/D:Id/I:View/I:Fragment/I:FirstGrain/I");
			if (!pTopGrains->GetBranch("Data")) pTopGrains->Branch("Data", &Grain, "X/D:Y/D:Z/D:Area/I:Id/I");
			if (!pBottomGrains->GetBranch("Data")) pBottomGrains->Branch("Data", &Grain, "X/D:Y/D:Z/D:Area/I:Id/I");
			for (i = 0; i < Header.Views; i++)
			{
				View.Id = i;
				View.TileX = ReadInt(f);
				View.TileY = ReadInt(f);
				ViewMap.TopPosX = pReadDouble(f);
				ViewMap.BottomPosX = pReadDouble(f);
				ViewMap.TopPosY = pReadDouble(f);
				ViewMap.BottomPosY = pReadDouble(f);
				ViewMap.TopMapPosX = pReadDouble(f);
				ViewMap.BottomMapPosX = pReadDouble(f);
				ViewMap.TopMapPosY = pReadDouble(f);
				ViewMap.BottomMapPosY = pReadDouble(f);
				ViewMap.TopMapMXX = pReadDouble(f);
				ViewMap.TopMapMXY = pReadDouble(f);
				ViewMap.TopMapMYX = pReadDouble(f);
				ViewMap.TopMapMYY = pReadDouble(f);
				ViewMap.BottomMapMXX = pReadDouble(f);
				ViewMap.BottomMapMXY = pReadDouble(f);
				ViewMap.BottomMapMYX = pReadDouble(f);
				ViewMap.BottomMapMYY = pReadDouble(f);
				View.TopLayers = ReadInt(f);
				View.BottomLayers = ReadInt(f);
				Header.TopLayers += View.TopLayers;
				Header.BottomLayers += View.BottomLayers;
				ViewMap.TopExt = pReadDouble(f);
				ViewMap.TopInt = pReadDouble(f);
				ViewMap.BottomInt = pReadDouble(f);
				ViewMap.BottomExt = pReadDouble(f);
				View.TopFlags = ReadByte(f);
				View.BottomFlags = ReadByte(f);
				View.TopTracks = ReadInt(f);
				View.BottomTracks = ReadInt(f);
				pViews->Fill();
				Header.TopTracks += View.TopTracks;
				Header.BottomTracks += View.BottomTracks;
				pTempViews[i].toptks = View.TopTracks;
				pTempViews[i].bottomtks = View.BottomTracks;
				pTempViews[i].topgrs = 0;
				pTempViews[i].bottomgrs = 0;
				pTempViews[i].toplayers = View.TopLayers;
				pTempViews[i].bottomlayers = View.BottomLayers;
			}
			for (i = 0; i < Header.Views; i++)
			{
				for (j = 0; j < pTempViews[i].toplayers; j++)
				{
					Layer.Id = j;
					Layer.Grains = ReadInt(f);
					Layer.Z = pReadDouble(f);
					pTopLayers->Fill();
				}
				for (j = 0; j < pTempViews[i].bottomlayers; j++)
				{
					Layer.Id = j;
					Layer.Grains = ReadInt(f);
					Layer.Z = pReadDouble(f);
					pBottomLayers->Fill();
				}
			}
			for (i = 0; i < Header.Views; i++)
			{
				for (j = 0; j < 2; j++)
				{
					TTree *pTks = j ? pBottomTracks : pTopTracks;
					int tkcount = j ? pTempViews[i].bottomtks : pTempViews[i].toptks;
					for (k = 0; k < tkcount; k++)
					{
						Track.AreaSum = ReadInt(f);
						Track.Grains = ReadInt(f);
						Track.InterceptX = pReadDouble(f);
						Track.InterceptY = pReadDouble(f);
						Track.InterceptZ = pReadDouble(f);
						Track.SlopeX = pReadDouble(f);
						Track.SlopeY = pReadDouble(f);
						pReadDouble(f);
						Track.Sigma = pReadDouble(f);
						Track.TopZ = pReadDouble(f);
						Track.BottomZ = pReadDouble(f);
						Track.Id = k;
						Track.View = i;
						Track.Fragment = Header.Index;
						Track.FirstGrain = j ? bottomgrcount : topgrcount;
						pTks->Fill();
						if (j == 0)
						{
							topgrcount += Track.Grains;
							pTempViews[i].topgrs += Track.Grains;
						}
						else
						{
							bottomgrcount += Track.Grains;
							pTempViews[i].bottomgrs += Track.Grains;
						}
					}
				}
			}
			if (Header.CodingMode == rwdGCNull)
			{
				Header.TopGrains = topgrcount;
				Header.BottomGrains = bottomgrcount;
				topgrcount = bottomgrcount = 0;
				for (i = 0; i < Header.Views; i++)
				{
					for (j = 0; j < 2; j++)
					{
						TTree *pGrs = j ? pBottomGrains : pTopGrains;
						int grcount = j ? pTempViews[i].bottomgrs : pTempViews[i].topgrs;
						int grbase = j ? bottomgrcount : topgrcount;
						for (k = 0; k < grcount; k++)
						{
							Grain.Area = ReadInt(f) & 0x0000ffff;
							Grain.X = pReadDouble(f);
							Grain.Y = pReadDouble(f);
							Grain.Z = pReadDouble(f);
							Grain.Id = k + grbase;
							pGrs->Fill();
						}
						if (j) bottomgrcount += grcount;
						else topgrcount += grcount;
					}
				}
			}
			pHeader->Fill();
		}
	}
	catch(...)
	{
		if (pTempViews) delete [] pTempViews;
		if (f) fclose(f);
		return false;
	}
	if (pTempViews) delete [] pTempViews;
	fclose(f);
	return true;
}

bool TSySalRWD::SaveRWD(char *rwdfilename, int number)
{
	RWDHeader Header;
	RWDView View;
	RWDViewMap ViewMap;
	RWDLayer Layer;
	RWDEmulsionTrack Track;
	RWDGrain Grain;

	FILE *f = 0;
	try
	{		
		int i, j, k;
		int vbase = 0, ttbase = 0, tbbase = 0, gtbase = 0, gbbase = 0, ltbase = 0, lbbase = 0;
		pHeader->GetBranch("Data")->SetAddress(&Header);
		Header.Views = 0;
		Header.TopGrains = Header.TopLayers = Header.TopTracks = Header.BottomGrains = Header.BottomLayers = Header.BottomTracks = 0;
		for (i = 0; i <= number; i++)
		{
			vbase += Header.Views;
			ltbase += Header.TopLayers;
			lbbase += Header.BottomLayers;
			ttbase += Header.TopTracks;
			tbbase += Header.BottomTracks;
			gtbase += Header.TopGrains;
			gbbase += Header.BottomGrains;
			pHeader->GetEntry(i);
		}
		f = fopen(rwdfilename, "wb");
		WriteData((char)0x66, f);
		WriteData((short)rwdFmtNormalDouble, f);
		WriteData(Header.Id0, f);
		WriteData(Header.Id1, f);
		WriteData(Header.Id2, f);
		WriteData(Header.Id3, f);
		WriteData(Header.Index, f);
		WriteData(Header.StartView, f);
		WriteData(Header.Views, f);
		WriteData((int)0, f);
		WriteData(Header.CodingMode, f);
		for (i = 0; i < 256; i++)
			WriteData((char)0, f);
		
		pViews->GetBranch("Data")->SetAddress(&View);
		pViews->GetBranch("Map")->SetAddress(&ViewMap);
		pTopLayers->GetBranch("Data")->SetAddress(&Layer);
		pBottomLayers->GetBranch("Data")->SetAddress(&Layer);
		pTopTracks->GetBranch("Data")->SetAddress(&Track);
		pBottomTracks->GetBranch("Data")->SetAddress(&Track);
		pTopGrains->GetBranch("Data")->SetAddress(&Grain);
		pBottomGrains->GetBranch("Data")->SetAddress(&Grain);

		for (i = 0; i < Header.Views; i++)
		{
			pViews->GetEntry(vbase + i);
			WriteData(View.TileX, f);
			WriteData(View.TileY, f);
			WriteData(ViewMap.TopPosX, f);
			WriteData(ViewMap.BottomPosX, f);
			WriteData(ViewMap.TopPosY, f);
			WriteData(ViewMap.BottomPosY, f);
			WriteData(ViewMap.TopMapPosX, f);
			WriteData(ViewMap.BottomMapPosX, f);
			WriteData(ViewMap.TopMapPosY, f);
			WriteData(ViewMap.BottomMapPosY, f);
			WriteData(ViewMap.TopMapMXX, f);
			WriteData(ViewMap.TopMapMXY, f);
			WriteData(ViewMap.TopMapMYX, f);
			WriteData(ViewMap.TopMapMYY, f);
			WriteData(ViewMap.BottomMapMXX, f);
			WriteData(ViewMap.BottomMapMXY, f);
			WriteData(ViewMap.BottomMapMYX, f);
			WriteData(ViewMap.BottomMapMYY, f);
			WriteData(View.TopLayers, f);
			WriteData(View.BottomLayers, f);
			WriteData(ViewMap.TopExt, f);
			WriteData(ViewMap.TopInt, f);
			WriteData(ViewMap.BottomInt, f);
			WriteData(ViewMap.BottomExt, f);
			WriteData((char)View.TopFlags, f);
			WriteData((char)View.BottomFlags, f);
			WriteData(View.TopTracks, f);
			WriteData(View.BottomTracks, f);
		}

		for (i = 0; i < Header.Views; i++)
		{
			pViews->GetEntry(vbase + i);
			for (j = 0; j < View.TopLayers; j++)
			{
				pTopLayers->GetEntry(ltbase++);
				WriteData(Layer.Grains, f);
				WriteData(Layer.Z, f);
			}
			for (j = 0; j < View.BottomLayers; j++)
			{
				pBottomLayers->GetEntry(lbbase++);
				WriteData(Layer.Grains, f);
				WriteData(Layer.Z, f);
			}
		}

		int httbase = ttbase;
		int htbbase = tbbase;
		for (i = 0; i < Header.Views; i++)
		{
			pViews->GetEntry(vbase + i);
			for (j = 0; j < View.TopTracks; j++)
			{
				pTopTracks->GetEntry(httbase++);
				WriteData(Track.AreaSum, f);
				WriteData(Track.Grains, f);
				WriteData(Track.InterceptX, f);
				WriteData(Track.InterceptY, f);
				WriteData(Track.InterceptZ, f);
				WriteData(Track.SlopeX, f);
				WriteData(Track.SlopeY, f);
				WriteData((double)1.0, f);
				WriteData(Track.Sigma, f);
				WriteData(Track.TopZ, f);
				WriteData(Track.BottomZ, f);
			}
			for (j = 0; j < View.BottomTracks; j++)
			{
				pBottomTracks->GetEntry(htbbase++);
				WriteData(Track.AreaSum, f);
				WriteData(Track.Grains, f);
				WriteData(Track.InterceptX, f);
				WriteData(Track.InterceptY, f);
				WriteData(Track.InterceptZ, f);
				WriteData(Track.SlopeX, f);
				WriteData(Track.SlopeY, f);
				WriteData((double)1.0, f);
				WriteData(Track.Sigma, f);
				WriteData(Track.TopZ, f);
				WriteData(Track.BottomZ, f);
			}
		}

		if (Header.CodingMode == rwdGCNull)
		{
			for (i = 0; i < Header.Views; i++)
			{
				pViews->GetEntry(vbase++);
				for (j = 0; j < View.TopTracks; j++)
				{
					pTopTracks->GetEntry(ttbase++);
					for (k = 0; k < Track.Grains; k++)
					{
						pTopGrains->GetEntry(gtbase++);
						WriteData(Grain.Area, f);
						WriteData(Grain.X, f);
						WriteData(Grain.Y, f);
						WriteData(Grain.Z, f);
					}
				}
				for (j = 0; j < View.BottomTracks; j++)
				{
					pBottomTracks->GetEntry(tbbase++);
					for (k = 0; k < Track.Grains; k++)
					{
						pBottomGrains->GetEntry(gbbase++);
						WriteData(Grain.Area, f);
						WriteData(Grain.X, f);
						WriteData(Grain.Y, f);
						WriteData(Grain.Z, f);
					}
				}
			}
		}
	}
	catch(...)
	{
		if (f) fclose(f);
		return false;
	}
	fclose(f);
	return true;
}

//----------------- TSySalTSR

TSySalTSR::TSySalTSR(TFile *pfile) : pFile(pfile)
{
	pHeader = new TTree("TSRHeader", "TSRHeader"); pHeader->SetDirectory(pFile);
	pLayers = new TTree("TSRLayers", "TSRLayers"); pLayers->SetDirectory(pFile);
	pSegments = new TTree("TSRSegments", "TSRSegments"); pSegments->SetDirectory(pFile);
	pTracks = new TTree("TSRTracks", "TSRTracks"); pTracks->SetDirectory(pFile);
	pTrackSegments = new TTree("TSRTrackSegments", "TSRTrackSegments"); pTrackSegments->SetDirectory(pFile);
	pVertices = new TTree("TSRVertices", "TSRVertices"); pVertices->SetDirectory(pFile);
	pVertexTracks = new TTree("TSRVertexTracks", "TSRVertexTracks"); pVertexTracks->SetDirectory(pFile);
}

TSySalTSR::~TSySalTSR()
{
	delete pHeader;
	delete pLayers;
	delete pSegments;
	delete pTracks;
	delete pTrackSegments;
	delete pVertices;
	delete pVertexTracks;
}

bool TSySalTSR::LoadTSR(char *tsrfilename)
{
	TSRHeader Header;
	TSRLayer Layer;
	TSRAlignment Alignment;
	TSRSegment Segment;
	TSRTrack Track;
	TSRTrackSegment TrackSegment;
	TSRVertex Vertex;
	TSRVertexTrack VertexTrack;

	struct t_st
	{
		Int_t TrackOwnerId;
		Int_t TrackId;
		Int_t TrackLength;
	};

	struct t_tl
	{
		Int_t N;
		t_st *pS;
		Int_t FilePos;
	};

	t_tl *pSegIndices = 0;
	FILE *f = 0;
	int i, j, k, h;
	try
	{
		f = fopen(tsrfilename, "rb");
		if (!pHeader->GetBranch("Data")) pHeader->Branch("Data", &Header, "Id0/I:Id1/I:Id2/I:Id3/I:MinX/D:MaxX/D:MinY/D:MaxY/D:MinZ/D:MaxZ/D:Sheets/I:Tracks/I:Vertices/I:MaxTracksInSegment/I:RefCenterX/D:RefCenterY/D:RefCenterZ/D:Segments/I");
		char infotype;
		infotype = ReadByte(f);
		short headerformat;
		headerformat = ReadShort(f);
		if (infotype != 0x49) throw 0;
		if (headerformat != tsrFmtNormalDouble) throw 0;
		Header.Id0 = ReadInt(f);
		Header.Id1 = ReadInt(f);
		Header.Id2 = ReadInt(f);
		Header.Id3 = ReadInt(f);
		Header.MinX = ReadDouble(f);
		Header.MinY = ReadDouble(f);
		Header.MinZ = ReadDouble(f);
		Header.MaxX = ReadDouble(f);
		Header.MaxY = ReadDouble(f);
		Header.MaxZ = ReadDouble(f);
		for (i = 0; i < 104; i++) ReadByte(f);
		Header.Sheets = ReadInt(f);
		Header.Tracks = ReadInt(f);
		Header.Vertices = ReadInt(f);
		Header.MaxTracksInSegment = ReadInt(f);
		Header.Segments = 0;
		Header.RefCenterX = ReadDouble(f);
		Header.RefCenterY = ReadDouble(f);
		Header.RefCenterZ = ReadDouble(f);

		pSegIndices = new t_tl[Header.Sheets];
		for (i = 0; i < Header.Sheets; i++)
		{
			pSegIndices[i].N = 0;
			pSegIndices[i].pS = 0;
			pSegIndices[i].FilePos = 0;
		}

		if (!pLayers->GetBranch("Data")) pLayers->Branch("Data", &Layer, "Id/I:SheetId/I:DownstreamExt/D:DownstreamInt/D:UpstreamInt/D:UpstreamExt/D:RefCenterX/D:RefCenterY/D:RefCenterZ/D:Segments/I:FirstSegment/I");
		if (!pLayers->GetBranch("Alignment")) pLayers->Branch("Alignment", &Alignment, "DeformationXX/D:DeformationXY/D:DeformationYX/D:DeformationYY/D:TranslationX/D:TranslationY/D:TranslationZ/D:DeltaSlopeX/D:DeltaSlopeY/D:DeltaShrinkX/D:DeltaShrinkY/D");
		if (!pSegments->GetBranch("Data")) pSegments->Branch("Data", &Segment, "AreaSum/I:Grains/I:InterceptX/D:InterceptY/D:InterceptZ/D:SlopeX/D:SlopeY/D:Sigma/D:TopZ/D:BottomZ/D:BaseTrackId/I:LayerOwnerId/I:LayerId/I:TrackOwnerId/I:TrackId/I:TrackLength/I");
		if (!pTrackSegments->GetBranch("Data")) pTrackSegments->Branch("Data", &TrackSegment, "LayerOwnerId/I:LayerId/I");
		if (!pTracks->GetBranch("Data")) pTracks->Branch("Data", &Track, "DownstreamZeroX/D:DownstreamZeroY/D:DownstreamSlopeX/D:DownstreamSlopeY:UpstreamZeroX/D:UpstreamZeroY/D:UpstreamSlopeX/D:UpstreamSlopeY/D:Id/I:Segments/I:FirstSegment/I:UpstreamVertexId/I:DownstreamVertexId/I");
		if (!pVertices->GetBranch("Data")) pVertices->Branch("Data", &Vertex, "X/D:Y/D:Z/D:AverageDistance/D:DeltaX/D:DeltaY/D:Id/I:Tracks/I:FirstTrack/I");
		if (!pVertexTracks->GetBranch("Data")) pVertexTracks->Branch("Data", &VertexTrack, "TrackId/I:IsUpstream/I");

		Layer.FirstSegment = 0;
		for (i = 0; i < Header.Sheets; i++)
		{
			Layer.Id = i;
			Layer.SheetId = ReadInt(f);
			Layer.DownstreamExt = ReadDouble(f);
			Layer.DownstreamInt = ReadDouble(f);
			Layer.UpstreamInt = ReadDouble(f);
			Layer.UpstreamExt = ReadDouble(f);
			Layer.RefCenterZ = ReadDouble(f);
			Layer.RefCenterX = Header.RefCenterX;
			Layer.RefCenterY = Header.RefCenterY;

			Alignment.DeformationXX = ReadDouble(f);
			Alignment.DeformationXY = ReadDouble(f);
			Alignment.DeformationYX = ReadDouble(f);
			Alignment.DeformationYY = ReadDouble(f);
			Alignment.TranslationX = ReadDouble(f);
			Alignment.TranslationY = ReadDouble(f);
			Alignment.TranslationZ = ReadDouble(f);
			ReadDouble(f); ReadDouble(f); ReadDouble(f); ReadDouble(f);
			Alignment.DeltaSlopeX = ReadDouble(f);
			Alignment.DeltaSlopeY = ReadDouble(f);
			Alignment.DeltaShrinkX = ReadDouble(f);
			Alignment.DeltaShrinkY = ReadDouble(f);
			ReadDouble(f); ReadDouble(f); ReadDouble(f); ReadDouble(f);

			Layer.Segments = ReadInt(f);
			Header.Segments += Layer.Segments;
			ReadInt(f); ReadInt(f); ReadInt(f);
			pLayers->Fill();
			Layer.FirstSegment += Layer.Segments;

			pSegIndices[i].N = Layer.Segments;
			pSegIndices[i].pS = new t_st[Layer.Segments];
			pSegIndices[i].FilePos = ftell(f);
			fseek(f, (4 * Header.MaxTracksInSegment + 76) * Layer.Segments, SEEK_CUR);
		}
		pHeader->Fill();

		Track.FirstSegment = 0;
		for (i = 0; i < Header.Tracks; i++)
		{
			Track.Id = i;
			Track.Segments = ReadInt(f);
			for (k = 0; k < Track.Segments; k++)
			{
				TrackSegment.LayerOwnerId = ReadInt(f);
				TrackSegment.LayerId = ReadInt(f);
				t_st &r = pSegIndices[TrackSegment.LayerOwnerId].pS[TrackSegment.LayerId];
				r.TrackOwnerId = i;
				r.TrackId = k;
				r.TrackLength = Track.Segments;
				pTrackSegments->Fill();
			}
			Track.UpstreamVertexId = ReadInt(f);
			Track.DownstreamVertexId = ReadInt(f);
			ReadInt(f);
			Track.DownstreamZeroX = ReadDouble(f);
			Track.DownstreamZeroY = ReadDouble(f);
			Track.DownstreamSlopeX = ReadDouble(f);
			Track.DownstreamSlopeY = ReadDouble(f);
			Track.UpstreamZeroX = ReadDouble(f);
			Track.UpstreamZeroY = ReadDouble(f);
			Track.UpstreamSlopeX = ReadDouble(f);
			Track.UpstreamSlopeY = ReadDouble(f);
			pTracks->Fill();
			Track.FirstSegment += Track.Segments;
		}

		Int_t VPos = ftell(f);
		for (i = 0; i < Header.Sheets; i++)
		{
			fseek(f, pSegIndices[i].FilePos, SEEK_SET);
			for (j = 0; j < pSegIndices[i].N; j++)
			{
				if (Header.MaxTracksInSegment > 0)
				{
					h = ReadInt(f);
					for (k = 1; k < Header.MaxTracksInSegment; k++) ReadInt(f);
				}
				else h = -1;
				Segment.BaseTrackId = h;
				Segment.Grains = ReadShort(f);
				Segment.AreaSum = ReadShort(f);
				Segment.InterceptX = ReadDouble(f);
				Segment.InterceptY = ReadDouble(f);
				Segment.InterceptZ = ReadDouble(f);
				Segment.SlopeX = ReadDouble(f);
				Segment.SlopeY = ReadDouble(f);
				ReadDouble(f);
				Segment.Sigma = ReadDouble(f);
				Segment.TopZ = ReadDouble(f);
				Segment.BottomZ = ReadDouble(f);
				Segment.LayerOwnerId = i;
				Segment.LayerId = j;
				Segment.TrackOwnerId = pSegIndices[i].pS[j].TrackOwnerId;
				Segment.TrackId = pSegIndices[i].pS[j].TrackId;
				Segment.TrackLength = pSegIndices[i].pS[j].TrackLength;
				pSegments->Fill();
			}
			delete [] pSegIndices[i].pS;
			pSegIndices[i].pS = 0;
			pSegIndices[i].N = 0;
		}
		delete [] pSegIndices;
		pSegIndices = 0;

		fseek(f, VPos, SEEK_SET);
		Vertex.FirstTrack = 0;
		for (i = 0; i < Header.Vertices; i++)
		{
			Vertex.Id = i;
			Vertex.Tracks = ReadInt(f);
			Vertex.X = ReadDouble(f);
			Vertex.Y = ReadDouble(f);
			Vertex.Z = ReadDouble(f);
			Vertex.AverageDistance = ReadDouble(f);
			for (j = 0; j < Vertex.Tracks; j++)
			{
				VertexTrack.TrackId = ReadInt(f);
				VertexTrack.IsUpstream = ReadByte(f);
				pVertexTracks->Fill();
				ReadInt(f); ReadInt(f); ReadInt(f); ReadInt(f);
			}
			Vertex.DeltaX = ReadDouble(f);
			Vertex.DeltaY = ReadDouble(f);
			ReadDouble(f); ReadDouble(f);
			pVertices->Fill();
			Vertex.FirstTrack += Vertex.Tracks;
		}

	}
	catch (...)
	{
		if (pSegIndices)
		{
			for (i = 0; i < Header.Sheets; i++)
			{
				if (pSegIndices[i].pS) delete [] pSegIndices[i].pS;
				pSegIndices[i].N = 0;
			}
			delete [] pSegIndices;
			pSegIndices = 0;
		}

		if (f) fclose(f);
		return false;
	}
	if (f) fclose(f);
	return true;
}

bool TSySalTSR::SaveTSR(char *tsrfilename, int number)
{
	TSRHeader Header;
	TSRLayer Layer;
	TSRAlignment Alignment;
	TSRSegment Segment;
	TSRTrack Track;
	TSRTrackSegment TrackSegment;
	TSRVertex Vertex;
	TSRVertexTrack VertexTrack;

	FILE *f = 0;
	int i, j, k;
	try
	{

		int sbase = 0, tbase = 0, vbase = 0, lbase = 0;
		int tsbase = 0, vtbase = 0;
		pHeader->GetBranch("Data")->SetAddress(&Header);
		pLayers->GetBranch("Data")->SetAddress(&Layer);
		pLayers->GetBranch("Alignment")->SetAddress(&Alignment);
		pSegments->GetBranch("Data")->SetAddress(&Segment);
		pTrackSegments->GetBranch("Data")->SetAddress(&TrackSegment);
		pTracks->GetBranch("Data")->SetAddress(&Track);
		pVertices->GetBranch("Data")->SetAddress(&Vertex);
		pVertexTracks->GetBranch("Data")->SetAddress(&VertexTrack);
		Header.Segments = Header.Sheets = Header.Tracks = Header.Vertices = 0;
		for (i = 0; i <= number; i++)
		{
			sbase += Header.Segments;
			tbase += Header.Tracks;
			vbase += Header.Vertices;
			lbase += Header.Sheets;
			if (i > 0)
			{
				pTracks->GetEntry(tbase - 1);
				tsbase += Track.FirstSegment + Track.Segments;
				pVertices->GetEntry(vbase - 1);
				vtbase += Vertex.FirstTrack + Vertex.Tracks;
			}
			pHeader->GetEntry(i);
		}
		f = fopen(tsrfilename, "wb");
		WriteData((char)0x49, f);
		WriteData((short)tsrFmtNormalDouble, f);
		WriteData(Header.Id0, f);
		WriteData(Header.Id1, f);
		WriteData(Header.Id2, f);
		WriteData(Header.Id3, f);
		WriteData(Header.MinX, f);
		WriteData(Header.MinY, f);
		WriteData(Header.MinZ, f);
		WriteData(Header.MaxX, f);
		WriteData(Header.MaxY, f);
		WriteData(Header.MaxZ, f);
		for (i = 0; i < 104; i++) WriteData((char)0, f);
		WriteData(Header.Sheets, f);
		WriteData(Header.Tracks, f);
		WriteData(Header.Vertices, f);
		WriteData(Header.MaxTracksInSegment, f);
		WriteData(Header.RefCenterX, f);
		WriteData(Header.RefCenterY, f);
		WriteData(Header.RefCenterZ, f);

		for (i = 0; i < Header.Sheets; i++)
		{
			pLayers->GetEntry(lbase++);
			WriteData(Layer.SheetId, f);
			WriteData(Layer.DownstreamExt, f);
			WriteData(Layer.DownstreamInt, f);
			WriteData(Layer.UpstreamInt, f);
			WriteData(Layer.UpstreamExt, f);
			WriteData(Layer.RefCenterZ, f);

			WriteData(Alignment.DeformationXX, f);
			WriteData(Alignment.DeformationXY, f);
			WriteData(Alignment.DeformationYX, f);
			WriteData(Alignment.DeformationYY, f);
			WriteData(Alignment.TranslationX, f);
			WriteData(Alignment.TranslationY, f);
			WriteData(Alignment.TranslationZ, f);
			WriteData(0.0, f); WriteData(0.0, f); WriteData(0.0, f); WriteData(0.0, f);
			WriteData(Alignment.DeltaSlopeX, f);
			WriteData(Alignment.DeltaSlopeY, f);
			WriteData(Alignment.DeltaShrinkX, f);
			WriteData(Alignment.DeltaShrinkY, f);
			WriteData(0.0, f); WriteData(0.0, f); WriteData(0.0, f); WriteData(0.0, f);

			WriteData(Layer.Segments, f);
			WriteData(0, f); WriteData(0, f); WriteData(0, f);

			for (j = 0; j < Layer.Segments; j++)
			{
				pSegments->GetEntry(sbase++);
				if (Header.MaxTracksInSegment > 0)
				{
					WriteData(Segment.BaseTrackId, f);
					for (k = 1; k < Header.MaxTracksInSegment; k++) WriteData(-1, f);
				}

				WriteData((short)Segment.Grains, f);
				WriteData((short)Segment.AreaSum, f);
				WriteData(Segment.InterceptX, f);
				WriteData(Segment.InterceptY, f);
				WriteData(Segment.InterceptZ, f);
				WriteData(Segment.SlopeX, f);
				WriteData(Segment.SlopeY, f);
				WriteData((double)1.0, f);
				WriteData(Segment.Sigma, f);
				WriteData(Segment.TopZ, f);
				WriteData(Segment.BottomZ, f);
			}
		}

		for (i = 0; i < Header.Tracks; i++)
		{
			pTracks->GetEntry(tbase++);
			WriteData(Track.Segments, f);
			for (k = 0; k < Track.Segments; k++)
			{
				pTrackSegments->GetEntry(tsbase++);
				WriteData(TrackSegment.LayerOwnerId, f);
				WriteData(TrackSegment.LayerId, f);
			}
			WriteData(Track.UpstreamVertexId, f);
			WriteData(Track.DownstreamVertexId, f);
			WriteData(0, f);
			WriteData(Track.DownstreamZeroX, f);
			WriteData(Track.DownstreamZeroY, f);
			WriteData(Track.DownstreamSlopeX, f);
			WriteData(Track.DownstreamSlopeY, f);
			WriteData(Track.UpstreamZeroX, f);
			WriteData(Track.UpstreamZeroY, f);
			WriteData(Track.UpstreamSlopeX, f);
			WriteData(Track.UpstreamSlopeY, f);
		}

		for (i = 0; i < Header.Vertices; i++)
		{
			pVertices->GetEntry(vbase++);
			WriteData(Vertex.Tracks, f);
			WriteData(Vertex.X, f);
			WriteData(Vertex.Y, f);
			WriteData(Vertex.Z, f);
			WriteData(Vertex.AverageDistance, f);
			for (j = 0; j < Vertex.Tracks; j++)
			{
				pVertexTracks->GetEntry(vtbase++);
				WriteData(VertexTrack.TrackId, f);
				WriteData((char)VertexTrack.IsUpstream, f);
				WriteData(0, f); WriteData(0, f); WriteData(0, f); WriteData(0, f);
			}
			WriteData(Vertex.DeltaX, f);
			WriteData(Vertex.DeltaY, f);
			WriteData(0.0, f); WriteData(0.0, f);
		}
	}
	catch (...)
	{
		if (f) fclose(f);
		return false;
	}
	if (f) fclose(f);
	return true;
}
