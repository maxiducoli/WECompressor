// WECompressorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WECompressor.h"
#include "WECompressorDlg.h"
#include "AboutDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWECompressorDlg dialog

CWECompressorDlg::CWECompressorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWECompressorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWECompressorDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Tab1 = NULL;
	m_Tab2 = NULL;
	m_Tab3 = NULL;

}

void CWECompressorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWECompressorDlg)
		DDX_Control(pDX, IDC_MAIN_TAB, m_MainTab);	
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWECompressorDlg, CDialog)
	//{{AFX_MSG_MAP(CWECompressorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
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
	
	//m_imagelistTab.Create(IDB_TABCTRL_IMAGE, 11, 0, RGB(0, 255, 0));
	//m_tabctrl.SetImageList(&m_imagelistTab);

	m_Tab1 = new CWECompressorTab1;
	m_Tab1->Create(CWECompressorTab1::IDD, &m_MainTab);
	m_MainTab.AddTab(m_Tab1, "Decompress", 0);
	m_Tab1->m_pTab = &m_MainTab;

	m_Tab2 = new CWECompressorTab2;
	m_Tab2->Create(CWECompressorTab2::IDD, &m_MainTab);
	m_MainTab.AddTab(m_Tab2, "Compress", 1);
	m_Tab2->m_pTab = &m_MainTab;

	m_Tab3 = new CWECompressorTab3;
	m_Tab3->Create(CWECompressorTab3::IDD, &m_MainTab);
	m_MainTab.AddTab(m_Tab3, "TEX Manager", 2);
	m_Tab3->m_pTab = &m_MainTab;

	//** customizing the tab control --------
//	m_MainTab.SetDisabledColor(RGB(255, 0, 0));
	m_MainTab.SetSelectedColor(RGB(0, 0, 255));
	m_MainTab.SetMouseOverColor(RGB(255, 255, 255));
	m_MainTab.EnableTab(0, TRUE);	
		
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWECompressorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDialog dlgAbout;
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


void CWECompressorDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if (m_Tab1)
		delete m_Tab1;
	if (m_Tab2)
		delete m_Tab2;
	if (m_Tab3)
		delete m_Tab3;

}
