// WECompressorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WECompressor.h"
#include "WECompressorDlg.h"
#include "WECompress.h"
#include "ScrollBitmapDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString	tempStr;
	char sepa[] = "#";
	char stringTemp[2000];
	char *token;

	CDialog::OnInitDialog();
	
	CListBox* pList = (CListBox*) GetDlgItem(IDC_LIST_HELP);

	ASSERT(pList != NULL);

	if (pList != NULL)
	{
		pList->ResetContent();

		/*tempStr.LoadString(IDS_INFO_HELP1);
	
		strcpy(stringTemp, tempStr);
		// Establish string and get the first token:
		token = strtok(stringTemp, sepa );		
		while (token != NULL)
		{
			pList->AddString(token);
			/* Get next tok:
			token = strtok( NULL, sepa );
		}*/

		pList->AddString("This is very very very beta version");
		pList->AddString("Not to be used for releasing yet");
		pList->AddString("Thanx CARP for assistance and support");
		pList->AddString("in PSX ASM decompress routine.");
		pList->AddString("10/05/2003 - CopyRight Walxer");
		/*pList->AddString("Informazioni su WE Player Editor");
		pList->AddString("---------------------------------------------------");
		pList->AddString("");
		pList->AddString("Questo programma serve x aggiornare i files");
		pList->AddString("select.bin e slpm_8660.00 che contengono");
		pList->AddString("tutti i dati dei giocatori, gli ordinamenti dei");
		pList->AddString("numeri di maglia e i nomi dei giocatori.");
		pList->AddString("Tale aggiornameto viene fatto convertendo");
		pList->AddString("i dati contenuti nei files delle Memory Card,");
		pList->AddString("senza quindi bisogno di complicati editor,");
		pList->AddString("ma sfruttando proprio quello messo a");
		pList->AddString("disposizione nel gioco stesso.");
		pList->AddString("Per memorizzare con correttezza i dati");
		pList->AddString("nelle Memory Card, si deve seguire questo");
		pList->AddString("schema:");
		pList->AddString("- Creare i 22 giocatori e metterli nei 22");
		pList->AddString(" stock liberi della Memory Card (Ovviamente");
		pList->AddString(" se volete editare una squadra di ML i");
		pList->AddString(" giocatori riconosciuti saranno i primi 18).");
		pList->AddString(" Non dimenticare il nome e inserire i giocatori");
		pList->AddString(" seguendo lo stesso ordine per ruolo usato");
		pList->AddString(" dal gioco stesso, quindi a partire dal portiere");
		pList->AddString(" fino all'attaccante, e partend da sinistra");
		pList->AddString(" quando i giocatori rivestono gli stessi ruoli.");
		pList->AddString("- Inserire l'ordinamento dei numeri di maglia");
		pList->AddString("  dei giocatori al posto dell'EIRE, la prima");
		pList->AddString("  squadra national x inenderci.");
		pList->AddString("- Editare una strategia per la squadra da");
		pList->AddString("  inserire, salvarla al primo slot libero");
		pList->AddString("  nella Memory Card (dopo i 2 blocchi delle");
		pList->AddString("  opzioni) nel primo slot dei 15 disponibili");
		pList->AddString("  per le strategie. Non dimenticare pero'");
		pList->AddString("  di editare anche capitano, battitori di");
		pList->AddString("  rigori, punizioni e calci d'angolo.");
		pList->AddString("- Salvare il tutto su una Memory Card vuota,");
		pList->AddString("  che non contenga altro che queste cose.");
		pList->AddString("A questo punto siete pronti x la");
		pList->AddString("conversione, che avverra' in maniera");
		pList->AddString("automatica e rapida.");
		pList->AddString("Selezionate la squadra da sostituire, oltre");
		pList->AddString("ad aver ovviamente specificato i files da");
		pList->AddString("leggere (Memory Card) e da modificare");
		pList->AddString("(select.bin e slpm_8660.00), e scegliete");
		pList->AddString("cosa si desidera aggiornare nei 2 file da");
		pList->AddString("modificare (nomi, caratteristiche, ecc...).");
		pList->AddString("Completato questo aggiornameto, siete");
		pList->AddString("pronti x aggiornare il file immagine,");		
		pList->AddString("inserendo i 2 file alla posizione giusta");
		pList->AddString("con l'aiuto del mio programmino");
		pList->AddString("BIN Patcher 1.1.");
		pList->AddString("");
		pList->AddString("Walxer");
		pList->AddString("-----------");
		pList->AddString("walxer@tiscalinet.it");
		pList->AddString("http://walxer.winningeleven.com");*/
	}
	MessageBeep(MB_ICONINFORMATION);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWECompressorDlg dialog

