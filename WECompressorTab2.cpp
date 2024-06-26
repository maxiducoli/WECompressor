// WECompressorTab2.cpp : implementation file
//

#include "stdafx.h"
#include "WECompressor.h"
#include "XTabCtrl.h"
#include "WECompressorTab2.h"
#include "AboutDialog.h"
#include "WECompress.h"
#include "BitmapDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWECompressorTab2 dialog


CWECompressorTab2::CWECompressorTab2(CWnd* pParent /*=NULL*/)
	: CDialog(CWECompressorTab2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWECompressorTab2)
		m_ComboIndex = 0;
		m_ComboPalIndex = 0;
		m_OffsetImage = _T("30");
		m_OffsetPal = _T("25EC");		
		m_ManualImage = FALSE;
		m_ManualPalette = FALSE;
		m_AutomaticPal = TRUE;
		m_AdvancedMode = TRUE;
		m_EnableTex = FALSE;
		m_ComboGame = 0;
		m_UseSameFile = FALSE;
	//}}AFX_DATA_INIT

	m_ImageFile = CString(" ");
	m_PaletteFile = CString(" ");
	m_SourceImageFile = CString(" ");
	m_SourcePaletteFile = CString(" ");
	m_ActualImagesIndex = 0;
	m_ActualPalettesIndex = 0;
	m_ActualColorsNumber = 256;
	
	m_FirstOK = FALSE;
	m_SecondOK = FALSE;
	m_ThirdOK = FALSE;
	m_FourthOK = FALSE;
	m_pTab = NULL;
}

CWECompressorTab2::~CWECompressorTab2()
{
	UpdateData(TRUE);
	if (m_ImagesList)
		m_ImagesList.DeleteAllItems();
	if (m_PalettesList)
		m_PalettesList.DeleteAllItems();
	FreeListMem(TRUE);
	FreeListMem(FALSE);	
	
}

void CWECompressorTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWECompressorTab2)
		DDX_Control(pDX, IDC_LIST_PALETTES, m_PalettesList);
		DDX_Control(pDX, IDC_LIST_IMAGES, m_ImagesList);
		DDX_CBIndex(pDX, IDC_COMBO_SELFILE, m_ComboIndex);
		DDX_CBIndex(pDX, IDC_COMBO_SELPAL, m_ComboPalIndex);
		DDX_Text(pDX, IDC_EDIT_OFFSET_IMAGES, m_OffsetImage);
		DDX_Text(pDX, IDC_EDIT_OFFSET_PAL, m_OffsetPal);		
		DDX_Check(pDX, IDC_MANUAL_IMAGES, m_ManualImage);
		DDX_Check(pDX, IDC_MANUAL_PALETTE, m_ManualPalette);
		DDX_Check(pDX, IDC_CHECK_AUTOPAL, m_AutomaticPal);
		DDX_Check(pDX, IDC_ADVANCED, m_AdvancedMode);
		DDX_Check(pDX, IDC_SHIRT_TEX, m_EnableTex);
		DDX_CBIndex(pDX, IDC_COMBO_SELGAME, m_ComboGame);
	DDX_Check(pDX, IDC_CHECK_IMAGEANDPAL, m_UseSameFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWECompressorTab2, CDialog)
	//{{AFX_MSG_MAP(CWECompressorTab2)
		ON_BN_CLICKED(ID_INFO, OnInfo)
		ON_BN_CLICKED(IDC_SELBUTTON3, OnBrowseImage)
		ON_BN_CLICKED(IDC_SELBUTTON4, OnBrowsePalette)		
		ON_BN_CLICKED(IDC_BUTTON_MAKEFILE, OnButtonMakeFile)
		ON_NOTIFY(NM_CLICK, IDC_LIST_PALETTES, OnClickListPalettes)
		ON_NOTIFY(NM_CLICK, IDC_LIST_IMAGES, OnClickListImages)
		ON_NOTIFY(NM_RCLICK, IDC_LIST_PALETTES, OnRclickListPalettes)
		ON_NOTIFY(NM_RCLICK, IDC_LIST_IMAGES, OnRclickListImages)
		ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_PALETTES, OnKeydownListPalettes)
		ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_IMAGES, OnKeydownListImages)
		ON_CBN_SELCHANGE(IDC_COMBO_SELFILE, OnSelchangeComboSelfile)
		ON_BN_CLICKED(IDC_BUTTON_VIEWIMAGE, OnButtonViewImage)
		ON_BN_CLICKED(IDC_MANUAL_IMAGES, OnClickManualImages)
		ON_BN_CLICKED(IDC_MANUAL_PALETTE, OnClickManualPalette)
		ON_BN_CLICKED(IDOK, OnQuit)	
		ON_BN_CLICKED(IDC_SELBUTTON, OnBrowseSrcImage)
		ON_BN_CLICKED(IDC_SELBUTTON2, OnBrowseSrcPalette)
		ON_BN_CLICKED(IDC_ADVANCED, OnClickAdvanced)
		ON_BN_CLICKED(IDC_CHECK_AUTOPAL, OnCheckAutopal)
		ON_CBN_SELCHANGE(IDC_COMBO_SELPAL, OnSelchangeComboSelpal)
	ON_CBN_SELCHANGE(IDC_COMBO_SELGAME, OnChangeGameSel)
	ON_BN_CLICKED(IDC_CHECK_IMAGEANDPAL, OnCheckImageAndPal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWECompressorTab2 message handlers

BOOL CWECompressorTab2::OnInitDialog()
{
	CDialog::OnInitDialog();

	// load CButtonST
	m_FOpenFirst.SubclassDlgItem(IDC_SELBUTTON, this);
	m_FOpenFirst.SetIcon(IDI_SELFILE); 

	m_FOpenSec.SubclassDlgItem(IDC_SELBUTTON2, this);
	m_FOpenSec.SetIcon(IDI_SELFILE);

	m_FOpenThird.SubclassDlgItem(IDC_SELBUTTON3, this);
	m_FOpenThird.SetIcon(IDI_SELFILE);

	m_FOpenFourth.SubclassDlgItem(IDC_SELBUTTON4, this);
	m_FOpenFourth.SetIcon(IDI_SELFILE);

	// create ToolsTips
	AddHelpTTips();

	// init tables
	m_ImagesList.SetExtendedStyle(m_ImagesList.GetExtendedStyle()  
	 | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_UNDERLINEHOT);
	m_ImagesList.InsertColumn(0, "ID", LVCFMT_LEFT, 24);
	m_ImagesList.InsertColumn(1, CString(MAKEINTRESOURCE(IDS_IMAGETABCOL2)), LVCFMT_LEFT, 50);
	m_ImagesList.InsertColumn(2, CString(MAKEINTRESOURCE(IDS_IMAGETABCOL3)), LVCFMT_CENTER, 40);
	m_ImagesList.InsertColumn(3, CString(MAKEINTRESOURCE(IDS_IMAGETABCOL4)), LVCFMT_CENTER, 40);
	m_ImagesList.InsertColumn(4, CString(MAKEINTRESOURCE(IDS_IMAGETABCOL5)), LVCFMT_CENTER, 50);
	m_ImagesList.InsertColumn(5, CString(MAKEINTRESOURCE(IDS_IMAGETABCOL6)), LVCFMT_CENTER, 50);
	m_ImagesList.InsertColumn(6, CString(MAKEINTRESOURCE(IDS_IMAGETABCOL7)), LVCFMT_LEFT, 50);
	m_ImagesList.InsertColumn(7, CString(MAKEINTRESOURCE(IDS_IMAGETABCOL8)), LVCFMT_CENTER, 50);

	m_PalettesList.SetExtendedStyle(m_PalettesList.GetExtendedStyle() 
	 | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_UNDERLINEHOT);
	m_PalettesList.InsertColumn(0, "ID", LVCFMT_LEFT, 24);
	m_PalettesList.InsertColumn(1, CString(MAKEINTRESOURCE(IDS_PALTABCOL2)), LVCFMT_LEFT, 50);
	m_PalettesList.InsertColumn(2, CString(MAKEINTRESOURCE(IDS_PALTABCOL3)), LVCFMT_CENTER, 40);
	m_PalettesList.InsertColumn(3, CString(MAKEINTRESOURCE(IDS_PALTABCOL4)), LVCFMT_CENTER, 46);
	m_PalettesList.InsertColumn(4, CString(MAKEINTRESOURCE(IDS_PALTABCOL5)), LVCFMT_CENTER, 46);
	m_PalettesList.InsertColumn(5, CString(MAKEINTRESOURCE(IDS_PALTABCOL6)), LVCFMT_CENTER, 38);
	m_PalettesList.InsertColumn(6, CString(MAKEINTRESOURCE(IDS_PALTABCOL7)), LVCFMT_CENTER, 36);
	m_PalettesList.InsertColumn(7, CString(MAKEINTRESOURCE(IDS_PALTABCOL8)), LVCFMT_LEFT, 50);
	m_PalettesList.InsertColumn(8, CString(MAKEINTRESOURCE(IDS_PALTABCOL9)), LVCFMT_CENTER, 50);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWECompressorTab2::AddHelpTTips()
{
	CString Temp;
	//PPTOOLTIP_INFO ti;
	m_ctlTT.Create (this);

	Temp = CString(MAKEINTRESOURCE(IDS_HELP_INFORMATION_TITLE));
	m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB2_SELBUTTON)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON2), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB2_SELBUTTON2)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON3), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB2_SELBUTTON3)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON4), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB2_SELBUTTON4)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_MANUAL_IMAGES), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_MANUAL_IMAGE)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_MANUAL_PALETTE), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_MANUAL_PAL)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_COMBO_PALETTE), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_COMBO_PAL)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_EDIT_OFFSET_PAL), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_OFFSET_PAL)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_EDIT_OFFSET_IMAGES), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_OFFSET_IMAGE)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_EDIT_X), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_IMAGE_X)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_EDIT_Y), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_IMAGE_Y)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_COMBO_SELFILE), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB2_SELFILE)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_COMBO_SELPAL), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB2_SELPAL)), IDI_PP_INFORMATION);	
	m_ctlTT.AddTool(GetDlgItem(IDC_ADVANCED), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB2_ADVANCED)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_CHECK_AUTOPAL), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB2_AUTOPAL)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_COMBO_SELGAME), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB1_SELGAME)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_SHIRT_TEX), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB1_TEXSHIRT)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_BUTTON_VIEWIMAGE), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB2_VIEW)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_CHECK_IMAGEANDPAL), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB_IMAGEPAL)), IDI_PP_INFORMATION);	
	m_ctlTT.AddTool(GetDlgItem(IDC_BUTTON_MAKEFILE), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB2_INSERTFILE)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(ID_INFO), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_INFO)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDOK), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_EXIT)), IDI_PP_INFORMATION);
	//m_ctlTT.AddTool(m_pTab->GetDlgItem(IDC_WECOMPRESSOR), 
	//					Temp + CString(MAKEINTRESOURCE(IDS_HELP_WECOMPRESSOR)), IDI_PP_INFORMATION);

	UpdateData(FALSE);
	
}

