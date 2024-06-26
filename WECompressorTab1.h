#if !defined(AFX_WECOMPRESSORTAB1_H__0EA18662_84B6_11D7_A189_444553540000__INCLUDED_)
#define AFX_WECOMPRESSORTAB1_H__0EA18662_84B6_11D7_A189_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WECompressorTab1.h : header file
//

#include "PPToolTip.h"
#include "BtnST.h"

/////////////////////////////////////////////////////////////////////////////
// CWECompressorTab1 dialog

class CWECompressorTab1 : public CDialog
{
// Construction
public:
	CWECompressorTab1(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWECompressorTab1();
	CXTabCtrl *m_pTab;
// Dialog Data
	//{{AFX_DATA(CWECompressorTab1)
	enum { IDD = IDD_WECOMPRESSOR_TAB1 };
		CListCtrl	m_PalettesList;
		CListCtrl	m_ImagesList;
		int			m_ComboIndex;
		BOOL		m_ManualImage;
		BOOL		m_ManualPalette;
		CString		m_OffsetImage;
		CString		m_OffsetPal;
		int			m_BitPalette;
		int			m_ImageX;
		int			m_ImageY;		
		int			m_ComboGame;
		BOOL		m_EnableTex;
		BOOL		m_UseSameFile;
	//}}AFX_DATA

	CFilesStructList m_ImageFileList;
	CFilesStructList m_PaletteFileList;
	CString m_ImageFile;
	CString m_PaletteFile;
	CString m_DestFile;
	UINT	m_ActualImagesIndex;
	UINT	m_ActualPalettesIndex;
	UINT	m_ActualColorsNumber;
	BOOL	m_FirstOK;
	BOOL	m_SecondOK;	
	BOOL	m_ThirdOK;	

	void FreeListMem(BOOL Select);
	void AddHelpTTips();
	BOOL UpdateFileList(BOOL Select);
	void OnChangeFocus(BOOL Select);
	BOOL CreateTIM(CString NameFile);
	BOOL CreateBMP(CString NameFile);
	BOOL CreateRAW(CString NameFile);
	BOOL CreateTXT(CString NameFile);
	BOOL OffsetMatch(BYTE Code);
	BOOL OffsetTranslate(BYTE Code,ULONG *Offset);
	BOOL SearchImages();
	BOOL SearchPalettes();
	BOOL SetManualImage();
	BOOL SetManualPalette();
	BOOL UpdateMyData(BOOL bValid);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWECompressorTab1)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:	

	CButtonST	m_FOpenFirst;
	CButtonST	m_FOpenSec;
	CButtonST	m_FOpenThird;
	CPPToolTip  m_ctlTT;

	// Generated message map functions
	//{{AFX_MSG(CWECompressorTab1)
		virtual BOOL OnInitDialog();
		afx_msg void OnInfo();
		afx_msg void OnBrowseImage();
		afx_msg void OnBrowsePalette();
		afx_msg void OnBrowseDest();
		afx_msg void OnButtonMakeFile();
		afx_msg void OnClickListPalettes(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnClickListImages(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnRclickListPalettes(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnRclickListImages(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnKeydownListPalettes(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnKeydownListImages(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnSelchangeComboSelfile();
		afx_msg void OnButtonViewImage();
		afx_msg void OnClickManualImages();
		afx_msg void OnClickManualPalette();
		afx_msg void OnQuit();
		afx_msg void OnSelchangeComboPalette();
	afx_msg void OnChangeGameSel();
	afx_msg void OnDblClickListPalettes(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblClickListImages(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckImageAndPal();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WECOMPRESSORTAB1_H__0EA18662_84B6_11D7_A189_444553540000__INCLUDED_)
