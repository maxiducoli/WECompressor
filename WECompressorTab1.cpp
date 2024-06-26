// WECompressorTab1.cpp : implementation file
//

#include "stdafx.h"
#include "WECompressor.h"
#include "XTabCtrl.h"
#include "WECompressorTab1.h"
#include "AboutDialog.h"
#include "WECompress.h"
#include "BitmapDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWECompressorTab1 dialog


CWECompressorTab1::CWECompressorTab1(CWnd* pParent /*=NULL*/)
	: CDialog(CWECompressorTab1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWECompressorTab1)
		m_ComboIndex = 0;
		m_ManualImage = FALSE;
		m_ManualPalette = FALSE;
		m_OffsetImage = _T("30");
		m_OffsetPal = _T("25EC");
		m_BitPalette = 1;
		m_ImageX = 128;
		m_ImageY = 128;
		m_ComboGame = 0;
		m_EnableTex = FALSE;
		m_UseSameFile = FALSE;
	//}}AFX_DATA_INIT
	m_ImageFile = CString(" ");
	m_PaletteFile = CString(" ");
	m_DestFile = CString(" ");
	m_ActualImagesIndex = 0;
	m_ActualPalettesIndex = 0;
	m_ActualColorsNumber = 0;
	
	m_FirstOK = FALSE;
	m_SecondOK = FALSE;
	m_ThirdOK = FALSE;
	m_pTab = NULL;
}

CWECompressorTab1::~CWECompressorTab1()
{
	UpdateData(TRUE);
	if (m_ImagesList)
		m_ImagesList.DeleteAllItems();
	if (m_PalettesList)
		m_PalettesList.DeleteAllItems();
	FreeListMem(TRUE);
	FreeListMem(FALSE);
	
}

void CWECompressorTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWECompressorTab1)		
	DDX_Control(pDX, IDC_LIST_PALETTES, m_PalettesList);
	DDX_Control(pDX, IDC_LIST_IMAGES, m_ImagesList);
	DDX_CBIndex(pDX, IDC_COMBO_SELFILE, m_ComboIndex);
	DDX_Check(pDX, IDC_MANUAL_IMAGES, m_ManualImage);
	DDX_Check(pDX, IDC_MANUAL_PALETTE, m_ManualPalette);
	DDX_Text(pDX, IDC_EDIT_OFFSET_IMAGES, m_OffsetImage);
	DDX_Text(pDX, IDC_EDIT_OFFSET_PAL, m_OffsetPal);
	DDX_CBIndex(pDX, IDC_COMBO_PALETTE, m_BitPalette);
	DDX_Text(pDX, IDC_EDIT_X, m_ImageX);
	DDV_MinMaxInt(pDX, m_ImageX, 1, 256);
	DDX_Text(pDX, IDC_EDIT_Y, m_ImageY);
	DDV_MinMaxInt(pDX, m_ImageY, 1, 256);
	DDX_CBIndex(pDX, IDC_COMBO_SELGAME, m_ComboGame);
	DDX_Check(pDX, IDC_SHIRT_TEXTURE, m_EnableTex);
	DDX_Check(pDX, IDC_CHECK_IMAGEANDPAL, m_UseSameFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWECompressorTab1, CDialog)
	//{{AFX_MSG_MAP(CWECompressorTab1)
		ON_BN_CLICKED(ID_INFO, OnInfo)
		ON_BN_CLICKED(IDC_SELBUTTON, OnBrowseImage)
		ON_BN_CLICKED(IDC_SELBUTTON2, OnBrowsePalette)
		ON_BN_CLICKED(IDC_SELBUTTON3, OnBrowseDest)
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
	ON_CBN_SELCHANGE(IDC_COMBO_PALETTE, OnSelchangeComboPalette)
	ON_CBN_SELCHANGE(IDC_COMBO_SELGAME, OnChangeGameSel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PALETTES, OnDblClickListPalettes)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_IMAGES, OnDblClickListImages)
	ON_BN_CLICKED(IDC_CHECK_IMAGEANDPAL, OnCheckImageAndPal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWECompressorTab1 message handlers

BOOL CWECompressorTab1::OnInitDialog()
{
	CDialog::OnInitDialog();

	// load CButtonST
	m_FOpenFirst.SubclassDlgItem(IDC_SELBUTTON, this);
	m_FOpenFirst.SetIcon(IDI_SELFILE); 

	m_FOpenSec.SubclassDlgItem(IDC_SELBUTTON2, this);
	m_FOpenSec.SetIcon(IDI_SELFILE);

	m_FOpenThird.SubclassDlgItem(IDC_SELBUTTON3, this);
	m_FOpenThird.SetIcon(IDI_SELFILE);

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

void CWECompressorTab1::AddHelpTTips()
{
	CString Temp;
	//PPTOOLTIP_INFO ti;
	m_ctlTT.Create (this);

	Temp = CString(MAKEINTRESOURCE(IDS_HELP_INFORMATION_TITLE));
	m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB1_SELBUTTON)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON2), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB1_SELBUTTON2)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON3), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB1_SELBUTTON3)), IDI_PP_INFORMATION);
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
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB1_SELFILE)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_COMBO_SELGAME), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB1_SELGAME)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_SHIRT_TEXTURE), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB1_TEXSHIRT)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_CHECK_IMAGEANDPAL), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB_IMAGEPAL)), IDI_PP_INFORMATION);	
	m_ctlTT.AddTool(GetDlgItem(IDC_BUTTON_VIEWIMAGE), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB1_VIEW)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(ID_INFO), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_INFO)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDC_BUTTON_MAKEFILE), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_TAB1_MAKEFILE)), IDI_PP_INFORMATION);
	m_ctlTT.AddTool(GetDlgItem(IDOK), 
						Temp + CString(MAKEINTRESOURCE(IDS_HELP_EXIT)), IDI_PP_INFORMATION);
	//m_ctlTT.AddTool(m_pTab->GetDlgItem(IDC_WECOMPRESSOR), 
	//					Temp + CString(MAKEINTRESOURCE(IDS_HELP_WECOMPRESSOR)), IDI_PP_INFORMATION);

	UpdateData(FALSE);
	
}

