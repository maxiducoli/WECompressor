// WECompressorDlg.h : header file
//

#if !defined(AFX_WECOMPRESSORDLG_H__7BC6B607_6523_11D7_A188_444553540000__INCLUDED_)
#define AFX_WECOMPRESSORDLG_H__7BC6B607_6523_11D7_A188_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabCtrlSSL.h"
#include "MyToolTipCtrl.h"    // Added by ClassView
#include "BtnST.h"

//
//  TIM File structures and keywords
//

#define TIM_ID1         0x10              /* TIM ID    */
#define TIM_4Bit        0x08              /* USE CLUT  */
#define TIM_8Bit        0x09              /* USE CLUT  */
#define TIM_16Bit       0x02              /* NO CLUT   */
#define TIM_24Bit       0x03              /* NO CLUT   */

typedef struct 
{
	DWORD   id1;
	DWORD   type;
	DWORD   nextlen;
} TIM_HEADER;

typedef struct
{
	WORD	vramx;
	WORD	vramy;
	WORD	ncols;
	WORD	npals;
} TIM_CLUTINFO;

typedef struct
{
	DWORD	blocklen;
	WORD    vramx;
	WORD	vramy;
	WORD	xsize;
	WORD	ysize;
} TIM_DATAINFO;

typedef struct
{
	WORD	ID;
	WORD	VramX;
	WORD	VramY;
	WORD	width;
	WORD	height;
	WORD	unknown3;
	WORD	offset;
	WORD	separator;
	WORD	unknown5;
	WORD	unknown6;
	WORD	unknown7;
	WORD	unknown8;
	WORD	unknown9;
	WORD	unknown10;
	WORD	unknown11;
	WORD	unknown12;
} DATA_HEADER;

//
// BMP keywords...
//

#define BMFH_SIZE               (14)
#define BMIH_SIZE               (40)
#define RGB_SIZE                (4*256)
#define TOTAL_HEADER_SIZE       (BMFH_SIZE + BMIH_SIZE + RGB_SIZE)

//
//

class CFilesStruct
{
public:	
	DATA_HEADER	m_Header;
	BYTE *m_DataBlock;
	ULONG m_BlockLen;
	DWORD m_OffsetReal;
	BYTE m_MutiplyFactor;
	BYTE m_MultiplyY;
	
};

typedef CTypedPtrList<CPtrList, CFilesStruct*> CFilesStructList;

/////////////////////////////////////////////////////////////////////////////
// CWECompressorDlg dialog

class CWECompressorDlg : public CDialog
{
// Construction
public:
	CWECompressorDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CWECompressorDlg();

// Dialog Data
	//{{AFX_DATA(CWECompressorDlg)
	enum { IDD = IDD_WECOMPRESSOR_DIALOG };
	CListCtrl	m_PalettesList;
	CListCtrl	m_ImagesList;
	int			m_ComboIndex;
	BOOL	m_ManualImage;
	BOOL	m_ManualPalette;
	CString	m_OffsetImage;
	CString	m_OffsetPal;
	int		m_BitPalette;
	int		m_ImageX;
	int		m_ImageY;
	//}}AFX_DATA

	CFilesStructList m_ImageFileList;
	CFilesStructList m_PaletteFileList;
	CTabCtrlSSL	m_MainTab;
	CString m_ImageFile;
	CString m_PaletteFile;
	CString m_DestFile;
	UINT	m_ActualImagesIndex;
	UINT	m_ActualPalettesIndex;
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
	BOOL SearchImages();
	BOOL SearchPalettes();
	BOOL SetManualImage();
	BOOL SetManualPalette();
	BOOL UpdateMyData(BOOL bValid);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWECompressorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CButtonST	m_FOpenFirst;
	CButtonST	m_FOpenSec;
	CButtonST	m_FOpenThird;
	CMyToolTipCtrl	m_ctlTT;
	// Property pages
	CWECompressorDlgTab1 m_Tab1;
	//CWECompressorDlgTab2 m_Tab2;

	// Generated message map functions
	//{{AFX_MSG(CWECompressorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WECOMPRESSORDLG_H__7BC6B607_6523_11D7_A188_444553540000__INCLUDED_)