CWECompressorDlg::CWECompressorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWECompressorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWECompressorDlg)
	m_ComboIndex = 0;
	m_ManualImage = FALSE;
	m_ManualPalette = FALSE;
	m_OffsetImage = _T("30");
	m_OffsetPal = _T("25EC");
	m_BitPalette = 1;
	m_ImageX = 128;
	m_ImageY = 128;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_ImageFile = CString(" ");
	m_PaletteFile = CString(" ");
	m_DestFile = CString(" ");
	m_ActualImagesIndex = 0;
	m_ActualPalettesIndex = 0;
	
	m_FirstOK = FALSE;
	m_SecondOK = FALSE;
	m_ThirdOK = FALSE;
}

CWECompressorDlg::~CWECompressorDlg()
{
	if (m_ImagesList)
		m_ImagesList.DeleteAllItems();
	if (m_PalettesList)
		m_PalettesList.DeleteAllItems();
	FreeListMem(TRUE);
	FreeListMem(FALSE);
	
}

void CWECompressorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWECompressorDlg)
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
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWECompressorDlg, CDialog)
	//{{AFX_MSG_MAP(CWECompressorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWECompressorDlg message handlers

BOOL CWECompressorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

		// Setup the tab control
	int nPageID = 0;
	//m_MainTab.AddSSLPage (_T("Basic Tab"), nPageID++, IDD_TAB_BASIC);
	m_Tab1.Create (IDD_WEFLASHEDITOR_TABLE1, this);
	m_MainTab.AddSSLPage (_T("Player Properties"), nPageID++, &m_Tab1);

	m_Tab2.Create (IDD_WEFLASHEDITOR_TABLE2, this);
	m_MainTab.AddSSLPage (_T("Team Setting"), nPageID++, &m_Tab2);

	m_MainTab.ActivateSSLPage(1);
	m_MainTab.ActivateSSLPage(0);
		
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWECompressorDlg::AddHelpTTips()
{
	m_ctlTT.Create (this);
	//m_ctlTT.AddTool (GetDlgItem (IDC_CHECK_SECTOR), _T ("This is a window"), NULL, 0);
	m_ctlTT.AddWindowTool(GetDlgItem (IDC_SELBUTTON), MAKEINTRESOURCE(IDS_HELP_SELBUTTON));
	m_ctlTT.AddWindowTool(GetDlgItem (IDC_SELBUTTON2), MAKEINTRESOURCE(IDS_HELP_SELBUTTON2));
	m_ctlTT.AddWindowTool(GetDlgItem (IDC_SELBUTTON3), MAKEINTRESOURCE(IDS_HELP_SELBUTTON3));
	m_ctlTT.AddWindowTool(GetDlgItem (IDC_WECOMPRESSOR), MAKEINTRESOURCE(IDS_HELP_WECOMPRESSOR));
	m_ctlTT.AddWindowTool(GetDlgItem (IDC_BUTTON_VIEWIMAGE), MAKEINTRESOURCE(IDS_HELP_VIEW));
	m_ctlTT.AddWindowTool(GetDlgItem (ID_INFO), MAKEINTRESOURCE(IDS_HELP_INFO));
	m_ctlTT.AddWindowTool(GetDlgItem (IDOK), MAKEINTRESOURCE(IDS_HELP_EXIT));

}

void CWECompressorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWECompressorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWECompressorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWECompressorDlg::OnInfo() 
{
	CAboutDlg dlgAbout;

	dlgAbout.DoModal();
	
}