void CWECompressorTab2::OnInfo() 
{
	CAboutDialog dlgAbout;
	dlgAbout.DoModal();
	
}

void CWECompressorTab2::FreeListMem(BOOL Select)
{
	UpdateData(TRUE);
	if (Select)
	{
		POSITION pos = m_ImageFileList.GetHeadPosition();

		while (pos != NULL)
		{
			CFilesStruct* p_ImageList = m_ImageFileList.GetNext(pos);

			delete p_ImageList->m_DataBlock;
			delete p_ImageList;
			//delete m_ImageList.GetNext(pos);
		}
		m_ImageFileList.RemoveAll();
	}
	else
	{
		POSITION pos = m_PaletteFileList.GetHeadPosition();

		while (pos != NULL)
		{
			CFilesStruct* p_PaletteList = m_PaletteFileList.GetNext(pos);
			delete p_PaletteList->m_DataBlock;
			delete p_PaletteList;
			//delete m_PaletteFileList.GetNext(pos);
		}
		m_PaletteFileList.RemoveAll();

	}
	
}

BOOL CWECompressorTab2::UpdateMyData(BOOL bValid)
{
	BOOL bTemp;
	CString tempStr;
	//char *tempPath = "All'anima de li mortacci tua e de chi ntoo dice caa mano arzata!";	
	//char *tempPath = NULL;
	char tempPath[_MAX_PATH];

	if (GetDlgItem(IDC_FILE_IMAGE)->IsWindowEnabled() == TRUE)
	{
		if (bValid == FALSE)
		{						
			if (m_ImageFile == "")
				GetDlgItem(IDC_FILE_IMAGE)->SetWindowText(
												CString(MAKEINTRESOURCE(IDS_NAME_NOFILE)));
			else
			{								
				PathCompactPathEx(tempPath, m_ImageFile, 50, '\\');
				GetDlgItem(IDC_FILE_IMAGE)->SetWindowText(CString(tempPath));				
			}

		}
		else
		{
			GetDlgItem(IDC_FILE_IMAGE)->GetWindowText(tempStr);
			if (tempStr == CString(MAKEINTRESOURCE(IDS_NAME_NOFILE)))		
				m_ImageFile = CString("");

		}
	}

	if (GetDlgItem(IDC_FILE_PALETTE)->IsWindowEnabled() == TRUE)
	{
		if (bValid == FALSE)
		{			
			if (m_PaletteFile == "")
				GetDlgItem(IDC_FILE_PALETTE)->SetWindowText(
													CString(MAKEINTRESOURCE(IDS_NAME_NOFILE)));
			else
			{					
				PathCompactPathEx(tempPath, m_PaletteFile, 50, '\\');
				GetDlgItem(IDC_FILE_PALETTE)->SetWindowText(CString(tempPath));				
			}			

		}
		else
		{
			GetDlgItem(IDC_FILE_PALETTE)->GetWindowText(tempStr);
			if (tempStr == CString(MAKEINTRESOURCE(IDS_NAME_NOFILE)))		
				m_PaletteFile = CString("");

		}
	}

	if (GetDlgItem(IDC_FILE_READIMAGE)->IsWindowEnabled() == TRUE)
	{
		if (bValid == FALSE)
		{			
			if (m_SourceImageFile == "")
				GetDlgItem(IDC_FILE_READIMAGE)->SetWindowText(
													CString(MAKEINTRESOURCE(IDS_NAME_NOFILE)));
			else
			{					
				PathCompactPathEx(tempPath, m_SourceImageFile, 50, '\\');
				GetDlgItem(IDC_FILE_READIMAGE)->SetWindowText(CString(tempPath));				
			}			

		}
		else
		{
			GetDlgItem(IDC_FILE_READIMAGE)->GetWindowText(tempStr);
			if (tempStr == CString(MAKEINTRESOURCE(IDS_NAME_NOFILE)))		
				m_SourceImageFile = CString("");

		}
	}

	if (GetDlgItem(IDC_FILE_READPAL)->IsWindowEnabled() == TRUE)
	{
		if (bValid == FALSE)
		{			
			if (m_SourcePaletteFile == "")
				GetDlgItem(IDC_FILE_READPAL)->SetWindowText(
													CString(MAKEINTRESOURCE(IDS_NAME_NOFILE)));
			else
			{					
				PathCompactPathEx(tempPath, m_SourcePaletteFile, 50, '\\');
				GetDlgItem(IDC_FILE_READPAL)->SetWindowText(CString(tempPath));				
			}			

		}
		else
		{
			GetDlgItem(IDC_FILE_READPAL)->GetWindowText(tempStr);
			if (tempStr == CString(MAKEINTRESOURCE(IDS_NAME_NOFILE)))		
				m_SourcePaletteFile = CString("");

		}
	}

	bTemp = TRUE;
	bTemp = UpdateData(bValid) && bTemp;

	return bTemp;
}

BOOL CWECompressorTab2::OffsetMatch(BYTE Code) 
{
	BOOL Res;

	Res = FALSE;
	if (m_ComboGame == 0)
	{
		if (((Code > 0x0B) && (Code < 0x13)) || (Code == 0x08))
			Res=TRUE;
	}
	else
	if (m_ComboGame == 1)
	{
		if (((Code > 0x07) && (Code < 0x0B)) || ((Code > 0x0F) && (Code < 0x14)))
			Res=TRUE;
	}
	else
	if (m_ComboGame == 2)
	{
		if (((Code > 0x19) && (Code < 0x1D)) || (Code == 0x11) || (Code == 0x13))
			Res=TRUE;
	}
	else
	if (m_ComboGame == 3)
	{
		if (((Code > 0x18) && (Code < 0x1D)) || (Code == 0x13))
			Res=TRUE;
	}
	else
	if (m_ComboGame == 4)
	{
		if (((Code > 0x18) && (Code < 0x1F)))
			Res=TRUE;
	}
	else
	if (m_ComboGame == 5)
	{
		if (((Code > 0x13) && (Code < 0x17)) || ((Code > 0x17) && (Code < 0x1D)))
			Res=TRUE;
	}

	return Res;

}

BOOL CWECompressorTab2::OffsetTranslate(BYTE Code,ULONG *Offset)
{
	BOOL Res;

	Res = FALSE;
	if (m_ComboGame == 0)
	{
		if (Code == 0x08)
			*Offset = *Offset + 0x14E8;
		else
		if (Code == 0x0C)
			*Offset = *Offset - 0x8000;
		else
		if (Code == 0x0D)
			*Offset = *Offset + 0x8000;
		else
		if (Code == 0x0E)
			*Offset = *Offset + 0x18000;
		else
		if (Code == 0x0F)
			*Offset = *Offset;
		else
		if (Code == 0x10)
			*Offset = *Offset + 0x10000;
		else
		if (Code == 0x11)
			*Offset = *Offset + 0x20000;
		else
		if (Code == 0x12)
			*Offset = *Offset + 0x30000;

		if (((Code > 0x0B) && (Code < 0x13)) || (Code == 0x08))
			Res=TRUE;
	}
	else
	if (m_ComboGame == 1)
	{
		if (Code == 0x08)
			*Offset = *Offset - 0x8000;
		else
		if (Code == 0x09)
			*Offset = *Offset + 0x8000;
		else
		if (Code == 0x0A)
			*Offset = *Offset + 0x18000;
		else		
		if (Code == 0x10)
			*Offset = *Offset - 0xC000;
		else
		if (Code == 0x11)
		{
			if (m_EnableTex)
				*Offset = *Offset + 0x4000;
			else
				*Offset = *Offset - 0xC000;
		}
		else
		if (Code == 0x12)
			*Offset = *Offset + 0x4000;
		else
		if (Code == 0x13)
			*Offset = *Offset + 0x14000;

		if (((Code > 0x07) && (Code < 0x0B)) || ((Code > 0x0F) && (Code < 0x14)))
			Res=TRUE;
	}
	else
	if (m_ComboGame == 2)
	{
		if (Code == 0x11)
			*Offset = *Offset;////////////////////////
		else
		if (Code == 0x13)
			*Offset = *Offset - 0x3000;
		else
		if (Code == 0x1A)
			*Offset = *Offset - 0x6000;
		else		
		if (Code == 0x1B)
			*Offset = *Offset + 0xA000;
		else
		if (Code == 0x1C)
			*Offset = *Offset + 0x1A000;
		
		if (((Code > 0x19) && (Code < 0x1D)) || (Code == 0x11) || (Code == 0x13))
			Res=TRUE;
	}
	else
	if (m_ComboGame == 3)
	{
		if (Code == 0x13)
			*Offset = *Offset - 0x3000;
		else
		if (Code == 0x19)
			*Offset = *Offset - 0xE800;
		else
		if (Code == 0x1A)
			*Offset = *Offset + 0x1800;
		else		
		if (Code == 0x1B)
			*Offset = *Offset + 0x11800;
		else
		if (Code == 0x1C)
			*Offset = *Offset + 0x21800;
		
		if (((Code > 0x18) && (Code < 0x1D)) || (Code == 0x13))
			Res=TRUE;
	}
	else
	if (m_ComboGame == 4)
	{
		if (Code == 0x19)
			*Offset = *Offset - 0xE800;
		else
		if (Code == 0x1A)
			*Offset = *Offset + 0x1800;
		else
		if (Code == 0x1B)
			*Offset = *Offset + 0x11800;
		else
		if (Code == 0x1C)
			*Offset = *Offset + 0x21800;
		else
		if (Code == 0x1D)
			*Offset = *Offset - 0x6000;
		else
		if (Code == 0x1E)
			*Offset = *Offset + 0xA000;
		
		if (((Code > 0x18) && (Code < 0x1F)))
			Res=TRUE;
	}
	else
	if (m_ComboGame == 5)
	{
		if (Code == 0x14)
			*Offset = *Offset - 0xB600;
		else
		if (Code == 0x15)
			*Offset = *Offset + 0x4A00;
		else
		if (Code == 0x16)
			*Offset = *Offset + 0x14A00;
		else
		if (Code == 0x18)
			*Offset = *Offset;///////////////////////////
		else
		if (Code == 0x19)
			*Offset = *Offset + 0x10000;
		else
		if (Code == 0x1B)
			*Offset = *Offset - 0xC000;
		else
		if (Code == 0x1C)
			*Offset = *Offset + 0x4000;
		
		if (((Code > 0x13) && (Code < 0x17)) || ((Code > 0x17) && (Code < 0x1D)))
			Res=TRUE;
	}

	return Res;

}

