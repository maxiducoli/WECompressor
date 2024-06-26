#if !defined(AFX_WECOMPRESSORTAB3_H__5DC62CA3_96B3_11D7_A189_444553540000__INCLUDED_)
#define AFX_WECOMPRESSORTAB3_H__5DC62CA3_96B3_11D7_A189_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WECompressorTab3.h : header file
//

#include "PPToolTip.h"
#include "BtnST.h"

/////////////////////////////////////////////////////////////////////////////
// CWECompressorTab3 dialog

class CWECompressorTab3 : public CDialog
{
// Construction
public:
	CWECompressorTab3(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWECompressorTab3();

	CXTabCtrl *m_pTab;
	BOOL	m_FlagOK[12];
	CString	m_NewTexFile;
	CString	m_TexFileGioc1;
	CString	m_TexFileGioc2;
	CString	m_PalFileGioc1;
	CString	m_PalFileGioc2;
	CString	m_PalFilePort1;
	CString	m_PalFilePort2;
	CString	m_TexFileManLun1;
	CString	m_TexFileManLun2;
	CString	m_TexFlagFile;
	CString	m_PalFlagFile;
	CString	m_TexRefreeFile;
	UINT	m_ActualColorsNumber;

	void AddHelpTTips();
	void InitializeButtons();
	BOOL CreateTEX();
	BOOL CheckValidity();
	BOOL UpdateMyData(BOOL bValid);
	BOOL UpdateControl(int IDCtrl,CString *NameFile,int Length,BOOL bValid);
	int BrowseFileTex(WORD Title,CString *NameFile,int IDCtrl,int Num,int IdxCtrl);
	void ViewImage(CString NameFileImage,CString NameFilePalette,int IdxImage,int IdxPal);
	BOOL DecodeImage(BYTE *BufSrc,BYTE **BufDest,ULONG xsize,ULONG ysize,BYTE depth,BYTE ComprFlag);
	BOOL CreateBMP(CString NameFileNew,CString NameFileImage,CString NameFilePalette,int IdxImage,
					int IdxPal);
	void OnChangeComboSel(int IdxAutoActual,int *IdxAutoOther,int IdxTexActual,BOOL FlagCurrent,
						BOOL *FlagNewGioc,BOOL *FlagNewPort,int ComboSelPalGioc,int SelButtonPG,
						int ComboSelPalPort,int SelButtonPP,int FilePalGioc,int FilePalPort,
						CString TexFileActual,CString *PalFileGioc,int *IdxPalGioc,
						CString *PalFilePort,int *IdxPalPort);
	BOOL GetImageBlock(CString FileName,int FileType,BYTE **BufDest,UINT *BlockLen);
	BOOL GetLargeImageBlock(CString FileName,int FileType,BYTE **BufDest,BYTE **BufDest2,
							UINT *BlockLen,UINT *BlockLen2);
	BOOL GetClutBlock(CString FileName,int FileType,BYTE **Clut);
	BOOL CreateAllFiles(CString NameFile,BYTE *BufImage,BYTE *Clut,BYTE *BufCompr,UINT BlockLen);
	BOOL CreateAllCompleteFiles(CString NameFile,BYTE *BufImage,BYTE *BufImage2,BYTE *Clut);
	BOOL ExtractAllFiles(CString TexFile,CString DirPath);


// Dialog Data
	//{{AFX_DATA(CWECompressorTab3)
	enum { IDD = IDD_WECOMPRESSOR_TAB3 };
	int		m_GameType;
	int		m_IdxTexGio1;
	int		m_IdxTexGio2;
	int		m_IdxTexMan1;
	int		m_IdxTexMan2;
	int		m_IdxTexTifo;
	int		m_IdxTexRefree;
	int		m_IdxPalFlag;
	int		m_IdxPalGioc1;
	int		m_IdxPalGioc2;
	int		m_IdxPalPort1;
	int		m_IdxPalPort2;
	int		m_IdxAutoGio1;
	int		m_IdxAutoGio2;
	int		m_IdxAutoMan1;
	int		m_IdxAutoMan2;
	int		m_IdxAutoFlag;
	BOOL	m_LargeTex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWECompressorTab3)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CButtonST	m_FOpen1;
	CButtonST	m_FOpen2;
	CButtonST	m_FOpen3;
	CButtonST	m_FOpen4;
	CButtonST	m_FOpen5;
	CButtonST	m_FOpen6;
	CButtonST	m_FOpen7;
	CButtonST	m_FOpen8;
	CButtonST	m_FOpen9;
	CButtonST	m_FOpen10;
	CButtonST	m_FOpen11;
	CButtonST	m_FOpen12;
	CButtonST	m_FView2;
	CButtonST	m_FView5;
	CButtonST	m_FView6;
	CButtonST	m_FView8;
	CButtonST	m_FView11;
	CButtonST	m_FView12;	
	
	CPPToolTip  m_ctlTT;
	// Generated message map functions
	//{{AFX_MSG(CWECompressorTab3)
	virtual BOOL OnInitDialog();
	afx_msg void OnQuit();
	afx_msg void OnBrowseTexGioc1();
	afx_msg void OnBrowseTexGioc2();
	afx_msg void OnBrowseTexMan1();
	afx_msg void OnBrowseTexMan2();
	afx_msg void OnBrowseNewTex();
	afx_msg void OnBrowseTexFlag();
	afx_msg void OnBrowseTexRefree();
	afx_msg void OnBrowsePalGioc1();
	afx_msg void OnBrowsePalPort1();
	afx_msg void OnBrowsePalGioc2();
	afx_msg void OnBrowsePalPort2();
	afx_msg void OnBrowsePalFlag();
	afx_msg void OnViewTexGioc1();
	afx_msg void OnViewTexGioc2();
	afx_msg void OnViewTexMan1();
	afx_msg void OnViewTexMan2();
	afx_msg void OnViewTexFlag();
	afx_msg void OnViewTexRefree();
	afx_msg void OnInfo();
	afx_msg void OnChangeComboSelAutoFlag();
	afx_msg void OnChangeComboSelAutoMan1();
	afx_msg void OnChangeComboSelAutoGio1();
	afx_msg void OnChangeComboSelTexGio1();
	afx_msg void OnChangeComboSelTexGio2();
	afx_msg void OnChangeComboSelAutoMan2();
	afx_msg void OnChangeComboSelAutoGio2();
	afx_msg void OnChangeComboSelTexMan1();
	afx_msg void OnChangeComboSelTexMan2();
	afx_msg void OnButtonMakeTEX();
	afx_msg void OnLargeTexClick();
	afx_msg void OnButtonExtractTEX();
	afx_msg void OnChangeComboSelTexFlag();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WECOMPRESSORTAB3_H__5DC62CA3_96B3_11D7_A189_444553540000__INCLUDED_)
