// WECompressorTab3.cpp : implementation file
//

#include "stdafx.h"
#include "WECompressor.h"
#include "XTabCtrl.h"
#include "WECompressorTab3.h"
#include "AboutDialog.h"
#include "WECompress.h"
#include "BitmapDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWECompressorTab3 dialog


CWECompressorTab3::CWECompressorTab3(CWnd* pParent /*=NULL*/)
	: CDialog(CWECompressorTab3::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWECompressorTab3)
	m_GameType = 0;
	m_IdxTexGio1 = 0;
	m_IdxTexGio2 = 0;
	m_IdxTexMan1 = 0;
	m_IdxTexMan2 = 0;
	m_IdxTexTifo = 0;
	m_IdxTexRefree = 0;
	m_IdxPalFlag = 2;
	m_IdxPalGioc1 = 2;
	m_IdxPalGioc2 = 2;
	m_IdxPalPort1 = 0;
	m_IdxPalPort2 = 0;
	m_IdxAutoGio1 = 1;
	m_IdxAutoGio2 = 1;
	m_IdxAutoMan1 = 0;
	m_IdxAutoMan2 = 0;
	m_IdxAutoFlag = 1;
	m_LargeTex = FALSE;
	//}}AFX_DATA_INIT

	for (int i=0;i<12;i++)
		m_FlagOK[i] = FALSE;
	m_NewTexFile = CString(" ");	
	m_TexFileGioc1 = CString(" ");
	m_TexFileGioc2 = CString(" ");
	m_PalFileGioc1 = CString(" ");
	m_PalFileGioc2 = CString(" ");
	m_PalFilePort1 = CString(" ");
	m_PalFilePort2 = CString(" ");
	m_TexFileManLun1 = CString(" ");
	m_TexFileManLun2 = CString(" ");
	m_TexFlagFile =  CString(" ");
	m_PalFlagFile =  CString(" ");
	m_TexRefreeFile =  CString(" ");
	m_pTab = NULL;
	m_ActualColorsNumber = 256;
	
}

CWECompressorTab3::~CWECompressorTab3()
{	
}

void CWECompressorTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWECompressorTab3)
	DDX_CBIndex(pDX, IDC_COMBO_SELGAME, m_GameType);
	DDX_CBIndex(pDX, IDC_COMBO_SELTEXGIO1, m_IdxTexGio1);
	DDX_CBIndex(pDX, IDC_COMBO_SELTEXGIO2, m_IdxTexGio2);
	DDX_CBIndex(pDX, IDC_COMBO_SELTEXMAN1, m_IdxTexMan1);
	DDX_CBIndex(pDX, IDC_COMBO_SELTEXMAN2, m_IdxTexMan2);
	DDX_CBIndex(pDX, IDC_COMBO_SELTEXTIFO, m_IdxTexTifo);
	DDX_CBIndex(pDX, IDC_COMBO_SELTEXREFREE, m_IdxTexRefree);
	DDX_CBIndex(pDX, IDC_COMBO_SELPALFLAG, m_IdxPalFlag);
	DDX_CBIndex(pDX, IDC_COMBO_SELPALGIOC1, m_IdxPalGioc1);
	DDX_CBIndex(pDX, IDC_COMBO_SELPALGIOC2, m_IdxPalGioc2);
	DDX_CBIndex(pDX, IDC_COMBO_SELPALPORT1, m_IdxPalPort1);
	DDX_CBIndex(pDX, IDC_COMBO_SELPALPORT2, m_IdxPalPort2);
	DDX_CBIndex(pDX, IDC_COMBO_SELAUTOGIO1, m_IdxAutoGio1);
	DDX_CBIndex(pDX, IDC_COMBO_SELAUTOGIO2, m_IdxAutoGio2);
	DDX_CBIndex(pDX, IDC_COMBO_SELAUTOMAN1, m_IdxAutoMan1);
	DDX_CBIndex(pDX, IDC_COMBO_SELAUTOMAN2, m_IdxAutoMan2);
	DDX_CBIndex(pDX, IDC_COMBO_SELAUTOFLAG, m_IdxAutoFlag);
	DDX_Check(pDX, IDC_256X128MODE, m_LargeTex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWECompressorTab3, CDialog)
	//{{AFX_MSG_MAP(CWECompressorTab3)
	ON_BN_CLICKED(IDOK, OnQuit)
	ON_BN_CLICKED(IDC_SELBUTTON2, OnBrowseTexGioc1)
	ON_BN_CLICKED(IDC_SELBUTTON8, OnBrowseTexGioc2)
	ON_BN_CLICKED(IDC_SELBUTTON5, OnBrowseTexMan1)
	ON_BN_CLICKED(IDC_SELBUTTON11, OnBrowseTexMan2)
	ON_BN_CLICKED(IDC_SELBUTTON, OnBrowseNewTex)
	ON_BN_CLICKED(IDC_SELBUTTON6, OnBrowseTexFlag)
	ON_BN_CLICKED(IDC_SELBUTTON12, OnBrowseTexRefree)
	ON_BN_CLICKED(IDC_SELBUTTON3, OnBrowsePalGioc1)
	ON_BN_CLICKED(IDC_SELBUTTON4B, OnBrowsePalPort1)
	ON_BN_CLICKED(IDC_SELBUTTON9, OnBrowsePalGioc2)
	ON_BN_CLICKED(IDC_SELBUTTON10, OnBrowsePalPort2)
	ON_BN_CLICKED(IDC_SELBUTTON7, OnBrowsePalFlag)
	ON_BN_CLICKED(IDC_VIEWBUTTON2, OnViewTexGioc1)
	ON_BN_CLICKED(IDC_VIEWBUTTON8, OnViewTexGioc2)
	ON_BN_CLICKED(IDC_VIEWBUTTON5, OnViewTexMan1)
	ON_BN_CLICKED(IDC_VIEWBUTTON11, OnViewTexMan2)
	ON_BN_CLICKED(IDC_VIEWBUTTON6, OnViewTexFlag)
	ON_BN_CLICKED(IDC_VIEWBUTTON12, OnViewTexRefree)
	ON_BN_CLICKED(ID_INFO, OnInfo)
	ON_CBN_SELCHANGE(IDC_COMBO_SELAUTOFLAG, OnChangeComboSelAutoFlag)
	ON_CBN_SELCHANGE(IDC_COMBO_SELAUTOMAN1, OnChangeComboSelAutoMan1)
	ON_CBN_SELCHANGE(IDC_COMBO_SELAUTOGIO1, OnChangeComboSelAutoGio1)
	ON_CBN_SELCHANGE(IDC_COMBO_SELTEXGIO1, OnChangeComboSelTexGio1)
	ON_CBN_SELCHANGE(IDC_COMBO_SELTEXGIO2, OnChangeComboSelTexGio2)
	ON_CBN_SELCHANGE(IDC_COMBO_SELAUTOMAN2, OnChangeComboSelAutoMan2)
	ON_CBN_SELCHANGE(IDC_COMBO_SELAUTOGIO2, OnChangeComboSelAutoGio2)
	ON_CBN_SELCHANGE(IDC_COMBO_SELTEXMAN1, OnChangeComboSelTexMan1)
	ON_CBN_SELCHANGE(IDC_COMBO_SELTEXMAN2, OnChangeComboSelTexMan2)
	ON_BN_CLICKED(IDC_BUTTON_MAKETEX, OnButtonMakeTEX)
	ON_BN_CLICKED(IDC_256X128MODE, OnLargeTexClick)
	ON_BN_CLICKED(IDC_BUTTON_EXTRACTTEX, OnButtonExtractTEX)
	ON_CBN_SELCHANGE(IDC_COMBO_SELTEXTIFO, OnChangeComboSelTexFlag)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWECompressorTab3 message handlers

BOOL CWECompressorTab3::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// load CButtonST
	InitializeButtons();	

	// create ToolsTips
	AddHelpTTips();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWECompressorTab3::InitializeButtons()
{
	m_FOpen1.SubclassDlgItem(IDC_SELBUTTON, this);
	m_FOpen1.SetIcon(IDI_SELFILE); 

	m_FOpen2.SubclassDlgItem(IDC_SELBUTTON2, this);
	m_FOpen2.SetIcon(IDI_SELFILE);

	m_FOpen3.SubclassDlgItem(IDC_SELBUTTON3, this);
	m_FOpen3.SetIcon(IDI_SELFILE);

	m_FOpen4.SubclassDlgItem(IDC_SELBUTTON4B, this);
	m_FOpen4.SetIcon(IDI_SELFILE);

	m_FOpen5.SubclassDlgItem(IDC_SELBUTTON5, this);
	m_FOpen5.SetIcon(IDI_SELFILE);

	m_FOpen6.SubclassDlgItem(IDC_SELBUTTON6, this);
	m_FOpen6.SetIcon(IDI_SELFILE);

	m_FOpen7.SubclassDlgItem(IDC_SELBUTTON7, this);
	m_FOpen7.SetIcon(IDI_SELFILE);

	m_FOpen8.SubclassDlgItem(IDC_SELBUTTON8, this);
	m_FOpen8.SetIcon(IDI_SELFILE);

	m_FOpen9.SubclassDlgItem(IDC_SELBUTTON9, this);
	m_FOpen9.SetIcon(IDI_SELFILE);

	m_FOpen10.SubclassDlgItem(IDC_SELBUTTON10, this);
	m_FOpen10.SetIcon(IDI_SELFILE);

	m_FOpen11.SubclassDlgItem(IDC_SELBUTTON11, this);
	m_FOpen11.SetIcon(IDI_SELFILE);

	m_FOpen12.SubclassDlgItem(IDC_SELBUTTON12, this);
	m_FOpen12.SetIcon(IDI_SELFILE);

	m_FView2.SubclassDlgItem(IDC_VIEWBUTTON2, this);
	m_FView2.SetIcon(IDI_VIEWFILE);

	m_FView5.SubclassDlgItem(IDC_VIEWBUTTON5, this);
	m_FView5.SetIcon(IDI_VIEWFILE);

	m_FView6.SubclassDlgItem(IDC_VIEWBUTTON6, this);
	m_FView6.SetIcon(IDI_VIEWFILE);

	m_FView8.SubclassDlgItem(IDC_VIEWBUTTON8, this);
	m_FView8.SetIcon(IDI_VIEWFILE);

	m_FView11.SubclassDlgItem(IDC_VIEWBUTTON11, this);
	m_FView11.SetIcon(IDI_VIEWFILE);

	m_FView12.SubclassDlgItem(IDC_VIEWBUTTON12, this);
	m_FView12.SetIcon(IDI_VIEWFILE);
	
}

void CWECompressorTab3::AddHelpTTips()
{
	CString Temp;
	//PPTOOLTIP_INFO ti;
	m_ctlTT.Create (this);

	Temp = CString(MAKEINTRESOURCE(IDS_HELP_INFORMATION_TITLE));
	m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELBUTTON)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON2), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELBUTTON2)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON3), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELBUTTON3)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON4B), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELBUTTON4)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON5), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELBUTTON5)), IDI_PP_INFORMATION);	
	m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON6), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELBUTTON6)), IDI_PP_INFORMATION);	
	m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON7), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELBUTTON7)), IDI_PP_INFORMATION);	
	m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON8), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELBUTTON8)), IDI_PP_INFORMATION);	
	m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON9), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELBUTTON9)), IDI_PP_INFORMATION);	
	m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON10), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELBUTTON10)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON11), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELBUTTON11)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON12), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELBUTTON12)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_VIEWBUTTON2), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_VIEWBUTTON)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_VIEWBUTTON5), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_VIEWBUTTON)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_VIEWBUTTON6), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_VIEWBUTTON)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_VIEWBUTTON8), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_VIEWBUTTON)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_VIEWBUTTON11), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_VIEWBUTTON)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_VIEWBUTTON12), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_VIEWBUTTON)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_256X128MODE), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_256X128MODE)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_COMBO_SELTEXGIO1), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELFILE)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_COMBO_SELTEXGIO2), 
					Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELFILE)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_COMBO_SELTEXMAN1), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELFILE)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_COMBO_SELTEXMAN2), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELFILE)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_COMBO_SELTEXTIFO), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELFILE)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_COMBO_SELTEXREFREE), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELFILE)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_COMBO_SELPALGIOC1), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELPAL)), IDI_PP_INFORMATION);	
	m_ctlTT.AddTool(GetDlgItem(IDC_COMBO_SELPALGIOC2), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELPAL)), IDI_PP_INFORMATION);	
	m_ctlTT.AddTool(GetDlgItem(IDC_COMBO_SELPALPORT1), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELPAL)), IDI_PP_INFORMATION);	
	m_ctlTT.AddTool(GetDlgItem(IDC_COMBO_SELPALPORT2), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELPAL)), IDI_PP_INFORMATION);	
	m_ctlTT.AddTool(GetDlgItem(IDC_COMBO_SELPALFLAG), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELPAL)), IDI_PP_INFORMATION);	
	m_ctlTT.AddTool(GetDlgItem(IDC_COMBO_SELAUTOGIO1), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELAUTO)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_COMBO_SELAUTOGIO2), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELAUTO)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_COMBO_SELAUTOMAN1), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELAUTO)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_COMBO_SELAUTOMAN2), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELAUTO)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_COMBO_SELAUTOFLAG), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELAUTOFLAG)), IDI_PP_INFORMATION);
	/*	
	m_ctlTT.AddTool(GetDlgItem(IDC_ADVANCED), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB2_ADVANCED)), IDI_PP_INFORMATION);
	*/
	m_ctlTT.AddTool(GetDlgItem(IDC_BUTTON_MAKETEX), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_MAKETEX)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_BUTTON_EXTRACTTEX), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_EXTRACTTEX)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(ID_INFO), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_INFO)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDOK), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_EXIT)), IDI_PP_INFORMATION);
	//m_ctlTT.AddTool(m_pTab->GetDlgItem(IDC_WECOMPRESSOR), 
	//					Temp + CString(MAKEINTRESOURCE(IDS_HELP_WECOMPRESSOR)), IDI_PP_INFORMATION);

	UpdateData(FALSE);
	
}

void CWECompressorTab3::OnQuit() 
{
	AfxGetMainWnd()->SendMessage(WM_CLOSE, 0, 0);	
}


void CWECompressorTab3::OnInfo() 
{
	CAboutDialog dlgAbout;
	dlgAbout.DoModal();	
}

BOOL CWECompressorTab3::UpdateControl(int IDCtrl,CString *NameFile,int Length,BOOL bValid)
{
	CString tempStr;
	char tempPath[_MAX_PATH];

	if (GetDlgItem(IDCtrl)->IsWindowEnabled() == TRUE)
	{
		if (bValid == FALSE)
		{						
			if (*NameFile == "")
				GetDlgItem(IDCtrl)->SetWindowText(CString(MAKEINTRESOURCE(IDS_NAME_NOFILE)));
			else
			{								
				PathCompactPathEx(tempPath, *NameFile, Length, '\\');
				GetDlgItem(IDCtrl)->SetWindowText(CString(tempPath));				
			}

		}
		else
		{
			GetDlgItem(IDCtrl)->GetWindowText(tempStr);
			if (tempStr == CString(MAKEINTRESOURCE(IDS_NAME_NOFILE)))		
				*NameFile = CString("");

		}

		return TRUE;
	}
	
	return FALSE;

}