BOOL CWECompressorTab2::SearchImages() 
{
	CFile	fSource;
	CString TempMsg;
	CFileException e;
	UINT nSize,i;

	// open data file to read
	if (!fSource.Open(m_ImageFile, CFile::modeRead | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error reading in source File ") + m_ImageFile);
		return FALSE;
	}

	FreeListMem(TRUE);
	nSize = fSource.GetLength();

	BYTE* rbuf = new BYTE[nSize];
	fSource.Read(rbuf, nSize);
	fSource.Close();

	BYTE *pCur = rbuf;
	
	i = 0;
	while( i++ < nSize - 16)
	{
		if ((rbuf[i] == 0x0A) && (rbuf[i+1] == 0x00) && (rbuf[i+10] == 0x00) && 
			(rbuf[i+11] == 0x00) && (rbuf[i+15] == 0x80) && (OffsetMatch(rbuf[i+14]) == TRUE))
		{
			// Found the header!!!!
			CFilesStruct *fe = new CFilesStruct();			
			memcpy(&fe->m_Header,pCur+i,sizeof(DATA_HEADER));
			
			fe->m_OffsetReal = fe->m_Header.offset;
			OffsetTranslate(rbuf[i+14],&fe->m_OffsetReal);

			CWECompress tempclass;
			BYTE* tempblock = new BYTE[fe->m_Header.height*fe->m_Header.width*2];
			memcpy(tempblock,pCur + fe->m_OffsetReal, fe->m_Header.height*fe->m_Header.width*2);
			fe->m_BlockLen = tempclass.FindCompressedLength(tempblock);//i - fe->m_OffsetReal;
			delete tempblock;

			if (fe->m_Header.height < 128)
				fe->m_MultiplyY = (128 / fe->m_Header.height);
			else
				fe->m_MultiplyY = 1;
			
			(BYTE*) fe->m_DataBlock = new BYTE[fe->m_BlockLen];
			memcpy(fe->m_DataBlock,pCur + fe->m_OffsetReal, fe->m_BlockLen);

			m_ImageFileList.AddTail(fe);
			i+=15;
		}
		
	}

	/////////
	delete rbuf;	

	if (m_ImageFileList.IsEmpty())
		return FALSE;

	return TRUE;
}

BOOL CWECompressorTab2::SearchPalettes() 
{
	CFile	fSource;
	CString TempMsg;
	CFileException e;
	UINT nSize,i;

	// open data file to read
	if (!fSource.Open(m_PaletteFile, CFile::modeRead | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error reading in source File ") + m_PaletteFile);
		return FALSE;
	}

	FreeListMem(FALSE);
	nSize = fSource.GetLength();

	BYTE* rbuf = new BYTE[nSize];
	fSource.Read(rbuf, nSize);
	fSource.Close();

	BYTE *pCur = rbuf;
	
	i = 0;
	while( i++ < nSize - 16)
	{
		if ((rbuf[i] == 0x09) && (rbuf[i+10] == 0x00) && (rbuf[i+11] == 0x00) && 
			(rbuf[i+15] == 0x80) && (OffsetMatch(rbuf[i+14]) == TRUE))
		{
			// Found the header!!!!
			CFilesStruct *fe = new CFilesStruct();			
			memcpy(&fe->m_Header,pCur+i,sizeof(DATA_HEADER));

			fe->m_OffsetReal = fe->m_Header.offset;
			OffsetTranslate(rbuf[i+14],&fe->m_OffsetReal);
			
			// often errors
			// fe->m_BlockLen = i - fe->m_OffsetReal;

			if (fe->m_Header.width == 16)			
				fe->m_MultiplyFactor = 4;
			else
			if (fe->m_Header.width == 256)
				fe->m_MultiplyFactor = 2;
			else
			if (fe->m_Header.width == 65535)
				fe->m_MultiplyFactor = 1;
			else				
				fe->m_MultiplyFactor = 1; // 2/3 ma non posso

			fe->m_BlockLen = fe->m_Header.width*2; // 15 bit colours,so * 2
			(BYTE*) fe->m_DataBlock = new BYTE[fe->m_BlockLen];
			memcpy(fe->m_DataBlock,pCur + fe->m_OffsetReal, fe->m_BlockLen);

			m_PaletteFileList.AddTail(fe);
			i+=15;
		}
		
	}

	/////////
	delete rbuf;	

	if (m_PaletteFileList.IsEmpty())
		return FALSE;

	return TRUE;
}

BOOL CWECompressorTab2::SetManualImage()
{	
	CFile	fSource;	
	CFileException e;
	UINT nSize,i;

	// open data file to read
	if (!fSource.Open(m_ImageFile, CFile::modeRead | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error reading in source File ") + m_ImageFile);
		return FALSE;
	}

	FreeListMem(TRUE);
	nSize = fSource.GetLength();

	BYTE* rbuf = new BYTE[nSize];
	fSource.Read(rbuf, nSize);
	fSource.Close();

	BYTE *pCur = rbuf;

	i = 0;

	UpdateData(TRUE);
	// Make the header!!!!
	CFilesStruct *fe = new CFilesStruct();

	ZeroMemory(&fe->m_Header,sizeof(DATA_HEADER));
	fe->m_Header.ID = 10;	
	//fe->m_Header.width = m_ImageX / 2;
	//fe->m_Header.height = m_ImageY;
	fe->m_Header.width = 128 / 2;
	fe->m_Header.height = 128;
	fe->m_Header.VramX = 576;
	fe->m_Header.VramY = 256;
	//fe->m_Header.offset = strtol(m_OffsetImage, NULL, 16);
	fe->m_Header.separator = 32783;
	fe->m_Header.unknown5 = 255;

	fe->m_OffsetReal = strtol(m_OffsetImage, NULL, 16);
	
	CWECompress tempclass;
	BYTE* tempblock = new BYTE[fe->m_Header.height*fe->m_Header.width*2];
	memcpy(tempblock,pCur + fe->m_OffsetReal, fe->m_Header.height*fe->m_Header.width*2);
	fe->m_BlockLen = tempclass.FindCompressedLength(tempblock);//i - fe->m_OffsetReal;
	delete tempblock;

	if (fe->m_Header.height < 128)
		fe->m_MultiplyY = (128 / fe->m_Header.height);
	else
		fe->m_MultiplyY = 1;
			
	(BYTE*) fe->m_DataBlock = new BYTE[fe->m_BlockLen];
	memcpy(fe->m_DataBlock,pCur + fe->m_OffsetReal, fe->m_BlockLen);

	m_ImageFileList.AddTail(fe);

	/////////
	delete rbuf;	
	
	return TRUE;
}

BOOL CWECompressorTab2::SetManualPalette()
{	
	CFile	fSource;	
	CFileException e;
	UINT nSize,i;

	// open data file to read
	if (!fSource.Open(m_PaletteFile, CFile::modeRead | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error reading in source File ") + m_PaletteFile);
		return FALSE;
	}

	FreeListMem(FALSE);
	nSize = fSource.GetLength();

	BYTE* rbuf = new BYTE[nSize];
	fSource.Read(rbuf, nSize);
	fSource.Close();

	BYTE *pCur = rbuf;

	i = 0;
	UpdateData(TRUE);
	// Make the header!!!!
	CFilesStruct *fe = new CFilesStruct();

	ZeroMemory(&fe->m_Header,sizeof(DATA_HEADER));
	fe->m_Header.ID = 65289;
	/*if (m_BitPalette == 0)
		fe->m_Header.width = 16;
	else
		fe->m_Header.width = 256;*/
	fe->m_Header.height = 1;
	fe->m_Header.VramX = 0;
	fe->m_Header.VramY = 486;	
	//fe->m_Header.offset = strtol(m_OffsetPal, NULL, 16);
	fe->m_Header.separator = 32783;
	fe->m_Header.unknown5 = 255;

	fe->m_OffsetReal = strtol(m_OffsetPal, NULL, 16);
	
	if (fe->m_Header.width == 16)			
		fe->m_MultiplyFactor = 4;
	else
	if (fe->m_Header.width == 256)
		fe->m_MultiplyFactor = 2;
	else
	if (fe->m_Header.width == 65535)
		fe->m_MultiplyFactor = 1;
	else				
		fe->m_MultiplyFactor = 1; // 2/3 ma non posso

	fe->m_BlockLen = fe->m_Header.width*2; // 15 bit colours,so * 2
	(BYTE*) fe->m_DataBlock = new BYTE[fe->m_BlockLen];
	memcpy(fe->m_DataBlock,pCur + fe->m_OffsetReal, fe->m_BlockLen);

	m_PaletteFileList.AddTail(fe);

	/////////
	delete rbuf;	
	
	return TRUE;
}

BOOL CWECompressorTab2::UpdateFileList(BOOL Select) 
{
	CString TempMsg,temp;

	if (Select)
	{
		if (m_ImagesList)
		{
			m_ImagesList.DeleteAllItems();
		
			POSITION pos = m_ImageFileList.GetHeadPosition();//
		
			int i=0;
			while (pos != NULL)
			{				
				CFilesStruct* p_Images = m_ImageFileList.GetNext(pos);
					
				temp.Format("%d",i+1);
				int index = m_ImagesList.InsertItem(i++, temp);
				//m_ImagesList.SetItemData(index, i);
				temp.Format("0x%x", p_Images->m_OffsetReal);
				m_ImagesList.SetItemText(index, 1, temp);
				///if (p_Images->m_Header.width
				temp.Format("%u", p_Images->m_Header.width*2);				
				m_ImagesList.SetItemText(index, 2, temp);
				temp.Format("%u", p_Images->m_Header.height*p_Images->m_MultiplyY);
				m_ImagesList.SetItemText(index, 3, temp);
				temp.Format("%u", p_Images->m_Header.VramX);
				m_ImagesList.SetItemText(index, 4, temp);
				temp.Format("%u", p_Images->m_Header.VramY);
				m_ImagesList.SetItemText(index, 5, temp);
				if (p_Images->m_BlockLen > 0)
					temp.Format("%u", p_Images->m_BlockLen);
				else
					temp = CString(MAKEINTRESOURCE(IDS_ERROR_TAB_LENGTH));				
				m_ImagesList.SetItemText(index, 6, temp);
				temp.Format("0x%x", p_Images->m_Header.separator);
				m_ImagesList.SetItemText(index, 7, temp);				
			
			}

			TempMsg.Format("%d %s",m_ImagesList.GetItemCount(),CString(MAKEINTRESOURCE(IDS_INFO_IMAGES_FOUND)));
			GetDlgItem(IDC_NUM_IMAGES)->SetWindowText(CString(TempMsg));
						
			//m_ImagesList.SetTextColor(0x00ddaabb); // x i colori
			m_ImagesList.SetItemState(0,LVIS_SELECTED , -1);
			m_ImagesList.SetFocus();
		
		}
	}
	else
	{
		if (m_PalettesList)
		{
			m_PalettesList.DeleteAllItems();			
		
			POSITION pos = m_PaletteFileList.GetHeadPosition();//
		
			int i=0;
			while (pos != NULL)
			{			
				CFilesStruct* p_Palettes = m_PaletteFileList.GetNext(pos);
					
				temp.Format("%d",i+1);
				int index = m_PalettesList.InsertItem(i++, temp);
				//m_PalettesList.SetItemData(index, i);
				temp.Format("0x%x", p_Palettes->m_OffsetReal);
				m_PalettesList.SetItemText(index, 1, temp);
				temp.Format("%u", p_Palettes->m_Header.ID >> 8);
				m_PalettesList.SetItemText(index, 2, temp);
				temp.Format("%u", p_Palettes->m_Header.VramX);
				m_PalettesList.SetItemText(index, 3, temp);
				temp.Format("%u", p_Palettes->m_Header.VramY);
				m_PalettesList.SetItemText(index, 4, temp);
				temp.Format("%u", p_Palettes->m_Header.width);
				m_PalettesList.SetItemText(index, 5, temp);
				temp.Format("%u", p_Palettes->m_Header.height);
				m_PalettesList.SetItemText(index, 6, temp);
				temp.Format("%u", p_Palettes->m_BlockLen);
				m_PalettesList.SetItemText(index, 7, temp);
				temp.Format("0x%x", p_Palettes->m_Header.separator);
				m_PalettesList.SetItemText(index, 8, temp);
			
			}

			TempMsg.Format("%d %s",m_PalettesList.GetItemCount(),CString(MAKEINTRESOURCE(IDS_INFO_PALETTES_FOUND)));
			GetDlgItem(IDC_NUM_PALETTES)->SetWindowText(CString(TempMsg));

			m_PalettesList.SetItemState(0,LVIS_SELECTED , -1);
			m_PalettesList.SetFocus();
		
		}
	
	}

	return TRUE;
}

BOOL CWECompressorTab2::CreateBMP(CString NameFile)
{
	CFile   fImage,fPalette,NewFileBMP;
	CString TempMsg;
	CFileException e;
	UINT j,depth,totalheader,rgbsize,usedcol,comprflag;
	ULONG xsize,ysize,xtemp,ImageOffset,ImageLength,nImageSize,nPaletteSize;
	BYTE rgbq[RGB_SIZE256];
		
	// open data file to write
	if (!NewFileBMP.Open(NameFile, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + NameFile);
		return FALSE;
	}


	if (!fImage.Open(m_SourceImageFile, CFile::modeRead | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error reading in source File ") + m_SourceImageFile);
		return FALSE;
	}

	nImageSize = fImage.GetLength();

	BYTE* ImageBuf = new BYTE[nImageSize];
	fImage.Read(ImageBuf, nImageSize);
	fImage.Close();

	if (!m_AutomaticPal)
	{
		if (!fPalette.Open(m_SourcePaletteFile, CFile::modeRead | CFile::typeBinary, &e))
		{
			AfxMessageBox(_T("Error reading in source File ") + m_SourcePaletteFile);
			return FALSE;	
		}
		
		nPaletteSize = fPalette.GetLength();
	
	}
	else
		nPaletteSize = 1;

	BYTE* PaletteBuf = new BYTE[nPaletteSize];
	if (!m_AutomaticPal)
	{
		fPalette.Read(PaletteBuf,nPaletteSize);
		fPalette.Close();
	}

	BYTE *pImage = ImageBuf;
	BYTE *pPalette = PaletteBuf;
	
	// palette reading
	if (!m_AutomaticPal)
	{
		if (m_ComboPalIndex == 0)
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
		if (m_ComboIndex == 0)
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
		if (m_ComboIndex == 1)
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
	if (m_ComboIndex == 0)
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
	if (m_ComboIndex == 1)
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
	if (m_ComboIndex == 0)
	{
		memcpy(pImageData,pImage+ImageOffset,ImageLength);

	}
	else
	//if (m_ComboIndex == 1)
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

BOOL CWECompressorTab2::DecodeImage(BYTE *BufSrc,BYTE **BufDest,ULONG xsize,ULONG ysize,
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

BOOL CWECompressorTab2::CreateFiles()
{
	CFile   fImage,fPalette,NewFileImage,NewFileCLUT,NewFilePAL;
	CString TempMsg,mPalettePAL;
	CFileException e;
	UINT j,depth,totalheader,rgbsize,usedcol,comprflag;
	ULONG xsize,ysize,ImageOffset,ImageLength,nImageSize,nPaletteSize;
	BYTE rgbq[RGB_SIZE256];
	BYTE clut[RGB_SIZE256/2];
	BOOL Result;
		
	// open data file to write
	if (!NewFileImage.Open(m_ImageFile, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + m_ImageFile);
		return FALSE;
	}

	Result = TRUE;
	mPalettePAL = m_PaletteFile;
	mPalettePAL.Replace(".clu",".pal");	
	// open data file to write
	if (!NewFilePAL.Open(mPalettePAL, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + mPalettePAL);
		return FALSE;
	}
	// open data file to write
	if (!NewFileCLUT.Open(m_PaletteFile, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + m_PaletteFile);
		return FALSE;
	}

	if (!fImage.Open(m_SourceImageFile, CFile::modeRead | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error reading in source File ") + m_SourceImageFile);
		return FALSE;
	}
	
	nImageSize = fImage.GetLength();

	BYTE* ImageBuf = new BYTE[nImageSize];
	fImage.Read(ImageBuf, nImageSize);
	fImage.Close();

	if (!m_AutomaticPal)
	{
		if (!fPalette.Open(m_SourcePaletteFile, CFile::modeRead | CFile::typeBinary, &e))
		{
			AfxMessageBox(_T("Error reading in source File ") + m_SourcePaletteFile);
			return FALSE;	
		}
		
		nPaletteSize = fPalette.GetLength();
	
	}
	else
		nPaletteSize = 1;

	BYTE* PaletteBuf = new BYTE[nPaletteSize];
	if (!m_AutomaticPal)
	{
		fPalette.Read(PaletteBuf,nPaletteSize);
		fPalette.Close();
	}

	BYTE *pImage = ImageBuf;
	BYTE *pPalette = PaletteBuf;
	
	// palette reading
	if (!m_AutomaticPal)
	{
		if (m_ComboPalIndex == 0)
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


			memcpy(clut,pPalette, nPaletteSize);

			for (WORD col=0; col < nPaletteSize; col+=4)
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

			memcpy(rgbq,pPalette,nPaletteSize);

			j=0;
			for (UINT col=0; col < nPaletteSize; col+=4)
			{			
				WORD tempword = (((BYTE) rgbq[col+2] >> 3 | 
								 ((WORD) (rgbq[col+1] >> 3) << 5)) | 
								 (((DWORD) (BYTE) (rgbq[col] >> 3)) << 10));
				clut[j++] = LOBYTE(tempword);
				clut[j++] = HIBYTE(tempword);
				
			}

		}
		
	
	}
	else
	{
		if (m_ComboIndex == 0)
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

			memcpy(rgbq,pImage + 54,rgbsize);

			j=0;
			for (UINT col=0; col < rgbsize; col+=4)
			{				
				WORD tempword = (((BYTE) rgbq[col+2] >> 3 | 
								 ((WORD) (rgbq[col+1] >> 3) << 5)) | 
								 (((DWORD) (BYTE) (rgbq[col] >> 3)) << 10));
				clut[j++] = LOBYTE(tempword);
				clut[j++] = HIBYTE(tempword);
				
			}


		}
		else
		if (m_ComboIndex == 1)
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

			memcpy(clut,pImage + 20, usedcol*2);
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

	// image reading
	if (m_ComboIndex == 0)
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
	if (m_ComboIndex == 1)
	{		
		TIM_DATAINFO TData_read;
	
		memcpy(&TData_read,pImage+ 20 + usedcol*2,sizeof(TIM_DATAINFO));

		xsize = TData_read.xsize*2;
		ysize = TData_read.ysize;		
		ImageLength = xsize*ysize;
		ImageOffset = 32 + usedcol*2;
		
	}
	else
	{
		xsize = 128;
		ysize = 128;
		ImageLength = xsize*ysize;
		if (depth == 4)
			ImageLength = ImageLength/2; 
		ImageOffset = 0;

	}

	// write CLUT (psx uses 15bit RGB)
	NewFileCLUT.Write(clut,rgbsize/2);

	// write converted CLUT RGB table (psx uses 15bit RGB)
	NewFilePAL.Write(rgbq,rgbsize);

	BYTE* pImageData = new BYTE[ImageLength];
	if (m_ComboIndex == 0)
	{
		BYTE* pImageTemp = new BYTE[ImageLength];

		Result = DecodeImage(pImage+ImageOffset,&pImageTemp,xsize,ysize,depth,comprflag);
		
		CWECompress tempclass;
			
		tempclass.Compress(&pImageData,pImageTemp,&ImageLength,ImageLength);

		delete pImageTemp;
	}
	else
	//if (m_ComboIndex == 1)
	{
		CWECompress tempclass;
			
		tempclass.Compress(&pImageData,pImage+ImageOffset,&ImageLength,ImageLength);
		
	}

	// write Data block
	NewFileImage.Write(pImageData,ImageLength);

	delete ImageBuf;
	delete PaletteBuf;
	delete pImageData;

	NewFileImage.Close();
	NewFileCLUT.Close();
	NewFilePAL.Close();

	return Result;

}

BOOL CWECompressorTab2::InsertInFiles()
{
	CFile   fImageSrc,fPaletteSrc,fImageDest,fPaletteDest;
	CString TempMsg;
	CFileException e;
	UINT j,depth,totalheader,clutsize,usedcol,comprflag;
	ULONG xsize,ysize,ImageOffset,ImageLength,nImageSize,nPaletteSize,OffsetWritePAL,
		OffsetWriteImage,MaxLengthWriteImage,MaxLengthWritePAL;
	BYTE rgbq[RGB_SIZE256];
	BYTE clut[RGB_SIZE256/2];
	BOOL Result;
		
	// open data file to write
	if (!fImageDest.Open(m_ImageFile, CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + m_ImageFile);
		return FALSE;
	}

	if (m_ImageFile != m_PaletteFile)
	{
		// open data file to write
		if (!fPaletteDest.Open(m_PaletteFile, CFile::modeReadWrite | CFile::typeBinary, &e))
		{
			AfxMessageBox(_T("Error writing ") + m_PaletteFile);
			return FALSE;
		}
	}

	if (!fImageSrc.Open(m_SourceImageFile, CFile::modeRead | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error reading in source File ") + m_SourceImageFile);
		return FALSE;
	}
	
	Result = TRUE;
	nImageSize = fImageSrc.GetLength();

	OffsetWritePAL = m_PaletteFileList.GetAt(m_PaletteFileList.FindIndex(m_ActualPalettesIndex))->m_OffsetReal;
	MaxLengthWritePAL = m_PaletteFileList.GetAt(m_PaletteFileList.FindIndex(m_ActualPalettesIndex))->m_BlockLen;

	OffsetWriteImage = m_ImageFileList.GetAt(m_ImageFileList.FindIndex(m_ActualImagesIndex))->m_OffsetReal;
	MaxLengthWriteImage = m_ImageFileList.GetAt(m_ImageFileList.FindIndex(m_ActualImagesIndex))->m_BlockLen;

	BYTE* ImageBuf = new BYTE[nImageSize];
	fImageSrc.Read(ImageBuf, nImageSize);
	fImageSrc.Close();

	if (!m_AutomaticPal)
	{
		if (!fPaletteSrc.Open(m_SourcePaletteFile, CFile::modeRead | CFile::typeBinary, &e))
		{
			AfxMessageBox(_T("Error reading in source File ") + m_SourcePaletteFile);
			return FALSE;	
		}
		
		nPaletteSize = fPaletteSrc.GetLength();
	
	}
	else
		nPaletteSize = 1;

	BYTE* PaletteBuf = new BYTE[nPaletteSize];
	if (!m_AutomaticPal)
	{
		fPaletteSrc.Read(PaletteBuf,nPaletteSize);
		fPaletteSrc.Close();
	}

	BYTE *pImage = ImageBuf;
	BYTE *pPalette = PaletteBuf;
	
	// palette reading
	if (!m_AutomaticPal)
	{
		if (m_ComboPalIndex == 0)
		{
			if (nPaletteSize == 16*2)
			{
				depth = 4;
				usedcol = 16;
				totalheader = TOTAL_HEADER_SIZE16;
				clutsize = RGB_SIZE16/2;
			}
			else
			if (nPaletteSize == 256*2)
			{
				depth = 8;
				usedcol = 256;
				totalheader = TOTAL_HEADER_SIZE256;
				clutsize = RGB_SIZE256/2;
			}
			else
				return FALSE;

			memcpy(clut,pPalette, nPaletteSize);
		
		}
		else
		{
			if (nPaletteSize == 16*4)
			{
				depth = 4;
				usedcol = 16;
				totalheader = TOTAL_HEADER_SIZE16;
				clutsize = RGB_SIZE16/2;
			}
			else
			if (nPaletteSize == 256*4)
			{
				depth = 8;
				usedcol = 256;
				totalheader = TOTAL_HEADER_SIZE256;
				clutsize = RGB_SIZE256/2;
			}
			else
				return FALSE;

			memcpy(rgbq,pPalette,nPaletteSize);

			j=0;
			for (UINT col=0; col < nPaletteSize; col+=4)
			{			
				WORD tempword = (((BYTE) rgbq[col+2] >> 3 | 
								 ((WORD) (rgbq[col+1] >> 3) << 5)) | 
								 (((DWORD) (BYTE) (rgbq[col] >> 3)) << 10));
				clut[j++] = LOBYTE(tempword);
				clut[j++] = HIBYTE(tempword);
				
			}

		}
		
	
	}
	else
	{
		if (m_ComboIndex == 0)
		{
			BITMAPINFOHEADER bmih_read;

			memcpy(&bmih_read,pImage+BMFH_SIZE,sizeof(BITMAPINFOHEADER));			 
			depth = bmih_read.biBitCount;
						
			if (depth == 4)
			{
				totalheader = TOTAL_HEADER_SIZE16;
				clutsize = RGB_SIZE16/2;
				usedcol = 16;
			}
			else
			if (depth == 8)
			{
				totalheader = TOTAL_HEADER_SIZE256;
				clutsize = RGB_SIZE256/2;
				usedcol = 256;
			}
			else
				return FALSE;
				
			memcpy(rgbq,pImage + 54,clutsize*2);

			j=0;
			for (UINT col=0; col < clutsize*2; col+=4)
			{				
				WORD tempword = (((BYTE) rgbq[col+2] >> 3 | 
								 ((WORD) (rgbq[col+1] >> 3) << 5)) | 
								 (((DWORD) (BYTE) (rgbq[col] >> 3)) << 10));
				clut[j++] = LOBYTE(tempword);
				clut[j++] = HIBYTE(tempword);
				
			}


		}
		else
		if (m_ComboIndex == 1)
		{
			TIM_HEADER THead_read;
	
			memcpy(&THead_read,pImage,sizeof(TIM_HEADER));

			if (THead_read.type == TIM_4Bit)
			{
				depth = 4;
				usedcol = 16;
				totalheader = TOTAL_HEADER_SIZE16;
				clutsize = RGB_SIZE16/2;
			}
			else
			if (THead_read.type == TIM_8Bit)
			{
				depth = 8;
				usedcol = 256;
				totalheader = TOTAL_HEADER_SIZE256;
				clutsize = RGB_SIZE256/2;
			}
			else
				return FALSE;

			memcpy(clut,pImage + 20, clutsize);

		}
		else
			return FALSE;
		
	}

	// image reading
	if (m_ComboIndex == 0)
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
	if (m_ComboIndex == 1)
	{		
		TIM_DATAINFO TData_read;
	
		memcpy(&TData_read,pImage+ 20 + usedcol*2,sizeof(TIM_DATAINFO));

		xsize = TData_read.xsize*2;
		ysize = TData_read.ysize;		
		ImageLength = xsize*ysize;
		ImageOffset = 32 + usedcol*2;
		
	}
	else
	{
		xsize = 128;
		ysize = 128;
		ImageLength = xsize*ysize;
		if (depth == 4)
			ImageLength = ImageLength/2; 
		ImageOffset = 0;

	}

	// write CLUT (psx uses 15bit RGB)
	if (clutsize == MaxLengthWritePAL)
	{
		if (m_ImageFile != m_PaletteFile)
		{
			fPaletteDest.Seek(OffsetWritePAL,CFile::begin);
			fPaletteDest.Write(clut,clutsize);
			fPaletteDest.Close();
		}
		else
		{
			fImageDest.Seek(OffsetWritePAL,CFile::begin);
			fImageDest.Write(clut,clutsize);
		}
		
	}
	else
	{
		AfxMessageBox(_T("Error in Palette size "));
		Result = FALSE;
	}

	BYTE* pImageData = new BYTE[ImageLength];	
	if (m_ComboIndex == 0)
	{
		BYTE* pImageTemp = new BYTE[ImageLength];

		Result = DecodeImage(pImage+ImageOffset,&pImageTemp,xsize,ysize,depth,comprflag);
		
		CWECompress tempclass;
			
		tempclass.Compress(&pImageData,pImageTemp,&ImageLength,ImageLength);

		delete pImageTemp;
	}
	else
	//if (m_ComboIndex == 1)
	{
		CWECompress tempclass;
			
		tempclass.Compress(&pImageData,pImage+ImageOffset,&ImageLength,ImageLength);
		
	}
	
	TempMsg.Format("%s %u %s %u bytes?\n\n",CString(MAKEINTRESOURCE(IDS_INFO_INSERTBLOCK1)),
					ImageLength,CString(MAKEINTRESOURCE(IDS_INFO_INSERTBLOCK2)),
					MaxLengthWriteImage);
	
	if (ImageLength < MaxLengthWriteImage)
		TempMsg+= CString(MAKEINTRESOURCE(IDS_INFO_INSERTBLOCK_YES));
	else
		TempMsg+= CString(MAKEINTRESOURCE(IDS_INFO_INSERTBLOCK_NO));


	BOOL Res = AfxMessageBox(TempMsg, MB_YESNO | MB_ICONEXCLAMATION);	
	if (Res == IDYES)
	{
		// write Data block
		fImageDest.Seek(OffsetWriteImage,CFile::begin);
		fImageDest.Write(pImageData,ImageLength);		
	}
	else
		Result = FALSE;
	

	delete ImageBuf;
	delete PaletteBuf;
	delete pImageData;

	fImageDest.Close();

	return Result;

}


void CWECompressorTab2::OnBrowseImage() 
{
	CString	Temp,TempMsg;
	int	Res;
	
	UpdateData(TRUE);

	Temp.LoadString(IDS_FILTER_BIN);
	if (m_AdvancedMode)
	{
		CFileDialog MyFdlg(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_EXPLORER 
			| OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST ,(LPCTSTR) Temp, NULL);
	
		Temp.LoadString(IDS_INFO_TAB2_OPENIMAGE);
		MyFdlg.m_ofn.lpstrTitle = (LPCTSTR) Temp;
	
		//MyFdlg.m_ofn.lpstrInitialDir = m_nSelectedPath;

		// Invoke the dialog box	
		Res = MyFdlg.DoModal();
		if (Res == IDOK)
		{	
			m_ImageFile = MyFdlg.GetPathName();

			GetDlgItem(IDC_FILE_IMAGE)->EnableWindow(TRUE);
			m_ThirdOK = TRUE;
			if (m_UseSameFile)
			{
				m_PaletteFile = m_ImageFile;

				GetDlgItem(IDC_FILE_PALETTE)->EnableWindow(TRUE);
				m_FourthOK = TRUE;
			
				if (!m_ManualPalette)
				{
					if (SearchPalettes())
					{
						if (UpdateFileList(FALSE) == TRUE)
						{
							GetDlgItem(IDC_NUM_PALETTES)->ShowWindow(TRUE);
							GetDlgItem(IDC_LIST_PALETTES)->ShowWindow(TRUE);
				
						}
						OnChangeFocus(TRUE);
					}
					else
					{
						m_FourthOK = FALSE;
						GetDlgItem(IDC_FILE_PALETTE)->EnableWindow(FALSE);
						TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_INFO_NO_PALETTES_FOUND)) + "\n\n";
							MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_ERROR_MESSAGEBOX)), 		
								MB_ICONERROR);
					}

				}
				else
				{
					GetDlgItem(IDC_EDIT_OFFSET_PAL)->ShowWindow(TRUE);
					GetDlgItem(IDC_OFFSET_LAB2)->ShowWindow(TRUE);

				}

				UpdateMyData(FALSE);
				if (m_ctlTT.IsExistTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_PALETTE))))
					m_ctlTT.RemoveTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_PALETTE)));			
				m_ctlTT.AddTool(GetDlgItem (IDC_FILE_PALETTE), m_PaletteFile);
			}
	
			if (!m_ManualImage)
			{
				if (SearchImages())
				{
					if (UpdateFileList(TRUE) == TRUE)
					{
						GetDlgItem(IDC_NUM_IMAGES)->ShowWindow(TRUE);
						GetDlgItem(IDC_LIST_IMAGES)->ShowWindow(TRUE);					
					
					}
					OnChangeFocus(FALSE);
				}
				else
				{
					m_ThirdOK = FALSE;
					GetDlgItem(IDC_FILE_IMAGE)->EnableWindow(FALSE);
					TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_INFO_NO_IMAGES_FOUND)) + "\n\n";
					MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_ERROR_MESSAGEBOX)), 		
						MB_ICONERROR);
				}
					
			}
			else
			{
				GetDlgItem(IDC_EDIT_OFFSET_IMAGES)->ShowWindow(TRUE);		
				GetDlgItem(IDC_OFFSET_LAB1)->ShowWindow(TRUE);

			}

			if ((m_SecondOK || m_AutomaticPal) && m_FirstOK && m_FourthOK)
				GetDlgItem(IDC_BUTTON_MAKEFILE)->EnableWindow(TRUE);

			UpdateMyData(FALSE);
			if (m_ctlTT.IsExistTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_IMAGE))))
				m_ctlTT.RemoveTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_IMAGE)));
			m_ctlTT.AddTool(GetDlgItem (IDC_FILE_IMAGE), m_ImageFile);
					
		}
	}
	else
	{
		CFileDialog MyFdlg(FALSE, "bin" , "Custom", OFN_HIDEREADONLY | OFN_EXPLORER | 
						OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST , (LPCTSTR) Temp, NULL);	
	
		MyFdlg.m_ofn.lpstrTitle = (LPCTSTR) CString(MAKEINTRESOURCE(IDS_INFO_TAB2_NEWBIN));
	
		// Invoke the dialog box
		Res = MyFdlg.DoModal();
		if (Res == IDOK)
		{	
			m_ImageFile = MyFdlg.GetPathName();
			GetDlgItem(IDC_FILE_IMAGE)->EnableWindow(TRUE);
			m_ThirdOK = TRUE;

			if ((m_SecondOK || m_AutomaticPal) && m_FirstOK && m_FourthOK)		
				GetDlgItem(IDC_BUTTON_MAKEFILE)->EnableWindow(TRUE);
			UpdateMyData(FALSE);
			if (m_ctlTT.IsExistTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_IMAGE))))
				m_ctlTT.RemoveTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_IMAGE)));
			m_ctlTT.AddTool(GetDlgItem (IDC_FILE_IMAGE), m_ImageFile);
						
		}

	}
	
}