void CWECompressorTab1::OnInfo() 
{
	CAboutDialog dlgAbout;
	dlgAbout.DoModal();
	
}

void CWECompressorTab1::FreeListMem(BOOL Select)
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

BOOL CWECompressorTab1::UpdateMyData(BOOL bValid)
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
				PathCompactPathEx(tempPath, m_ImageFile, 54, '\\');
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
				PathCompactPathEx(tempPath, m_PaletteFile, 54, '\\');
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

	if (GetDlgItem(IDC_FILE_TIM)->IsWindowEnabled() == TRUE)
	{
		if (bValid == FALSE)
		{			
			if (m_DestFile == "")
				GetDlgItem(IDC_FILE_TIM)->SetWindowText(
													CString(MAKEINTRESOURCE(IDS_NAME_NOFILE)));
			else
			{					
				PathCompactPathEx(tempPath, m_DestFile, 54, '\\');
				GetDlgItem(IDC_FILE_TIM)->SetWindowText(CString(tempPath));				
			}			

		}
		else
		{
			GetDlgItem(IDC_FILE_TIM)->GetWindowText(tempStr);
			if (tempStr == CString(MAKEINTRESOURCE(IDS_NAME_NOFILE)))		
				m_DestFile = CString("");

		}
	}

	bTemp = TRUE;
	bTemp = UpdateData(bValid) && bTemp;

	return bTemp;
}

BOOL CWECompressorTab1::OffsetMatch(BYTE Code) 
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

BOOL CWECompressorTab1::OffsetTranslate(BYTE Code,ULONG *Offset)
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