void CWECompressorDlg::FreeListMem(BOOL Select)
{
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

BOOL CWECompressorDlg::UpdateMyData(BOOL bValid)
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
												CString(MAKEINTRESOURCE(IDS_NAME_FILEIMAGE)));
			else
			{								
				PathCompactPathEx(tempPath, m_ImageFile, 54, '\\');
				GetDlgItem(IDC_FILE_IMAGE)->SetWindowText(CString(tempPath));				
			}

		}
		else
		{
			GetDlgItem(IDC_FILE_IMAGE)->GetWindowText(tempStr);
			if (tempStr == CString(MAKEINTRESOURCE(IDS_NAME_FILEIMAGE)))		
				m_ImageFile = CString("");

		}
	}

	if (GetDlgItem(IDC_FILE_PALETTE)->IsWindowEnabled() == TRUE)
	{
		if (bValid == FALSE)
		{			
			if (m_PaletteFile == "")
				GetDlgItem(IDC_FILE_PALETTE)->SetWindowText(
													CString(MAKEINTRESOURCE(IDS_NAME_FILEPALETTE)));
			else
			{					
				PathCompactPathEx(tempPath, m_PaletteFile, 54, '\\');
				GetDlgItem(IDC_FILE_PALETTE)->SetWindowText(CString(tempPath));				
			}			

		}
		else
		{
			GetDlgItem(IDC_FILE_PALETTE)->GetWindowText(tempStr);
			if (tempStr == CString(MAKEINTRESOURCE(IDS_NAME_FILEPALETTE)))		
				m_PaletteFile = CString("");

		}
	}

	if (GetDlgItem(IDC_FILE_TIM)->IsWindowEnabled() == TRUE)
	{
		if (bValid == FALSE)
		{			
			if (m_DestFile == "")
				GetDlgItem(IDC_FILE_TIM)->SetWindowText(
													CString(MAKEINTRESOURCE(IDS_NAME_FILETIM)));
			else
			{					
				PathCompactPathEx(tempPath, m_DestFile, 54, '\\');
				GetDlgItem(IDC_FILE_TIM)->SetWindowText(CString(tempPath));				
			}			

		}
		else
		{
			GetDlgItem(IDC_FILE_TIM)->GetWindowText(tempStr);
			if (tempStr == CString(MAKEINTRESOURCE(IDS_NAME_FILETIM)))		
				m_DestFile = CString("");

		}
	}

	bTemp = TRUE;
	bTemp = UpdateData(bValid) && bTemp;

	return bTemp;
}