void CWECompressorTab2::OnBrowsePalette() 
{
	CString	Temp,TempMsg;
	int	Res;
		
	UpdateData(TRUE);

	if (m_AdvancedMode)
	{		
		Temp.LoadString(IDS_FILTER_BIN);
		CFileDialog MyFdlg(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_EXPLORER 
			| OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST ,(LPCTSTR) Temp, NULL);
	
		Temp.LoadString(IDS_INFO_TAB2_OPENPALETTE);
		MyFdlg.m_ofn.lpstrTitle = (LPCTSTR) Temp;
	
		//MyFdlg.m_ofn.lpstrInitialDir = m_nSelectedPath;

		// Invoke the dialog box
		Res = MyFdlg.DoModal();
		if (Res == IDOK)
		{	
			m_PaletteFile = MyFdlg.GetPathName();
		
			GetDlgItem(IDC_FILE_PALETTE)->EnableWindow(TRUE);
			m_FourthOK = TRUE;
			
			if (!m_ManualPalette)
			{
				if (SearchPalettes())
				{
					if (UpdateFileList(FALSE) == TRUE)
					{
						GetDlgItem(IDC_NUM_PALETTES)->ShowWindow(TRUE);
						GetDlgItem(IDC_LIST_PALETTES)->ShowWindow(TRUE);
			
					}
					OnChangeFocus(TRUE);
				}
				else
				{
					m_FourthOK = FALSE;
					GetDlgItem(IDC_FILE_PALETTE)->EnableWindow(FALSE);
					TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_INFO_NO_PALETTES_FOUND)) + "\n\n";
					MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_ERROR_MESSAGEBOX)), 		
							MB_ICONERROR);
				}

			}
			else
			{
				GetDlgItem(IDC_EDIT_OFFSET_PAL)->ShowWindow(TRUE);
				GetDlgItem(IDC_OFFSET_LAB2)->ShowWindow(TRUE);

			}

			if (m_FirstOK && (m_SecondOK || m_AutomaticPal) && m_ThirdOK)		
				GetDlgItem(IDC_BUTTON_MAKEFILE)->EnableWindow(TRUE);

			UpdateMyData(FALSE);
			if (m_ctlTT.IsExistTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_PALETTE))))
				m_ctlTT.RemoveTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_PALETTE)));			
			m_ctlTT.AddTool(GetDlgItem (IDC_FILE_PALETTE), m_PaletteFile);

		}
	}
	else
	{
		Temp.LoadString(IDS_FILTER_CLU);
		CFileDialog MyFdlg(FALSE, "clu" , "Custom", OFN_HIDEREADONLY | OFN_EXPLORER | 
						OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST , (LPCTSTR) Temp, NULL);	
	
		MyFdlg.m_ofn.lpstrTitle = (LPCTSTR) CString(MAKEINTRESOURCE(IDS_INFO_TAB2_NEWPAL));
	
		// Invoke the dialog box
		Res = MyFdlg.DoModal();
		if (Res == IDOK)
		{	
			m_PaletteFile = MyFdlg.GetPathName();
			GetDlgItem(IDC_FILE_PALETTE)->EnableWindow(TRUE);
			m_FourthOK = TRUE;
			if (m_FirstOK && (m_SecondOK || m_AutomaticPal) && m_ThirdOK)		
				GetDlgItem(IDC_BUTTON_MAKEFILE)->EnableWindow(TRUE);
			UpdateMyData(FALSE);
			if (m_ctlTT.IsExistTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_PALETTE))))
				m_ctlTT.RemoveTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_PALETTE)));			
			m_ctlTT.AddTool(GetDlgItem (IDC_FILE_PALETTE), m_PaletteFile);
						
		}
	}
	
}

