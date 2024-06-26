#if !defined(AFX_WECOMPRESS_H__D664A141_5E51_11D7_A188_9D8EF7C41842__INCLUDED_)
#define AFX_WECOMPRESS_H__D664A141_5E51_11D7_A188_9D8EF7C41842__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WECompress.h : header file
//

#define HASHTAB  4096	// size of hash
#define N		 1024	// size of ring buffer 
#define F  		 34     // size of look ahead buffer
#define THRESHOLD 3     // minimum match length
						// if match_length is greater than this 

/////////////////////////////////////////////////////////////////////////////
// CWECompress window

class CWECompress
{
// Construction
public:
	CWECompress();
	virtual ~CWECompress();

	void InitTree(void);
	void InsertNode(UINT r);
	void DeleteNode(UINT r);
	void LocateNode(UINT r, UINT *match_len, UINT *match_pos);
	BOOL Compress(BYTE **BufDest, BYTE *BufSrc, ULONG *SizeResult, ULONG SizeSrc);	
	BOOL DeCompress(BYTE **BufDest, BYTE *BufSrc);
	LONG FindCompressedLength(BYTE *BufSrc);

private:
	BYTE ring_buff[N+F];
	UINT next[N+1+HASHTAB], prev[N+1]; /* reserve space for hash as sons */

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WECOMPRESS_H__D664A141_5E51_11D7_A188_9D8EF7C41842__INCLUDED_)