BOOL CWECompressorTab3::UpdateMyData(BOOL bValid)
{
	BOOL bTemp;
	
	UpdateControl(IDC_FILE_NEWTEX,&m_NewTexFile,50,bValid);
	UpdateControl(IDC_FILE_TEXGIOC1,&m_TexFileGioc1,45,bValid);
	UpdateControl(IDC_FILE_TEXGIOC2,&m_TexFileGioc2,45,bValid);
	UpdateControl(IDC_FILE_PALGIOC1,&m_PalFileGioc1,45,bValid);
	UpdateControl(IDC_FILE_PALGIOC2,&m_PalFileGioc2,45,bValid);
	UpdateControl(IDC_FILE_PALPORT1,&m_PalFilePort1,45,bValid);
	UpdateControl(IDC_FILE_PALPORT2,&m_PalFilePort2,45,bValid);
	UpdateControl(IDC_FILE_TEXMANLUN1,&m_TexFileManLun1,45,bValid);
	UpdateControl(IDC_FILE_TEXMANLUN2,&m_TexFileManLun2,45,bValid);
	UpdateControl(IDC_FILE_TEXFLAG,&m_TexFlagFile,45,bValid);
	UpdateControl(IDC_FILE_PALFLAG,&m_PalFlagFile,45,bValid);
	UpdateControl(IDC_FILE_TEXREFREE,&m_TexRefreeFile,45,bValid);
		
	bTemp = TRUE;
	bTemp = UpdateData(bValid) && bTemp;

	return bTemp;
}

BOOL CWECompressorTab3::CheckValidity()
{	
	for (int i=0;i<12;i++)
	{
		if (m_LargeTex && ((i == 4) || (i == 10)))
			i++;
		if (m_FlagOK[i] == FALSE)
				return FALSE;
	}

	
	GetDlgItem(IDC_BUTTON_MAKETEX)->EnableWindow(TRUE);
	return TRUE;
}