void CWECompressorTab2::OnBrowseSrcImage() 
{
	CString	Temp,Temp2;
	int		Res;	
	
	UpdateData(TRUE);
	if (m_ComboIndex == 0)
	{
		Temp = CString(MAKEINTRESOURCE(IDS_FILTER_BMP));
		Temp2 = CString(MAKEINTRESOURCE(IDS_INFO_TAB2_OPENBMP));		
	}
	else
	if (m_ComboIndex == 1)
	{
		Temp = CString(MAKEINTRESOURCE(IDS_FILTER_TIM));
		Temp2 = CString(MAKEINTRESOURCE(IDS_INFO_TAB2_OPENTIM));		

	}
	else
	{
		Temp = CString(MAKEINTRESOURCE(IDS_FILTER_RAW));
		Temp2 = CString(MAKEINTRESOURCE(IDS_INFO_TAB2_OPENRAW));		
	}
	
	CFileDialog MyFdlg(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_EXPLORER 
		| OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST ,(LPCTSTR) Temp, NULL);
	
	MyFdlg.m_ofn.lpstrTitle = (LPCTSTR) Temp2;
	
	// Invoke the dialog box
	Res = MyFdlg.DoModal();
	if (Res == IDOK)
	{	
		m_SourceImageFile = MyFdlg.GetPathName();
		GetDlgItem(IDC_FILE_READIMAGE)->EnableWindow(TRUE);
		m_FirstOK = TRUE;
		
		if ((m_SecondOK || m_AutomaticPal) && m_ThirdOK && m_FourthOK)
				GetDlgItem(IDC_BUTTON_MAKEFILE)->EnableWindow(TRUE);
		if ((m_SecondOK || m_AutomaticPal))
			GetDlgItem(IDC_BUTTON_VIEWIMAGE)->EnableWindow(TRUE);

		UpdateMyData(FALSE);
		if (m_ctlTT.IsExistTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_READIMAGE))))
				m_ctlTT.RemoveTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_READIMAGE)));
		m_ctlTT.AddTool(GetDlgItem (IDC_FILE_READIMAGE), m_SourceImageFile);
						
	}
	
}