BOOL CWECompressorDlg::SearchImages() 
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
	
	nSize = fSource.GetLength();

	BYTE* rbuf = new BYTE[nSize];
	fSource.ReadHuge(rbuf, nSize);
	fSource.Close();

	BYTE *pCur = rbuf;
	
	i = 0;
	FreeListMem(TRUE);
	while( i++ < nSize - 16)
	{
		if ((rbuf[i] == 0x0A) && (rbuf[i+1] == 0x00) && (rbuf[i+10] == 0x00) && 
			(rbuf[i+15] == 0x80) && ((rbuf[i+14] > 0x0B) && (rbuf[i+14] < 0x11)))
		{
			// Found the header!!!!
			CFilesStruct *fe = new CFilesStruct();			
			memcpy(&fe->m_Header,pCur+i,sizeof(DATA_HEADER));
			
			if (rbuf[i+14] == 0x0F)
				fe->m_OffsetReal = fe->m_Header.offset;
			else
			if (rbuf[i+14] == 0x0C)
				fe->m_OffsetReal = fe->m_Header.offset - 0x8000;
			else
			if (rbuf[i+14] == 0x0D)
				fe->m_OffsetReal = fe->m_Header.offset + 0x8000;
			else
			if (rbuf[i+14] == 0x0E)
				fe->m_OffsetReal = fe->m_Header.offset + 0x18000;
			else
			if (rbuf[i+14] == 0x10)
				fe->m_OffsetReal = fe->m_Header.offset + 0x10000;
			else
			if (rbuf[i+14] == 0x11)
				fe->m_OffsetReal = fe->m_Header.offset + 0x20000;
			else
			if (rbuf[i+14] == 0x12)
				fe->m_OffsetReal = fe->m_Header.offset + 0x30000;

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

	return TRUE;
}

BOOL CWECompressorDlg::SearchPalettes() 
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
	
	nSize = fSource.GetLength();

	BYTE* rbuf = new BYTE[nSize];
	fSource.ReadHuge(rbuf, nSize);
	fSource.Close();

	BYTE *pCur = rbuf;
	
	i = 0;
	FreeListMem(FALSE);
	while( i++ < nSize - 16)
	{
		if ((rbuf[i] == 0x09) && (rbuf[i+10] == 0x00) && (rbuf[i+15] == 0x80) && 
			((rbuf[i+14] > 0x0B) && (rbuf[i+14] < 0x11)))
		{
			// Found the header!!!!
			CFilesStruct *fe = new CFilesStruct();			
			memcpy(&fe->m_Header,pCur+i,sizeof(DATA_HEADER));

			if (rbuf[i+14] == 0x0F)
				fe->m_OffsetReal = fe->m_Header.offset;
			else
			if (rbuf[i+14] == 0x0C)
				fe->m_OffsetReal = fe->m_Header.offset - 0x8000;
			else
			if (rbuf[i+14] == 0x0D)
				fe->m_OffsetReal = fe->m_Header.offset + 0x8000;
			else
			if (rbuf[i+14] == 0x0E)
				fe->m_OffsetReal = fe->m_Header.offset + 0x18000;
			else
			if (rbuf[i+14] == 0x10)
				fe->m_OffsetReal = fe->m_Header.offset + 0x10000;
			else
			if (rbuf[i+14] == 0x11)
				fe->m_OffsetReal = fe->m_Header.offset + 0x20000;
			else
			if (rbuf[i+14] == 0x12)
				fe->m_OffsetReal = fe->m_Header.offset + 0x30000;

			// often errors
			// fe->m_BlockLen = i - fe->m_OffsetReal;

			if (fe->m_Header.width == 16)			
				fe->m_MutiplyFactor = 2;//4;
			else
			if (fe->m_Header.width == 256)
				fe->m_MutiplyFactor = 2;
			else
			if (fe->m_Header.width == 65535)
				fe->m_MutiplyFactor = 1;
			else				
				fe->m_MutiplyFactor = 1; // 2/3 ma non posso

			fe->m_BlockLen = fe->m_Header.width*2; // 15 bit colours,so * 2
			(BYTE*) fe->m_DataBlock = new BYTE[fe->m_BlockLen];
			memcpy(fe->m_DataBlock,pCur + fe->m_OffsetReal, fe->m_BlockLen);

			m_PaletteFileList.AddTail(fe);
			i+=15;
		}
		
	}

	/////////
	delete rbuf;	

	return TRUE;
}

BOOL CWECompressorDlg::SetManualImage()
{	
	CString TempNum;
	CFile	fSource;	
	CFileException e;
	UINT nSize,i;

	// open data file to read
	if (!fSource.Open(m_ImageFile, CFile::modeRead | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error reading in source File ") + m_ImageFile);
		return FALSE;
	}
	
	nSize = fSource.GetLength();

	BYTE* rbuf = new BYTE[nSize];
	fSource.ReadHuge(rbuf, nSize);
	fSource.Close();

	BYTE *pCur = rbuf;

	i = 0;
	FreeListMem(TRUE);
	UpdateData(TRUE);
	// Make the header!!!!
	CFilesStruct *fe = new CFilesStruct();

	ZeroMemory(&fe->m_Header,sizeof(DATA_HEADER));
	fe->m_Header.ID = 10;	
	fe->m_Header.width = m_ImageX / 2;
	fe->m_Header.height = m_ImageY;
	fe->m_Header.VramX = 576;
	fe->m_Header.VramY = 256;
	TempNum = CString("0x") + m_OffsetImage;
	fe->m_Header.offset = strtol(TempNum, NULL, 16);
	fe->m_Header.separator = 32783;
	fe->m_Header.unknown5 = 255;

	fe->m_OffsetReal = fe->m_Header.offset;
	
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

BOOL CWECompressorDlg::SetManualPalette()
{	
	CString TempNum;
	CFile	fSource;	
	CFileException e;
	UINT nSize,i;

	// open data file to read
	if (!fSource.Open(m_PaletteFile, CFile::modeRead | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error reading in source File ") + m_PaletteFile);
		return FALSE;
	}
	
	nSize = fSource.GetLength();

	BYTE* rbuf = new BYTE[nSize];
	fSource.ReadHuge(rbuf, nSize);
	fSource.Close();

	BYTE *pCur = rbuf;

	i = 0;
	FreeListMem(FALSE);
	UpdateData(TRUE);
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
	TempNum = CString("0x") + m_OffsetPal;
	fe->m_Header.offset = strtol(TempNum, NULL, 16);
	fe->m_Header.separator = 32783;
	fe->m_Header.unknown5 = 255;

	fe->m_OffsetReal = fe->m_Header.offset;
	
	if (fe->m_Header.width == 16)			
		fe->m_MutiplyFactor = 2;//4;
	else
	if (fe->m_Header.width == 256)
		fe->m_MutiplyFactor = 2;
	else
	if (fe->m_Header.width == 65535)
		fe->m_MutiplyFactor = 1;
	else				
		fe->m_MutiplyFactor = 1; // 2/3 ma non posso

	fe->m_BlockLen = fe->m_Header.width*2; // 15 bit colours,so * 2
	(BYTE*) fe->m_DataBlock = new BYTE[fe->m_BlockLen];
	memcpy(fe->m_DataBlock,pCur + fe->m_OffsetReal, fe->m_BlockLen);

	m_PaletteFileList.AddTail(fe);

	/////////
	delete rbuf;	
	
	return TRUE;
}

BOOL CWECompressorDlg::UpdateFileList(BOOL Select) 
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
				temp.Format("%u", p_Images->m_BlockLen);
				m_ImagesList.SetItemText(index, 6, temp);
			
			}

			TempMsg.Format("%d Immagini trovate",m_ImagesList.GetItemCount());
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
			
			}

			TempMsg.Format("%d Palette trovate",m_PalettesList.GetItemCount());
			GetDlgItem(IDC_NUM_PALETTES)->SetWindowText(CString(TempMsg));

			m_PalettesList.SetItemState(0,LVIS_SELECTED , -1);
			m_PalettesList.SetFocus();
		
		}
	
	}

	return TRUE;
}