BOOL CWECompressorTab1::SearchImages() 
{
	CFile	fSource;
	CString TempMsg;
	CFileException e;
	UINT nSize,i;

	UpdateData(TRUE);
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
			
		  	if (fe->m_BlockLen > 0)
			{
				(BYTE*) fe->m_DataBlock = new BYTE[fe->m_BlockLen];
				memcpy(fe->m_DataBlock,pCur + fe->m_OffsetReal, fe->m_BlockLen);
			}
			
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

BOOL CWECompressorTab1::SearchPalettes() 
{
	CFile	fSource;
	CString TempMsg;
	CFileException e;
	UINT nSize,i;

	UpdateData(TRUE);
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
				fe->m_MultiplyFactor = 4;//4;
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

BOOL CWECompressorTab1::SetManualImage()
{	
	CFile	fSource;	
	CFileException e;
	UINT nSize,i;

	UpdateData(TRUE);
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

	// Make the header!!!!
	CFilesStruct *fe = new CFilesStruct();
	ZeroMemory(&fe->m_Header,sizeof(DATA_HEADER));
	fe->m_Header.ID = 10;	
	fe->m_Header.width = m_ImageX / 2;
	fe->m_Header.height = m_ImageY;
	fe->m_Header.VramX = 576;
	fe->m_Header.VramY = 256;
	//fe->m_Header.offset = strtol(TempNum, NULL, 16);
	fe->m_Header.separator = 32783;
	fe->m_Header.unknown5 = 255;

	fe->m_OffsetReal = strtol(m_OffsetImage, NULL, 16);//fe->m_Header.offset;
	
	CWECompress tempclass;
	BYTE* tempblock = new BYTE[fe->m_Header.height*fe->m_Header.width*2];
	memcpy(tempblock,pCur + fe->m_OffsetReal, fe->m_Header.height*fe->m_Header.width*2);
	fe->m_BlockLen = tempclass.FindCompressedLength(tempblock);//i - fe->m_OffsetReal;
	delete tempblock;

	if (fe->m_Header.height < 128)
		fe->m_MultiplyY = (128 / fe->m_Header.height);
	else
		fe->m_MultiplyY = 1;
			
	if (fe->m_BlockLen > 0)
	{
		(BYTE*) fe->m_DataBlock = new BYTE[fe->m_BlockLen];
		memcpy(fe->m_DataBlock,pCur + fe->m_OffsetReal, fe->m_BlockLen);
	}
	
	m_ImageFileList.AddTail(fe);

	/////////
	delete rbuf;	
	
	return TRUE;
}

BOOL CWECompressorTab1::SetManualPalette()
{	
	CFile	fSource;	
	CFileException e;
	UINT nSize,i;

	UpdateData(TRUE);
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

	// Make the header!!!!
	CFilesStruct *fe = new CFilesStruct();
	ZeroMemory(&fe->m_Header,sizeof(DATA_HEADER));
	fe->m_Header.ID = 65289;
	if (m_BitPalette == 0)
		fe->m_Header.width = 16;
	else
		fe->m_Header.width = 256;
	fe->m_Header.height = 1;
	fe->m_Header.VramX = 0;
	fe->m_Header.VramY = 486;
	//fe->m_Header.offset = strtol(m_OffsetPal, NULL, 16);
	fe->m_Header.separator = 32783;
	fe->m_Header.unknown5 = 255;

	fe->m_OffsetReal = strtol(m_OffsetPal, NULL, 16);//fe->m_Header.offset;
	
	if (fe->m_Header.width == 16)			
		fe->m_MultiplyFactor = 4;//4;
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

BOOL CWECompressorTab1::UpdateFileList(BOOL Select) 
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

BOOL CWECompressorTab1::CreateTIM(CString NameFile)
{
	CFile   NewFileTIM;	
	CString TempMsg;
	CFileException e;
	UINT i,multfact;
	
	// open data file to write
	if (!NewFileTIM.Open(NameFile, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + NameFile);
		return FALSE;
	}

	POSITION pos = m_PaletteFileList.GetHeadPosition();// Catch Palettes List Infos

	i=0;
	while (pos != NULL)
	{	
		CFilesStruct* p_Palettes = m_PaletteFileList.GetNext(pos);
		if  (i++ == m_ActualPalettesIndex)
		{
			TIM_HEADER THead;
			TIM_CLUTINFO TClut;
	
			// Write TIM header
			THead.id1 = TIM_ID1;
	
			if (p_Palettes->m_Header.width == 0x10)
				THead.type = TIM_4Bit;
			else
			 if (p_Palettes->m_Header.width == 0x100)
				THead.type = TIM_8Bit;
			  else
				if (p_Palettes->m_Header.width == 0x10000)
					THead.type = TIM_16Bit;
				else
					THead.type = TIM_24Bit;

			THead.nextlen = p_Palettes->m_BlockLen + 12;
			NewFileTIM.Write(&THead,sizeof( TIM_HEADER ));

			// write Clut Header
			TClut.vramx = p_Palettes->m_Header.VramX;
			TClut.vramy = p_Palettes->m_Header.VramY;
			TClut.ncols = p_Palettes->m_Header.width;
			TClut.npals = p_Palettes->m_Header.height;

			NewFileTIM.Write(&TClut,sizeof( TIM_CLUTINFO ));

			// write CLUT DATA
			NewFileTIM.Write(p_Palettes->m_DataBlock,p_Palettes->m_BlockLen);

			multfact = p_Palettes->m_MultiplyFactor;

		}
		
	}

	pos = m_ImageFileList.GetHeadPosition();// Catch Data List Infos

	i=0;
	while (pos != NULL)
	{		
		CFilesStruct* p_Images = m_ImageFileList.GetNext(pos);
		if  (i++ == m_ActualImagesIndex)
		{
			TIM_DATAINFO TData;
			ULONG DataLength;

			// write Data Header
			
			TData.vramx = p_Images->m_Header.VramX;
			TData.vramy = p_Images->m_Header.VramY;
			TData.xsize = p_Images->m_Header.width;
			TData.ysize = p_Images->m_Header.height*p_Images->m_MultiplyY;							
			DataLength = p_Images->m_Header.width*multfact*TData.ysize;
			if (multfact > 2)
				DataLength = DataLength / 2;
			TData.blocklen = DataLength + 12;

			NewFileTIM.Write(&TData,sizeof( TIM_DATAINFO ));

			CWECompress tempclass;
			BYTE* pData = new BYTE[DataLength];
			ZeroMemory(pData,DataLength);
			if (p_Images->m_BlockLen == 0)
			{
				delete pData;
				return FALSE;
			
			}
			tempclass.DeCompress(&pData,p_Images->m_DataBlock);
		
			// write Data Block
			NewFileTIM.Write(pData,DataLength);

			delete pData;

		}
		
	}

	NewFileTIM.Close();

	return TRUE;

}

BOOL CWECompressorTab1::CreateBMP(CString NameFile)
{
	CFile   NewFileBMP;	
	CString TempMsg;
	CFileException e;
	UINT i,j,multfact,planes,depth,totalheader,rgbsize,usedcol;
	ULONG xsize,ysize,imagesize,xtemp;
	BYTE rgbq[RGB_SIZE256];
	BYTE* pData;
	
	// open data file to write
	if (!NewFileBMP.Open(NameFile, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + NameFile);
		return FALSE;
	}

	POSITION pos = m_PaletteFileList.GetHeadPosition();// Catch Palettes List Infos

	i=0;
	totalheader = 0;
	rgbsize = 0;
	usedcol = 0;
	while (pos != NULL)
	{	
		CFilesStruct* p_Palettes = m_PaletteFileList.GetNext(pos);
		if  (i++ == m_ActualPalettesIndex)
		{
			if (p_Palettes->m_Header.width == 0x10)
			{
				depth = 4;
				usedcol = 16;
				totalheader = TOTAL_HEADER_SIZE16;
				rgbsize = RGB_SIZE16;
			}
			else
			if (p_Palettes->m_Header.width == 0x100)
			{
				depth = 8;
				usedcol = 256;
				totalheader = TOTAL_HEADER_SIZE256;
				rgbsize = RGB_SIZE256;
			}
			else
			if (p_Palettes->m_Header.width == 0x10000)
				depth = 16;
			else
				depth = 24;

			// write converted CLUT RGB table (psx uses 15bit RGB)
			for (WORD col=0; col < rgbsize; col+=4)
			{				
				WORD* tempword = new WORD;
				memcpy(tempword,p_Palettes->m_DataBlock + (col/2), 2);
				rgbq[col] = (*tempword>>10) << 3;
				rgbq[col+1] = ((*tempword>>5)&0x1f) << 3;
				rgbq[col+2] = ((*tempword)&0x1f) << 3;
				rgbq[col+3] = 0;

				delete tempword;
			}

			planes = p_Palettes->m_Header.height;
			multfact = p_Palettes->m_MultiplyFactor;
			m_ActualColorsNumber = usedcol;

		}
		
	}

	pos = m_ImageFileList.GetHeadPosition();// Catch Data List Infos

	i=0;
	while (pos != NULL)
	{		
		CFilesStruct* p_Images = m_ImageFileList.GetNext(pos);
		if  (i++ == m_ActualImagesIndex)
		{
			xsize = p_Images->m_Header.width*multfact;
			ysize = p_Images->m_Header.height*p_Images->m_MultiplyY;
			imagesize = xsize*ysize;

			CWECompress tempclass;
			(BYTE*) pData = new BYTE[imagesize];
			BYTE* pDataRev = new BYTE[imagesize];
			ZeroMemory(pDataRev,imagesize);
			if (p_Images->m_BlockLen == 0)
			{
				delete pDataRev;
				delete pData;
				return FALSE;
			
			}
			tempclass.DeCompress(&pDataRev,p_Images->m_DataBlock);
			
			// copy reverse data to pData
			j=0;
			if (multfact == 4)
			{
				// 4 bit
				xtemp = p_Images->m_Header.width*2;
				for(long y1=ysize-1;y1>=0;y1--)
				{
					for(unsigned long x1=0;x1<xtemp;x1++)
					{
						pData[j] = (pDataRev[(y1*xtemp)+x1])>>4;
						pData[j] |= ((pDataRev[(y1*xtemp)+x1] << 4) & 0xF0);
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
						pData[j++] = pDataRev[(y1*xtemp)+x1];}

			}
			
								
			delete pDataRev;

		}
		
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
	bmih.biCompression = BI_RGB;
	bmih.biSizeImage = (xsize*ysize*depth)/8;
	bmih.biXPelsPerMeter = 0;
	bmih.biYPelsPerMeter = 0;
	bmih.biClrUsed = usedcol;	
	bmih.biClrImportant = 0;
	
	NewFileBMP.Write(&bmih,sizeof( BITMAPINFOHEADER ));
		
	// write converted CLUT RGB table (psx uses 15bit RGB)
	NewFileBMP.Write(rgbq,rgbsize);

	// write Data block
	NewFileBMP.Write(pData,imagesize);

	delete pData;

	NewFileBMP.Close();

	return TRUE;

}

BOOL CWECompressorTab1::CreateRAW(CString NameFile)
{
	CFile   NewFileRAW,NewFilePAL,NewFileCLUT;
	CString TempMsg;
	CFileException e;
	UINT i,multfact,rgbsize;
	ULONG imagesize;
	BYTE rgbq[RGB_SIZE256];
	BYTE* pData;
	
	// open data file to write
	if (!NewFileRAW.Open(NameFile, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + NameFile);
		return FALSE;
	}

	NameFile.Replace(".raw",".pal");
	// open palette file to write
	if (!NewFilePAL.Open(NameFile, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + NameFile);
		return FALSE;
	}

	NameFile.Replace(".pal",".clu");
	// open palette file to write
	if (!NewFileCLUT.Open(NameFile, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + NameFile);
		return FALSE;
	}

	POSITION pos = m_PaletteFileList.GetHeadPosition();// Catch Palettes List Infos

	i=0;
	while (pos != NULL)
	{	
		CFilesStruct* p_Palettes = m_PaletteFileList.GetNext(pos);
		if  (i++ == m_ActualPalettesIndex)
		{
			if (p_Palettes->m_Header.width == 0x10)
				rgbsize = RGB_SIZE16;
			else
				rgbsize = RGB_SIZE256;
			
			// write converted CLUT RGB table (psx uses 15bit RGB)
			for (WORD col=0; col < rgbsize; col+=4)
			{				
				WORD* tempword = new WORD;
				memcpy(tempword,p_Palettes->m_DataBlock + (col/2), 2);
				rgbq[col] = (*tempword>>10) << 3;
				rgbq[col+1] = ((*tempword>>5)&0x1f) << 3;
				rgbq[col+2] = ((*tempword)&0x1f) << 3;
				rgbq[col+3] = 0;

				delete tempword;
			}

			// write PAL DATA
			NewFilePAL.Write(rgbq,rgbsize);			

			// write CLUT DATA
			NewFileCLUT.Write(p_Palettes->m_DataBlock,p_Palettes->m_BlockLen);

			multfact = p_Palettes->m_MultiplyFactor;

		}
		
	}

	pos = m_ImageFileList.GetHeadPosition();// Catch Data List Infos

	i=0;
	while (pos != NULL)
	{		
		CFilesStruct* p_Images = m_ImageFileList.GetNext(pos);
		if  (i++ == m_ActualImagesIndex)
		{
			imagesize = 
				p_Images->m_Header.width*multfact*p_Images->m_Header.height*p_Images->m_MultiplyY;
			
			CWECompress tempclass;
			(BYTE*) pData = new BYTE[imagesize];			
			ZeroMemory(pData,imagesize);
			if (p_Images->m_BlockLen == 0)
			{
				delete pData;
				return FALSE;
			
			}
			tempclass.DeCompress(&pData,p_Images->m_DataBlock);

			// write Data block
			NewFileRAW.Write(pData,imagesize);

			delete pData;

		}
		
	}		

	NewFileRAW.Close();
	NewFilePAL.Close();
	NewFileCLUT.Close();

	return TRUE;

}

BOOL CWECompressorTab1::CreateTXT(CString NameFile)
{
	CFile   NewFileTXT;
	CString TempMsg,TempMsg2;
	CFileException e;
	UINT i,lenrow;
	
	// open data file to write
	if (!NewFileTXT.Open(NameFile, CFile::modeCreate | CFile::modeWrite | CFile::typeText, &e))
	{
		AfxMessageBox(_T("Error writing ") + NameFile);
		return FALSE;
	}

	TempMsg = CString(MAKEINTRESOURCE(IDS_INFO_TXT_GRAPHICS)) + m_ImageFile + "\r\n";
	NewFileTXT.Write(TempMsg,TempMsg.GetLength());
	TempMsg2 = "";
	for (i=0;i<TempMsg.GetLength() - 2;i++)
		TempMsg2 += '-';
	TempMsg2+="\r\n";
	NewFileTXT.Write(TempMsg2,TempMsg2.GetLength());
	TempMsg2= "  ID    ";
	TempMsg2+= CString(MAKEINTRESOURCE(IDS_IMAGETABCOL2));
	TempMsg2+= "   " + CString(MAKEINTRESOURCE(IDS_IMAGETABCOL3));
	TempMsg2+= "  " + CString(MAKEINTRESOURCE(IDS_IMAGETABCOL4));
	TempMsg2+= "  " + CString(MAKEINTRESOURCE(IDS_IMAGETABCOL5));
	TempMsg2+= " " + CString(MAKEINTRESOURCE(IDS_IMAGETABCOL6));
	TempMsg2+= "  " + CString(MAKEINTRESOURCE(IDS_IMAGETABCOL7));
	TempMsg2+= "  " + CString(MAKEINTRESOURCE(IDS_IMAGETABCOL8));
	TempMsg2+="\r\n";
	lenrow = TempMsg2.GetLength();
	for (i=0;i<lenrow;i++)
		TempMsg2 += '-';
	TempMsg2+="\r\n";
	NewFileTXT.Write(TempMsg2,TempMsg2.GetLength());
	
	POSITION pos = m_ImageFileList.GetHeadPosition();// Catch Data List Infos

	i=0;
	while (pos != NULL)
	{		
		CFilesStruct* p_Images = m_ImageFileList.GetNext(pos);
		POSITION pos2 = m_PaletteFileList.GetHeadPosition();
		CFilesStruct* p_Palettes = m_PaletteFileList.GetNext(pos2);
							 
		TempMsg2.Format("  %2d    %6x    %3u    %3u    %3u    %3u     %8u     0x%4x\r\n",
			(1 + i++),p_Images->m_OffsetReal,
			p_Images->m_Header.width*p_Palettes->m_MultiplyFactor,
			p_Images->m_Header.height*p_Images->m_MultiplyY,p_Images->m_Header.VramX,
			p_Images->m_Header.VramY,p_Images->m_BlockLen,p_Images->m_Header.separator);	
		NewFileTXT.Write(TempMsg2,TempMsg2.GetLength());
		
	}

	TempMsg2 ="";
	for (i=0;i<lenrow;i++)
		TempMsg2 += '-';
	TempMsg2+="\r\n\r\n";
	NewFileTXT.Write(TempMsg2,TempMsg2.GetLength());

	TempMsg = CString(MAKEINTRESOURCE(IDS_INFO_TXT_PALETTES)) + m_PaletteFile + "\r\n";
	NewFileTXT.Write(TempMsg,TempMsg.GetLength());
	TempMsg2 = "";
	for (i=0;i<TempMsg.GetLength() - 2;i++)
		TempMsg2 += '-';
	TempMsg2+="\r\n";
	NewFileTXT.Write(TempMsg2,TempMsg2.GetLength());
	TempMsg2= "  ID    ";
	TempMsg2+= CString(MAKEINTRESOURCE(IDS_PALTABCOL2));
	TempMsg2+= "   " + CString(MAKEINTRESOURCE(IDS_PALTABCOL3));
	TempMsg2+= "   " + CString(MAKEINTRESOURCE(IDS_PALTABCOL4));
	TempMsg2+= " " + CString(MAKEINTRESOURCE(IDS_PALTABCOL5));
	TempMsg2+= " " + CString(MAKEINTRESOURCE(IDS_PALTABCOL6));
	TempMsg2+= "  " + CString(MAKEINTRESOURCE(IDS_PALTABCOL7));
	TempMsg2+= "  " + CString(MAKEINTRESOURCE(IDS_PALTABCOL8));
	TempMsg2+= "  " + CString(MAKEINTRESOURCE(IDS_PALTABCOL9));
	TempMsg2+="\r\n";
	lenrow = TempMsg2.GetLength();
	for (i=0;i<lenrow;i++)
		TempMsg2 += '-';
	TempMsg2+="\r\n";
	NewFileTXT.Write(TempMsg2,TempMsg2.GetLength());
	
	pos = m_PaletteFileList.GetHeadPosition();// Catch Data List Infos

	i=0;
	while (pos != NULL)
	{		
		CFilesStruct* p_Palettes = m_PaletteFileList.GetNext(pos);
			
		TempMsg2.Format("  %2d    %6x    %3u    %3u    %3u    %3u   %3u  %8u        0x%4x\r\n",
			(1 + i++),p_Palettes->m_OffsetReal,p_Palettes->m_Header.ID >> 8,
			p_Palettes->m_Header.VramX,p_Palettes->m_Header.VramY,
			p_Palettes->m_Header.width,p_Palettes->m_Header.height,p_Palettes->m_BlockLen,
			p_Palettes->m_Header.separator);	
		NewFileTXT.Write(TempMsg2,TempMsg2.GetLength());
		
	}

	TempMsg2 ="";
	for (i=0;i<lenrow;i++)
		TempMsg2 += '-';
	TempMsg2+="\r\n";
	NewFileTXT.Write(TempMsg2,TempMsg2.GetLength());
	
	NewFileTXT.Close();

	return TRUE;

		
}

void CWECompressorTab1::OnBrowseImage() 
{
	CString	Temp,TempMsg;
	int	Res;
			
	Temp.LoadString(IDS_FILTER_BIN);
	CFileDialog MyFdlg(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_EXPLORER 
		| OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST ,(LPCTSTR) Temp, NULL);
	
	Temp.LoadString(IDS_INFO_TAB1_OPENIMAGE);
	MyFdlg.m_ofn.lpstrTitle = (LPCTSTR) Temp;
	
	//MyFdlg.m_ofn.lpstrInitialDir = m_nSelectedPath;

	// Invoke the dialog box
	UpdateData(TRUE);
	Res = MyFdlg.DoModal();
	if (Res == IDOK)
	{	
		m_ImageFile = MyFdlg.GetPathName();
		GetDlgItem(IDC_FILE_IMAGE)->EnableWindow(TRUE);
		m_FirstOK = TRUE;

		if (m_UseSameFile)
		{
			m_PaletteFile = m_ImageFile;

			GetDlgItem(IDC_FILE_PALETTE)->EnableWindow(TRUE);
			m_SecondOK = TRUE;
		
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
					m_SecondOK = FALSE;
					GetDlgItem(IDC_FILE_PALETTE)->EnableWindow(FALSE);
					TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_INFO_NO_PALETTES_FOUND)) + "\n\n";
					MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_ERROR_MESSAGEBOX)), 		
							MB_ICONERROR);
				}

			}
			else
			{
				GetDlgItem(IDC_EDIT_OFFSET_PAL)->ShowWindow(TRUE);
				GetDlgItem(IDC_COMBO_PALETTE)->ShowWindow(TRUE);
				GetDlgItem(IDC_OFFSET_LAB2)->ShowWindow(TRUE);
				GetDlgItem(IDC_PALLAB)->ShowWindow(TRUE);
			}

			UpdateMyData(FALSE);
			if (m_ctlTT.IsExistTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_PALETTE))))
				m_ctlTT.RemoveTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_PALETTE)));;			
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
				m_FirstOK = FALSE;
				GetDlgItem(IDC_FILE_IMAGE)->EnableWindow(FALSE);
				TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_INFO_NO_IMAGES_FOUND)) + "\n\n";
				MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_ERROR_MESSAGEBOX)), 		
						MB_ICONERROR);
			}


		}
		else
		{
			GetDlgItem(IDC_EDIT_OFFSET_IMAGES)->ShowWindow(TRUE);
			GetDlgItem(IDC_EDIT_X)->ShowWindow(TRUE);
			GetDlgItem(IDC_EDIT_Y)->ShowWindow(TRUE);
			GetDlgItem(IDC_XXLAB)->ShowWindow(TRUE);
			GetDlgItem(IDC_XLAB)->ShowWindow(TRUE);
			GetDlgItem(IDC_YLAB)->ShowWindow(TRUE);
			GetDlgItem(IDC_OFFSET_LAB1)->ShowWindow(TRUE);
		}

		if (m_SecondOK && m_ThirdOK)
			GetDlgItem(IDC_BUTTON_MAKEFILE)->EnableWindow(TRUE);

		if (m_SecondOK)
			GetDlgItem(IDC_BUTTON_VIEWIMAGE)->EnableWindow(TRUE);

		UpdateMyData(FALSE);
		if (m_ctlTT.IsExistTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_IMAGE))))
			m_ctlTT.RemoveTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_IMAGE)));;
		m_ctlTT.AddTool(GetDlgItem (IDC_FILE_IMAGE), m_ImageFile);		

	}
	
}