void CWECompressorTab2::OnBrowseSrcPalette() 
{
	CString	Temp,Temp2;
	int		Res;	
	
	UpdateData(TRUE);
	if (m_ComboPalIndex == 0)
	{
		Temp = CString(MAKEINTRESOURCE(IDS_FILTER_CLU));
		Temp2 = CString(MAKEINTRESOURCE(IDS_INFO_TAB2_OPENCLUT));		
	}
	else	
	{
		Temp = CString(MAKEINTRESOURCE(IDS_FILTER_PAL));
		Temp2 = CString(MAKEINTRESOURCE(IDS_INFO_TAB2_OPENPAL));		

	}
	
	CFileDialog MyFdlg(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_EXPLORER 
		| OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST ,(LPCTSTR) Temp, NULL);
	
	MyFdlg.m_ofn.lpstrTitle = (LPCTSTR) Temp2;
	
	// Invoke the dialog box
	Res = MyFdlg.DoModal();
	if (Res == IDOK)
	{	
		m_SourcePaletteFile = MyFdlg.GetPathName();
		GetDlgItem(IDC_FILE_READPAL)->EnableWindow(TRUE);
		m_SecondOK = TRUE;
		if (m_FirstOK && m_ThirdOK && m_FourthOK)
				GetDlgItem(IDC_BUTTON_MAKEFILE)->EnableWindow(TRUE);
		if (m_FirstOK)
			GetDlgItem(IDC_BUTTON_VIEWIMAGE)->EnableWindow(TRUE);

		UpdateMyData(FALSE);
		if (m_ctlTT.IsExistTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_READPAL))))
				m_ctlTT.RemoveTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_READPAL)));
		m_ctlTT.AddTool(GetDlgItem (IDC_FILE_READPAL), m_SourcePaletteFile);
						
	}
	
}

