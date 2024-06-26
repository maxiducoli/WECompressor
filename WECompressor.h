// WECompressor.h : main header file for the WECOMPRESSOR application
//

#if !defined(AFX_WECOMPRESSOR_H__7BC6B605_6523_11D7_A188_444553540000__INCLUDED_)
#define AFX_WECOMPRESSOR_H__7BC6B605_6523_11D7_A188_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "Structures.h"

/////////////////////////////////////////////////////////////////////////////
// CWECompressorApp:
// See WECompressor.cpp for the implementation of this class
//

class CWECompressorApp : public CWinApp
{
public:
	CWECompressorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWECompressorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWECompressorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WECOMPRESSOR_H__7BC6B605_6523_11D7_A188_444553540000__INCLUDED_)
