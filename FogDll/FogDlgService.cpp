

float CFogDlg::GetFloat(CWnd *MyEdit)
{
	float myfloat = 0.f;
	int Value = 0;
	CString myString;
	MyEdit->GetWindowText(myString);
	Value = sscanf(myString,"%f",&myfloat);
	if(Value != 1){ myfloat = 0; MyEdit->SetWindowText("0.0");}
	return myfloat;
}

int CFogDlg::GetInteger(CWnd *MyEdit)
{
	int myint = 0;
	int Value;
	CString myString;
	MyEdit->GetWindowText(myString);
	Value = sscanf(myString,"%d",&myint);
	if(Value != 1){ myint = 0; MyEdit->SetWindowText("0");}
	return myint;
}

void CFogDlg::SetInteger(UINT IDC, int toText)
{
	CString temp;
	SetDlgItemText(IDC,(temp.Format("%d",toText),temp));		
}

void CFogDlg::SetFloat(UINT IDC, float toText)
{
	CString temp;
	SetDlgItemText(IDC,(temp.Format("%f",toText),temp));
}





void CFogDlg::GetFrameRange(int Frames,int &StartFrame,int &LastFrame)
{
	StartFrame = 0;//GetInteger(GetDlgItem(IDC_EDT_FOGMAIN_STARTFRAME));
	if(StartFrame < 1 )StartFrame = 1;
	if(StartFrame > Frames - 4)StartFrame = Frames - 4;
	LastFrame = 1000;//GetInteger(GetDlgItem(IDC_EDT_FOGMAIN_LASTFRAME)); 
	if(LastFrame < 2)LastFrame = 2;
	if(LastFrame > Frames)LastFrame = Frames;
//	SetInteger(IDC_EDT_FOGMAIN_LASTFRAME,LastFrame);
//	SetInteger(IDC_EDT_FOGMAIN_STARTFRAME,StartFrame);
}

void CFogDlg::SetDialogData(int Min, int Max, int Frame, float Media, float Depth)
{
	SetInteger(IDC_EDT_FOGMAIN_MINIMO,Min);
	SetInteger(IDC_EDT_FOGMAIN_MASSIMO,Max);
	SetFloat(IDC_EDT_FOGMAIN_MEDIO,Media);
	SetInteger(IDC_EDT_FOGMAIN_FRAME,Frame);
	SetFloat(IDC_EDT_FOGMAIN_DEPTH,Depth);
}

void CFogDlg::GetComputingParameters(int &Threshold, int &ImageDivision, int &Delta)
{
	Threshold = GetInteger(GetDlgItem(IDC_EDT_FOGMAIN_THRESHOLD));
	ImageDivision = GetInteger(GetDlgItem(IDC_EDT_FOGMAIN_CELLSIZE));
	Delta = GetInteger(GetDlgItem(IDC_EDT_FOGMAIN_DELTA));
}
void CFogDlg::OnScannerLoadImages() 
{
#ifdef FOG_HOME
	FILE * pImagesFile = fopen("C:\\Fulvio\\Fog2000\\Interazione di un pione.raw","rb");
#endif
#ifndef FOG_HOME
	FILE * pImagesFile = fopen("C:\\sysal2000\\fog2000\\debug\\Images.raw","rb");
#endif
	CFileDialog dlg(TRUE);
	char filter[] = "Raw Images and Depths *.raw\0*.raw\0All Files *.*\0*.*\0";
	dlg.m_ofn.lpstrFilter = filter;
//	dlg.m_ofn.Flags |= OFN_EXPLORER;
	int value = dlg.DoModal();
	if(value == IDOK)
	{
		FILE * pImagesFile = fopen(dlg.GetPathName(),"rb");
		int XWidth = m_MicroParameters.HalfCCDLength*2;
		int YWidth = m_MicroParameters.HalfCCDWidth*2;
		if(pImagesFile != NULL)
		{
			if(m_Scanner.m_pGlobalBytes1 != NULL)
			{
				fread(&m_Scanner.m_NumberOfImages,4,1,pImagesFile);
				for(int i = 0; i < m_Scanner.m_NumberOfImages; i++)
				{
					fread(m_CGrainFinder.m_depths + i,sizeof(float),1,pImagesFile);
					fread(m_Scanner.m_pGlobalBytes1 + i*XWidth*YWidth,XWidth,YWidth,pImagesFile);
				}
			}
			fclose(pImagesFile);
			if(m_Scanner.m_pGlobalBytes1 != NULL)m_Scanner.m_bGlobalBytesLoaded = true;
		}
	}
}