void CWECompressorTab1::OnBrowsePalette() 
{
	CString	Temp,TempMsg;
	int	Res;
			
	Temp.LoadString(IDS_FILTER_BIN);
	CFileDialog MyFdlg(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_EXPLORER 
		| OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST ,(LPCTSTR) Temp, NULL);
	
	Temp.LoadString(IDS_INFO_TAB1_OPENPALETTE);
	MyFdlg.m_ofn.lpstrTitle = (LPCTSTR) Temp;
	
	//MyFdlg.m_ofn.lpstrInitialDir = m_nSelectedPath;

	UpdateData(TRUE);
	// Invoke the dialog box
	Res = MyFdlg.DoModal();
	if (Res == IDOK)
	{	
		m_PaletteFile = MyFdlg.GetPathName();

		GetDlgItem(IDC_FILE_PALETTE)->EnableWindow(TRUE);
		m_SecondOK = TRUE;
		
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
				m_SecondOK = FALSE;
				GetDlgItem(IDC_FILE_PALETTE)->EnableWindow(FALSE);
				TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_INFO_NO_PALETTES_FOUND)) + "\n\n";
				MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_ERROR_MESSAGEBOX)), 		
						MB_ICONERROR);
			}

		}
		else
		{
			GetDlgItem(IDC_EDIT_OFFSET_PAL)->ShowWindow(TRUE);
			GetDlgItem(IDC_COMBO_PALETTE)->ShowWindow(TRUE);
			GetDlgItem(IDC_OFFSET_LAB2)->ShowWindow(TRUE);
			GetDlgItem(IDC_PALLAB)->ShowWindow(TRUE);
		}

		if (m_FirstOK && m_ThirdOK)
			GetDlgItem(IDC_BUTTON_MAKEFILE)->EnableWindow(TRUE);

		if (m_FirstOK)
			GetDlgItem(IDC_BUTTON_VIEWIMAGE)->EnableWindow(TRUE);

		UpdateMyData(FALSE);
		if (m_ctlTT.IsExistTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_PALETTE))))
			m_ctlTT.RemoveTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_PALETTE)));;			
		m_ctlTT.AddTool(GetDlgItem (IDC_FILE_PALETTE), m_PaletteFile);

	}
					
}