void CWECompressorTab2::OnChangeFocus(BOOL Select)
{
	UpdateData(TRUE);
	if (!m_ManualImage)
		m_ActualImagesIndex = m_ImagesList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	else
		m_ActualImagesIndex = 0;

	if (!m_ManualPalette)
		m_ActualPalettesIndex = m_PalettesList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	else
		m_ActualPalettesIndex = 0;

	if (Select)
	{
		if (m_ImagesList && (!m_ManualImage))
		{
			POSITION pos = m_ImageFileList.GetHeadPosition();//
		
			int i=0;
			BYTE factor;
			CString temp;

			if (m_ManualPalette)
			{
				UINT m_BitPalette;

				if (m_BitPalette == 0)
				{
					factor = 4;
					m_ActualColorsNumber = 16;
				}
				else
				{
					factor = 2;
					m_ActualColorsNumber = 256;
				}
			}
			else
				factor = m_PaletteFileList.GetAt(m_PaletteFileList.FindIndex(m_ActualPalettesIndex))->m_MultiplyFactor;

			while (pos != NULL)
			{				
				CFilesStruct* p_Images = m_ImageFileList.GetNext(pos);
					
				temp.Format("%u", p_Images->m_Header.width*factor);
				m_ImagesList.SetItemText(i++, 2, temp);
							
			}			
		
		}
	}

	UpdateData(FALSE);
	
}

void CWECompressorTab2::OnButtonMakeFile() 
{
	CString TempMsg;

	UpdateData(TRUE);
	if (m_AdvancedMode)
	{
		if (m_ManualImage)
			SetManualImage();
		if (m_ManualPalette)
			SetManualPalette();
		if ( !InsertInFiles() )
		{
			TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_ERROR_TAB2_INSERTBIN)) + "\n\n";
			MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_ERROR_MESSAGEBOX)), 		
						MB_ICONERROR);
		}
		else
		{
			TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_INFO_INSERTBIN_OK)) + "\n\n";
			MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_INFO_INSERTBIN_OK)), 
						MB_ICONINFORMATION);
		}


	}
	else
	{
		if ( !CreateFiles() )
		{
			TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_ERROR_TAB2_MAKEBIN)) + "\n\n";
			MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_ERROR_MESSAGEBOX)), 		
						MB_ICONERROR);
		}
		else
		{
			TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_INFO_MAKEBIN_OK)) + "\n\n";
			MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_INFO_MAKEBIN_OK)), 
						MB_ICONINFORMATION);
		}

	}


}

void CWECompressorTab2::OnButtonViewImage() 
{
	CString TempName;
	char tmPath[255];
	
	UpdateData(TRUE);
	if (m_ManualImage)
		SetManualImage();
	if (m_ManualPalette)
		SetManualPalette();
	// Prepare Temp File
	GetTempPath(255, tmPath);
	TempName = CString(tmPath) + "WECompr.tmp";	
	if (CreateBMP(TempName))
	{
		CBitmapDialog dlg(TempName,0,0,m_ActualColorsNumber);

		dlg.DoModal();
	}
	
}

void CWECompressorTab2::OnClickListImages(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnChangeFocus(FALSE);
	
	*pResult = 0;
}

void CWECompressorTab2::OnRclickListImages(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnChangeFocus(FALSE);
	
	*pResult = 0;
}

void CWECompressorTab2::OnKeydownListImages(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;

	OnChangeFocus(FALSE);

	*pResult = 0;
}

void CWECompressorTab2::OnClickListPalettes(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnChangeFocus(TRUE);
	
	*pResult = 0;
}


void CWECompressorTab2::OnRclickListPalettes(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnChangeFocus(TRUE);
	
	*pResult = 0;
}

void CWECompressorTab2::OnKeydownListPalettes(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	
	OnChangeFocus(TRUE);
	
	*pResult = 0;
}


void CWECompressorTab2::OnSelchangeComboSelfile() 
{
	CString TempMsg;

	TempMsg = CString(MAKEINTRESOURCE(IDS_HELP_INFORMATION_TITLE));
	UpdateData(TRUE);	
	m_ctlTT.RemoveTool(m_ctlTT.FindTool(GetDlgItem(IDC_SELBUTTON)));
		
	GetDlgItem(IDC_CHECK_AUTOPAL)->EnableWindow(TRUE);
	if (m_ComboIndex == 0)
		m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON), 
					TempMsg + CString(MAKEINTRESOURCE(IDS_HELP_TAB2_SELBUTTON)), IDI_PP_INFORMATION);
	else
	if (m_ComboIndex == 1)
		m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON), 
					TempMsg + CString(MAKEINTRESOURCE(IDS_HELP_TAB2_SELBUTTONB)), IDI_PP_INFORMATION);
	else
	{
		m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON), 
					TempMsg + CString(MAKEINTRESOURCE(IDS_HELP_TAB2_SELBUTTONC)), IDI_PP_INFORMATION);	
		if (m_AutomaticPal)
		{
			m_AutomaticPal = FALSE;
			UpdateData(FALSE);
			OnCheckAutopal();
		}
	}
	
}

