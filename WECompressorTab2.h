#if !defined(AFX_WECOMPRESSORTAB2_H__97E81BA1_8583_11D7_A189_444553540000__INCLUDED_)
#define AFX_WECOMPRESSORTAB2_H__97E81BA1_8583_11D7_A189_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WECompressorTab2.h : header file
//

#include "PPToolTip.h"
#include "BtnST.h"

/////////////////////////////////////////////////////////////////////////////
// CWECompressorTab2 dialog

class CWECompressorTab2 : public CDialog
{
// Construction
public:
	CWECompressorTab2(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWECompressorTab2();
	CXTabCtrl *m_pTab;

// Dialog Data
	//{{AFX_DATA(CWECompressorTab2)
	enum { IDD = IDD_WECOMPRESSOR_TAB2 };
		CListCtrl	m_PalettesList;
		CListCtrl	m_ImagesList;
		int			m_ComboIndex;
		int			m_ComboPalIndex;
		CString		m_OffsetImage;
		CString		m_OffsetPal;
		BOOL		m_ManualImage;
		BOOL		m_ManualPalette;
		BOOL		m_AutomaticPal;		
		BOOL		m_AdvancedMode;
		BOOL		m_EnableTex;
		int			m_ComboGame;
		BOOL		m_UseSameFile;
	//}}AFX_DATA

	CFilesStructList m_ImageFileList;
	CFilesStructList m_PaletteFileList;
	CString m_ImageFile;
	CString m_PaletteFile;
	CString m_SourceImageFile;
	CString m_SourcePaletteFile;
	UINT	m_ActualImagesIndex;
	UINT	m_ActualPalettesIndex;
	UINT	m_ActualColorsNumber;
	BOOL	m_FirstOK;
	BOOL	m_SecondOK;	
	BOOL	m_ThirdOK;
	BOOL	m_FourthOK;

	void FreeListMem(BOOL Select);
	void AddHelpTTips();
	BOOL UpdateFileList(BOOL Select);
	void OnChangeFocus(BOOL Select);
	BOOL CreateBMP(CString NameFile);
	BOOL CreateFiles();
	BOOL InsertInFiles();
	BOOL OffsetMatch(BYTE Code);
	BOOL OffsetTranslate(BYTE Code,ULONG *Offset);
	BOOL DecodeImage(BYTE *BufSrc,BYTE **BufDest,ULONG xsize,ULONG ysize,BYTE depth,BYTE ComprFlag);
	BOOL SearchImages();
	BOOL SearchPalettes();
	BOOL SetManualImage();
	BOOL SetManualPalette();
	BOOL UpdateMyData(BOOL bValid);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWECompressorTab2)
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
	CButtonST	m_FOpenFourth;
	CPPToolTip  m_ctlTT;

	// Generated message map functions
	//{{AFX_MSG(CWECompressorTab2)
		virtual BOOL OnInitDialog();
		afx_msg void OnInfo();
		afx_msg void OnBrowseImage();
		afx_msg void OnBrowsePalette();		
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
		afx_msg void OnBrowseSrcImage();
		afx_msg void OnBrowseSrcPalette();
		afx_msg void OnClickAdvanced();
		afx_msg void OnCheckAutopal();
		afx_msg void OnSelchangeComboSelpal();
	afx_msg void OnChangeGameSel();
	afx_msg void OnCheckImageAndPal();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WECOMPRESSORTAB2_H__97E81BA1_8583_11D7_A189_444553540000__INCLUDED_)