void CWECompressorTab1::OnBrowseDest() 
{
	CString	Temp,Temp2,DefExt;
	int		Res;	
	
	UpdateData(TRUE);
	if (m_ComboIndex == 0)
	{
		Temp = CString(MAKEINTRESOURCE(IDS_FILTER_TIM));
		Temp2 = CString(MAKEINTRESOURCE(IDS_INFO_TAB1_NEWTIM));
		DefExt = "tim";
	}
	else
	if (m_ComboIndex == 1)
	{
		Temp = CString(MAKEINTRESOURCE(IDS_FILTER_BMP));
		Temp2 = CString(MAKEINTRESOURCE(IDS_INFO_TAB1_NEWBMP));
		DefExt = "bmp";
	}
	else
	if (m_ComboIndex == 2)
	{
		Temp = CString(MAKEINTRESOURCE(IDS_FILTER_RAW));
		Temp2 = CString(MAKEINTRESOURCE(IDS_INFO_TAB1_NEWRAW));
		DefExt = "raw";
	}
	else
	if (m_ComboIndex == 3)
	{
		Temp = CString(MAKEINTRESOURCE(IDS_FILTER_TXT));
		Temp2 = CString(MAKEINTRESOURCE(IDS_INFO_TAB1_NEWTXT));
		DefExt = "txt";
	}
	else	
	{
		Temp = CString(MAKEINTRESOURCE(IDS_FILTER_ALL));
		Temp2 = CString(MAKEINTRESOURCE(IDS_INFO_TAB1_NEWALL));
		DefExt = "";
	}
	
	CFileDialog MyFdlg(FALSE, DefExt , "Custom", OFN_HIDEREADONLY | OFN_EXPLORER | 
						OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST , (LPCTSTR) Temp, NULL);	
	
	MyFdlg.m_ofn.lpstrTitle = (LPCTSTR) Temp2;
	
	// Invoke the dialog box
	Res = MyFdlg.DoModal();
	if (Res == IDOK)
	{	
		m_DestFile = MyFdlg.GetPathName();
		GetDlgItem(IDC_FILE_TIM)->EnableWindow(TRUE);
		m_ThirdOK = TRUE;
		if (m_FirstOK && m_SecondOK)
				GetDlgItem(IDC_BUTTON_MAKEFILE)->EnableWindow(TRUE);
		UpdateMyData(FALSE);
		if (m_ctlTT.IsExistTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_TIM))))
				m_ctlTT.RemoveTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_TIM)));
		m_ctlTT.AddTool(GetDlgItem (IDC_FILE_TIM), m_DestFile);
						
	}
	
}

