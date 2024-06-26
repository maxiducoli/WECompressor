#if !defined(AFX_BITMAPDIALOG_H__F8D408C3_9604_11D7_A189_444553540000__INCLUDED_)
#define AFX_BITMAPDIALOG_H__F8D408C3_9604_11D7_A189_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BitmapDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBitmapDialog dialog

class CBitmapDialog : public CDialog
{
// Construction
public:
	CBitmapDialog(CString filepath,int ID1,int ID2,int Colors,CWnd* pParent = NULL);	// standard constructor
	virtual ~CBitmapDialog();

	CString		m_BMPFileTmp;
	int			m_ID1,m_ID2,m_Colors;
	UINT		m_nBits;

	void OnShow();

// Dialog Data
	//{{AFX_DATA(CBitmapDialog)
	enum { IDD = IDD_SCROLLBITMAP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBitmapDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CDC m_dcMem;            // Compatible Memory DC for dialog
	
	HBITMAP m_hBmpOld;    // Handle of old bitmap to save
	HBITMAP m_hBmpNew;    // Handle of new bitmap from file
		
	BITMAP m_bmInfo;        // Bitmap Information structure	

	// Generated message map functions
	//{{AFX_MSG(CBitmapDialog)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITMAPDIALOG_H__F8D408C3_9604_11D7_A189_444553540000__INCLUDED_)