BOOL CWECompressorTab3::CreateBMP(CString NameFileNew,CString NameFileImage,CString NameFilePalette,int IdxImage,int IdxPal)
{
	CFile   fImage,fPalette,NewFileBMP;
	CString TempMsg;
	CFileException e;
	UINT j,depth,totalheader,rgbsize,usedcol,comprflag;
	ULONG xsize,ysize,xtemp,ImageOffset,ImageLength,nImageSize,nPaletteSize;
	BYTE rgbq[RGB_SIZE256],AutoPal;
		
	// open data file to write
	if (!NewFileBMP.Open(NameFileNew, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + NameFileNew);
		return FALSE;
	}

	AutoPal = NameFileImage.Compare(NameFilePalette);

	if (!fImage.Open(NameFileImage, CFile::modeRead | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error reading in File ") + NameFileImage);
		return FALSE;
	}
	
	nImageSize = fImage.GetLength();

	BYTE* ImageBuf = new BYTE[nImageSize];
	fImage.Read(ImageBuf, nImageSize);
	fImage.Close();

	if (AutoPal != 0)
	{
		if (!fPalette.Open(NameFilePalette, CFile::modeRead | CFile::typeBinary, &e))
		{
			AfxMessageBox(_T("Error reading in File ") + NameFilePalette);
			return FALSE;	
		}
		
		nPaletteSize = fPalette.GetLength();
	
	}
	else
		nPaletteSize = 1;

	BYTE* PaletteBuf = new BYTE[nPaletteSize];
	if (AutoPal != 0)
	{
		fPalette.Read(PaletteBuf,nPaletteSize);
		fPalette.Close();
	}

	BYTE *pImage = ImageBuf;
	BYTE *pPalette = PaletteBuf;
	
	// palette reading
	if (AutoPal != 0)
	{
		if (IdxPal == 0)
		{
			if (nPaletteSize == 16*2)
			{
				depth = 4;
				usedcol = 16;
				totalheader = TOTAL_HEADER_SIZE16;
				rgbsize = RGB_SIZE16;
			}
			else
			if (nPaletteSize == 256*2)
			{
				depth = 8;
				usedcol = 256;
				totalheader = TOTAL_HEADER_SIZE256;
				rgbsize = RGB_SIZE256;
			}
			else
				return FALSE;

			for (UINT col=0; col < nPaletteSize; col+=4)
			{				
				WORD* tempword = new WORD;
				memcpy(tempword,pPalette + (col/2), 2);
				rgbq[col] = ((WORD) (*tempword>>10)) << 3;
				rgbq[col+1] = ((WORD) (*tempword>>5)&0x1f) << 3;
				rgbq[col+2] = ((WORD) (*tempword)&0x1f) << 3;
				rgbq[col+3] = 0;

				delete tempword;
			}
		}
		else
		{
			if (nPaletteSize == 16*4)
			{
				depth = 4;
				usedcol = 16;
				totalheader = TOTAL_HEADER_SIZE16;
				rgbsize = RGB_SIZE16;
			}
			else
			if (nPaletteSize == 256*4)
			{
				depth = 8;
				usedcol = 256;
				totalheader = TOTAL_HEADER_SIZE256;
				rgbsize = RGB_SIZE256;
			}
			else
				return FALSE;

			for (UINT col=0; col < nPaletteSize; col++)
				rgbq[col] = *(pPalette + col);
			
		}
		
	
	}
	else
	{
		if (IdxImage == 0)
		{
			BITMAPINFOHEADER bmih_read;

			memcpy(&bmih_read,pImage+BMFH_SIZE,sizeof(BITMAPINFOHEADER));			 
			depth = bmih_read.biBitCount;

			if (depth == 4)
			{
				totalheader = TOTAL_HEADER_SIZE16;
				rgbsize = RGB_SIZE16;
				usedcol = 16;
			}
			else
			if (depth == 8)
			{
				totalheader = TOTAL_HEADER_SIZE256;
				rgbsize = RGB_SIZE256;
				usedcol = 256;
			}
			else
				return FALSE;

			for (UINT col=0; col < rgbsize; col++)
				rgbq[col] = *(pImage + 54 + col);

		}
		else
		if (IdxImage == 1)
		{
			TIM_HEADER THead_read;
	
			memcpy(&THead_read,pImage,sizeof(TIM_HEADER));

			if (THead_read.type == TIM_4Bit)
			{
				depth = 4;
				usedcol = 16;
				totalheader = TOTAL_HEADER_SIZE16;
				rgbsize = RGB_SIZE16;
			}
			else
			if (THead_read.type == TIM_8Bit)
			{
				depth = 8;
				usedcol = 256;
				totalheader = TOTAL_HEADER_SIZE256;
				rgbsize = RGB_SIZE256;
			}
			else
				return FALSE;

			for (WORD col=0; col < rgbsize; col+=4)
			{				
				WORD* tempword = new WORD;
				memcpy(tempword,pImage + 20 + (col/2), 2);
				rgbq[col] = ((WORD) (*tempword>>10)) << 3;
				rgbq[col+1] = ((WORD) (*tempword>>5)&0x1f) << 3;
				rgbq[col+2] = ((WORD) (*tempword)&0x1f) << 3;
				rgbq[col+3] = 0;

				delete tempword;
			}

		}
		else
			return FALSE;
		
	}

	m_ActualColorsNumber = usedcol;

	// image reading
	if (IdxImage == 0)
	{
		BITMAPINFOHEADER bmih_read;

		memcpy(&bmih_read,pImage+BMFH_SIZE,sizeof(BITMAPINFOHEADER));
		xsize = bmih_read.biWidth;
		ysize = bmih_read.biHeight;
		comprflag = bmih_read.biCompression;
		ImageOffset = totalheader;
		ImageLength = xsize*ysize;

		if (depth == 4)
			ImageLength = ImageLength/2; 

	}
	else
	if (IdxImage == 1)
	{		
		TIM_DATAINFO TData_read;
	
		memcpy(&TData_read,pImage+ 20 + usedcol*2,sizeof(TIM_DATAINFO));

		xsize = TData_read.xsize*2;
		ysize = TData_read.ysize;
		comprflag = BI_RGB;
		ImageLength = xsize*ysize;
		if (depth == 4)
			xsize = xsize*2;
			
		ImageOffset = 32 + usedcol*2;
		
	}
	else
	{
		xsize = 128;
		ysize = 128;
		comprflag = BI_RGB;
		ImageLength = xsize*ysize;
		if (depth == 4)
			ImageLength = ImageLength/2; 
		ImageOffset = 0;

	}

	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	
	bmfh.bfType = 0x4D42;// BM
	bmfh.bfSize = totalheader + (xsize*ysize*depth)/8;
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = totalheader;

	NewFileBMP.Write(&bmfh,sizeof( BITMAPFILEHEADER ));
	
	bmih.biSize = BMIH_SIZE;
	bmih.biWidth = xsize;
	bmih.biHeight = ysize;
	bmih.biPlanes = 1;
	bmih.biBitCount = depth;
	bmih.biCompression = comprflag;
	bmih.biSizeImage = (xsize*ysize*depth)/8;
	bmih.biXPelsPerMeter = 0;
	bmih.biYPelsPerMeter = 0;
	bmih.biClrUsed = usedcol;
	bmih.biClrImportant = 0;
	
	NewFileBMP.Write(&bmih,sizeof( BITMAPINFOHEADER ));
		
	// write converted CLUT RGB table (psx uses 15bit RGB)
	NewFileBMP.Write(rgbq,rgbsize);

	BYTE* pImageData = new BYTE[ImageLength];
	if (IdxImage == 0)
	{
		memcpy(pImageData,pImage+ImageOffset,ImageLength);

	}
	else
	//if (IdxImage == 1)
	{
		BYTE* pData = pImage+ImageOffset;
		j=0;
		if (depth == 4)
		{
			// 4 bit
			xtemp =  xsize/2;
			for(long y1=ysize-1;y1>=0;y1--)
			{
				for(unsigned long x1=0;x1<xtemp;x1++)
				{
					pImageData[j] = (pData[(y1*xtemp)+x1])>>4;
					pImageData[j] |= ((pData[(y1*xtemp)+x1] << 4) & 0xF0);
					j++;
				}
			}

		}
		else
		{
			// 8 bit
			xtemp = xsize;
			for(long y1=ysize-1;y1>=0;y1--){
				for(unsigned long x1=0;x1<xtemp;x1++)
					pImageData[j++] = pData[(y1*xtemp)+x1];}
		}

	}

	// write Data block
	NewFileBMP.Write(pImageData,ImageLength);

	delete ImageBuf;
	delete PaletteBuf;
	delete pImageData;

	NewFileBMP.Close();

	return TRUE;

}

BOOL CWECompressorTab3::DecodeImage(BYTE *BufSrc,BYTE **BufDest,ULONG xsize,ULONG ysize,
									BYTE depth,BYTE ComprFlag)
{
	ULONG xtemp;
	UINT j;
	
	BYTE *pDest = *BufDest;

	j=0;
	if (depth == 4)
	{
		// 4 bit
		xtemp =  xsize/2;
		if (ComprFlag == BI_RGB)
		{		
			for(long y1=ysize-1;y1>=0;y1--)
			{
				for(unsigned long x1=0;x1<xtemp;x1++)
				{
					pDest[j] = (BufSrc[(y1*xtemp)+x1])>>4;
					pDest[j] |= ((BufSrc[(y1*xtemp)+x1] << 4) & 0xF0);
					j++;
				}
			}
		}
		else
		{
			// BI_RLE4
			BOOL bEOB = FALSE;
			BYTE *pSrc = BufSrc;
			
			int code1, code2, i, k, hi=0, abs_cou=0, adj_cou=0;

			BYTE* pTempData = new BYTE[xtemp*ysize];
			pDest = pTempData;

			BYTE *sta_ptr = pDest;
			for(i=0;i<xtemp*ysize && !bEOB;i+=2) 
			{
				code1 = *pSrc++;
				code2 = *pSrc++;

				if (abs_cou) 
				{
					if (hi)
						*pDest++ |= (code1 >> 4);
					else
						*pDest = (code1 & 0xF0);
					abs_cou--;
					hi ^= 1;
					
					if (abs_cou) 
					{
						if (hi)
							*pDest++ |= (code1 & 0x0F);
						else
							*pDest = (code1 << 4);
						abs_cou--;
						hi ^= 1;
					}
					
					if( abs_cou )
					{
						if (hi)
							*pDest++ |= (code2 >> 4);
						else
							*pDest = (code2 & 0xF0);
						abs_cou--;
						hi ^= 1;
					}
					
					if( abs_cou )
					{
						if (hi)
							*pDest++ |= (code2 & 0x0F);
						else
							*pDest = (code2 << 4);
						abs_cou--;
						hi ^= 1;
					}
					continue;

				}
									
				if (code1 == 0)  // RLE_COMMAND
				{
					switch (code2) // Escape
					{
						case 0:	// End of line escape EOL
								if( !adj_cou )  adj_cou = 3-((pDest-sta_ptr+3)%4);
								for(i=0;i<adj_cou;i++) *pDest++ = 0;
								continue;
						case 1: // End of block escape EOB
								if( !adj_cou )  adj_cou = 3-((pDest-sta_ptr+3)%4);
								for(i=0;i<adj_cou;i++) *pDest++ = 0;
								bEOB = TRUE;
								break;
						case 2: // Delta escape. RLE_DELTA								
								break;
						default: // Literal packet
								abs_cou = code2;
								break;
					}	
					continue;
				}
			
				if (!bEOB) // Literal
				{
					for(k=0;k < code1 / 2;k++ )
					{
						if (hi) 
						{
							*pDest++ |= (code2 >> 4);
							*pDest = (code2 & 0x0F);
						} 
						else 
							*pDest++ = code2;
					}

					if (code1%2) 
					{
						if (hi)
							*pDest++ |= (code2 >> 4);
						else 
							*pDest = (code2 & 0xF0);
						hi ^= 1;
					}

				}
			}

			pDest = *BufDest;
			for(long y1=ysize-1;y1>=0;y1--)
			{
				for(unsigned long x1=0;x1<xtemp;x1++)
				{
					pDest[j] = (pTempData[(y1*xtemp)+x1])>>4;
					pDest[j] |= ((pTempData[(y1*xtemp)+x1] << 4) & 0xF0);
					j++;
				}
			}

			delete pTempData;

		}
	}
	else
	{
		// 8 bit
		
		xtemp = xsize;
		if (ComprFlag == BI_RGB)
		{		
			for(long y1=ysize-1;y1>=0;y1--){
				for(unsigned long x1=0;x1<xtemp;x1++)
					pDest[j++] = BufSrc[(y1*xtemp)+x1];}
		}
		else
		{
			// BI_RLE8
			BOOL bEOB = FALSE;
			BYTE *pSrc = BufSrc;
			
			int code1, code2, i, k, abs_cou=0, adj_cou=0;

			BYTE* pTempData = new BYTE[xtemp*ysize];
			pDest = pTempData;

			BYTE *sta_ptr = pDest;
			for(i=0;i<xtemp*ysize && !bEOB;i+=2) 
			{
				code1 = *pSrc++;
				code2 = *pSrc++;

				if (abs_cou) 
				{
					*pDest++ = code1;
					abs_cou--;
					if (abs_cou) 
					{
						*pDest++ = code2;
						abs_cou--;
					}
					continue;
				}
					
				if (code1 == 0)  // RLE_COMMAND
				{
					switch (code2) // Escape
					{
						case 0:	// End of line escape EOL
								if( !adj_cou )  adj_cou = 3-((pDest-sta_ptr+3)%4);
								for(i=0;i<adj_cou;i++) *pDest++ = 0;
								continue;
						case 1: // End of block escape EOB
								if( !adj_cou )  adj_cou = 3-((pDest-sta_ptr+3)%4);
								for(i=0;i<adj_cou;i++) *pDest++ = 0;
								bEOB = TRUE;
								break;
						case 2: // Delta escape. RLE_DELTA								
								break;
						default: // Literal packet
								abs_cou = code2;
								break;
					}	
					continue;
				}
			
				if (!bEOB) // Literal
					for(k=0;k < code1;k++ ) 
						*pDest++ = code2;				
			}

			pDest = *BufDest;
			for(long y1=ysize-1;y1>=0;y1--){
				for(unsigned long x1=0;x1<xtemp;x1++)
					pDest[j++] = pTempData[(y1*xtemp)+x1];}

			delete pTempData;
		}
	}

	return TRUE;
}

void CWECompressorTab3::ViewImage(CString NameFileImage,CString NameFilePalette,int IdxImage,int IdxPal)
{
	CString TempName;
	char tmPath[255];
	
	UpdateData(TRUE);
	// Prepare Temp File
	GetTempPath(255, tmPath);
	TempName = CString(tmPath) + "WEShirt.tmp";
	if (CreateBMP(TempName,NameFileImage,NameFilePalette,IdxImage,IdxPal))
	{
		CBitmapDialog dlg(TempName,0,0,m_ActualColorsNumber);

		dlg.DoModal();
	}
	
}

BOOL CWECompressorTab3::GetImageBlock(CString FileName,int FileType,BYTE **BufDest,UINT *BlockLen)
{
	CFile   fImageSrc;
	CString TempMsg;
	CFileException e;
	UINT depth,comprflag;
	ULONG xsize,ysize,ImageOffset,ImageLength,nImageSize;
	BOOL Result;
		
	if (!fImageSrc.Open(FileName, CFile::modeRead | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error reading in source File ") + FileName);
		return FALSE;
	}
	
	Result = TRUE;
	nImageSize = fImageSrc.GetLength();

	BYTE* ImageBuf = new BYTE[nImageSize];
	fImageSrc.Read(ImageBuf,nImageSize);
	fImageSrc.Close();

	BYTE *pImage = ImageBuf;	
	
	// image reading
	depth = 8;
	if (FileType == 0)
	{
		BITMAPINFOHEADER bmih_read;

		memcpy(&bmih_read,pImage+BMFH_SIZE,sizeof(BITMAPINFOHEADER));
		xsize = bmih_read.biWidth;
		ysize = bmih_read.biHeight;
		comprflag = bmih_read.biCompression;
		ImageOffset = TOTAL_HEADER_SIZE256;
		ImageLength = xsize*ysize;
	}
	else
	if (FileType == 1)
	{		
		TIM_DATAINFO TData_read;
	
		memcpy(&TData_read,pImage + 20 + RGB_SIZE256/2,sizeof(TIM_DATAINFO));

		xsize = TData_read.xsize*2;
		ysize = TData_read.ysize;		
		ImageLength = xsize*ysize;
		ImageOffset = 32 + RGB_SIZE256/2;
		
	}
	else
	{
		xsize = 128;
		ysize = 128;
		ImageLength = xsize*ysize;	
		ImageOffset = 0;

	}

	BYTE* pImageData = new BYTE[ImageLength];	

	if (FileType == 0)
	{
		// 8 bit
		
		BYTE* pImageTemp = new BYTE[ImageLength];

		Result = DecodeImage(pImage+ImageOffset,&pImageTemp,xsize,ysize,depth,comprflag);
		
		CWECompress tempclass;
			
		tempclass.Compress(&pImageData,pImageTemp,&ImageLength,ImageLength);

		delete pImageTemp;		

	}
	else
	if (FileType == 1)
	{
		CWECompress tempclass;
			
		tempclass.Compress(&pImageData,pImage+ImageOffset,&ImageLength,ImageLength);
	}
	else
	if (FileType == 2)
	{
		CWECompress tempclass;
			
		ImageLength = tempclass.FindCompressedLength(pImage+ImageOffset);

		memcpy(pImageData,pImage+ImageOffset,ImageLength);
	}
	else
	{
		memcpy(pImageData,pImage+ImageOffset,ImageLength);
	}

	memcpy(*BufDest,pImageData,ImageLength);

	*BlockLen = ImageLength;

	delete ImageBuf;
	delete pImageData;

	return Result;
}

BOOL CWECompressorTab3::GetLargeImageBlock(CString FileName,int FileType,BYTE **BufDest,
										   BYTE **BufDest2,UINT *BlockLen,UINT *BlockLen2)
{
	CFile   fImageSrc;
	CString TempMsg;
	CFileException e;
	UINT j,depth,comprflag;
	ULONG xsize,ysize,xtemp,ImageOffset,ImageLength,nImageSize;
	BOOL Result;
		
	if (!fImageSrc.Open(FileName, CFile::modeRead | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error reading in source File ") + FileName);
		return FALSE;
	}
	
	nImageSize = fImageSrc.GetLength();

	BYTE* ImageBuf = new BYTE[nImageSize];
	fImageSrc.Read(ImageBuf,nImageSize);
	fImageSrc.Close();

	BYTE *pImage = ImageBuf;	
	
	// image reading
	depth = 8;
	if (FileType == 0)
	{
		BITMAPINFOHEADER bmih_read;

		memcpy(&bmih_read,pImage+BMFH_SIZE,sizeof(BITMAPINFOHEADER));
		xsize = bmih_read.biWidth;
		ysize = bmih_read.biHeight;
		comprflag = bmih_read.biCompression;
		ImageOffset = TOTAL_HEADER_SIZE256;
		ImageLength = xsize*ysize;
	}
	else
	if (FileType == 1)
	{		
		TIM_DATAINFO TData_read;
	
		memcpy(&TData_read,pImage + 20 + RGB_SIZE256/2,sizeof(TIM_DATAINFO));

		xsize = TData_read.xsize*2;
		ysize = TData_read.ysize;		
		ImageLength = xsize*ysize;
		ImageOffset = 32 + RGB_SIZE256/2;
		
	}
	else
	{
		xsize = 256;
		ysize = 128;
		ImageLength = xsize*ysize;	
		ImageOffset = 0;

	}
	
	BYTE* pImageData = new BYTE[ImageLength];
	BYTE* pImage1 = new BYTE[ImageLength];
	BYTE* pImage2 = new BYTE[ImageLength];
	nImageSize = ImageLength /2;
	BYTE* pData = pImage+ImageOffset;
	if (FileType == 0)
	{
		// 8 bit
		
		BYTE* pImageTemp = new BYTE[ImageLength];

		Result = DecodeImage(pImage+ImageOffset,&pImageTemp,xsize,ysize,depth,comprflag);
		
		// copy reverse data to pData
		j=0;
		xtemp = xsize / 2;
		for(long y1=0;y1<ysize;y1++)
		{
			for(unsigned long x1=0;x1<xtemp;x1++)
			{
				pImage2[(y1*xtemp)+x1] = pImageTemp[j+xtemp];
				pImage1[(y1*xtemp)+x1] = pImageTemp[j++];
			}
			j+= xtemp;
		}

		CWECompress tempclass;
			
		tempclass.Compress(&pImageData,pImage1,&ImageLength,nImageSize);
		memcpy(*BufDest,pImageData,ImageLength);
		*BlockLen = ImageLength;

		tempclass.Compress(&pImageData,pImage2,&ImageLength,nImageSize);
		memcpy(*BufDest2,pImageData,ImageLength);
		*BlockLen2 = ImageLength;

		delete pImageTemp;

	}
	else
	if ((FileType == 1) || (FileType == 3))
	{
		memcpy(pImageData,pData,ImageLength);

		// copy reverse data to pData
		j=0;
		xtemp = xsize / 2;
		for(long y1=0;y1<ysize;y1++)
		{
			for(unsigned long x1=0;x1<xtemp;x1++)
			{
				pImage2[(y1*xtemp)+x1] = pData[j+xtemp];
				pImage1[(y1*xtemp)+x1] = pData[j++];
			}
			j+= xtemp;
		}

		CWECompress tempclass;		

		tempclass.Compress(&pImageData,pImage1,&ImageLength,nImageSize);
		memcpy(*BufDest,pImageData,ImageLength);
		*BlockLen = ImageLength;

		tempclass.Compress(&pImageData,pImage2,&ImageLength,nImageSize);
		memcpy(*BufDest2,pImageData,ImageLength);
		*BlockLen2 = ImageLength;

	}
	else
	{
		CWECompress tempclass;
		
		tempclass.DeCompress(&pImageData,pData);

		// copy reverse data to pData
		j=0;
		xtemp = xsize / 2;
		for(long y1=0;y1<ysize;y1++)
		{
			for(unsigned long x1=0;x1<xtemp;x1++)
			{
				pImage2[(y1*xtemp)+x1] = pData[j+xtemp];
				pImage1[(y1*xtemp)+x1] = pData[j++];
			}
			j+= xtemp;
		}

		tempclass.Compress(&pImageData,pImage1,&ImageLength,nImageSize);
		memcpy(*BufDest,pImageData,ImageLength);
		*BlockLen = ImageLength;

		tempclass.Compress(&pImageData,pImage2,&ImageLength,nImageSize);
		memcpy(*BufDest2,pImageData,ImageLength);
		*BlockLen2 = ImageLength;
	}
	
	delete ImageBuf;
	delete pImageData;
	delete pImage1;
	delete pImage2;

	return Result;
}


BOOL CWECompressorTab3::GetClutBlock(CString FileName,int FileType,BYTE **Clut)
{
	CFile   fPaletteSrc;
	CString TempMsg;
	CFileException e;
	UINT j,depth,totalheader,clutsize,usedcol;
	ULONG nPaletteSize;
	BYTE rgbq[RGB_SIZE256];
	BYTE clut256[RGB_SIZE256/2];
	
	if (!fPaletteSrc.Open(FileName, CFile::modeRead | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error reading in source File ") + FileName);
		return FALSE;	
	}
		
	nPaletteSize = fPaletteSrc.GetLength();
	
	BYTE* PaletteBuf = new BYTE[nPaletteSize];
	fPaletteSrc.Read(PaletteBuf,nPaletteSize);
	fPaletteSrc.Close();
	
	BYTE *pPalette = PaletteBuf;
	
	// palette reading
	depth = 8;
	usedcol = 256;
	totalheader = TOTAL_HEADER_SIZE256;
	clutsize = RGB_SIZE256/2;

	if (FileType == 0)
	{
		memcpy(clut256,pPalette, nPaletteSize);
		
	}
	else
	if (FileType == 1)
	{
		memcpy(rgbq,pPalette,nPaletteSize);

			j=0;
			for (UINT col=0; col < nPaletteSize; col+=4)
			{			
				WORD tempword = (((BYTE) rgbq[col+2] >> 3 | 
								 ((WORD) (rgbq[col+1] >> 3) << 5)) | 
								 (((DWORD) (BYTE) (rgbq[col] >> 3)) << 10));
				clut256[j++] = LOBYTE(tempword);
				clut256[j++] = HIBYTE(tempword);
				
			}

	}
	else
	if (FileType == 2)
	{
		BITMAPINFOHEADER bmih_read;

		memcpy(&bmih_read,pPalette+BMFH_SIZE,sizeof(BITMAPINFOHEADER));			 
		depth = bmih_read.biBitCount;
		//usedcol = bmih_read.biClrUsed;

		memcpy(rgbq,pPalette + 54,clutsize*2);

		j=0;
		for (UINT col=0; col < clutsize*2; col+=4)
		{				
			WORD tempword = (((BYTE) rgbq[col+2] >> 3 | 
							 ((WORD) (rgbq[col+1] >> 3) << 5)) | 
							 (((DWORD) (BYTE) (rgbq[col] >> 3)) << 10));
			clut256[j++] = LOBYTE(tempword);
			clut256[j++] = HIBYTE(tempword);
				
		}


	}
	else
	if (FileType == 3)
	{
		memcpy(clut256,pPalette + 20, clutsize);

	}
	else
		return FALSE;
			
	
	memcpy(*Clut,clut256, clutsize);

	delete PaletteBuf;
	
	return TRUE;
}

BOOL CWECompressorTab3::CreateTEX()
{
	CFile   fNewTex;
	CString TempMsg;
	CFileException e;
	UINT BlockLength,BlockLength2,StartOffset;
	ULONG TexLength;	

	const INT32 MaxTexLen = 65535;
	const INT32 MaxTexSize = 128*128;
		
	// open data file to write
	if (!fNewTex.Open(m_NewTexFile, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + m_NewTexFile);
		return FALSE;
	}

	BYTE* nTexBuf = new BYTE[MaxTexLen];
	BYTE* nBlockBuf = new BYTE[MaxTexSize];
	BYTE* nBlockClut = new BYTE[RGB_SIZE256/2];

	BYTE *pMainHeader = nTexBuf;
	BYTE *pCur = nTexBuf + 48;

	// Prepare Main 48 Header
	if (m_GameType == 0)
	{
		BYTE HeaderData[48] = 
		{
			0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 
			0x0F, 0x80, 0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 
			0x0F, 0x80, 0x00, 0x00, 0x0F, 0x80 
		};

		memcpy(pMainHeader, HeaderData, 48);

	}
	else
	{
		BYTE HeaderData[48] = 
		{
			0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 
			0x0F, 0x80, 0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 
			0x0F, 0x80, 0x00, 0x00, 0x0F, 0x80 
		};

		memcpy(pMainHeader, HeaderData, 48);
	}

	if (!m_LargeTex)
	{
		// Prepare 1st block : Player/GK Data Tex 1st shirt
		if (!GetImageBlock(m_TexFileGioc1,m_IdxTexGio1,&nBlockBuf,&BlockLength))
		{
			fNewTex.Close();
			delete nTexBuf;	
			delete nBlockBuf;	
			return FALSE;
		}
		memcpy(pCur, nBlockBuf, BlockLength);	
		StartOffset = pCur - nTexBuf;
		pCur+= BlockLength;
		// write header
		if (m_GameType == 0)
		{
			BYTE SubHeader[32] = 
			{
				0x0A, 0x00, 0x40, 0x02, 0x00, 0x01, 0x40, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00
			};

			memcpy(pCur, SubHeader, 32);

			*(pCur + 12) = LOBYTE(StartOffset);
			*(pCur + 13) = HIBYTE(StartOffset);		
			*pMainHeader = LOBYTE(pCur - nTexBuf);
			*(pMainHeader + 1) = HIBYTE(pCur - nTexBuf);
			pCur += 32;
		}
		else
		{
			BYTE SubHeader[32] = 
			{
				0x0A, 0x00, 0x40, 0x02, 0x00, 0x01, 0x40, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00
			};

			memcpy(pCur, SubHeader, 32);

			*(pCur + 12) = LOBYTE(StartOffset);
			*(pCur + 13) = HIBYTE(StartOffset);		
			*pMainHeader = LOBYTE(pCur - nTexBuf);
			*(pMainHeader + 1) = HIBYTE(pCur - nTexBuf);
			pCur += 32;		
		}

		// Prepare 2nd block : Player/GK Long Shirts Data Tex 1st shirt	 
		if (!GetImageBlock(m_TexFileManLun1,m_IdxTexMan1,&nBlockBuf,&BlockLength))
		{
			fNewTex.Close();
			delete nTexBuf;	
			delete nBlockBuf;	
			return FALSE;
		}
		memcpy(pCur, nBlockBuf, BlockLength);
		StartOffset = pCur - nTexBuf;
		pCur+= BlockLength;
		// write header
		if (m_GameType == 0)
		{
			BYTE SubHeader[32] = 
			{
				0x0A, 0x00, 0x40, 0x02, 0x80, 0x01, 0x40, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00
			};
	
			memcpy(pCur, SubHeader, 32);

			*(pCur + 12) = LOBYTE(StartOffset);
			*(pCur + 13) = HIBYTE(StartOffset);		
			*(pMainHeader + 36)= LOBYTE(pCur - nTexBuf);
			*(pMainHeader + 37) = HIBYTE(pCur - nTexBuf);
			pCur += 32;
		}
		else
		{
			BYTE SubHeader[32] = 
			{
				0x0A, 0x00, 0x40, 0x02, 0x80, 0x01, 0x40, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00
			};

			memcpy(pCur, SubHeader, 32);

			*(pCur + 12) = LOBYTE(StartOffset);
			*(pCur + 13) = HIBYTE(StartOffset);		
			*(pMainHeader + 36)= LOBYTE(pCur - nTexBuf);
			*(pMainHeader + 37) = HIBYTE(pCur - nTexBuf);
			pCur += 32;		
		}
	}
	else
	{
		// Prepare 1st and 2nd block : Player/GK Data FULL Tex 1st shirt
		BYTE* nBlockBuf2 = new BYTE[MaxTexSize];
		if (!GetLargeImageBlock(m_TexFileGioc1,m_IdxTexGio1,&nBlockBuf,&nBlockBuf2,&BlockLength,
								&BlockLength2))
		{
			fNewTex.Close();
			delete nTexBuf;	
			delete nBlockBuf;
			delete nBlockBuf2;
			return FALSE;
		}
		memcpy(pCur, nBlockBuf, BlockLength);	
		StartOffset = pCur - nTexBuf;
		pCur+= BlockLength;
		// write header
		if (m_GameType == 0)
		{
			BYTE SubHeader[32] = 
			{
				0x0A, 0x00, 0x40, 0x02, 0x00, 0x01, 0x40, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00
			};

			memcpy(pCur, SubHeader, 32);

			*(pCur + 12) = LOBYTE(StartOffset);
			*(pCur + 13) = HIBYTE(StartOffset);		
			*pMainHeader = LOBYTE(pCur - nTexBuf);
			*(pMainHeader + 1) = HIBYTE(pCur - nTexBuf);
			pCur += 32;
		}
		else
		{
			BYTE SubHeader[32] = 
			{
				0x0A, 0x00, 0x40, 0x02, 0x00, 0x01, 0x40, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00
			};

			memcpy(pCur, SubHeader, 32);

			*(pCur + 12) = LOBYTE(StartOffset);
			*(pCur + 13) = HIBYTE(StartOffset);		
			*pMainHeader = LOBYTE(pCur - nTexBuf);
			*(pMainHeader + 1) = HIBYTE(pCur - nTexBuf);
			pCur += 32;		
		}

		memcpy(pCur, nBlockBuf2, BlockLength2);
		StartOffset = pCur - nTexBuf;
		pCur+= BlockLength2;
		// write header
		if (m_GameType == 0)
		{
			BYTE SubHeader[32] = 
			{
				0x0A, 0x00, 0x40, 0x02, 0x80, 0x01, 0x40, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00
			};
	
			memcpy(pCur, SubHeader, 32);

			*(pCur + 12) = LOBYTE(StartOffset);
			*(pCur + 13) = HIBYTE(StartOffset);		
			*(pMainHeader + 36)= LOBYTE(pCur - nTexBuf);
			*(pMainHeader + 37) = HIBYTE(pCur - nTexBuf);
			pCur += 32;
		}
		else
		{
			BYTE SubHeader[32] = 
			{
				0x0A, 0x00, 0x40, 0x02, 0x80, 0x01, 0x40, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00
			};

			memcpy(pCur, SubHeader, 32);

			*(pCur + 12) = LOBYTE(StartOffset);
			*(pCur + 13) = HIBYTE(StartOffset);		
			*(pMainHeader + 36)= LOBYTE(pCur - nTexBuf);
			*(pMainHeader + 37) = HIBYTE(pCur - nTexBuf);
			pCur += 32;		
		}

		delete nBlockBuf2;

	}

	// Prepare 3rd block : Player Palette Tex 1st shirt
	if (!GetClutBlock(m_PalFileGioc1,m_IdxPalGioc1,&nBlockClut))
	{
		fNewTex.Close();
		delete nTexBuf;
		delete nBlockClut;
		return FALSE;
	}

	memcpy(pCur, nBlockClut, RGB_SIZE256/2);
	StartOffset = pCur - nTexBuf;
	pCur += RGB_SIZE256/2;
	if (m_GameType == 0)
	{
		BYTE SubHeader[32] = 
		{
			0x09, 0xFF, 0x00, 0x00, 0xE6, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
			0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00
		};

		memcpy(pCur, SubHeader, 32);

		*(pCur + 12) = LOBYTE(StartOffset);
		*(pCur + 13) = HIBYTE(StartOffset);
		*(pMainHeader + 4) = LOBYTE(pCur - nTexBuf);
		*(pMainHeader + 5) = HIBYTE(pCur - nTexBuf);
		pCur += 32;
	}
	else
	{
		BYTE SubHeader[32] = 
		{
			0x09, 0xFF, 0x00, 0x00, 0xE6, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
			0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00
		};

		memcpy(pCur, SubHeader, 32);

		*(pCur + 12) = LOBYTE(StartOffset);
		*(pCur + 13) = HIBYTE(StartOffset);
		*(pMainHeader + 4) = LOBYTE(pCur - nTexBuf);
		*(pMainHeader + 5) = HIBYTE(pCur - nTexBuf);
		pCur += 32;
	}

	// Prepare 4th block : GK Palette Tex 1st shirt
	if (!GetClutBlock(m_PalFilePort1,m_IdxPalPort1,&nBlockClut))
	{
		fNewTex.Close();
		delete nTexBuf;
		delete nBlockClut;
		return FALSE;
	}

	memcpy(pCur, nBlockClut, RGB_SIZE256/2);
	StartOffset = pCur - nTexBuf;
	pCur += RGB_SIZE256/2;
	if (m_GameType == 0)
	{
		BYTE SubHeader[32] = 
		{
			0x09, 0xFF, 0x00, 0x00, 0xE8, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
			0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00
		};

		memcpy(pCur, SubHeader, 32);

		*(pCur + 12) = LOBYTE(StartOffset);
		*(pCur + 13) = HIBYTE(StartOffset);
		*(pMainHeader + 16) = LOBYTE(pCur - nTexBuf);
		*(pMainHeader + 17) = HIBYTE(pCur - nTexBuf);
		pCur += 32;
	}
	else
	{
		BYTE SubHeader[32] = 
		{
			0x09, 0xFF, 0x00, 0x00, 0xE8, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
			0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00
		};

		memcpy(pCur, SubHeader, 32);

		*(pCur + 12) = LOBYTE(StartOffset);
		*(pCur + 13) = HIBYTE(StartOffset);
		*(pMainHeader + 16) = LOBYTE(pCur - nTexBuf);
		*(pMainHeader + 17) = HIBYTE(pCur - nTexBuf);
		pCur += 32;
	}

	if (!m_LargeTex)
	{
		// Prepare 5th block : Player/GK Data Tex 2nd shirt
		if (!GetImageBlock(m_TexFileGioc2,m_IdxTexGio2,&nBlockBuf,&BlockLength))
		{
			fNewTex.Close();
			delete nTexBuf;	
			delete nBlockBuf;	
			return FALSE;
		}
		memcpy(pCur, nBlockBuf, BlockLength);
		StartOffset = pCur - nTexBuf;
		pCur+= BlockLength;
		// write header
		if (m_GameType == 0)
		{
			BYTE SubHeader[32] = 
			{
				0x0A, 0x00, 0x40, 0x02, 0x00, 0x01, 0x40, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00
			};

			memcpy(pCur, SubHeader, 32);
	
			*(pCur + 12) = LOBYTE(StartOffset);
			*(pCur + 13) = HIBYTE(StartOffset);		
			*(pMainHeader + 8) = LOBYTE(pCur - nTexBuf);
			*(pMainHeader + 9) = HIBYTE(pCur - nTexBuf);
			pCur += 32;
		}
		else
		{
			BYTE SubHeader[32] = 
			{
				0x0A, 0x00, 0x40, 0x02, 0x00, 0x01, 0x40, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00
			};

			memcpy(pCur, SubHeader, 32);

			*(pCur + 12) = LOBYTE(StartOffset);
			*(pCur + 13) = HIBYTE(StartOffset);		
			*(pMainHeader + 8) = LOBYTE(pCur - nTexBuf);
			*(pMainHeader + 9) = HIBYTE(pCur - nTexBuf);
			pCur += 32;		
		}

		// Prepare 6th block : Player/GK Long Shirts Data Tex 2nd shirt
	 
		if (!GetImageBlock(m_TexFileManLun2,m_IdxTexMan2,&nBlockBuf,&BlockLength))
		{
			fNewTex.Close();
			delete nTexBuf;	
			delete nBlockBuf;	
			return FALSE;
		}
		memcpy(pCur, nBlockBuf, BlockLength);
		StartOffset = pCur - nTexBuf;
		pCur+= BlockLength;
		// write header
		if (m_GameType == 0)
		{
			BYTE SubHeader[32] = 
			{
				0x0A, 0x00, 0x40, 0x02, 0x80, 0x01, 0x40, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00
			};

			memcpy(pCur, SubHeader, 32);

			*(pCur + 12) = LOBYTE(StartOffset);
			*(pCur + 13) = HIBYTE(StartOffset);		
			*(pMainHeader + 40)= LOBYTE(pCur - nTexBuf);
			*(pMainHeader + 41) = HIBYTE(pCur - nTexBuf);
			pCur += 32;
		}
		else
		{
			BYTE SubHeader[32] = 
			{
				0x0A, 0x00, 0x40, 0x02, 0x80, 0x01, 0x40, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00
			};

			memcpy(pCur, SubHeader, 32);

			*(pCur + 12) = LOBYTE(StartOffset);
			*(pCur + 13) = HIBYTE(StartOffset);		
			*(pMainHeader + 40)= LOBYTE(pCur - nTexBuf);
			*(pMainHeader + 41) = HIBYTE(pCur - nTexBuf);
			pCur += 32;		
		}
	}
	else
	{
		// Prepare 5th and 6th block : Player/GK Data FULL Tex 2nd shirt

		BYTE* nBlockBuf2 = new BYTE[MaxTexSize];
		if (!GetLargeImageBlock(m_TexFileGioc2,m_IdxTexGio2,&nBlockBuf,&nBlockBuf2,&BlockLength,
								&BlockLength2))		
		{
			fNewTex.Close();
			delete nTexBuf;	
			delete nBlockBuf;
			delete nBlockBuf2;
			return FALSE;
		}
		memcpy(pCur, nBlockBuf, BlockLength);
		StartOffset = pCur - nTexBuf;
		pCur+= BlockLength;
		// write header
		if (m_GameType == 0)
		{
			BYTE SubHeader[32] = 
			{
				0x0A, 0x00, 0x40, 0x02, 0x00, 0x01, 0x40, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00
			};

			memcpy(pCur, SubHeader, 32);
	
			*(pCur + 12) = LOBYTE(StartOffset);
			*(pCur + 13) = HIBYTE(StartOffset);		
			*(pMainHeader + 8) = LOBYTE(pCur - nTexBuf);
			*(pMainHeader + 9) = HIBYTE(pCur - nTexBuf);
			pCur += 32;
		}
		else
		{
			BYTE SubHeader[32] = 
			{
				0x0A, 0x00, 0x40, 0x02, 0x00, 0x01, 0x40, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00
			};

			memcpy(pCur, SubHeader, 32);

			*(pCur + 12) = LOBYTE(StartOffset);
			*(pCur + 13) = HIBYTE(StartOffset);		
			*(pMainHeader + 8) = LOBYTE(pCur - nTexBuf);
			*(pMainHeader + 9) = HIBYTE(pCur - nTexBuf);
			pCur += 32;		
		}

		////
		memcpy(pCur, nBlockBuf2, BlockLength2);
		StartOffset = pCur - nTexBuf;
		pCur+= BlockLength2;
		// write header
		if (m_GameType == 0)
		{
			BYTE SubHeader[32] = 
			{
				0x0A, 0x00, 0x40, 0x02, 0x80, 0x01, 0x40, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00
			};

			memcpy(pCur, SubHeader, 32);

			*(pCur + 12) = LOBYTE(StartOffset);
			*(pCur + 13) = HIBYTE(StartOffset);		
			*(pMainHeader + 40)= LOBYTE(pCur - nTexBuf);
			*(pMainHeader + 41) = HIBYTE(pCur - nTexBuf);
			pCur += 32;
		}
		else
		{
			BYTE SubHeader[32] = 
			{
				0x0A, 0x00, 0x40, 0x02, 0x80, 0x01, 0x40, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
				0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00
			};

			memcpy(pCur, SubHeader, 32);

			*(pCur + 12) = LOBYTE(StartOffset);
			*(pCur + 13) = HIBYTE(StartOffset);		
			*(pMainHeader + 40)= LOBYTE(pCur - nTexBuf);
			*(pMainHeader + 41) = HIBYTE(pCur - nTexBuf);
			pCur += 32;		
		}

		delete nBlockBuf2;

	}

	// Prepare 7th block : Player Palette Tex 2nd shirt
	if (!GetClutBlock(m_PalFileGioc2,m_IdxPalGioc2,&nBlockClut))
	{
		fNewTex.Close();
		delete nTexBuf;
		delete nBlockClut;
		return FALSE;
	}

	memcpy(pCur, nBlockClut, RGB_SIZE256/2);
	StartOffset = pCur - nTexBuf;
	pCur += RGB_SIZE256/2;
	if (m_GameType == 0)
	{
		BYTE SubHeader[32] = 
		{
			0x09, 0xFF, 0x00, 0x00, 0xE6, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
			0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00
		};

		memcpy(pCur, SubHeader, 32);

		*(pCur + 12) = LOBYTE(StartOffset);
		*(pCur + 13) = HIBYTE(StartOffset);
		*(pMainHeader + 12) = LOBYTE(pCur - nTexBuf);
		*(pMainHeader + 13) = HIBYTE(pCur - nTexBuf);
		pCur += 32;
	}
	else
	{
		BYTE SubHeader[32] = 
		{
			0x09, 0xFF, 0x00, 0x00, 0xE6, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
			0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00
		};

		memcpy(pCur, SubHeader, 32);

		*(pCur + 12) = LOBYTE(StartOffset);
		*(pCur + 13) = HIBYTE(StartOffset);
		*(pMainHeader + 12) = LOBYTE(pCur - nTexBuf);
		*(pMainHeader + 13) = HIBYTE(pCur - nTexBuf);
		pCur += 32;
	}

	// Prepare 8th block : GK Palette Tex 2nd shirt
	if (!GetClutBlock(m_PalFilePort2,m_IdxPalPort2,&nBlockClut))
	{
		fNewTex.Close();
		delete nTexBuf;
		delete nBlockClut;
		return FALSE;
	}

	memcpy(pCur, nBlockClut, RGB_SIZE256/2);
	StartOffset = pCur - nTexBuf;
	pCur += RGB_SIZE256/2;
	if (m_GameType == 0)
	{
		BYTE SubHeader[32] = 
		{
			0x09, 0xFF, 0x00, 0x00, 0xE8, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
			0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00
		};

		memcpy(pCur, SubHeader, 32);

		*(pCur + 12) = LOBYTE(StartOffset);
		*(pCur + 13) = HIBYTE(StartOffset);
		*(pMainHeader + 20) = LOBYTE(pCur - nTexBuf);
		*(pMainHeader + 21) = HIBYTE(pCur - nTexBuf);
		pCur += 32;
	}
	else
	{
		BYTE SubHeader[32] = 
		{
			0x09, 0xFF, 0x00, 0x00, 0xE8, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
			0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00
		};

		memcpy(pCur, SubHeader, 32);

		*(pCur + 12) = LOBYTE(StartOffset);
		*(pCur + 13) = HIBYTE(StartOffset);
		*(pMainHeader + 20) = LOBYTE(pCur - nTexBuf);
		*(pMainHeader + 21) = HIBYTE(pCur - nTexBuf);
		pCur += 32;
	}

	// Prepare 9th block : Flag Data Tex
	if (!GetImageBlock(m_TexFlagFile,m_IdxTexTifo,&nBlockBuf,&BlockLength))
	{
		fNewTex.Close();
		delete nTexBuf;	
		delete nBlockBuf;	
		return FALSE;
	}
	memcpy(pCur, nBlockBuf, BlockLength);
	StartOffset = pCur - nTexBuf;
	pCur+= BlockLength;
	// write header
	if (m_GameType == 0)
	{
		BYTE SubHeader[32] = 
		{
			0x0A, 0x00, 0xC0, 0x02, 0x00, 0x01, 0x40, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
			0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00
		};

		memcpy(pCur, SubHeader, 32);

		*(pCur + 12) = LOBYTE(StartOffset);
		*(pCur + 13) = HIBYTE(StartOffset);		
		*(pMainHeader + 28) = LOBYTE(pCur - nTexBuf);
		*(pMainHeader + 29) = HIBYTE(pCur - nTexBuf);
		pCur += 32;
	}
	else
	{
		BYTE SubHeader[32] = 
		{
			0x0A, 0x00, 0xC0, 0x02, 0x00, 0x01, 0x40, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
			0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00
		};

		memcpy(pCur, SubHeader, 32);

		*(pCur + 12) = LOBYTE(StartOffset);
		*(pCur + 13) = HIBYTE(StartOffset);		
		*(pMainHeader + 28)= LOBYTE(pCur - nTexBuf);
		*(pMainHeader + 29) = HIBYTE(pCur - nTexBuf);
		pCur += 32;		
	}

	// Prepare 10th block : Flag Palette Tex
	if (!GetClutBlock(m_PalFlagFile,m_IdxPalFlag,&nBlockClut))
	{
		fNewTex.Close();
		delete nTexBuf;
		delete nBlockClut;
		return FALSE;
	}

	memcpy(pCur, nBlockClut, RGB_SIZE256/2);
	StartOffset = pCur - nTexBuf;
	pCur += RGB_SIZE256/2;
	if (m_GameType == 0)
	{
		BYTE SubHeader[32] = 
		{
			0x09, 0xFF, 0x00, 0x01, 0xE0, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
			0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00
		};

		memcpy(pCur, SubHeader, 32);

		*(pCur + 12) = LOBYTE(StartOffset);
		*(pCur + 13) = HIBYTE(StartOffset);
		*(pMainHeader + 32) = LOBYTE(pCur - nTexBuf);
		*(pMainHeader + 33) = HIBYTE(pCur - nTexBuf);
		pCur += 32;
	}
	else
	{
		BYTE SubHeader[32] = 
		{
			0x09, 0xFF, 0x00, 0x01, 0xE0, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
			0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00
		};

		memcpy(pCur, SubHeader, 32);

		*(pCur + 12) = LOBYTE(StartOffset);
		*(pCur + 13) = HIBYTE(StartOffset);
		*(pMainHeader + 32) = LOBYTE(pCur - nTexBuf);
		*(pMainHeader + 33) = HIBYTE(pCur - nTexBuf);
		pCur += 32;
	}

	// Prepare 11th block : Refree Data Tex
	if (!GetImageBlock(m_TexRefreeFile,m_IdxTexRefree,&nBlockBuf,&BlockLength))
	{
		fNewTex.Close();
		delete nTexBuf;	
		delete nBlockBuf;	
		return FALSE;
	}
	memcpy(pCur, nBlockBuf, BlockLength);	
	StartOffset = pCur - nTexBuf;
	pCur+= BlockLength;
	// write header
	if (m_GameType == 0)
	{
		BYTE SubHeader[32] = 
		{
			0x0A, 0x00, 0x00, 0x03, 0x80, 0x01, 0x40, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
			0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00
		};

		memcpy(pCur, SubHeader, 32);

		*(pCur + 12) = LOBYTE(StartOffset);
		*(pCur + 13) = HIBYTE(StartOffset);		
		*(pMainHeader + 44) = LOBYTE(pCur - nTexBuf);
		*(pMainHeader + 45) = HIBYTE(pCur - nTexBuf);
		pCur += 32;
	}
	else
	{
		BYTE SubHeader[32] = 
		{
			0x0A, 0x00, 0x00, 0x03, 0x80, 0x01, 0x40, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
			0x0F, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00
		};

		memcpy(pCur, SubHeader, 32);

		*(pCur + 12) = LOBYTE(StartOffset);
		*(pCur + 13) = HIBYTE(StartOffset);		
		*(pMainHeader + 44)= LOBYTE(pCur - nTexBuf);
		*(pMainHeader + 45) = HIBYTE(pCur - nTexBuf);
		pCur += 32;		
	}

	TexLength = pCur - nTexBuf;
	fNewTex.Write(nTexBuf,TexLength);
	fNewTex.Close();
	delete nTexBuf;	
	delete nBlockBuf;
	delete nBlockClut;

	return TRUE;
}

void CWECompressorTab3::OnButtonMakeTEX() 
{
	CString TempMsg;

	UpdateData(TRUE);

	if ( !CreateTEX() )
	{
		TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_ERROR_TAB3_MAKETEX)) + "\n\n";
		MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_ERROR_MESSAGEBOX)), 		
					MB_ICONERROR);
	}
	else
	{
		TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_INFO_MAKETEX_OK)) + "\n\n";
		MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_INFO_MAKETEX_OK)), 
					MB_ICONINFORMATION);
	}

}