void CWECompressorTab1::OnChangeFocus(BOOL Select)
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

void CWECompressorTab1::OnSelchangeComboPalette() 
{
	UpdateData(TRUE);
	m_ActualImagesIndex = m_ImagesList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if ((!m_ManualImage) && m_FirstOK && m_ImagesList)
		{
			POSITION pos = m_ImageFileList.GetHeadPosition();//
		
			int i=0;
			BYTE factor;
			CString temp;

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
						
			while (pos != NULL)
			{				
				CFilesStruct* p_Images = m_ImageFileList.GetNext(pos);
					
				temp.Format("%u", p_Images->m_Header.width*factor);
				m_ImagesList.SetItemText(i++, 2, temp);
							
			}			
		
		}
	
}

void CWECompressorTab1::OnButtonMakeFile() 
{
	CString TempMsg;

	UpdateData(TRUE);
	if (m_ManualImage)
		SetManualImage();
	if (m_ManualPalette)
		SetManualPalette();
	if (m_ComboIndex == 0)
	{
		if ( !CreateTIM(m_DestFile) )
		{
			TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_ERROR_TAB1_TIM)) + "\n\n";
			MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_ERROR_MESSAGEBOX)), 		
						MB_ICONERROR);
		}
		else
		{
			TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_INFO_TIMOK)) + "\n\n";
			MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_INFO_TIMOK)), 
						MB_ICONINFORMATION);
		}
	}
	else
	if (m_ComboIndex == 1)
	{
		if ( !CreateBMP(m_DestFile) )
		{
			TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_ERROR_TAB1_BMP)) + "\n\n";
			MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_ERROR_MESSAGEBOX)), 		
						MB_ICONERROR);
		}
		else
		{
			TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_INFO_BMPOK)) + "\n\n";
			MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_INFO_BMPOK)), 
						MB_ICONINFORMATION);
		}
	}
	else
	if (m_ComboIndex == 2)
	{
		if ( !CreateRAW(m_DestFile) )
		{
			TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_ERROR_TAB1_RAW)) + "\n\n";
			MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_ERROR_MESSAGEBOX)), 		
						MB_ICONERROR);
		}
		else
		{
			TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_INFO_RAWOK)) + "\n\n";
			MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_INFO_RAWOK)), 
						MB_ICONINFORMATION);
		}
		
	}
	else
	if (m_ComboIndex == 3)
	{
		if ( !CreateTXT(m_DestFile) )
		{
			TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_ERROR_TAB1_TXT)) + "\n\n";
			MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_ERROR_MESSAGEBOX)), 		
						MB_ICONERROR);
		}
		else
		{
			TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_INFO_TXTOK)) + "\n\n";
			MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_INFO_TXTOK)), 
						MB_ICONINFORMATION);
		}
		
	}
	else
	{
		if ( !CreateTIM(CString(m_DestFile + ".tim")) && 
			 !CreateBMP(CString(m_DestFile + ".bmp")) &&
			 !CreateRAW(CString(m_DestFile + ".raw")) &&
			 !CreateTXT(CString(m_DestFile + ".txt")))
		{
			TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_ERROR_TAB1_ALL)) + "\n\n";
			MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_ERROR_MESSAGEBOX)), 		
						MB_ICONERROR);
		}
		else
		{
			TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_INFO_ALLOK)) + "\n\n";
			MessageBox( TempMsg, CString(MAKEINTRESOURCE(IDS_INFO_ALLOK)), 
						MB_ICONINFORMATION);
		}

	}

}