BOOL CWECompressorDlg::CreateTIM(CString NameFile)
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

			multfact = p_Palettes->m_MutiplyFactor;

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
			DataLength = 
				p_Images->m_Header.width*multfact*p_Images->m_Header.height*p_Images->m_MultiplyY;
			TData.blocklen = DataLength + 12;

			NewFileTIM.Write(&TData,sizeof( TIM_DATAINFO ));

			CWECompress tempclass;
			BYTE* pData = new BYTE[DataLength];
			ZeroMemory(pData,DataLength);
			tempclass.DeCompress(&pData,p_Images->m_DataBlock);
		
			// write Data Block
			NewFileTIM.Write(pData,DataLength);

			delete pData;

		}
		
	}

	NewFileTIM.Close();

	return TRUE;

}

BOOL CWECompressorDlg::CreateBMP(CString NameFile)
{
	CFile   NewFileBMP;	
	CString TempMsg;
	CFileException e;
	UINT i,j,multfact,planes,depth;
	ULONG xsize,ysize,imagesize;
	BYTE rgbq[RGB_SIZE];
	BYTE* pData;
	
	// open data file to write
	if (!NewFileBMP.Open(NameFile, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
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
				depth = 4;
			else
			if (p_Palettes->m_Header.width == 0x100)
				depth = 8;
			else
			if (p_Palettes->m_Header.width == 0x10000)
				depth = 16;
			else
				depth = 24;

			// write converted CLUT RGB table (psx uses 15bit RGB)
			for (WORD col=0; col < RGB_SIZE; col+=4)
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
			multfact = p_Palettes->m_MutiplyFactor;

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
			tempclass.DeCompress(&pDataRev,p_Images->m_DataBlock);
			
			// copy reverse data to pData			
			j=0;
			for(long y1=ysize-1;y1>=0;y1--){
				for(unsigned long x1=0;x1<xsize;x1++)
					pData[j++] = pDataRev[(y1*xsize)+x1];}

			delete pDataRev;

		}
		
	}

	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	
	bmfh.bfType = 0x4D42;// BM
	bmfh.bfSize = TOTAL_HEADER_SIZE + (xsize*ysize*depth)/8;
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = TOTAL_HEADER_SIZE;

	NewFileBMP.Write(&bmfh,sizeof( BITMAPFILEHEADER ));
	
	bmih.biSize = BMIH_SIZE;
	bmih.biWidth = xsize;
	bmih.biHeight = ysize;
	bmih.biPlanes = 1;
	bmih.biBitCount = depth;
	bmih.biCompression = 0;
	bmih.biSizeImage = (xsize*ysize*depth)/8;
	bmih.biXPelsPerMeter = 2835;
	bmih.biYPelsPerMeter = 2835;
	if (depth == 4)
		bmih.biClrUsed = 16;
	if (depth == 8)
		bmih.biClrUsed = 256;
	if (depth > 8)
		bmih.biClrUsed = 0;
	bmih.biClrImportant = 0;
	
	NewFileBMP.Write(&bmih,sizeof( BITMAPINFOHEADER ));
		
	// write converted CLUT RGB table (psx uses 15bit RGB)
	NewFileBMP.Write(rgbq,RGB_SIZE);

	// write Data block
	NewFileBMP.Write(pData,imagesize);

	delete pData;

	NewFileBMP.Close();

	return TRUE;

}