void CWECompressorTab2::OnSelchangeComboSelpal() 
{
	CString TempMsg;

	TempMsg = _T("<u><b>Informazione</b></u><br><br>");
	UpdateData(TRUE);	
	m_ctlTT.RemoveTool(m_ctlTT.FindTool(GetDlgItem(IDC_SELBUTTON2)));
	
	if (m_ComboPalIndex == 0)
		m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON2), 
					TempMsg + CString(MAKEINTRESOURCE(IDS_HELP_TAB2_SELBUTTON2)), IDI_PP_INFORMATION);
	else
		m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON2), 
					TempMsg + CString(MAKEINTRESOURCE(IDS_HELP_TAB2_SELBUTTON2B)), IDI_PP_INFORMATION);
		
}

void CWECompressorTab2::OnClickManualImages() 
{
	UpdateData(TRUE);
	if ((m_ManualImage) && (m_ThirdOK))
	{
		if (m_ImagesList)
			m_ImagesList.DeleteAllItems();
		FreeListMem(TRUE);	
		GetDlgItem(IDC_NUM_IMAGES)->ShowWindow(FALSE);
		GetDlgItem(IDC_LIST_IMAGES)->ShowWindow(FALSE);		
		GetDlgItem(IDC_EDIT_OFFSET_IMAGES)->ShowWindow(TRUE);		
		GetDlgItem(IDC_OFFSET_LAB1)->ShowWindow(TRUE);

	}
	else
	{
		if ((m_ThirdOK) && (m_ImagesList.GetItemCount() > 0))
		{
			GetDlgItem(IDC_NUM_IMAGES)->ShowWindow(TRUE);
			GetDlgItem(IDC_LIST_IMAGES)->ShowWindow(TRUE);
		}
		GetDlgItem(IDC_EDIT_OFFSET_IMAGES)->ShowWindow(FALSE);		
		GetDlgItem(IDC_OFFSET_LAB1)->ShowWindow(FALSE);

	}
	
}

void CWECompressorTab2::OnClickManualPalette() 
{	
	UpdateData(TRUE);
	if ((m_ManualPalette) && (m_FourthOK))
	{
		GetDlgItem(IDC_NUM_PALETTES)->ShowWindow(FALSE);
		GetDlgItem(IDC_LIST_PALETTES)->ShowWindow(FALSE);		
		GetDlgItem(IDC_EDIT_OFFSET_PAL)->ShowWindow(TRUE);		
		GetDlgItem(IDC_OFFSET_LAB2)->ShowWindow(TRUE);

	}
	else
	{
		if ((m_FourthOK) && (m_PalettesList.GetItemCount() > 0))
		{
			GetDlgItem(IDC_NUM_PALETTES)->ShowWindow(TRUE);
			GetDlgItem(IDC_LIST_PALETTES)->ShowWindow(TRUE);
		}
		GetDlgItem(IDC_EDIT_OFFSET_PAL)->ShowWindow(FALSE);		
		GetDlgItem(IDC_OFFSET_LAB2)->ShowWindow(FALSE);		
		
	}
	
		
}

void CWECompressorTab2::OnCheckAutopal() 
{
	UpdateData(TRUE);
	if (m_ComboIndex == 2)
	{
		m_AutomaticPal = FALSE;
		GetDlgItem(IDC_CHECK_AUTOPAL)->EnableWindow(FALSE);
		UpdateData(FALSE);
	}

	if (m_AutomaticPal)
	{
		GetDlgItem(IDC_PALETTE_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_SELPAL)->EnableWindow(FALSE);		
		GetDlgItem(IDC_SELBUTTON2)->EnableWindow(FALSE);		

	}
	else
	{
		GetDlgItem(IDC_PALETTE_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_SELPAL)->EnableWindow(TRUE);		
		GetDlgItem(IDC_SELBUTTON2)->EnableWindow(TRUE);
		
		
	}
	
}

void CWECompressorTab2::OnClickAdvanced() 
{
	CString TempMsg;

	TempMsg = _T("<u><b>Informazione</b></u><br><br>");	
	UpdateData(TRUE);	
	m_ctlTT.RemoveTool(m_ctlTT.FindTool(GetDlgItem(IDC_SELBUTTON3)));
	m_ctlTT.RemoveTool(m_ctlTT.FindTool(GetDlgItem(IDC_SELBUTTON4)));
	m_ctlTT.RemoveTool(m_ctlTT.FindTool(GetDlgItem(IDC_BUTTON_MAKEFILE)));
	GetDlgItem(IDC_FILE_IMAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_FILE_PALETTE)->EnableWindow(FALSE);
	m_ThirdOK = FALSE;	
	m_FourthOK = FALSE;
	if (m_AdvancedMode)
	{
		m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON3), 
				TempMsg + CString(MAKEINTRESOURCE(IDS_HELP_TAB2_SELBUTTON3)), IDI_PP_INFORMATION);
		m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON4), 
				TempMsg + CString(MAKEINTRESOURCE(IDS_HELP_TAB2_SELBUTTON4)), IDI_PP_INFORMATION);
		m_ctlTT.AddTool(GetDlgItem(IDC_BUTTON_MAKEFILE), 
				TempMsg + CString(MAKEINTRESOURCE(IDS_HELP_TAB2_INSERTFILE)), IDI_PP_INFORMATION);
		GetDlgItem(IDC_BUTTON_MAKEFILE)->SetWindowText(CString(MAKEINTRESOURCE(IDS_BUTTON_TAB2_INSERTFILE)));
		GetDlgItem(IDC_CHECK_AUTOPAL)->EnableWindow(TRUE);
		GetDlgItem(IDC_MANUAL_IMAGES)->EnableWindow(TRUE);
		GetDlgItem(IDC_MANUAL_PALETTE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_SELGAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_SHIRT_TEX)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_IMAGEANDPAL)->EnableWindow(TRUE);
		GetDlgItem(IDC_TITLE_IMAGE)->SetWindowText(CString(MAKEINTRESOURCE(IDS_INFO_TAB2_TITLE1)));
		GetDlgItem(IDC_TITLE_PALETTE)->SetWindowText(CString(MAKEINTRESOURCE(IDS_INFO_TAB2_PALETTE1)));
		OnCheckAutopal();
		OnClickManualPalette();
		OnClickManualImages();

	}
	else
	{
		m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON3), 
				TempMsg + CString(MAKEINTRESOURCE(IDS_HELP_TAB2_SELBUTTON3B)), IDI_PP_INFORMATION);
		m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON4), 
				TempMsg + CString(MAKEINTRESOURCE(IDS_HELP_TAB2_SELBUTTON4B)), IDI_PP_INFORMATION);
		m_ctlTT.AddTool(GetDlgItem(IDC_BUTTON_MAKEFILE), 
				TempMsg + CString(MAKEINTRESOURCE(IDS_HELP_TAB2_MAKEFILE)), IDI_PP_INFORMATION);
		GetDlgItem(IDC_BUTTON_MAKEFILE)->SetWindowText(CString(MAKEINTRESOURCE(IDS_BUTTON_TAB2_MAKEFILE)));
		GetDlgItem(IDC_TITLE_IMAGE)->SetWindowText(CString(MAKEINTRESOURCE(IDS_INFO_TAB2_TITLE2)));
		GetDlgItem(IDC_TITLE_PALETTE)->SetWindowText(CString(MAKEINTRESOURCE(IDS_INFO_TAB2_PALETTE2)));

		GetDlgItem(IDC_NUM_PALETTES)->ShowWindow(FALSE);
		GetDlgItem(IDC_LIST_PALETTES)->ShowWindow(FALSE);
		GetDlgItem(IDC_NUM_IMAGES)->ShowWindow(FALSE);
		GetDlgItem(IDC_LIST_IMAGES)->ShowWindow(FALSE);		
		GetDlgItem(IDC_EDIT_OFFSET_PAL)->ShowWindow(FALSE);		
		GetDlgItem(IDC_OFFSET_LAB2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_OFFSET_IMAGES)->ShowWindow(FALSE);		
		GetDlgItem(IDC_OFFSET_LAB1)->ShowWindow(FALSE);
		GetDlgItem(IDC_CHECK_AUTOPAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_MANUAL_IMAGES)->EnableWindow(FALSE);
		GetDlgItem(IDC_MANUAL_PALETTE)->EnableWindow(FALSE);
		GetDlgItem(IDC_PALETTE_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_SELPAL)->EnableWindow(FALSE);		
		GetDlgItem(IDC_SELBUTTON2)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_SELGAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_SHIRT_TEX)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_IMAGEANDPAL)->EnableWindow(FALSE);
		m_UseSameFile = FALSE;
		UpdateData(FALSE);
		OnCheckImageAndPal();
		
	}
		

}

void CWECompressorTab2::OnCheckImageAndPal() 
{
	CString StrTemp;

	UpdateData(TRUE);
	if (m_UseSameFile)
	{
		GetDlgItem(IDC_FILE_PALETTE)->EnableWindow(FALSE);
		GetDlgItem(IDC_SELBUTTON4)->EnableWindow(FALSE);		

	}
	else
	{
		GetDlgItem(IDC_SELBUTTON4)->EnableWindow(TRUE);		
		GetDlgItem(IDC_FILE_PALETTE)->GetWindowText(StrTemp);
		if (StrTemp != CString(MAKEINTRESOURCE(IDS_NAME_NOFILE)))
			GetDlgItem(IDC_FILE_PALETTE)->EnableWindow(TRUE);
			
	}
			
}

void CWECompressorTab2::OnChangeGameSel() 
{
	UpdateData(TRUE);
	if (m_ComboGame == 1)
		GetDlgItem(IDC_SHIRT_TEX)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_SHIRT_TEX)->EnableWindow(FALSE);
	
}

BOOL CWECompressorTab2::PreTranslateMessage(MSG* pMsg) 
{
	m_ctlTT.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

void CWECompressorTab2::OnQuit() 
{
	AfxGetMainWnd()->SendMessage(WM_CLOSE, 0, 0);
	
}