void CWECompressorTab1::OnButtonViewImage() 
{
	CString TempName;
	char tmPath[255];
	
	UpdateData(TRUE);
	if (m_ManualImage)
		SetManualImage();
	else
		OnChangeFocus(FALSE);

	if (m_ManualPalette)
		SetManualPalette();
	else
		OnChangeFocus(TRUE);
	// Prepare Temp File
	GetTempPath(255, tmPath);
	TempName = CString(tmPath) + "WECompr.tmp";	
	if (CreateBMP(TempName))
	{
		CBitmapDialog dlg(TempName,m_ActualImagesIndex+1,m_ActualPalettesIndex+1,
							m_ActualColorsNumber);

		dlg.DoModal();
	}
	
}

void CWECompressorTab1::OnClickListImages(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnChangeFocus(FALSE);
	
	*pResult = 0;
}

void CWECompressorTab1::OnRclickListImages(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnChangeFocus(FALSE);
	
	*pResult = 0;
}

void CWECompressorTab1::OnKeydownListImages(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;

	OnChangeFocus(FALSE);

	*pResult = 0;
}

void CWECompressorTab1::OnClickListPalettes(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnChangeFocus(TRUE);
	
	*pResult = 0;
}


void CWECompressorTab1::OnRclickListPalettes(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnChangeFocus(TRUE);
	
	*pResult = 0;
}

void CWECompressorTab1::OnKeydownListPalettes(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	
	OnChangeFocus(TRUE);
	
	*pResult = 0;
}


void CWECompressorTab1::OnDblClickListPalettes(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnChangeFocus(TRUE);
	OnButtonViewImage();
	
	*pResult = 0;
}

void CWECompressorTab1::OnDblClickListImages(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnChangeFocus(TRUE);
	OnButtonViewImage();
	
	*pResult = 0;
}


