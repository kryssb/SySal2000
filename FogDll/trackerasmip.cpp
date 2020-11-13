






SMip * SMip::AddNext(SMip * pMip)
{	
	if(pMip != NULL)
	{	if(pMip->pPrevious != NULL)pMip->pPrevious->pNext = pMip->pNext;
		if(pMip->pNext != NULL)pMip->pNext->pPrevious = pMip->pPrevious;	}
	if(this != NULL && pNext == NULL)
	{	pNext = (SMip *)calloc(sizeof(SMip),1);
		if(pNext == NULL)MessageBox(NULL,"Error Allocating Memory.\nCrashing!","SMip",MB_OK);	}
	if(this != NULL)
	{	SMip *pM = pNext;
		pNext = pMip;
		if(pNext == NULL)pNext = (SMip *)calloc(sizeof(SMip),1);
		pNext->pPrevious = this;
		pNext->pNext = pM;
		pM->pPrevious = pNext;
		return pNext;}
	else
	{	if(pMip != NULL)
		{	SMip *pPrev = pMip;
			while(pPrev->pPrevious != NULL)pPrev = pPrev->pPrevious;
			pMip->pPrevious = NULL;
			pMip->pNext = pPrev,pPrev->pPrevious = pMip;
			return pMip;	}
		else return NULL;
	}
}

SMip * SMip::LinkNext(SMip * pMip)
{	
	if(pMip != NULL)
	{	if(pMip->pPrevious != NULL)pMip->pPrevious->pNext = pMip->pNext;
		if(pMip->pNext != NULL)pMip->pNext->pPrevious = pMip->pPrevious;	}
	if(this != NULL && pNext == NULL)
	{	pNext = (SMip *)calloc(sizeof(SMip),1);
		if(pNext == NULL)MessageBox(NULL,"Error Allocating Memory.\nCrashing!","SMip",MB_OK);	}
	if(this != NULL)
	{	SMip *pM = pNext;
		pNext = pMip;
		if(pNext == NULL)pNext = (SMip *)calloc(sizeof(SMip),1);
		pNext->pPrevious = this;
		pNext->pNext = pM;
		pM->pPrevious = pNext;
		return pNext;}
	else
	{	if(pMip != NULL)
		{	SMip *pPrev = pMip;
			while(pPrev->pPrevious != NULL)pPrev = pPrev->pPrevious;
			pMip->pPrevious = NULL;
			pMip->pNext = pPrev,pPrev->pPrevious = pMip;
			return pMip;	}
		else return NULL;
	}
}


SMip * SMip::AddNew()
{
	SMip *pM = pNext;
	pNext = (SMip *)calloc(sizeof(SMip),1);
	pNext->pPrevious = this;
	pNext->pNext = pM;
	if(pM)pM->pPrevious = pNext;

	return pNext;
}


void SMip::Load(FILE * loadFile,int Version)
{
	if(Version < 7)
	{
		fread(&mx,sizeof(float),1,loadFile);
		fread(&nx,sizeof(float),1,loadFile);
		fread(&sigmax,sizeof(float),1,loadFile);
		fread(&mz,sizeof(float),1,loadFile);
		fread(&nz,sizeof(float),1,loadFile);
		fread(&sigmaz,sizeof(float),1,loadFile);
		fread(&GiC,sizeof(float),1,loadFile);
		fread(&md,sizeof(float),1,loadFile);
		fread(&NGrains,sizeof(int),1,loadFile);
		fread(&MaxZ,sizeof(float),1,loadFile);
		fread(&MinZ,sizeof(float),1,loadFile);
		fread(pGrains,sizeof(SIntGrain),NGrains,loadFile);
		my = 1.f;
		ny = 0.f;
		sigmay = 0.f;
		GetGap();
	}
	else if(Version == 7)
	{
		fread(this,4,24,loadFile);
		fread(pGrains,sizeof(SIntGrain),NGrains,loadFile);
	}
}
void SMip::Save(FILE * saveFile,int Version)
{
	if(Version < 7)
	{
		fwrite(&mx,sizeof(float),1,saveFile);
		fwrite(&nx,sizeof(float),1,saveFile);
		fwrite(&sigmax,sizeof(float),1,saveFile);
		fwrite(&mz,sizeof(float),1,saveFile);
		fwrite(&nz,sizeof(float),1,saveFile);
		fwrite(&sigmaz,sizeof(float),1,saveFile);
		fwrite(&GiC,sizeof(float),1,saveFile);
		fwrite(&md,sizeof(float),1,saveFile);
		fwrite(&NGrains,sizeof(int),1,saveFile);
		fwrite(&MaxZ,sizeof(float),1,saveFile);
		fwrite(&MinZ,sizeof(float),1,saveFile);
		fwrite(pGrains,sizeof(SIntGrain),NGrains,saveFile);
		return;
	}
	else if(Version == 7)
	{
/*		fwrite(&mx,sizeof(float),1,saveFile);
		fwrite(&nx,sizeof(float),1,saveFile);
		fwrite(&sigmax,sizeof(float),1,saveFile);
		fwrite(&my,sizeof(float),1,saveFile);
		fwrite(&ny,sizeof(float),1,saveFile);
		fwrite(&sigmay,sizeof(float),1,saveFile);
		fwrite(&mz,sizeof(float),1,saveFile);
		fwrite(&nz,sizeof(float),1,saveFile);
		fwrite(&sigmaz,sizeof(float),1,saveFile);
		fwrite(&Axe,sizeof(int),1,saveFile);
		fwrite(&Length,sizeof(float),1,saveFile);
		fwrite(&NomLength,sizeof(float),1,saveFile);
		fwrite(&md,sizeof(float),1,saveFile);
		fwrite(&MaxDist,sizeof(float),1,saveFile);
		fwrite(&MeanGap,sizeof(float),1,saveFile);
		fwrite(&MaxGap,sizeof(float),1,saveFile);
		fwrite(&MaxZ,sizeof(float),1,saveFile);
		fwrite(&MinZ,sizeof(float),1,saveFile);
		fwrite(&Alfa,sizeof(float),1,saveFile);
		fwrite(&NGrains,sizeof(int),1,saveFile);
		fwrite(&GiC,sizeof(float),1,saveFile);*/
		fwrite(this,4,24,saveFile);
		fwrite(pGrains,sizeof(SIntGrain),NGrains,saveFile);

	}
}

void SMip::GetGap()
{
	float wy,worker,distances = 0;
	int i;
	qsort(pGrains,NGrains,sizeof(SIntGrain),CompareIntGrainYA);
	distances = 0;
		wy = pGrains->y;
	for(i = 0; i < NGrains - 1;)
	{
		worker = wy;
		wy = (pGrains + ++i)->y;
		distances += (wy - worker);
	}
	MeanGap = ((float)sqrt(mx*mx + 1 + mz*mz))*(distances/(NGrains - 1));
}