BOOL CWECompressorDlg::CreateRAW(CString NameFile)
{
	CFile   NewFileRAW,NewFilePAL,NewFileCLUT;
	CString TempMsg;
	CFileException e;
	UINT i,multfact;
	ULONG imagesize;
	BYTE rgbq[RGB_SIZE];
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
			// write converted CLUT RGB table (psx uses 15bit RGB)
			for (WORD col=0; col < RGB_SIZE; col+=4)
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
			NewFilePAL.Write(rgbq,RGB_SIZE);			

			// write CLUT DATA
			NewFileCLUT.Write(p_Palettes->m_DataBlock,p_Palettes->m_BlockLen);

			multfact = p_Palettes->m_MutiplyFactor;

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

BOOL CWECompressorDlg::CreateTXT(CString NameFile)
{
	CFile   NewFileTXT;
	CString TempMsg,TempMsg2;
	CFileException e;
	UINT i;
	
	// open data file to write
	if (!NewFileTXT.Open(NameFile, CFile::modeCreate | CFile::modeReadWrite | CFile::typeText, &e))
	{
		AfxMessageBox(_T("Error writing ") + NameFile);
		return FALSE;
	}

	TempMsg = "Informazioni sulla Grafica del file " + m_ImageFile + " \r";
	NewFileTXT.Write(TempMsg,TempMsg.GetLength());
	TempMsg2 = "------------------------------------";
	for (i=0;i<m_ImageFile.GetLength();i++)
		TempMsg2 += '-';
	
	TempMsg2+="\n\n";
	NewFileTXT.Write(TempMsg2,TempMsg2.GetLength());

/*


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

			multfact = p_Palettes->m_MutiplyFactor;

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
			DataLength = 
				p_Images->m_Header.width*multfact*p_Images->m_Header.height*p_Images->m_MultiplyY;
			TData.blocklen = DataLength + 12;

			NewFileTXT.Write(&TData,sizeof( TIM_DATAINFO ));

			BYTE* pData = new BYTE[DataLength];
			ZeroMemory(pData,DataLength);
			DecompressData(&pData,p_Images->m_DataBlock);
		
			// write Data Block
			NewFileTXT.Write(pData,DataLength);

			delete pData;

		}
		
	}*/

	NewFileTXT.Close();

	return TRUE;

		
}

void CWECompressorDlg::OnBrowseImage() 
{
	CString	Temp;
	int	Res;
			
	Temp.LoadString(IDS_FILTER_BIN);
	CFileDialog MyFdlg(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_EXPLORER 
		| OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST ,(LPCTSTR) Temp, NULL);
	
	Temp.LoadString(IDS_INFO_OPENIMAGE);
	MyFdlg.m_ofn.lpstrTitle = (LPCTSTR) Temp;
	
	//MyFdlg.m_ofn.lpstrInitialDir = m_nSelectedPath;

	// Invoke the dialog box
	UpdateData(TRUE);
	Res = MyFdlg.DoModal();
	if (Res == IDOK)
	{	
		m_ImageFile = MyFdlg.GetPathName();
		//if (DammiLength(FALSE, m_SourceFile) == TRUE)
		{
			GetDlgItem(IDC_FILE_IMAGE)->EnableWindow(TRUE);
			m_FirstOK = TRUE;
			if (m_SecondOK && m_ThirdOK)
				GetDlgItem(IDC_BUTTON_MAKEFILE)->EnableWindow(TRUE);

			if (m_SecondOK)
				GetDlgItem(IDC_BUTTON_VIEWIMAGE)->EnableWindow(TRUE);

			if (!m_ManualImage)
			{
				SearchImages();
				if (UpdateFileList(TRUE) == TRUE)
				{
					GetDlgItem(IDC_NUM_IMAGES)->ShowWindow(TRUE);
					GetDlgItem(IDC_LIST_IMAGES)->ShowWindow(TRUE);					
				
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

			UpdateMyData(FALSE);
			m_ctlTT.AddWindowTool(GetDlgItem (IDC_FILE_IMAGE), m_ImageFile);

		}
					
	}
	
	
}

void CWECompressorDlg::OnBrowsePalette() 
{
	CString	Temp;
	int	Res;
			
	Temp.LoadString(IDS_FILTER_BIN);
	CFileDialog MyFdlg(TRUE,NULL,NULL, OFN_HIDEREADONLY | OFN_EXPLORER 
		| OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST ,(LPCTSTR) Temp, NULL);
	
	Temp.LoadString(IDS_INFO_OPENPALETTE);
	MyFdlg.m_ofn.lpstrTitle = (LPCTSTR) Temp;
	
	//MyFdlg.m_ofn.lpstrInitialDir = m_nSelectedPath;

	UpdateData(TRUE);
	// Invoke the dialog box
	Res = MyFdlg.DoModal();
	if (Res == IDOK)
	{	
		m_PaletteFile = MyFdlg.GetPathName();
		//if (DammiLength(FALSE, m_SourceFile) == TRUE)
		{
			GetDlgItem(IDC_FILE_PALETTE)->EnableWindow(TRUE);
			m_SecondOK = TRUE;
			if (m_FirstOK && m_ThirdOK)
				GetDlgItem(IDC_BUTTON_MAKEFILE)->EnableWindow(TRUE);

			if (m_FirstOK)
				GetDlgItem(IDC_BUTTON_VIEWIMAGE)->EnableWindow(TRUE);

			if (!m_ManualPalette)
			{
				SearchPalettes();
				if (UpdateFileList(FALSE) == TRUE)
				{
					GetDlgItem(IDC_NUM_PALETTES)->ShowWindow(TRUE);
					GetDlgItem(IDC_LIST_PALETTES)->ShowWindow(TRUE);
				
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
			m_ctlTT.AddWindowTool(GetDlgItem (IDC_FILE_PALETTE), m_PaletteFile);

		}
					
	}
	
	
}

void CWECompressorDlg::OnBrowseDest() 
{
	CString	Temp,Temp2,DefExt;
	int		Res;	
	
	UpdateData(TRUE);
	if (m_ComboIndex == 0)
	{
		Temp = CString(MAKEINTRESOURCE(IDS_FILTER_TIM));
		Temp2 = CString(MAKEINTRESOURCE(IDS_INFO_NEWTIM));
		DefExt = "tim";
	}
	else
	if (m_ComboIndex == 1)
	{
		Temp = CString(MAKEINTRESOURCE(IDS_FILTER_BMP));
		Temp2 = CString(MAKEINTRESOURCE(IDS_INFO_NEWBMP));
		DefExt = "bmp";
	}
	else
	if (m_ComboIndex == 2)
	{
		Temp = CString(MAKEINTRESOURCE(IDS_FILTER_RAW));
		Temp2 = CString(MAKEINTRESOURCE(IDS_INFO_NEWRAW));
		DefExt = "raw";
	}
	else
	if (m_ComboIndex == 3)
	{
		Temp = CString(MAKEINTRESOURCE(IDS_FILTER_TXT));
		Temp2 = CString(MAKEINTRESOURCE(IDS_INFO_NEWTXT));
		DefExt = "txt";
	}
	else	
	{
		Temp = CString(MAKEINTRESOURCE(IDS_FILTER_ALL));
		Temp2 = CString(MAKEINTRESOURCE(IDS_INFO_NEWALL));
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
		m_ctlTT.AddWindowTool(GetDlgItem (IDC_FILE_TIM), m_DestFile);
						
	}
	
}

void CWECompressorDlg::OnChangeFocus(BOOL Select)
{
	UpdateData(TRUE);
	m_ActualImagesIndex = m_ImagesList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	m_ActualPalettesIndex = m_PalettesList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if (Select)
	{
		if (m_ImagesList)
		{
			POSITION pos = m_ImageFileList.GetHeadPosition();//
		
			int i=0;
			BYTE factor;
			CString temp;

			factor = m_PaletteFileList.GetAt(m_PaletteFileList.FindIndex(m_ActualPalettesIndex))->m_MutiplyFactor;
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

void CWECompressorDlg::OnButtonMakeFile() 
{
	CString TempMsg;

	if (m_ManualImage)
		SetManualImage();
	if (m_ManualPalette)
		SetManualPalette();
	if (m_ComboIndex == 0)
	{
		if ( !CreateTIM(m_DestFile) )
		{
			TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_ERROR_TIM)) + "\n\n";
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
			TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_ERROR_BMP)) + "\n\n";
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
			TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_ERROR_RAW)) + "\n\n";
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
			TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_ERROR_TXT)) + "\n\n";
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
			TempMsg = "\n" + CString(MAKEINTRESOURCE(IDS_ERROR_ALL)) + "\n\n";
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

void CWECompressorDlg::OnButtonViewImage() 
{
	CString TempName;
	char tmPath[255];
	
	if (m_ManualImage)
		SetManualImage();
	if (m_ManualPalette)
		SetManualPalette();
	// Prepare Temp File
	GetTempPath(255, tmPath);
	TempName = CString(tmPath) + "WECompr.tmp";	
	if (CreateBMP(TempName))
	{
		CScrollBitmapDlg dlg(TempName);

		dlg.DoModal();
	}
	
}

void CWECompressorDlg::OnClickListImages(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnChangeFocus(FALSE);
	
	*pResult = 0;
}

void CWECompressorDlg::OnRclickListImages(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnChangeFocus(FALSE);
	
	*pResult = 0;
}

void CWECompressorDlg::OnKeydownListImages(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;

	OnChangeFocus(FALSE);

	*pResult = 0;
}

void CWECompressorDlg::OnClickListPalettes(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnChangeFocus(TRUE);
	
	*pResult = 0;
}


void CWECompressorDlg::OnRclickListPalettes(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnChangeFocus(TRUE);
	
	*pResult = 0;
}

void CWECompressorDlg::OnKeydownListPalettes(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	
	OnChangeFocus(TRUE);
	
	*pResult = 0;
}


void CWECompressorDlg::OnSelchangeComboSelfile() 
{
	CString temp;

	temp = m_DestFile.Left(m_DestFile.GetLength()-4);
	UpdateData(TRUE);
	if (m_ComboIndex == 0)
	{
		m_ctlTT.AddWindowTool(GetDlgItem (IDC_SELBUTTON3), MAKEINTRESOURCE(IDS_HELP_SELBUTTON3));
		temp += CString(".tim");

	}
	else
	if (m_ComboIndex == 1)
	{
		m_ctlTT.AddWindowTool(GetDlgItem (IDC_SELBUTTON3), MAKEINTRESOURCE(IDS_HELP_SELBUTTON3B));
		temp += CString(".bmp");
	}
	else
	if (m_ComboIndex == 2)
	{
		m_ctlTT.AddWindowTool(GetDlgItem (IDC_SELBUTTON3), MAKEINTRESOURCE(IDS_HELP_SELBUTTON3C));
		temp += CString(".raw");
	}
	else
	if (m_ComboIndex == 3)
	{
		m_ctlTT.AddWindowTool(GetDlgItem (IDC_SELBUTTON3), MAKEINTRESOURCE(IDS_HELP_SELBUTTON3D));
		temp += CString(".txt");
	}
	else	
		m_ctlTT.AddWindowTool(GetDlgItem (IDC_SELBUTTON3), MAKEINTRESOURCE(IDS_HELP_SELBUTTON3E));
		
	m_DestFile = temp;
	m_ctlTT.AddWindowTool(GetDlgItem (IDC_FILE_TIM), m_DestFile);
	UpdateMyData(FALSE);

}

void CWECompressorDlg::OnClickManualImages() 
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

void CWECompressorDlg::OnClickManualPalette() 
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