void CWECompressorTab1::OnSelchangeComboSelfile() 
{
	CString temp,TempMsg;

	temp = m_DestFile.Left(m_DestFile.GetLength()-4);
	TempMsg = CString(MAKEINTRESOURCE(IDS_HELP_INFORMATION_TITLE));
	UpdateData(TRUE);	
	m_ctlTT.RemoveTool(m_ctlTT.FindTool(GetDlgItem(IDC_SELBUTTON3)));
	
	if (m_ComboIndex == 0)
	{
		m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON3), 
					TempMsg + CString(MAKEINTRESOURCE(IDS_HELP_TAB1_SELBUTTON3)), IDI_PP_INFORMATION);
		temp += CString(".tim");

	}
	else
	if (m_ComboIndex == 1)
	{
		m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON3), 
					TempMsg + CString(MAKEINTRESOURCE(IDS_HELP_TAB1_SELBUTTON3B)), IDI_PP_INFORMATION);
		temp += CString(".bmp");
	}
	else
	if (m_ComboIndex == 2)
	{
		m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON3), 
					TempMsg + CString(MAKEINTRESOURCE(IDS_HELP_TAB1_SELBUTTON3C)), IDI_PP_INFORMATION);
		temp += CString(".raw");
	}
	else
	if (m_ComboIndex == 3)
	{
		m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON3), 
					TempMsg + CString(MAKEINTRESOURCE(IDS_HELP_TAB1_SELBUTTON3D)), IDI_PP_INFORMATION);
		temp += CString(".txt");
	}
	else	
		m_ctlTT.AddTool(GetDlgItem(IDC_SELBUTTON3), 
					TempMsg + CString(MAKEINTRESOURCE(IDS_HELP_TAB1_SELBUTTON3E)), IDI_PP_INFORMATION);
		
	m_DestFile = temp;
	if (m_ctlTT.IsExistTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_TIM))))
				m_ctlTT.RemoveTool(m_ctlTT.FindTool(GetDlgItem(IDC_FILE_TIM)));		
	m_ctlTT.AddTool(GetDlgItem (IDC_FILE_TIM), m_DestFile);
	UpdateMyData(FALSE);

}

void CWECompressorTab1::OnClickManualImages() 
{
	UpdateData(TRUE);
	if ((m_ManualImage) && (m_FirstOK))
	{
		GetDlgItem(IDC_NUM_IMAGES)->ShowWindow(FALSE);
		GetDlgItem(IDC_LIST_IMAGES)->ShowWindow(FALSE);		
		GetDlgItem(IDC_EDIT_OFFSET_IMAGES)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_X)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_Y)->ShowWindow(TRUE);
		GetDlgItem(IDC_XXLAB)->ShowWindow(TRUE);
		GetDlgItem(IDC_XLAB)->ShowWindow(TRUE);
		GetDlgItem(IDC_YLAB)->ShowWindow(TRUE);
		GetDlgItem(IDC_OFFSET_LAB1)->ShowWindow(TRUE);
		m_ActualImagesIndex = 0;	

	}
	else
	{
		if ((m_FirstOK) && (m_ImagesList.GetItemCount() > 0))
		{
			GetDlgItem(IDC_NUM_IMAGES)->ShowWindow(TRUE);
			GetDlgItem(IDC_LIST_IMAGES)->ShowWindow(TRUE);
		}
		GetDlgItem(IDC_EDIT_OFFSET_IMAGES)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_X)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_Y)->ShowWindow(FALSE);
		GetDlgItem(IDC_XXLAB)->ShowWindow(FALSE);
		GetDlgItem(IDC_XLAB)->ShowWindow(FALSE);
		GetDlgItem(IDC_YLAB)->ShowWindow(FALSE);
		GetDlgItem(IDC_OFFSET_LAB1)->ShowWindow(FALSE);

	}
	
}

void CWECompressorTab1::OnClickManualPalette() 
{	
	UpdateData(TRUE);
	if ((m_ManualPalette) && (m_SecondOK))
	{
		GetDlgItem(IDC_NUM_PALETTES)->ShowWindow(FALSE);
		GetDlgItem(IDC_LIST_PALETTES)->ShowWindow(FALSE);		
		GetDlgItem(IDC_EDIT_OFFSET_PAL)->ShowWindow(TRUE);
		GetDlgItem(IDC_COMBO_PALETTE)->ShowWindow(TRUE);
		GetDlgItem(IDC_OFFSET_LAB2)->ShowWindow(TRUE);
		GetDlgItem(IDC_PALLAB)->ShowWindow(TRUE);
		m_ActualPalettesIndex = 0;

	}
	else
	{
		if ((m_SecondOK) && (m_PalettesList.GetItemCount() > 0))
		{
			GetDlgItem(IDC_NUM_PALETTES)->ShowWindow(TRUE);
			GetDlgItem(IDC_LIST_PALETTES)->ShowWindow(TRUE);
		}
		GetDlgItem(IDC_EDIT_OFFSET_PAL)->ShowWindow(FALSE);
		GetDlgItem(IDC_COMBO_PALETTE)->ShowWindow(FALSE);
		GetDlgItem(IDC_OFFSET_LAB2)->ShowWindow(FALSE);
		GetDlgItem(IDC_PALLAB)->ShowWindow(FALSE);
		
	}
	
		
}


void CWECompressorTab1::OnCheckImageAndPal() 
{
	CString StrTemp;

	UpdateData(TRUE);
	if (m_UseSameFile)
	{
		GetDlgItem(IDC_FILE_PALETTE)->EnableWindow(FALSE);		
		GetDlgItem(IDC_SELBUTTON2)->EnableWindow(FALSE);		

	}
	else
	{		
		GetDlgItem(IDC_SELBUTTON2)->EnableWindow(TRUE);
		GetDlgItem(IDC_FILE_PALETTE)->GetWindowText(StrTemp);
		if (StrTemp != CString(MAKEINTRESOURCE(IDS_NAME_NOFILE)))
			GetDlgItem(IDC_FILE_PALETTE)->EnableWindow(TRUE);
			
		
	}
		
}


void CWECompressorTab1::OnChangeGameSel() 
{
	UpdateData(TRUE);
	if (m_ComboGame == 1)
		GetDlgItem(IDC_SHIRT_TEXTURE)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_SHIRT_TEXTURE)->EnableWindow(FALSE);
	
}

BOOL CWECompressorTab1::PreTranslateMessage(MSG* pMsg) 
{
	m_ctlTT.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

void CWECompressorTab1::OnQuit() 
{
	//delete m_pTab;
	AfxGetMainWnd()->SendMessage(WM_CLOSE, 0, 0);
	
}
