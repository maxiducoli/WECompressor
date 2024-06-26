// BitmapDialog.cpp : implementation file
//

#include "stdafx.h"
#include "WECompressor.h"
#include "BitmapDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBitmapDialog dialog


CBitmapDialog::CBitmapDialog(CString filepath,int ID1,int ID2,int Colors,CWnd* pParent /*=NULL*/)
	: CDialog(CBitmapDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBitmapDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hBmpNew = NULL;	
	
	m_BMPFileTmp = filepath;
	m_ID1 = ID1;
	m_ID2 = ID2;
	m_Colors = Colors;
}


CBitmapDialog::~CBitmapDialog()
{
	m_dcMem.DeleteDC();
	if (m_BMPFileTmp != "")
		CFile::Remove(m_BMPFileTmp);
}

BOOL CBitmapDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC( &dc );

	OnShow();	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBitmapDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBitmapDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBitmapDialog, CDialog)
	//{{AFX_MSG_MAP(CBitmapDialog)
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitmapDialog message handlers

void CBitmapDialog::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CBitmap *pBitmapOld = m_dcMem.SelectObject(CBitmap::FromHandle((HBITMAP) m_hBmpNew));
	CRect RectDlg;
	GetClientRect(&RectDlg);
	dc.SetStretchBltMode(COLORONCOLOR);
	
	dc.StretchBlt(0, 0, 
		           RectDlg.Width(), RectDlg.Height(), 
			       &m_dcMem, 
				   0, 0, 
				   m_bmInfo.bmWidth, m_bmInfo.bmHeight, SRCCOPY);
	
	m_dcMem.SelectObject(pBitmapOld);

}

void CBitmapDialog::OnShow() 
{	
	if(m_hBmpNew != NULL )
		DeleteObject(m_hBmpNew);
	
	m_hBmpNew =	(HBITMAP) LoadImage (
									AfxGetInstanceHandle(),   // handle to instance
									m_BMPFileTmp,  // name or identifier of the image
									IMAGE_BITMAP,        // image types
									0,     // desired width
									0,     // desired height
									LR_LOADFROMFILE); 

	if ( m_hBmpNew == NULL )
		AfxMessageBox("Load Image Failed");
	   // put the HBITMAP info into the CBitmap (but not the bitmap itself)
	else
	{
		// Convert to screen coordinates using static as base,
		// then to DIALOG (instead of static) client coords 
		// using dialog as base
		
		GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );
		//GetObject( (HPALETTE) m_hBmpNew , sizeof(WORD), &ColNum );
		VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew )  );

		CString TitleTmp;
				
		SetWindowPos(&wndTop,0,0,m_bmInfo.bmWidth*2,m_bmInfo.bmHeight*2,SWP_NOMOVE);//offsetx,offsety+m_bmInfo.bmHeight,m_size.cx,18);
		if (m_Colors == 16)
			m_nBits = 4;
		else
			m_nBits = 8;

		if (m_ID1 == 0)
			TitleTmp.Format("200%% - %ux%u %u %s",m_bmInfo.bmWidth,m_bmInfo.bmHeight,m_Colors,
					CString(MAKEINTRESOURCE(IDS_TITLE_COLORS)));
		else
			TitleTmp.Format("200%% - %s %d + %s %d - %ux%u %u %s (%d BIT)",
					CString(MAKEINTRESOURCE(IDS_TITLE_IMAGE)),
					m_ID1, CString(MAKEINTRESOURCE(IDS_TITLE_PALETTE)),m_ID2,m_bmInfo.bmWidth,
					m_bmInfo.bmHeight,m_Colors,CString(MAKEINTRESOURCE(IDS_TITLE_COLORS)),m_nBits);
					
		this->SetWindowText(TitleTmp);
			
		InvalidateRect(NULL,FALSE);
		
   }

}

void CBitmapDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	UINT nZoom;
	CString TitleTmp;
	
	nZoom = (cx * 100) / m_bmInfo.bmWidth;
	if (m_ID1 == 0)
		TitleTmp.Format("%d%% - %ux%u %u %s",nZoom,m_bmInfo.bmWidth,m_bmInfo.bmHeight,m_Colors,
					CString(MAKEINTRESOURCE(IDS_TITLE_COLORS)));
	else
		TitleTmp.Format("%d%% - %s %d + %s %d - %ux%u %u %s (%d BIT)",
					nZoom,CString(MAKEINTRESOURCE(IDS_TITLE_IMAGE)),
					m_ID1, CString(MAKEINTRESOURCE(IDS_TITLE_PALETTE)),m_ID2,m_bmInfo.bmWidth,
					m_bmInfo.bmHeight,m_Colors,CString(MAKEINTRESOURCE(IDS_TITLE_COLORS)),m_nBits);
					
	this->SetWindowText(TitleTmp);
			
	InvalidateRect(NULL,FALSE);

}
