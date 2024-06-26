// WECompressorDlg.h : header file
//

#if !defined(AFX_WECOMPRESSORDLG_H__7BC6B607_6523_11D7_A188_444553540000__INCLUDED_)
#define AFX_WECOMPRESSORDLG_H__7BC6B607_6523_11D7_A188_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PPToolTip.h"
#include "XTabCtrl.h"
#include "WECompressorTab1.h"
#include "WECompressorTab2.h"
#include "WECompressorTab3.h"

/////////////////////////////////////////////////////////////////////////////
// CWECompressorDlg dialog

class CWECompressorDlg : public CDialog
{
// Construction
public:
	CWECompressorDlg(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data
	//{{AFX_DATA(CWECompressorDlg)
		enum { IDD = IDD_WECOMPRESSOR_DIALOG };
		CXTabCtrl m_MainTab;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CWECompressorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	// Property pages
	CWECompressorTab1 *m_Tab1;
	CWECompressorTab2 *m_Tab2;
	CWECompressorTab3 *m_Tab3;

	// Generated message map functions
	//{{AFX_MSG(CWECompressorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();	
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WECOMPRESSORDLG_H__7BC6B607_6523_11D7_A188_444553540000__INCLUDED_)