BOOL CWECompressorTab3::CreateAllCompleteFiles(CString NameFile,BYTE *BufImage,BYTE *BufImage2,
											   BYTE *Clut)
{
	CFile   NewFileBMP,NewFileTIM,NewFileRAW,NewFileBIN,NewFileCLUT,NewFilePAL;	
	CString TempMsg;
	CFileException e;
	UINT j,depth;
	ULONG xsize,ysize,imagesize,xtemp,BlockLen;
	BYTE rgbq[RGB_SIZE256];
	BYTE* pData;
	
	// open data file to write
	TempMsg = NameFile + ".clu";
	if (!NewFileCLUT.Open(TempMsg, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + TempMsg);
		return FALSE;
	}

	NewFileCLUT.Write(Clut,RGB_SIZE256/2);
	NewFileCLUT.Close();

	// open data file to write
	TempMsg = NameFile + ".pal";
	if (!NewFilePAL.Open(TempMsg, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + TempMsg);
		return FALSE;
	}

	// write converted CLUT RGB table (psx uses 15bit RGB)
	for (WORD col=0; col < RGB_SIZE256; col+=4)
	{				
		WORD* tempword = new WORD;
		memcpy(tempword,Clut + (col/2), 2);
		rgbq[col] = (*tempword>>10) << 3;
		rgbq[col+1] = ((*tempword>>5)&0x1f) << 3;
		rgbq[col+2] = ((*tempword)&0x1f) << 3;
		rgbq[col+3] = 0;

		delete tempword;
	}

	NewFilePAL.Write(rgbq,RGB_SIZE256);
	NewFilePAL.Close();

	// Prepare joined image
	xsize = 256;
	ysize = 128;
	depth = 8;
	imagesize = xsize*ysize;
	BYTE* FullBlock = new BYTE[imagesize];

	// copy reverse data to pData
	j=0;
	xtemp = xsize / 2;
	for(long y1=0;y1<ysize;y1++)
	{
		for(unsigned long x1=0;x1<xtemp;x1++)
		{
			FullBlock[j+xtemp] = BufImage2[(y1*xtemp)+x1];
			FullBlock[j++] = BufImage[(y1*xtemp)+x1];
		}
		j+= xtemp;
	}

	//if (!OnlyPAL)
	{
		//////////// RAW
		// open data file to write
		TempMsg = NameFile + ".raw";
		if (!NewFileRAW.Open(TempMsg, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
		{
			AfxMessageBox(_T("Error writing ") + TempMsg);
			return FALSE;
		}

		NewFileRAW.Write(FullBlock,imagesize);
		NewFileRAW.Close();

		//////////// BIN
		// open data file to write
		TempMsg = NameFile + ".bin";
		if (!NewFileBIN.Open(TempMsg, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
		{
			AfxMessageBox(_T("Error writing ") + TempMsg);
			return FALSE;
		}

		CWECompress tempclass;
		BYTE* BufCompr = new BYTE[imagesize];

		tempclass.Compress(&BufCompr,FullBlock,&BlockLen,imagesize);
		NewFileBIN.Write(BufCompr,BlockLen);
		NewFileBIN.Close();

		delete BufCompr;

		//////////// BMP
		// open data file to write
		TempMsg = NameFile + ".bmp";
		if (!NewFileBMP.Open(TempMsg, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
		{
			AfxMessageBox(_T("Error writing ") + TempMsg);
			return FALSE;
		}

		(BYTE*) pData = new BYTE[imagesize];
			
		// copy reverse data to pData
		j=0;
		xtemp = xsize;
		for(long y1=ysize-1;y1>=0;y1--){
			for(unsigned long x1=0;x1<xtemp;x1++)
				pData[j++] = FullBlock[(y1*xtemp)+x1];}

		BITMAPFILEHEADER bmfh;
		BITMAPINFOHEADER bmih;
	
		bmfh.bfType = 0x4D42;// BM
		bmfh.bfSize = TOTAL_HEADER_SIZE256 + (xsize*ysize*depth)/8;
		bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
		bmfh.bfOffBits = TOTAL_HEADER_SIZE256;

		NewFileBMP.Write(&bmfh,sizeof( BITMAPFILEHEADER ));
	
		bmih.biSize = BMIH_SIZE;
		bmih.biWidth = xsize;
		bmih.biHeight = ysize;
		bmih.biPlanes = 1;
		bmih.biBitCount = depth;
		bmih.biCompression = BI_RGB;
		bmih.biSizeImage = (xsize*ysize*depth)/8;
		bmih.biXPelsPerMeter = 0;
		bmih.biYPelsPerMeter = 0;
		bmih.biClrUsed = 256;	
		bmih.biClrImportant = 0;
	
		NewFileBMP.Write(&bmih,sizeof( BITMAPINFOHEADER ));
		
		// write converted CLUT RGB table (psx uses 15bit RGB)
		NewFileBMP.Write(rgbq,RGB_SIZE256);

		// write Data block
		NewFileBMP.Write(pData,imagesize);

		delete pData;

		NewFileBMP.Close();

		//////////// TIM
		// open data file to write
		TempMsg = NameFile + ".tim";
		if (!NewFileTIM.Open(TempMsg, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
		{
			AfxMessageBox(_T("Error writing ") + TempMsg);
			return FALSE;
		}

		TIM_HEADER THead;
		TIM_CLUTINFO TClut;
	
		// Write TIM header
		THead.id1 = TIM_ID1;
		THead.type = TIM_8Bit;

		THead.nextlen = RGB_SIZE256 / 2 + 12;
		NewFileTIM.Write(&THead,sizeof( TIM_HEADER ));

		// write Clut Header
		TClut.vramx = 0x80;
		TClut.vramy = 0x01FF;
		TClut.ncols = 256;
		TClut.npals = 1;

		NewFileTIM.Write(&TClut,sizeof( TIM_CLUTINFO ));

		// write CLUT DATA
		NewFileTIM.Write(Clut,RGB_SIZE256 / 2);

		TIM_DATAINFO TData;
		ULONG DataLength;

		// write Data Header
			
		TData.vramx = 0x240;
		TData.vramy = 0x100;
		TData.xsize = 0x80;
		TData.ysize = 0x80;
		DataLength = TData.xsize*TData.ysize*2;			
		TData.blocklen = DataLength + 12;

		NewFileTIM.Write(&TData,sizeof( TIM_DATAINFO ));

		// write Data Block
		NewFileTIM.Write(FullBlock,DataLength);

		NewFileTIM.Close();

	}

	delete FullBlock;

	return TRUE;

}

BOOL CWECompressorTab3::CreateAllFiles(CString NameFile,BYTE *BufImage,BYTE *Clut,BYTE *BufCompr,
									   UINT BlockLen)
{
	CFile   NewFileBMP,NewFileTIM,NewFileRAW,NewFileBIN,NewFileCLUT,NewFilePAL;	
	CString TempMsg;
	CFileException e;
	UINT j,depth;
	ULONG xsize,ysize,imagesize,xtemp;
	BYTE rgbq[RGB_SIZE256];
	BYTE* pData;
	
	// open data file to write
	TempMsg = NameFile + ".clu";
	if (!NewFileCLUT.Open(TempMsg, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + TempMsg);
		return FALSE;
	}

	NewFileCLUT.Write(Clut,RGB_SIZE256/2);
	NewFileCLUT.Close();

	// open data file to write
	TempMsg = NameFile + ".pal";
	if (!NewFilePAL.Open(TempMsg, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + TempMsg);
		return FALSE;
	}

	// write converted CLUT RGB table (psx uses 15bit RGB)
	for (WORD col=0; col < RGB_SIZE256; col+=4)
	{				
		WORD* tempword = new WORD;
		memcpy(tempword,Clut + (col/2), 2);
		rgbq[col] = (*tempword>>10) << 3;
		rgbq[col+1] = ((*tempword>>5)&0x1f) << 3;
		rgbq[col+2] = ((*tempword)&0x1f) << 3;
		rgbq[col+3] = 0;

		delete tempword;
	}

	NewFilePAL.Write(rgbq,RGB_SIZE256);
	NewFilePAL.Close();

	//if (!OnlyPAL)
	{
		//////////// RAW
		// open data file to write
		TempMsg = NameFile + ".raw";
		if (!NewFileRAW.Open(TempMsg, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
		{
			AfxMessageBox(_T("Error writing ") + TempMsg);
			return FALSE;
		}

		NewFileRAW.Write(BufImage,128*128);
		NewFileRAW.Close();

		//////////// BIN
		// open data file to write
		TempMsg = NameFile + ".bin";
		if (!NewFileBIN.Open(TempMsg, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
		{
			AfxMessageBox(_T("Error writing ") + TempMsg);
			return FALSE;
		}

		NewFileBIN.Write(BufCompr,BlockLen);
		NewFileBIN.Close();

		//////////// BMP
		// open data file to write
		TempMsg = NameFile + ".bmp";
		if (!NewFileBMP.Open(TempMsg, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
		{
			AfxMessageBox(_T("Error writing ") + TempMsg);
			return FALSE;
		}

		xsize = 128;
		ysize = 128;
		depth = 8;
		imagesize = xsize*ysize;

		(BYTE*) pData = new BYTE[imagesize];
			
		// copy reverse data to pData
		j=0;
		xtemp = xsize;
		for(long y1=ysize-1;y1>=0;y1--){
			for(unsigned long x1=0;x1<xtemp;x1++)
				pData[j++] = BufImage[(y1*xtemp)+x1];}

		BITMAPFILEHEADER bmfh;
		BITMAPINFOHEADER bmih;
	
		bmfh.bfType = 0x4D42;// BM
		bmfh.bfSize = TOTAL_HEADER_SIZE256 + (xsize*ysize*depth)/8;
		bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
		bmfh.bfOffBits = TOTAL_HEADER_SIZE256;

		NewFileBMP.Write(&bmfh,sizeof( BITMAPFILEHEADER ));
	
		bmih.biSize = BMIH_SIZE;
		bmih.biWidth = xsize;
		bmih.biHeight = ysize;
		bmih.biPlanes = 1;
		bmih.biBitCount = depth;
		bmih.biCompression = BI_RGB;
		bmih.biSizeImage = (xsize*ysize*depth)/8;
		bmih.biXPelsPerMeter = 0;
		bmih.biYPelsPerMeter = 0;
		bmih.biClrUsed = 256;	
		bmih.biClrImportant = 0;
	
		NewFileBMP.Write(&bmih,sizeof( BITMAPINFOHEADER ));
		
		// write converted CLUT RGB table (psx uses 15bit RGB)
		NewFileBMP.Write(rgbq,RGB_SIZE256);

		// write Data block
		NewFileBMP.Write(pData,imagesize);

		delete pData;

		NewFileBMP.Close();

		//////////// TIM
		// open data file to write
		TempMsg = NameFile + ".tim";
		if (!NewFileTIM.Open(TempMsg, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
		{
			AfxMessageBox(_T("Error writing ") + TempMsg);
			return FALSE;
		}

		TIM_HEADER THead;
		TIM_CLUTINFO TClut;
	
		// Write TIM header
		THead.id1 = TIM_ID1;
		THead.type = TIM_8Bit;

		THead.nextlen = RGB_SIZE256 / 2 + 12;
		NewFileTIM.Write(&THead,sizeof( TIM_HEADER ));

		// write Clut Header
		TClut.vramx = 0x80;
		TClut.vramy = 0x01FF;
		TClut.ncols = 256;
		TClut.npals = 1;

		NewFileTIM.Write(&TClut,sizeof( TIM_CLUTINFO ));

		// write CLUT DATA
		NewFileTIM.Write(Clut,RGB_SIZE256 / 2);

		TIM_DATAINFO TData;
		ULONG DataLength;

		// write Data Header
			
		TData.vramx = 0x240;
		TData.vramy = 0x100;
		TData.xsize = 0x40;
		TData.ysize = 0x80;
		DataLength = TData.xsize*TData.ysize*2;			
		TData.blocklen = DataLength + 12;

		NewFileTIM.Write(&TData,sizeof( TIM_DATAINFO ));

		// write Data Block
		NewFileTIM.Write(BufImage,DataLength);

		NewFileTIM.Close();

	}

	return TRUE;

}

BOOL CWECompressorTab3::ExtractAllFiles(CString TexFile,CString DirPath)
{
	CFile	fShirtTex;
	CString TempMsg;
	CFileException e;
	UINT nSize;
	const INT32 MaxTexLen = 65535;
	const INT32 MaxTexSize = 128*128;
	DATA_HEADER	HeaderImage,HeaderImage2,HeaderPAL;
	WORD OffsetHeaderIm,OffsetHeaderIm2,OffsetHeaderPAL;
	
	_mkdir(DirPath); // make dir

	// open data tex file to read
	if (!fShirtTex.Open(TexFile, CFile::modeRead | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error reading ") + TexFile);
		return FALSE;
	}

	nSize = fShirtTex.GetLength();

	BYTE* rbuf = new BYTE[nSize];
	fShirtTex.Read(rbuf, nSize);
	fShirtTex.Close(); 

	BYTE *pCur = rbuf;
	BYTE *pMainHeader = rbuf;
	BYTE* tempblock = new BYTE[MaxTexSize*2];
	BYTE* pDataRev = new BYTE[MaxTexSize];
	BYTE* ClutBlock = new BYTE[RGB_SIZE256/2];
	CWECompress tempclass;

	if (!m_LargeTex)
	{
		// Pl/GK shirt 1st
	
		OffsetHeaderIm = (*pCur) + (*(pCur + 1) << 8);
		OffsetHeaderPAL = (*(pCur + 4)) + (*(pCur + 5) << 8);
		memcpy(&HeaderImage,pCur + OffsetHeaderIm,sizeof(DATA_HEADER));
		memcpy(&HeaderPAL,pCur + OffsetHeaderPAL,sizeof(DATA_HEADER));
		
		ZeroMemory(tempblock,MaxTexSize*2);
		ZeroMemory(pDataRev,MaxTexSize);
		ZeroMemory(ClutBlock,RGB_SIZE256/2);
		memcpy(tempblock,pCur + HeaderImage.offset, MaxTexSize*2);
		memcpy(ClutBlock,pCur + HeaderPAL.offset, RGB_SIZE256/2);
		tempclass.DeCompress(&pDataRev,tempblock);
	
		CreateAllFiles(DirPath + "\\Player1st",pDataRev,ClutBlock,tempblock,
						tempclass.FindCompressedLength(tempblock));

		// GK shirt/PAL 1st
		OffsetHeaderPAL = (*(pCur + 16)) + (*(pCur + 17) << 8);
		memcpy(&HeaderPAL,pCur + OffsetHeaderPAL,sizeof(DATA_HEADER));
		ZeroMemory(ClutBlock,RGB_SIZE256/2);
		memcpy(ClutBlock,pCur + HeaderPAL.offset, RGB_SIZE256/2);

		CreateAllFiles(DirPath + "\\GoalKeeper1st",pDataRev,ClutBlock,tempblock,
						tempclass.FindCompressedLength(tempblock));

		// Pl/GK shirt 2nd
		OffsetHeaderIm = (*(pCur + 8)) + (*(pCur + 9) << 8);
		OffsetHeaderPAL = (*(pCur + 12)) + (*(pCur + 13) << 8);
		memcpy(&HeaderImage,pCur + OffsetHeaderIm,sizeof(DATA_HEADER));
		memcpy(&HeaderPAL,pCur + OffsetHeaderPAL,sizeof(DATA_HEADER));
		ZeroMemory(tempblock,MaxTexSize*2);
		ZeroMemory(pDataRev,MaxTexSize);
		ZeroMemory(ClutBlock,RGB_SIZE256/2);
		memcpy(tempblock,pCur + HeaderImage.offset, MaxTexSize*2);
		memcpy(ClutBlock,pCur + HeaderPAL.offset, RGB_SIZE256/2);
		tempclass.DeCompress(&pDataRev,tempblock);

		CreateAllFiles(DirPath + "\\Player2nd",pDataRev,ClutBlock,tempblock,
						tempclass.FindCompressedLength(tempblock));

		// GK shirt/PAL 2nd
		OffsetHeaderPAL = (*(pCur + 20)) + (*(pCur + 21) << 8);
		memcpy(&HeaderPAL,pCur + OffsetHeaderPAL,sizeof(DATA_HEADER));
		ZeroMemory(ClutBlock,RGB_SIZE256/2);
		memcpy(ClutBlock,pCur + HeaderPAL.offset, RGB_SIZE256/2);

		CreateAllFiles(DirPath + "\\GoalKeeper2nd",pDataRev,ClutBlock,tempblock,
						tempclass.FindCompressedLength(tempblock));

		// Pl/GK long shirt 1st
		OffsetHeaderIm = (*(pCur + 36)) + (*(pCur + 37) << 8);
		OffsetHeaderPAL = (*(pCur + 4)) + (*(pCur + 5) << 8);
		memcpy(&HeaderImage,pCur + OffsetHeaderIm,sizeof(DATA_HEADER));
		memcpy(&HeaderPAL,pCur + OffsetHeaderPAL,sizeof(DATA_HEADER));
		
		ZeroMemory(tempblock,MaxTexSize*2);
		ZeroMemory(pDataRev,MaxTexSize);
		ZeroMemory(ClutBlock,RGB_SIZE256/2);
		memcpy(tempblock,pCur + HeaderImage.offset, MaxTexSize*2);
		memcpy(ClutBlock,pCur + HeaderPAL.offset, RGB_SIZE256/2);
		tempclass.DeCompress(&pDataRev,tempblock);
	
		CreateAllFiles(DirPath + "\\PlayerGKLong1st",pDataRev,ClutBlock,tempblock,
						tempclass.FindCompressedLength(tempblock));
		
		// Pl/GK long shirt 2nd
	
		OffsetHeaderIm = (*(pCur + 40)) + (*(pCur + 41) << 8);
		OffsetHeaderPAL = (*(pCur + 12)) + (*(pCur + 13) << 8);
		memcpy(&HeaderImage,pCur + OffsetHeaderIm,sizeof(DATA_HEADER));
		memcpy(&HeaderPAL,pCur + OffsetHeaderPAL,sizeof(DATA_HEADER));
	
		ZeroMemory(tempblock,MaxTexSize*2);
		ZeroMemory(pDataRev,MaxTexSize);
		ZeroMemory(ClutBlock,RGB_SIZE256/2);
		memcpy(tempblock,pCur + HeaderImage.offset, MaxTexSize*2);
		memcpy(ClutBlock,pCur + HeaderPAL.offset, RGB_SIZE256/2);
		tempclass.DeCompress(&pDataRev,tempblock);
	
		CreateAllFiles(DirPath + "\\PlayerGKLong2nd",pDataRev,ClutBlock,tempblock,
						tempclass.FindCompressedLength(tempblock));

	}
	else
	{
		// Pl/GK Complete shirt 1st

		BYTE* tempblock2 = new BYTE[MaxTexSize*2];
		BYTE* pDataRev2 = new BYTE[MaxTexSize];

		OffsetHeaderIm = (*pCur) + (*(pCur + 1) << 8);
		OffsetHeaderIm2 = (*(pCur + 36)) + (*(pCur + 37) << 8);
		OffsetHeaderPAL = (*(pCur + 4)) + (*(pCur + 5) << 8);
		memcpy(&HeaderImage,pCur + OffsetHeaderIm,sizeof(DATA_HEADER));
		memcpy(&HeaderImage2,pCur + OffsetHeaderIm2,sizeof(DATA_HEADER));
		memcpy(&HeaderPAL,pCur + OffsetHeaderPAL,sizeof(DATA_HEADER));
		
		ZeroMemory(tempblock,MaxTexSize*2);
		ZeroMemory(tempblock2,MaxTexSize*2);
		ZeroMemory(pDataRev,MaxTexSize);
		ZeroMemory(pDataRev2,MaxTexSize);
		ZeroMemory(ClutBlock,RGB_SIZE256/2);
		memcpy(tempblock,pCur + HeaderImage.offset, MaxTexSize*2);
		memcpy(tempblock2,pCur + HeaderImage2.offset, MaxTexSize*2);
		memcpy(ClutBlock,pCur + HeaderPAL.offset, RGB_SIZE256/2);
		tempclass.DeCompress(&pDataRev,tempblock);
		tempclass.DeCompress(&pDataRev2,tempblock2);
	
		CreateAllCompleteFiles(DirPath + "\\PlayerFull1st",pDataRev,pDataRev2,ClutBlock);

		// GK Complete shirt/PAL 1st
		OffsetHeaderPAL = (*(pCur + 16)) + (*(pCur + 17) << 8);
		memcpy(&HeaderPAL,pCur + OffsetHeaderPAL,sizeof(DATA_HEADER));
		ZeroMemory(ClutBlock,RGB_SIZE256/2);
		memcpy(ClutBlock,pCur + HeaderPAL.offset, RGB_SIZE256/2);

		CreateAllCompleteFiles(DirPath + "\\GoalKeeperFull1st",pDataRev,pDataRev2,ClutBlock);

		// Pl/GK Complete shirt 2nd

		OffsetHeaderIm = (*(pCur + 8)) + (*(pCur + 9) << 8);
		OffsetHeaderIm2 = (*(pCur + 40)) + (*(pCur + 41) << 8);
		OffsetHeaderPAL = (*(pCur + 12)) + (*(pCur + 13) << 8);
		memcpy(&HeaderImage,pCur + OffsetHeaderIm,sizeof(DATA_HEADER));
		memcpy(&HeaderImage2,pCur + OffsetHeaderIm2,sizeof(DATA_HEADER));
		memcpy(&HeaderPAL,pCur + OffsetHeaderPAL,sizeof(DATA_HEADER));
		
		ZeroMemory(tempblock,MaxTexSize*2);
		ZeroMemory(tempblock2,MaxTexSize*2);
		ZeroMemory(pDataRev,MaxTexSize);
		ZeroMemory(pDataRev2,MaxTexSize);
		ZeroMemory(ClutBlock,RGB_SIZE256/2);
		memcpy(tempblock,pCur + HeaderImage.offset, MaxTexSize*2);
		memcpy(tempblock2,pCur + HeaderImage2.offset, MaxTexSize*2);
		memcpy(ClutBlock,pCur + HeaderPAL.offset, RGB_SIZE256/2);
		tempclass.DeCompress(&pDataRev,tempblock);
		tempclass.DeCompress(&pDataRev2,tempblock2);
	
		CreateAllCompleteFiles(DirPath + "\\PlayerFull2nd",pDataRev,pDataRev2,ClutBlock);

		// GK Complete shirt/PAL 2nd
		OffsetHeaderPAL = (*(pCur + 20)) + (*(pCur + 21) << 8);
		memcpy(&HeaderPAL,pCur + OffsetHeaderPAL,sizeof(DATA_HEADER));
		ZeroMemory(ClutBlock,RGB_SIZE256/2);
		memcpy(ClutBlock,pCur + HeaderPAL.offset, RGB_SIZE256/2);

		CreateAllCompleteFiles(DirPath + "\\GoalKeeperFull2nd",pDataRev,pDataRev2,ClutBlock);
		
		delete tempblock2;
		delete pDataRev2; 
	}

	// Flag Texture
	
	OffsetHeaderIm = (*(pCur + 28)) + (*(pCur + 29) << 8);
	OffsetHeaderPAL = (*(pCur + 32)) + (*(pCur + 33) << 8);
	memcpy(&HeaderImage,pCur + OffsetHeaderIm,sizeof(DATA_HEADER));
	memcpy(&HeaderPAL,pCur + OffsetHeaderPAL,sizeof(DATA_HEADER));
	
	ZeroMemory(tempblock,MaxTexSize*2);
	ZeroMemory(pDataRev,MaxTexSize);
	ZeroMemory(ClutBlock,RGB_SIZE256/2);
	memcpy(tempblock,pCur + HeaderImage.offset, MaxTexSize*2);
	memcpy(ClutBlock,pCur + HeaderPAL.offset, RGB_SIZE256/2);
	tempclass.DeCompress(&pDataRev,tempblock);
	
	CreateAllFiles(DirPath + "\\Flag",pDataRev,ClutBlock,tempblock,
					tempclass.FindCompressedLength(tempblock));

	// Refree Texture
	
	OffsetHeaderIm = (*(pCur + 44)) + (*(pCur + 45) << 8);
	OffsetHeaderPAL = (*(pCur + 4)) + (*(pCur + 5) << 8);
	memcpy(&HeaderImage,pCur + OffsetHeaderIm,sizeof(DATA_HEADER));
	memcpy(&HeaderPAL,pCur + OffsetHeaderPAL,sizeof(DATA_HEADER));
	
	ZeroMemory(tempblock,MaxTexSize*2);
	ZeroMemory(pDataRev,MaxTexSize);
	ZeroMemory(ClutBlock,RGB_SIZE256/2);
	memcpy(tempblock,pCur + HeaderImage.offset, MaxTexSize*2);
	memcpy(ClutBlock,pCur + HeaderPAL.offset, RGB_SIZE256/2);
	tempclass.DeCompress(&pDataRev,tempblock);
	
	CreateAllFiles(DirPath + "\\Referee",pDataRev,ClutBlock,tempblock,
					tempclass.FindCompressedLength(tempblock));


	delete tempblock;
	delete pDataRev;
	delete ClutBlock;
	delete rbuf;

	return TRUE;		
		
}

void CWECompressorTab3::OnButtonExtractTEX() 
{
	CString	Temp,TempMsg,TexFile;	
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char dirpath[_MAX_PATH];
	int	Res;
			
	Temp.LoadString(IDS_FILTER_TEX);
	CFileDialog MyFdlg(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_EXPLORER 
		| OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST ,(LPCTSTR) Temp, NULL);
	
	Temp.LoadString(IDS_INFO_TAB3_OPENTEX);
	MyFdlg.m_ofn.lpstrTitle = (LPCTSTR) Temp;
	
	//MyFdlg.m_ofn.lpstrInitialDir = m_nSelectedPath;

	// Invoke the dialog box
	UpdateData(TRUE);
	Res = MyFdlg.DoModal();
	if (Res == IDOK)
	{	
		TexFile = MyFdlg.GetPathName();

		_splitpath((const char *) TexFile, drive, dir, fname, NULL);
		strcpy(dirpath, drive);
		strcat(dirpath, dir);
		strcat(dirpath, fname);
		
		TempMsg.Format("%s\n\n%s\n\n",CString(MAKEINTRESOURCE(IDS_INFO_CREATEDIR)),dirpath);
		Res = AfxMessageBox(TempMsg, MB_YESNO | MB_ICONQUESTION);	
		if (Res == IDYES)
		{
			if ( !ExtractAllFiles(TexFile,dirpath) )
			{
				TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_ERROR_TAB3_EXTRACTTEX)) + "\n\n";
				MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_ERROR_MESSAGEBOX)), 		
						MB_ICONERROR);
			}
			else
			{
				TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_INFO_EXTRACTTEX_OK)) + "\n\n";
				MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_INFO_EXTRACTTEX_OK)), 
							MB_ICONINFORMATION);
			}

		}
	}
	
}


void CWECompressorTab3::OnBrowseNewTex() 
{
	CString	Temp;
	int		Res;	
	
	UpdateData(TRUE);
	Temp = CString(MAKEINTRESOURCE(IDS_FILTER_TEX));
	CFileDialog MyFdlg(FALSE, "bin" , "Custom", OFN_HIDEREADONLY | OFN_EXPLORER | 
						OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST , (LPCTSTR) Temp, NULL);
	
	Temp = CString(MAKEINTRESOURCE(IDS_INFO_TAB3_NEWTEX));
	MyFdlg.m_ofn.lpstrTitle = (LPCTSTR) Temp;
	
	// Invoke the dialog box
	Res = MyFdlg.DoModal();
	if (Res == IDOK)
	{	
		m_NewTexFile = MyFdlg.GetPathName();
		GetDlgItem(IDC_FILE_NEWTEX)->EnableWindow(TRUE);		
		m_FlagOK[0] = TRUE;
		CheckValidity();
		UpdateMyData(FALSE);
		if (m_ctlTT.IsExistTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_NEWTEX))))
			m_ctlTT.RemoveTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_NEWTEX)));			
		m_ctlTT.AddTool(GetDlgItem (IDC_FILE_NEWTEX), m_NewTexFile);
				
	}
	
}

int CWECompressorTab3::BrowseFileTex(WORD Title,CString *NameFile,int IDCtrl,int Num,int IdxCtrl) 
{
	CString		Temp;	
	int			Res;

	if ((Num== 1) || (Num== 4) || (Num== 5) || (Num== 7) || (Num== 10) || (Num== 11))
	{
		if (IdxCtrl == 0)
			Temp = CString(MAKEINTRESOURCE(IDS_FILTER_BMP));
		else
		if (IdxCtrl == 1)
			Temp = CString(MAKEINTRESOURCE(IDS_FILTER_TIM));
		else
		if (IdxCtrl == 2)
			Temp = CString(MAKEINTRESOURCE(IDS_FILTER_BINCOMPR));
		else
			Temp = CString(MAKEINTRESOURCE(IDS_FILTER_RAW));
			
	}
	else
	{
		if (IdxCtrl == 0)
			Temp = CString(MAKEINTRESOURCE(IDS_FILTER_CLU));
		else
		if (IdxCtrl == 1)
			Temp = CString(MAKEINTRESOURCE(IDS_FILTER_PAL));
		else
		if (IdxCtrl == 2)
			Temp = CString(MAKEINTRESOURCE(IDS_FILTER_BMP));
		else
			Temp = CString(MAKEINTRESOURCE(IDS_FILTER_TIM));
	}
	
	CFileDialog MyFdlg(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_EXPLORER 
		| OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST ,(LPCTSTR) Temp, NULL);
	
	Temp = CString(MAKEINTRESOURCE(Title));
	MyFdlg.m_ofn.lpstrTitle = (LPCTSTR) Temp;
	
	// Invoke the dialog box
	Res = MyFdlg.DoModal();
	if (Res == IDOK)
	{	
		*NameFile = MyFdlg.GetPathName();
		GetDlgItem(IDCtrl)->EnableWindow(TRUE);
		m_FlagOK[Num] = TRUE;
		
		CheckValidity();
		UpdateMyData(FALSE);
		if (m_ctlTT.IsExistTool(m_ctlTT.FindTool(GetDlgItem(IDCtrl))))
				m_ctlTT.RemoveTool(m_ctlTT.FindTool(GetDlgItem(IDCtrl)));
		m_ctlTT.AddTool(GetDlgItem (IDCtrl), *NameFile);	
					
	}

	return Res;
	
}

void CWECompressorTab3::OnBrowseTexGioc1() 
{
	int Res;

	UpdateData(TRUE);
	Res = BrowseFileTex(IDS_INFO_TAB3_OPENTEXGIOC1,&m_TexFileGioc1,IDC_FILE_TEXGIOC1,1,m_IdxTexGio1);
	if (Res == IDOK)
	{
		OnChangeComboSelTexGio1();
		if (m_FlagOK[2] || m_FlagOK[3])
			GetDlgItem(IDC_VIEWBUTTON2)->EnableWindow(TRUE);

	}

}

void CWECompressorTab3::OnBrowseTexGioc2() 
{
	int Res;

	UpdateData(TRUE);
	Res = BrowseFileTex(IDS_INFO_TAB3_OPENTEXGIOC2,&m_TexFileGioc2,IDC_FILE_TEXGIOC2,7,m_IdxTexGio2);
	if (Res == IDOK)
	{
		OnChangeComboSelTexGio2();
		if (m_FlagOK[8] || m_FlagOK[9])
			GetDlgItem(IDC_VIEWBUTTON8)->EnableWindow(TRUE);

	}		
	
}

void CWECompressorTab3::OnBrowseTexMan1() 
{
	int Res;

	UpdateData(TRUE);
	Res = BrowseFileTex(IDS_INFO_TAB3_OPENTEXMAN1,&m_TexFileManLun1,IDC_FILE_TEXMANLUN1,4,m_IdxTexMan1);
	if (Res == IDOK)
	{
		OnChangeComboSelTexMan1();
		if (m_FlagOK[2] || m_FlagOK[3])
			GetDlgItem(IDC_VIEWBUTTON5)->EnableWindow(TRUE);

	}
	
}

void CWECompressorTab3::OnBrowseTexMan2() 
{
	int Res;

	UpdateData(TRUE);
	Res = BrowseFileTex(IDS_INFO_TAB3_OPENTEXMAN2,&m_TexFileManLun2,IDC_FILE_TEXMANLUN2,10,m_IdxTexMan1);
	if (Res == IDOK)
	{
		OnChangeComboSelTexMan2();
		if (m_FlagOK[8] || m_FlagOK[9])
			GetDlgItem(IDC_VIEWBUTTON11)->EnableWindow(TRUE);

	}
	
}

void CWECompressorTab3::OnBrowseTexFlag() 
{
	int Res;

	UpdateData(TRUE);
	Res = BrowseFileTex(IDS_INFO_TAB3_OPENFLAG,&m_TexFlagFile,IDC_FILE_TEXFLAG,5,m_IdxTexTifo);
	if (Res == IDOK)
	{
		OnChangeComboSelAutoFlag();
		if (m_FlagOK[6])
		GetDlgItem(IDC_VIEWBUTTON6)->EnableWindow(TRUE);
	}
	
}

void CWECompressorTab3::OnBrowseTexRefree() 
{
	int Res;

	UpdateData(TRUE);
	Res = BrowseFileTex(IDS_INFO_TAB3_OPENREFREE,&m_TexRefreeFile,IDC_FILE_TEXREFREE,11,m_IdxTexRefree);
	if ((Res == IDOK) && (m_IdxTexRefree < 2))
		GetDlgItem(IDC_VIEWBUTTON12)->EnableWindow(TRUE);
	
}

void CWECompressorTab3::OnBrowsePalGioc1() 
{
	int Res;

	UpdateData(TRUE);
	Res = BrowseFileTex(IDS_INFO_TAB3_OPENPALGIOC1,&m_PalFileGioc1,IDC_FILE_PALGIOC1,2,m_IdxPalGioc1);
	//if ((Res == IDOK) && (m_IdxPalGioc1 < 2))
	//	GetDlgItem(IDC_VIEWBUTTON6)->EnableWindow(TRUE);
	
}

void CWECompressorTab3::OnBrowsePalGioc2() 
{
	int Res;

	UpdateData(TRUE);
	Res = BrowseFileTex(IDS_INFO_TAB3_OPENPALGIOC2,&m_PalFileGioc2,IDC_FILE_PALGIOC2,8,m_IdxPalGioc2);
	//if ((Res == IDOK) && (m_IdxPalGioc2 < 2))
	//	GetDlgItem(IDC_VIEWBUTTON6)->EnableWindow(TRUE);
	
}

void CWECompressorTab3::OnBrowsePalPort1() 
{
	int Res;

	UpdateData(TRUE);
	Res = BrowseFileTex(IDS_INFO_TAB3_OPENPALPORT1,&m_PalFilePort1,IDC_FILE_PALPORT1,3,m_IdxPalPort1);
	//if ((Res == IDOK) && (m_IdxPalPort1 < 2))
	//	GetDlgItem(IDC_VIEWBUTTON6)->EnableWindow(TRUE);
	
}

void CWECompressorTab3::OnBrowsePalPort2() 
{
	int Res;

	UpdateData(TRUE);
	Res = BrowseFileTex(IDS_INFO_TAB3_OPENPALPORT2,&m_PalFilePort2,IDC_FILE_PALPORT2,9,m_IdxPalPort2);
	//if ((Res == IDOK) && (m_IdxPalPort2 < 2))
	//	GetDlgItem(IDC_VIEWBUTTON6)->EnableWindow(TRUE);
	
}

void CWECompressorTab3::OnBrowsePalFlag() 
{
	int Res;

	UpdateData(TRUE);
	Res = BrowseFileTex(IDS_INFO_TAB3_OPENFLAGPAL,&m_PalFlagFile,IDC_FILE_PALFLAG,6,m_IdxPalFlag);
	//if ((Res == IDOK) && (m_IdxPalFlag < 2))
	//	GetDlgItem(IDC_VIEWBUTTON6)->EnableWindow(TRUE);
	
}

void CWECompressorTab3::OnViewTexGioc1() 
{
	UpdateData(TRUE);
	if (m_IdxAutoGio1 == 2)
		ViewImage(m_TexFileGioc1,m_PalFilePort1,m_IdxTexGio1,m_IdxPalPort1);
	else
		ViewImage(m_TexFileGioc1,m_PalFileGioc1,m_IdxTexGio1,m_IdxPalGioc1);
}

void CWECompressorTab3::OnViewTexGioc2() 
{
	UpdateData(TRUE);
	if (m_IdxAutoGio2 == 2)
		ViewImage(m_TexFileGioc2,m_PalFilePort2,m_IdxTexGio2,m_IdxPalPort2);
	else
		ViewImage(m_TexFileGioc2,m_TexFileGioc2,m_IdxTexGio2,m_IdxPalGioc2);
}

void CWECompressorTab3::OnViewTexMan1() 
{
	UpdateData(TRUE);
	if (m_IdxAutoMan1 == 2)
		ViewImage(m_TexFileManLun1,m_PalFilePort1,m_IdxTexMan1,m_IdxPalPort1);
	else		
		ViewImage(m_TexFileManLun1,m_PalFileGioc1,m_IdxTexMan1,m_IdxPalGioc1);
}

void CWECompressorTab3::OnViewTexMan2() 
{
	UpdateData(TRUE);
	if (m_IdxAutoMan2 == 2)
		ViewImage(m_TexFileManLun2,m_PalFilePort2,m_IdxTexMan2,m_IdxPalPort2);
	else		
		ViewImage(m_TexFileManLun2,m_PalFileGioc2,m_IdxTexMan2,m_IdxPalGioc2);	
	
}

void CWECompressorTab3::OnViewTexFlag() 
{
	UpdateData(TRUE);
	ViewImage(m_TexFlagFile,m_PalFlagFile,m_IdxTexTifo,m_IdxPalFlag);
	
}

void CWECompressorTab3::OnViewTexRefree() 
{
	UpdateData(TRUE);
	if (m_IdxTexRefree < 2)
		ViewImage(m_TexRefreeFile,m_TexRefreeFile,m_IdxTexRefree,m_IdxTexRefree+2);
	
}

void CWECompressorTab3::OnChangeComboSelTexFlag() 
{
	OnChangeComboSelAutoFlag();
	
}


void CWECompressorTab3::OnChangeComboSelAutoFlag() 
{
	UpdateData(TRUE);
	if (m_IdxAutoFlag == 0)
	{		
		GetDlgItem(IDC_COMBO_SELPALFLAG)->EnableWindow(TRUE);
		GetDlgItem(IDC_SELBUTTON7)->EnableWindow(TRUE);		
				
	}
	else
	{		
		GetDlgItem(IDC_COMBO_SELPALFLAG)->EnableWindow(FALSE);
		GetDlgItem(IDC_SELBUTTON7)->EnableWindow(FALSE);

		if (m_IdxTexTifo > 1)
		{
			GetDlgItem(IDC_COMBO_SELPALFLAG)->EnableWindow(TRUE);
			GetDlgItem(IDC_SELBUTTON7)->EnableWindow(TRUE);
		}
	
		if ((m_IdxTexTifo < 2) &&  (m_FlagOK[5]))
		{
			m_FlagOK[6] = TRUE;
			CheckValidity();
			GetDlgItem(IDC_FILE_PALFLAG)->EnableWindow(TRUE);
			m_PalFlagFile = m_TexFlagFile;
			m_IdxPalFlag = m_IdxTexTifo + 2;
			UpdateMyData(FALSE);
			GetDlgItem(IDC_FILE_PALFLAG)->EnableWindow(FALSE);
		}

	}
	
}

void CWECompressorTab3::OnChangeComboSel(int IdxAutoActual,int *IdxAutoOther,int IdxTexActual,
										 BOOL FlagCurrent,BOOL *FlagNewGioc,BOOL *FlagNewPort,
										 int ComboSelPalGioc,int SelButtonPG,int ComboSelPalPort,
										 int SelButtonPP,int FilePalGioc,int FilePalPort,
										 CString TexFileActual,CString *PalFileGioc,
										 int *IdxPalGioc,CString *PalFilePort,int *IdxPalPort)
{
	if  (IdxAutoActual > 0)
	{
		if (IdxAutoActual == *IdxAutoOther)
		{
			*IdxAutoOther = 0;
			UpdateData(FALSE);
		}

		if (IdxTexActual > 1)
		{	
			if (IdxAutoActual == 1)
			{
				GetDlgItem(ComboSelPalGioc)->EnableWindow(TRUE);
				GetDlgItem(SelButtonPG)->EnableWindow(TRUE);
			}
			else
			{
				GetDlgItem(ComboSelPalPort)->EnableWindow(TRUE);
				GetDlgItem(SelButtonPP)->EnableWindow(TRUE);
			}
		}
		else
		{		
			if (IdxAutoActual == 1)
			{
				GetDlgItem(ComboSelPalGioc)->EnableWindow(FALSE);
				GetDlgItem(SelButtonPG)->EnableWindow(FALSE);
				if (*IdxAutoOther == 0)
				{
					GetDlgItem(ComboSelPalPort)->EnableWindow(TRUE);
					GetDlgItem(SelButtonPP)->EnableWindow(TRUE);
					if (*FlagNewPort)
						GetDlgItem(FilePalPort)->EnableWindow(TRUE);
				}

				if (FlagCurrent)
				{
					*FlagNewGioc = TRUE;
					CheckValidity();
					GetDlgItem(FilePalGioc)->EnableWindow(TRUE);
					*PalFileGioc = TexFileActual;
					*IdxPalGioc = IdxTexActual + 2;
					UpdateMyData(FALSE);
					GetDlgItem(FilePalGioc)->EnableWindow(FALSE);
				}
			}
			else
			if (IdxAutoActual == 2)
			{
				if (*IdxAutoOther == 0)
				{
					GetDlgItem(ComboSelPalGioc)->EnableWindow(TRUE);
					GetDlgItem(SelButtonPG)->EnableWindow(TRUE);
					if (*FlagNewGioc)
						GetDlgItem(FilePalGioc)->EnableWindow(TRUE);
				}
				
				GetDlgItem(ComboSelPalPort)->EnableWindow(FALSE);
				GetDlgItem(SelButtonPP)->EnableWindow(FALSE);				

				if (FlagCurrent)
				{
					*FlagNewPort = TRUE;
					CheckValidity();
					GetDlgItem(FilePalPort)->EnableWindow(TRUE);
					*PalFilePort = TexFileActual;
					*IdxPalPort = IdxTexActual + 2;
					UpdateMyData(FALSE);
					GetDlgItem(FilePalPort)->EnableWindow(FALSE);
				}
			}
					
		}		
	}
	else
	{
		if (*IdxAutoOther != 1)
		{
			GetDlgItem(ComboSelPalGioc)->EnableWindow(TRUE);
			GetDlgItem(SelButtonPG)->EnableWindow(TRUE);
			if (*FlagNewGioc)
				GetDlgItem(FilePalGioc)->EnableWindow(TRUE);
		}

		if (*IdxAutoOther != 2)
		{
			GetDlgItem(ComboSelPalPort)->EnableWindow(TRUE);
			GetDlgItem(SelButtonPP)->EnableWindow(TRUE);
			if (*FlagNewPort)
				GetDlgItem(FilePalPort)->EnableWindow(TRUE);
		}
		
	}
	
}

void CWECompressorTab3::OnChangeComboSelTexGio1() 
{
	UpdateData(TRUE);
	OnChangeComboSel(m_IdxAutoGio1,&m_IdxAutoMan1,m_IdxTexGio1,m_FlagOK[1],&m_FlagOK[2],
					 &m_FlagOK[3],IDC_COMBO_SELPALGIOC1,IDC_SELBUTTON3,IDC_COMBO_SELPALPORT1,
					 IDC_SELBUTTON4B,IDC_FILE_PALGIOC1,IDC_FILE_PALPORT1,m_TexFileGioc1,
					 &m_PalFileGioc1,&m_IdxPalGioc1,&m_PalFilePort1,&m_IdxPalPort1);

}

void CWECompressorTab3::OnChangeComboSelTexGio2() 
{
	UpdateData(TRUE);
	OnChangeComboSel(m_IdxAutoGio2,&m_IdxAutoMan2,m_IdxTexGio2,m_FlagOK[7],&m_FlagOK[8],
					 &m_FlagOK[9],IDC_COMBO_SELPALGIOC2,IDC_SELBUTTON9,IDC_COMBO_SELPALPORT2,
					 IDC_SELBUTTON10,IDC_FILE_PALGIOC2,IDC_FILE_PALPORT2,m_TexFileGioc2,
					 &m_PalFileGioc2,&m_IdxPalGioc2,&m_PalFilePort2,&m_IdxPalPort2);
}

void CWECompressorTab3::OnChangeComboSelTexMan1() 
{
	UpdateData(TRUE);
	OnChangeComboSel(m_IdxAutoMan1,&m_IdxAutoGio1,m_IdxTexMan1,m_FlagOK[4],&m_FlagOK[2],
					 &m_FlagOK[3],IDC_COMBO_SELPALGIOC1,IDC_SELBUTTON3,IDC_COMBO_SELPALPORT1,
					 IDC_SELBUTTON4B,IDC_FILE_PALGIOC1,IDC_FILE_PALPORT1,m_TexFileManLun1,
					 &m_PalFileGioc1,&m_IdxPalGioc1,&m_PalFilePort1,&m_IdxPalPort1);
}

void CWECompressorTab3::OnChangeComboSelTexMan2() 
{
	UpdateData(TRUE);
	OnChangeComboSel(m_IdxAutoMan2,&m_IdxAutoGio2,m_IdxTexMan2,m_FlagOK[10],&m_FlagOK[8],
					 &m_FlagOK[9],IDC_COMBO_SELPALGIOC2,IDC_SELBUTTON9,IDC_COMBO_SELPALPORT2,
					 IDC_SELBUTTON10,IDC_FILE_PALGIOC2,IDC_FILE_PALPORT2,m_TexFileManLun2,
					 &m_PalFileGioc2,&m_IdxPalGioc2,&m_PalFilePort2,&m_IdxPalPort2);
	
}

void CWECompressorTab3::OnChangeComboSelAutoGio1() 
{
	OnChangeComboSelTexGio1();
	
}

void CWECompressorTab3::OnChangeComboSelAutoGio2() 
{
	OnChangeComboSelTexGio2();
	
}

void CWECompressorTab3::OnChangeComboSelAutoMan1() 
{
	OnChangeComboSelTexMan1();
	
}

void CWECompressorTab3::OnChangeComboSelAutoMan2() 
{
	OnChangeComboSelTexMan2();
	
}

void CWECompressorTab3::OnLargeTexClick() 
{
	CString TempMsg;

	TempMsg = _T("<u><b>Informazione</b></u><br><br>");	
	UpdateData(TRUE);	
	m_ctlTT.RemoveTool(m_ctlTT.FindTool(GetDlgItem(IDC_SELBUTTON2)));
	m_ctlTT.RemoveTool(m_ctlTT.FindTool(GetDlgItem(IDC_SELBUTTON8)));
	if (m_LargeTex)
	{
		m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON2), 
				TempMsg + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELBUTTON2B)), IDI_PP_INFORMATION);
		m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON8), 
				TempMsg + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELBUTTON8B)), IDI_PP_INFORMATION);
		
		GetDlgItem(IDC_FILE_TEXMANLUN1)->ShowWindow(FALSE);
		GetDlgItem(IDC_SELBUTTON5)->ShowWindow(FALSE);
		GetDlgItem(IDC_VIEWBUTTON5)->ShowWindow(FALSE);
		GetDlgItem(IDC_COMBO_SELTEXMAN1)->ShowWindow(FALSE);
		GetDlgItem(IDC_COMBO_SELAUTOMAN1)->ShowWindow(FALSE);
		GetDlgItem(IDC_TYPETEXT1)->ShowWindow(FALSE);
		GetDlgItem(IDC_AUTOPALTEXT1)->ShowWindow(FALSE);
		GetDlgItem(IDC_MANLUNTEXT1)->ShowWindow(FALSE);
		GetDlgItem(IDC_FILE_TEXMANLUN2)->ShowWindow(FALSE);
		GetDlgItem(IDC_SELBUTTON11)->ShowWindow(FALSE);
		GetDlgItem(IDC_VIEWBUTTON11)->ShowWindow(FALSE);
		GetDlgItem(IDC_COMBO_SELTEXMAN2)->ShowWindow(FALSE);
		GetDlgItem(IDC_COMBO_SELAUTOMAN2)->ShowWindow(FALSE);
		GetDlgItem(IDC_TYPETEXT2)->ShowWindow(FALSE);
		GetDlgItem(IDC_AUTOPALTEXT2)->ShowWindow(FALSE);
		GetDlgItem(IDC_MANLUNTEXT2)->ShowWindow(FALSE);
	
		GetDlgItem(IDC_TEXGIOCTEXT1)->SetWindowText(CString(MAKEINTRESOURCE(IDS_INFO_TAB3_TITLE2)));
		GetDlgItem(IDC_TEXGIOCTEXT2)->SetWindowText(CString(MAKEINTRESOURCE(IDS_INFO_TAB3_TITLE2)));
		GetDlgItem(IDC_BUTTON_MAKETEX)->EnableWindow(FALSE);
		CheckValidity();
	}
	else
	{
		m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON2), 
				TempMsg + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELBUTTON2)), IDI_PP_INFORMATION);
		m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON8), 
				TempMsg + CString(MAKEINTRESOURCE(IDS_HELP_TAB3_SELBUTTON8)), IDI_PP_INFORMATION);

		GetDlgItem(IDC_FILE_TEXMANLUN1)->ShowWindow(TRUE);
		GetDlgItem(IDC_SELBUTTON5)->ShowWindow(TRUE);
		GetDlgItem(IDC_VIEWBUTTON5)->ShowWindow(TRUE);
		GetDlgItem(IDC_COMBO_SELTEXMAN1)->ShowWindow(TRUE);
		GetDlgItem(IDC_COMBO_SELAUTOMAN1)->ShowWindow(TRUE);
		GetDlgItem(IDC_TYPETEXT1)->ShowWindow(TRUE);
		GetDlgItem(IDC_AUTOPALTEXT1)->ShowWindow(TRUE);
		GetDlgItem(IDC_MANLUNTEXT1)->ShowWindow(TRUE);
		GetDlgItem(IDC_FILE_TEXMANLUN2)->ShowWindow(TRUE);
		GetDlgItem(IDC_SELBUTTON11)->ShowWindow(TRUE);
		GetDlgItem(IDC_VIEWBUTTON11)->ShowWindow(TRUE);
		GetDlgItem(IDC_COMBO_SELTEXMAN2)->ShowWindow(TRUE);
		GetDlgItem(IDC_COMBO_SELAUTOMAN2)->ShowWindow(TRUE);
		GetDlgItem(IDC_TYPETEXT2)->ShowWindow(TRUE);
		GetDlgItem(IDC_AUTOPALTEXT2)->ShowWindow(TRUE);
		GetDlgItem(IDC_MANLUNTEXT2)->ShowWindow(TRUE);
		
		GetDlgItem(IDC_TEXGIOCTEXT1)->SetWindowText(CString(MAKEINTRESOURCE(IDS_INFO_TAB3_TITLE1)));
		GetDlgItem(IDC_TEXGIOCTEXT2)->SetWindowText(CString(MAKEINTRESOURCE(IDS_INFO_TAB3_TITLE1)));
		GetDlgItem(IDC_BUTTON_MAKETEX)->EnableWindow(FALSE);
		CheckValidity();
		
	}
		
}

BOOL CWECompressorTab3::PreTranslateMessage(MSG* pMsg) 
{
	m_ctlTT.RelayEvent(pMsg);
		
	return CDialog::PreTranslateMessage(pMsg);
}

