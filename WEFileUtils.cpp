#include "stdafx.h"
#include "WECompressor.h"
#include "WEFileUtils.h"
#include "WECompress.h"

/////////////////////////////////////////////////////////////////////////////

int			m_ComboIndex= 0;
int			m_ComboPalIndex= 0;
int			m_OffsetImage = 0;
int			m_OffsetPal= 0;
//BOOL		m_ManualImage= FALSE;
//BOOL		m_ManualPalette = FALSE;
BOOL		m_AutomaticPal= TRUE;
BOOL		m_UseSameFile= FALSE;

CString m_ImageFile= CString(" ");			//	Ruta de la imagen en el BIN
CString m_PaletteFile= CString(" ");		//	Ruta de la paleta
CString m_SourceImageFile= CString(" ");	//	
CString m_SourcePaletteFile= CString(" ");	//		
UINT	m_ActualImagesIndex= 0;				//	
UINT	m_ActualPalettesIndex = 0;			//	
UINT	m_ActualColorsNumber= 256;			//	


/////////////////////////////////////////////////////////////////////////////
// CWECompressorTab2 message handlers

BOOL CreateBMP(CString NameFile)
{
	CFile   fImage,fPalette,NewFileBMP;
	CString TempMsg;
	CFileException e;
	UINT j,depth,totalheader,rgbsize,usedcol,comprflag;
	ULONG xsize,ysize,xtemp,ImageOffset,ImageLength,nImageSize,nPaletteSize;
	BYTE rgbq[RGB_SIZE256];
		
	// open data file to write
	if (!NewFileBMP.Open(NameFile, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + NameFile);
		return FALSE;
	}


	if (!fImage.Open(m_SourceImageFile, CFile::modeRead | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error reading in source File ") + m_SourceImageFile);
		return FALSE;
	}

	nImageSize = fImage.GetLength();

	BYTE* ImageBuf = new BYTE[nImageSize];
	fImage.Read(ImageBuf, nImageSize);
	fImage.Close();

	if (!m_AutomaticPal)
	{
		if (!fPalette.Open(m_SourcePaletteFile, CFile::modeRead | CFile::typeBinary, &e))
		{
			AfxMessageBox(_T("Error reading in source File ") + m_SourcePaletteFile);
			return FALSE;	
		}
		
		nPaletteSize = fPalette.GetLength();
	
	}
	else
		nPaletteSize = 1;

	BYTE* PaletteBuf = new BYTE[nPaletteSize];
	if (!m_AutomaticPal)
	{
		fPalette.Read(PaletteBuf,nPaletteSize);
		fPalette.Close();
	}

	BYTE *pImage = ImageBuf;
	BYTE *pPalette = PaletteBuf;
	
	// palette reading
	if (!m_AutomaticPal)
	{
		if (m_ComboPalIndex == 0)
		{
			if (nPaletteSize == 16*2)
			{
				depth = 4;
				usedcol = 16;
				totalheader = TOTAL_HEADER_SIZE16;
				rgbsize = RGB_SIZE16;
			}
			else
			if (nPaletteSize == 256*2)
			{
				depth = 8;
				usedcol = 256;
				totalheader = TOTAL_HEADER_SIZE256;
				rgbsize = RGB_SIZE256;
			}
			else
				return FALSE;

			for (UINT col=0; col < nPaletteSize; col+=4)
			{				
				WORD* tempword = new WORD;
				memcpy(tempword,pPalette + (col/2), 2);
				rgbq[col] = ((WORD) (*tempword>>10)) << 3;
				rgbq[col+1] = ((WORD) (*tempword>>5)&0x1f) << 3;
				rgbq[col+2] = ((WORD) (*tempword)&0x1f) << 3;
				rgbq[col+3] = 0;

				delete tempword;
			}
		}
		else
		{
			if (nPaletteSize == 16*4)
			{
				depth = 4;
				usedcol = 16;
				totalheader = TOTAL_HEADER_SIZE16;
				rgbsize = RGB_SIZE16;
			}
			else
			if (nPaletteSize == 256*4)
			{
				depth = 8;
				usedcol = 256;
				totalheader = TOTAL_HEADER_SIZE256;
				rgbsize = RGB_SIZE256;
			}
			else
				return FALSE;

			for (UINT col=0; col < nPaletteSize; col++)
				rgbq[col] = *(pPalette + col);
			
		}
		
	
	}
	else
	{
		if (m_ComboIndex == 0)
		{
			BITMAPINFOHEADER bmih_read;

			memcpy(&bmih_read,pImage+BMFH_SIZE,sizeof(BITMAPINFOHEADER));			 
			depth = bmih_read.biBitCount;
		
			if (depth == 4)
			{
				totalheader = TOTAL_HEADER_SIZE16;
				rgbsize = RGB_SIZE16;
				usedcol = 16;
			}
			else
			if (depth == 8)
			{
				totalheader = TOTAL_HEADER_SIZE256;
				rgbsize = RGB_SIZE256;
				usedcol = 256;
			}
			else
				return FALSE;

			for (UINT col=0; col < rgbsize; col++)
				rgbq[col] = *(pImage + 54 + col);

		}
		else
		if (m_ComboIndex == 1)
		{
			TIM_HEADER THead_read;
	
			memcpy(&THead_read,pImage,sizeof(TIM_HEADER));

			if (THead_read.type == TIM_4Bit)
			{
				depth = 4;
				usedcol = 16;
				totalheader = TOTAL_HEADER_SIZE16;
				rgbsize = RGB_SIZE16;
			}
			else
			if (THead_read.type == TIM_8Bit)
			{
				depth = 8;
				usedcol = 256;
				totalheader = TOTAL_HEADER_SIZE256;
				rgbsize = RGB_SIZE256;
			}
			else
				return FALSE;

			for (WORD col=0; col < rgbsize; col+=4)
			{				
				WORD* tempword = new WORD;
				memcpy(tempword,pImage + 20 + (col/2), 2);
				rgbq[col] = ((WORD) (*tempword>>10)) << 3;
				rgbq[col+1] = ((WORD) (*tempword>>5)&0x1f) << 3;
				rgbq[col+2] = ((WORD) (*tempword)&0x1f) << 3;
				rgbq[col+3] = 0;

				delete tempword;
			}

		}
		else
			return FALSE;
		
	}

	m_ActualColorsNumber = usedcol;

	// image reading
	if (m_ComboIndex == 0)
	{
		BITMAPINFOHEADER bmih_read;

		memcpy(&bmih_read,pImage+BMFH_SIZE,sizeof(BITMAPINFOHEADER));
		xsize = bmih_read.biWidth;
		ysize = bmih_read.biHeight;
		comprflag = bmih_read.biCompression;
		ImageOffset = totalheader;
		ImageLength = xsize*ysize;
		
		if (depth == 4)
			ImageLength = ImageLength/2; 

	}
	else
	if (m_ComboIndex == 1)
	{		
		TIM_DATAINFO TData_read;
	
		memcpy(&TData_read,pImage+ 20 + usedcol*2,sizeof(TIM_DATAINFO));

		xsize = TData_read.xsize*2;
		ysize = TData_read.ysize;
		comprflag = BI_RGB;
		ImageLength = xsize*ysize;
		if (depth == 4)
			xsize = xsize*2;
			
		ImageOffset = 32 + usedcol*2;
		
	}
	else
	{
		xsize = 128;
		ysize = 128;
		comprflag = BI_RGB;
		ImageLength = xsize*ysize;
		if (depth == 4)
			ImageLength = ImageLength/2; 
		ImageOffset = 0;

	}

	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	
	bmfh.bfType = 0x4D42;// BM
	bmfh.bfSize = totalheader + (xsize*ysize*depth)/8;
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = totalheader;

	NewFileBMP.Write(&bmfh,sizeof( BITMAPFILEHEADER ));
	
	bmih.biSize = BMIH_SIZE;
	bmih.biWidth = xsize;
	bmih.biHeight = ysize;
	bmih.biPlanes = 1;
	bmih.biBitCount = depth;
	bmih.biCompression = comprflag;
	bmih.biSizeImage = (xsize*ysize*depth)/8;
	bmih.biXPelsPerMeter = 0;
	bmih.biYPelsPerMeter = 0;
	bmih.biClrUsed = usedcol;
	bmih.biClrImportant = 0;
	
	NewFileBMP.Write(&bmih,sizeof( BITMAPINFOHEADER ));
		
	// write converted CLUT RGB table (psx uses 15bit RGB)
	NewFileBMP.Write(rgbq,rgbsize);

	BYTE* pImageData = new BYTE[ImageLength];
	if (m_ComboIndex == 0)
	{
		memcpy(pImageData,pImage+ImageOffset,ImageLength);

	}
	else
	//if (m_ComboIndex == 1)
	{
		BYTE* pData = pImage+ImageOffset;
		j=0;
		if (depth == 4)
		{
			// 4 bit
			xtemp =  xsize/2;
			for(long y1=ysize-1;y1>=0;y1--)
			{
				for(unsigned long x1=0;x1<xtemp;x1++)
				{
					pImageData[j] = (pData[(y1*xtemp)+x1])>>4;
					pImageData[j] |= ((pData[(y1*xtemp)+x1] << 4) & 0xF0);
					j++;
				}
			}

		}
		else
		{
			// 8 bit
			xtemp = xsize;
			for(long y1=ysize-1;y1>=0;y1--){
				for(unsigned long x1=0;x1<xtemp;x1++)
					pImageData[j++] = pData[(y1*xtemp)+x1];}
		}

	}

	// write Data block
	NewFileBMP.Write(pImageData,ImageLength);

	delete ImageBuf;
	delete PaletteBuf;
	delete pImageData;

	NewFileBMP.Close();

	return TRUE;

}

BOOL DecodeImage(BYTE *BufSrc,BYTE **BufDest,ULONG xsize,ULONG ysize,
									BYTE depth,BYTE ComprFlag)
{
	ULONG xtemp;
	UINT j;
	
	BYTE *pDest = *BufDest;

	j=0;
	if (depth == 4)
	{
		// 4 bit
		xtemp =  xsize/2;
		if (ComprFlag == BI_RGB)
		{		
			for(long y1=ysize-1;y1>=0;y1--)
			{
				for(unsigned long x1=0;x1<xtemp;x1++)
				{
					pDest[j] = (BufSrc[(y1*xtemp)+x1])>>4;
					pDest[j] |= ((BufSrc[(y1*xtemp)+x1] << 4) & 0xF0);
					j++;
				}
			}
		}
		else
		{
			// BI_RLE4
			BOOL bEOB = FALSE;
			BYTE *pSrc = BufSrc;
			
			int code1, code2, i, k, hi=0, abs_cou=0, adj_cou=0;

			BYTE* pTempData = new BYTE[xtemp*ysize];
			pDest = pTempData;

			BYTE *sta_ptr = pDest;
			for(i=0;i<xtemp*ysize && !bEOB;i+=2) 
			{
				code1 = *pSrc++;
				code2 = *pSrc++;

				if (abs_cou) 
				{
					if (hi)
						*pDest++ |= (code1 >> 4);
					else
						*pDest = (code1 & 0xF0);
					abs_cou--;
					hi ^= 1;
					
					if (abs_cou) 
					{
						if (hi)
							*pDest++ |= (code1 & 0x0F);
						else
							*pDest = (code1 << 4);
						abs_cou--;
						hi ^= 1;
					}
					
					if( abs_cou )
					{
						if (hi)
							*pDest++ |= (code2 >> 4);
						else
							*pDest = (code2 & 0xF0);
						abs_cou--;
						hi ^= 1;
					}
					
					if( abs_cou )
					{
						if (hi)
							*pDest++ |= (code2 & 0x0F);
						else
							*pDest = (code2 << 4);
						abs_cou--;
						hi ^= 1;
					}
					continue;

				}
									
				if (code1 == 0)  // RLE_COMMAND
				{
					switch (code2) // Escape
					{
						case 0:	// End of line escape EOL
								if( !adj_cou )  adj_cou = 3-((pDest-sta_ptr+3)%4);
								for(i=0;i<adj_cou;i++) *pDest++ = 0;
								continue;
						case 1: // End of block escape EOB
								if( !adj_cou )  adj_cou = 3-((pDest-sta_ptr+3)%4);
								for(i=0;i<adj_cou;i++) *pDest++ = 0;
								bEOB = TRUE;
								break;
						case 2: // Delta escape. RLE_DELTA								
								break;
						default: // Literal packet
								abs_cou = code2;
								break;
					}	
					continue;
				}
			
				if (!bEOB) // Literal
				{
					for(k=0;k < code1 / 2;k++ )
					{
						if (hi) 
						{
							*pDest++ |= (code2 >> 4);
							*pDest = (code2 & 0x0F);
						} 
						else 
							*pDest++ = code2;
					}

					if (code1%2) 
					{
						if (hi)
							*pDest++ |= (code2 >> 4);
						else 
							*pDest = (code2 & 0xF0);
						hi ^= 1;
					}

				}
			}

			pDest = *BufDest;
			for(long y1=ysize-1;y1>=0;y1--)
			{
				for(unsigned long x1=0;x1<xtemp;x1++)
				{
					pDest[j] = (pTempData[(y1*xtemp)+x1])>>4;
					pDest[j] |= ((pTempData[(y1*xtemp)+x1] << 4) & 0xF0);
					j++;
				}
			}

			delete pTempData;

		}
	}
	else
	{
		// 8 bit
		
		xtemp = xsize;
		if (ComprFlag == BI_RGB)
		{		
			for(long y1=ysize-1;y1>=0;y1--){
				for(unsigned long x1=0;x1<xtemp;x1++)
					pDest[j++] = BufSrc[(y1*xtemp)+x1];}
		}
		else
		{
			// BI_RLE8
			BOOL bEOB = FALSE;
			BYTE *pSrc = BufSrc;
			
			int code1, code2, i, k, abs_cou=0, adj_cou=0;

			BYTE* pTempData = new BYTE[xtemp*ysize];
			pDest = pTempData;

			BYTE *sta_ptr = pDest;
			for(i=0;i<xtemp*ysize && !bEOB;i+=2) 
			{
				code1 = *pSrc++;
				code2 = *pSrc++;

				if (abs_cou) 
				{
					*pDest++ = code1;
					abs_cou--;
					if (abs_cou) 
					{
						*pDest++ = code2;
						abs_cou--;
					}
					continue;
				}
					
				if (code1 == 0)  // RLE_COMMAND
				{
					switch (code2) // Escape
					{
						case 0:	// End of line escape EOL
								if( !adj_cou )  adj_cou = 3-((pDest-sta_ptr+3)%4);
								for(i=0;i<adj_cou;i++) *pDest++ = 0;
								continue;
						case 1: // End of block escape EOB
								if( !adj_cou )  adj_cou = 3-((pDest-sta_ptr+3)%4);
								for(i=0;i<adj_cou;i++) *pDest++ = 0;
								bEOB = TRUE;
								break;
						case 2: // Delta escape. RLE_DELTA								
								break;
						default: // Literal packet
								abs_cou = code2;
								break;
					}	
					continue;
				}
			
				if (!bEOB) // Literal
					for(k=0;k < code1;k++ ) 
						*pDest++ = code2;				
			}

			pDest = *BufDest;
			for(long y1=ysize-1;y1>=0;y1--){
				for(unsigned long x1=0;x1<xtemp;x1++)
					pDest[j++] = pTempData[(y1*xtemp)+x1];}

			delete pTempData;
		}
	}

	return TRUE;
}

BOOL CreateFiles()
{
	CFile   fImage,fPalette,NewFileImage,NewFileCLUT,NewFilePAL;
	CString TempMsg,mPalettePAL;
	CFileException e;
	UINT j,depth,totalheader,rgbsize,usedcol,comprflag;
	ULONG xsize,ysize,ImageOffset,ImageLength,nImageSize,nPaletteSize;
	BYTE rgbq[RGB_SIZE256];
	BYTE clut[RGB_SIZE256/2];
	BOOL Result;
		
	// open data file to write
	if (!NewFileImage.Open(m_ImageFile, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + m_ImageFile);
		return FALSE;
	}

	Result = TRUE;
	mPalettePAL = m_PaletteFile;
	//mPalettePAL.Replace(".clu",".pal");	
	// open data file to write
	if (!NewFilePAL.Open(mPalettePAL, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + mPalettePAL);
		return FALSE;
	}
	// open data file to write
	if (!NewFileCLUT.Open(m_PaletteFile, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + m_PaletteFile);
		return FALSE;
	}

	if (!fImage.Open(m_SourceImageFile, CFile::modeRead | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error reading in source File ") + m_SourceImageFile);
		return FALSE;
	}
	
	nImageSize = fImage.GetLength();

	BYTE* ImageBuf = new BYTE[nImageSize];
	fImage.Read(ImageBuf, nImageSize);
	fImage.Close();

	if (!m_AutomaticPal)
	{
		if (!fPalette.Open(m_SourcePaletteFile, CFile::modeRead | CFile::typeBinary, &e))
		{
			AfxMessageBox(_T("Error reading in source File ") + m_SourcePaletteFile);
			return FALSE;	
		}
		
		nPaletteSize = fPalette.GetLength();
	
	}
	else
		nPaletteSize = 1;

	BYTE* PaletteBuf = new BYTE[nPaletteSize];
	if (!m_AutomaticPal)
	{
		fPalette.Read(PaletteBuf,nPaletteSize);
		fPalette.Close();
	}

	BYTE *pImage = ImageBuf;
	BYTE *pPalette = PaletteBuf;
	
	// palette reading
	if (!m_AutomaticPal)
	{
		if (m_ComboPalIndex == 0)
		{
			if (nPaletteSize == 16*2)
			{
				depth = 4;
				usedcol = 16;
				totalheader = TOTAL_HEADER_SIZE16;
				rgbsize = RGB_SIZE16;
			}
			else
			if (nPaletteSize == 256*2)
			{
				depth = 8;
				usedcol = 256;
				totalheader = TOTAL_HEADER_SIZE256;
				rgbsize = RGB_SIZE256;
			}
			else
				return FALSE;


			memcpy(clut,pPalette, nPaletteSize);

			for (WORD col=0; col < nPaletteSize; col+=4)
			{				
				WORD* tempword = new WORD;
				memcpy(tempword,pPalette + (col/2), 2);
				rgbq[col] = ((WORD) (*tempword>>10)) << 3;
				rgbq[col+1] = ((WORD) (*tempword>>5)&0x1f) << 3;
				rgbq[col+2] = ((WORD) (*tempword)&0x1f) << 3;
				rgbq[col+3] = 0;				

				delete tempword;
			}
		}
		else
		{
			if (nPaletteSize == 16*4)
			{
				depth = 4;
				usedcol = 16;
				totalheader = TOTAL_HEADER_SIZE16;
				rgbsize = RGB_SIZE16;
			}
			else
			if (nPaletteSize == 256*4)
			{
				depth = 8;
				usedcol = 256;
				totalheader = TOTAL_HEADER_SIZE256;
				rgbsize = RGB_SIZE256;
			}
			else
				return FALSE;

			memcpy(rgbq,pPalette,nPaletteSize);

			j=0;
			for (UINT col=0; col < nPaletteSize; col+=4)
			{			
				WORD tempword = (((BYTE) rgbq[col+2] >> 3 | 
								 ((WORD) (rgbq[col+1] >> 3) << 5)) | 
								 (((DWORD) (BYTE) (rgbq[col] >> 3)) << 10));
				clut[j++] = LOBYTE(tempword);
				clut[j++] = HIBYTE(tempword);
				
			}

		}
		
	
	}
	else
	{
		if (m_ComboIndex == 0)
		{
			BITMAPINFOHEADER bmih_read;

			memcpy(&bmih_read,pImage+BMFH_SIZE,sizeof(BITMAPINFOHEADER));			 
			depth = bmih_read.biBitCount;
			
			if (depth == 4)
			{
				totalheader = TOTAL_HEADER_SIZE16;
				rgbsize = RGB_SIZE16;
				usedcol = 16;
			}
			else
			if (depth == 8)
			{
				totalheader = TOTAL_HEADER_SIZE256;
				rgbsize = RGB_SIZE256;
				usedcol = 256;
			}
			else
				return FALSE;

			memcpy(rgbq,pImage + 54,rgbsize);

			j=0;
			for (UINT col=0; col < rgbsize; col+=4)
			{				
				WORD tempword = (((BYTE) rgbq[col+2] >> 3 | 
								 ((WORD) (rgbq[col+1] >> 3) << 5)) | 
								 (((DWORD) (BYTE) (rgbq[col] >> 3)) << 10));
				clut[j++] = LOBYTE(tempword);
				clut[j++] = HIBYTE(tempword);
				
			}


		}
		else
		if (m_ComboIndex == 1)
		{
			TIM_HEADER THead_read;
	
			memcpy(&THead_read,pImage,sizeof(TIM_HEADER));

			if (THead_read.type == TIM_4Bit)
			{
				depth = 4;
				usedcol = 16;
				totalheader = TOTAL_HEADER_SIZE16;
				rgbsize = RGB_SIZE16;
			}
			else
			if (THead_read.type == TIM_8Bit)
			{
				depth = 8;
				usedcol = 256;
				totalheader = TOTAL_HEADER_SIZE256;
				rgbsize = RGB_SIZE256;
			}
			else
				return FALSE;

			memcpy(clut,pImage + 20, usedcol*2);
			for (WORD col=0; col < rgbsize; col+=4)
			{				
				WORD* tempword = new WORD;
				memcpy(tempword,pImage + 20 + (col/2), 2);
				rgbq[col] = ((WORD) (*tempword>>10)) << 3;
				rgbq[col+1] = ((WORD) (*tempword>>5)&0x1f) << 3;
				rgbq[col+2] = ((WORD) (*tempword)&0x1f) << 3;
				rgbq[col+3] = 0;

				delete tempword;
			}

		}
		else
			return FALSE;
		
	}

	// image reading
	if (m_ComboIndex == 0)
	{
		BITMAPINFOHEADER bmih_read;

		memcpy(&bmih_read,pImage+BMFH_SIZE,sizeof(BITMAPINFOHEADER));
		xsize = bmih_read.biWidth;
		ysize = bmih_read.biHeight;
		comprflag = bmih_read.biCompression;
		ImageOffset = totalheader;
		ImageLength = xsize*ysize;
		if (depth == 4)
			ImageLength = ImageLength/2; 

	}
	else
	if (m_ComboIndex == 1)
	{		
		TIM_DATAINFO TData_read;
	
		memcpy(&TData_read,pImage+ 20 + usedcol*2,sizeof(TIM_DATAINFO));

		xsize = TData_read.xsize*2;
		ysize = TData_read.ysize;		
		ImageLength = xsize*ysize;
		ImageOffset = 32 + usedcol*2;
		
	}
	else
	{
		xsize = 128;
		ysize = 128;
		ImageLength = xsize*ysize;
		if (depth == 4)
			ImageLength = ImageLength/2; 
		ImageOffset = 0;

	}

	// write CLUT (psx uses 15bit RGB)
	NewFileCLUT.Write(clut,rgbsize/2);

	// write converted CLUT RGB table (psx uses 15bit RGB)
	NewFilePAL.Write(rgbq,rgbsize);

	BYTE* pImageData = new BYTE[ImageLength];
	if (m_ComboIndex == 0)
	{
		BYTE* pImageTemp = new BYTE[ImageLength];

		Result = DecodeImage(pImage+ImageOffset,&pImageTemp,xsize,ysize,depth,comprflag);
		
		CWECompress tempclass;
			
		tempclass.Compress(&pImageData,pImageTemp,&ImageLength,ImageLength);

		delete pImageTemp;
	}
	else
	//if (m_ComboIndex == 1)
	{
		CWECompress tempclass;
			
		tempclass.Compress(&pImageData,pImage+ImageOffset,&ImageLength,ImageLength);
		
	}

	// write Data block
	NewFileImage.Write(pImageData,ImageLength);

	delete ImageBuf;
	delete PaletteBuf;
	delete pImageData;

	NewFileImage.Close();
	NewFileCLUT.Close();
	NewFilePAL.Close();

	return Result;

}

BOOL CreateNewFiles(CString m_ImageFile, CString m_PaletteFile, CString m_SourceImageFile,
					CString m_SourcePaletteFile, int m_ComboIndex, int m_ComboPalIndex, bool m_AutomaticPal)
{
	CFile   fImage, fPalette, NewFileImage, NewFileCLUT, NewFilePAL;
	CString TempMsg, mPalettePAL;
	CFileException e;
	UINT j, depth, totalheader, rgbsize, usedcol, comprflag;
	ULONG xsize, ysize, ImageOffset, ImageLength, nImageSize, nPaletteSize;
	BYTE rgbq[RGB_SIZE256];
	BYTE clut[RGB_SIZE256 / 2];
	BOOL Result;

	// open data file to write
	if (!NewFileImage.Open(m_ImageFile, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + m_ImageFile);
		return FALSE;
	}

	Result = TRUE;
	mPalettePAL = m_PaletteFile;
	//mPalettePAL.Replace(".clu",".pal");	
	// open data file to write
	if (!NewFilePAL.Open(mPalettePAL, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + mPalettePAL);
		return FALSE;
	}
	// open data file to write
	if (!NewFileCLUT.Open(m_PaletteFile, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + m_PaletteFile);
		return FALSE;
	}

	if (!fImage.Open(m_SourceImageFile, CFile::modeRead | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error reading in source File ") + m_SourceImageFile);
		return FALSE;
	}

	nImageSize = fImage.GetLength();

	BYTE* ImageBuf = new BYTE[nImageSize];
	fImage.Read(ImageBuf, nImageSize);
	fImage.Close();

	if (!m_AutomaticPal)
	{
		if (!fPalette.Open(m_SourcePaletteFile, CFile::modeRead | CFile::typeBinary, &e))
		{
			AfxMessageBox(_T("Error reading in source File ") + m_SourcePaletteFile);
			return FALSE;
		}

		nPaletteSize = fPalette.GetLength();

	}
	else
		nPaletteSize = 1;

	BYTE* PaletteBuf = new BYTE[nPaletteSize];
	if (!m_AutomaticPal)
	{
		fPalette.Read(PaletteBuf, nPaletteSize);
		fPalette.Close();
	}

	BYTE *pImage = ImageBuf;
	BYTE *pPalette = PaletteBuf;

	// palette reading
	if (!m_AutomaticPal)
	{
		if (m_ComboPalIndex == 0)
		{
			if (nPaletteSize == 16 * 2)
			{
				depth = 4;
				usedcol = 16;
				totalheader = TOTAL_HEADER_SIZE16;
				rgbsize = RGB_SIZE16;
			}
			else
				if (nPaletteSize == 256 * 2)
				{
					depth = 8;
					usedcol = 256;
					totalheader = TOTAL_HEADER_SIZE256;
					rgbsize = RGB_SIZE256;
				}
				else
					return FALSE;


			memcpy(clut, pPalette, nPaletteSize);

			for (WORD col = 0; col < nPaletteSize; col += 4)
			{
				WORD* tempword = new WORD;
				memcpy(tempword, pPalette + (col / 2), 2);
				rgbq[col] = ((WORD)(*tempword >> 10)) << 3;
				rgbq[col + 1] = ((WORD)(*tempword >> 5) & 0x1f) << 3;
				rgbq[col + 2] = ((WORD)(*tempword) & 0x1f) << 3;
				rgbq[col + 3] = 0;

				delete tempword;
			}
		}
		else
		{
			if (nPaletteSize == 16 * 4)
			{
				depth = 4;
				usedcol = 16;
				totalheader = TOTAL_HEADER_SIZE16;
				rgbsize = RGB_SIZE16;
			}
			else
				if (nPaletteSize == 256 * 4)
				{
					depth = 8;
					usedcol = 256;
					totalheader = TOTAL_HEADER_SIZE256;
					rgbsize = RGB_SIZE256;
				}
				else
					return FALSE;

			memcpy(rgbq, pPalette, nPaletteSize);

			j = 0;
			for (UINT col = 0; col < nPaletteSize; col += 4)
			{
				WORD tempword = (((BYTE)rgbq[col + 2] >> 3 |
					((WORD)(rgbq[col + 1] >> 3) << 5)) |
					(((DWORD)(BYTE)(rgbq[col] >> 3)) << 10));
				clut[j++] = LOBYTE(tempword);
				clut[j++] = HIBYTE(tempword);

			}

		}


	}
	else
	{
		if (m_ComboIndex == 0)
		{
			BITMAPINFOHEADER bmih_read;

			memcpy(&bmih_read, pImage + BMFH_SIZE, sizeof(BITMAPINFOHEADER));
			depth = bmih_read.biBitCount;

			if (depth == 4)
			{
				totalheader = TOTAL_HEADER_SIZE16;
				rgbsize = RGB_SIZE16;
				usedcol = 16;
			}
			else
				if (depth == 8)
				{
					totalheader = TOTAL_HEADER_SIZE256;
					rgbsize = RGB_SIZE256;
					usedcol = 256;
				}
				else
					return FALSE;

			memcpy(rgbq, pImage + 54, rgbsize);

			j = 0;
			for (UINT col = 0; col < rgbsize; col += 4)
			{
				WORD tempword = (((BYTE)rgbq[col + 2] >> 3 |
					((WORD)(rgbq[col + 1] >> 3) << 5)) |
					(((DWORD)(BYTE)(rgbq[col] >> 3)) << 10));
				clut[j++] = LOBYTE(tempword);
				clut[j++] = HIBYTE(tempword);

			}


		}
		else
			if (m_ComboIndex == 1)
			{
				TIM_HEADER THead_read;

				memcpy(&THead_read, pImage, sizeof(TIM_HEADER));

				if (THead_read.type == TIM_4Bit)
				{
					depth = 4;
					usedcol = 16;
					totalheader = TOTAL_HEADER_SIZE16;
					rgbsize = RGB_SIZE16;
				}
				else
					if (THead_read.type == TIM_8Bit)
					{
						depth = 8;
						usedcol = 256;
						totalheader = TOTAL_HEADER_SIZE256;
						rgbsize = RGB_SIZE256;
					}
					else
						return FALSE;

				memcpy(clut, pImage + 20, usedcol * 2);
				for (WORD col = 0; col < rgbsize; col += 4)
				{
					WORD* tempword = new WORD;
					memcpy(tempword, pImage + 20 + (col / 2), 2);
					rgbq[col] = ((WORD)(*tempword >> 10)) << 3;
					rgbq[col + 1] = ((WORD)(*tempword >> 5) & 0x1f) << 3;
					rgbq[col + 2] = ((WORD)(*tempword) & 0x1f) << 3;
					rgbq[col + 3] = 0;

					delete tempword;
				}

			}
			else
				return FALSE;

	}

	// image reading
	if (m_ComboIndex == 0)
	{
		BITMAPINFOHEADER bmih_read;

		memcpy(&bmih_read, pImage + BMFH_SIZE, sizeof(BITMAPINFOHEADER));
		xsize = bmih_read.biWidth;
		ysize = bmih_read.biHeight;
		comprflag = bmih_read.biCompression;
		ImageOffset = totalheader;
		ImageLength = xsize*ysize;
		if (depth == 4)
			ImageLength = ImageLength / 2;

	}
	else
		if (m_ComboIndex == 1)
		{
			TIM_DATAINFO TData_read;

			memcpy(&TData_read, pImage + 20 + usedcol * 2, sizeof(TIM_DATAINFO));

			xsize = TData_read.xsize * 2;
			ysize = TData_read.ysize;
			ImageLength = xsize*ysize;
			ImageOffset = 32 + usedcol * 2;

		}
		else
		{
			xsize = 128;
			ysize = 128;
			ImageLength = xsize*ysize;
			if (depth == 4)
				ImageLength = ImageLength / 2;
			ImageOffset = 0;

		}

	// write CLUT (psx uses 15bit RGB)
	NewFileCLUT.Write(clut, rgbsize / 2);

	// write converted CLUT RGB table (psx uses 15bit RGB)
	NewFilePAL.Write(rgbq, rgbsize);

	BYTE* pImageData = new BYTE[ImageLength];
	if (m_ComboIndex == 0)
	{
		BYTE* pImageTemp = new BYTE[ImageLength];

		Result = DecodeImage(pImage + ImageOffset, &pImageTemp, xsize, ysize, depth, comprflag);

		CWECompress tempclass;

		tempclass.Compress(&pImageData, pImageTemp, &ImageLength, ImageLength);

		delete pImageTemp;
	}
	else
		//if (m_ComboIndex == 1)
	{
		CWECompress tempclass;

		tempclass.Compress(&pImageData, pImage + ImageOffset, &ImageLength, ImageLength);

	}

	// write Data block
	NewFileImage.Write(pImageData, ImageLength);

	delete ImageBuf;
	delete PaletteBuf;
	delete pImageData;

	NewFileImage.Close();
	NewFileCLUT.Close();
	NewFilePAL.Close();

	return Result;

}

BOOL CreateNewBMP(CString NameFile, int m_ComboIndex, int m_ComboPalIndex, bool m_AutomaticPal)
{
	CFile   fImage, fPalette, NewFileBMP;
	CString TempMsg;
	CFileException e;
	UINT j, depth, totalheader, rgbsize, usedcol, comprflag;
	ULONG xsize, ysize, xtemp, ImageOffset, ImageLength, nImageSize, nPaletteSize;
	BYTE rgbq[RGB_SIZE256];

	// open data file to write
	if (!NewFileBMP.Open(NameFile, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error writing ") + NameFile);
		return FALSE;
	}


	if (!fImage.Open(m_SourceImageFile, CFile::modeRead | CFile::typeBinary, &e))
	{
		AfxMessageBox(_T("Error reading in source File ") + m_SourceImageFile);
		return FALSE;
	}

	nImageSize = fImage.GetLength();

	BYTE* ImageBuf = new BYTE[nImageSize];
	fImage.Read(ImageBuf, nImageSize);
	fImage.Close();

	if (!m_AutomaticPal)
	{
		if (!fPalette.Open(m_SourcePaletteFile, CFile::modeRead | CFile::typeBinary, &e))
		{
			AfxMessageBox(_T("Error reading in source File ") + m_SourcePaletteFile);
			return FALSE;
		}

		nPaletteSize = fPalette.GetLength();

	}
	else
		nPaletteSize = 1;

	BYTE* PaletteBuf = new BYTE[nPaletteSize];
	if (!m_AutomaticPal)
	{
		fPalette.Read(PaletteBuf, nPaletteSize);
		fPalette.Close();
	}

	BYTE *pImage = ImageBuf;
	BYTE *pPalette = PaletteBuf;

	// palette reading
	if (!m_AutomaticPal)
	{
		if (m_ComboPalIndex == 0)
		{
			if (nPaletteSize == 16 * 2)
			{
				depth = 4;
				usedcol = 16;
				totalheader = TOTAL_HEADER_SIZE16;
				rgbsize = RGB_SIZE16;
			}
			else
				if (nPaletteSize == 256 * 2)
				{
					depth = 8;
					usedcol = 256;
					totalheader = TOTAL_HEADER_SIZE256;
					rgbsize = RGB_SIZE256;
				}
				else
					return FALSE;

			for (UINT col = 0; col < nPaletteSize; col += 4)
			{
				WORD* tempword = new WORD;
				memcpy(tempword, pPalette + (col / 2), 2);
				rgbq[col] = ((WORD)(*tempword >> 10)) << 3;
				rgbq[col + 1] = ((WORD)(*tempword >> 5) & 0x1f) << 3;
				rgbq[col + 2] = ((WORD)(*tempword) & 0x1f) << 3;
				rgbq[col + 3] = 0;

				delete tempword;
			}
		}
		else
		{
			if (nPaletteSize == 16 * 4)
			{
				depth = 4;
				usedcol = 16;
				totalheader = TOTAL_HEADER_SIZE16;
				rgbsize = RGB_SIZE16;
			}
			else
				if (nPaletteSize == 256 * 4)
				{
					depth = 8;
					usedcol = 256;
					totalheader = TOTAL_HEADER_SIZE256;
					rgbsize = RGB_SIZE256;
				}
				else
					return FALSE;

			for (UINT col = 0; col < nPaletteSize; col++)
				rgbq[col] = *(pPalette + col);

		}


	}
	else
	{
		if (m_ComboIndex == 0)
		{
			BITMAPINFOHEADER bmih_read;

			memcpy(&bmih_read, pImage + BMFH_SIZE, sizeof(BITMAPINFOHEADER));
			depth = bmih_read.biBitCount;

			if (depth == 4)
			{
				totalheader = TOTAL_HEADER_SIZE16;
				rgbsize = RGB_SIZE16;
				usedcol = 16;
			}
			else
				if (depth == 8)
				{
					totalheader = TOTAL_HEADER_SIZE256;
					rgbsize = RGB_SIZE256;
					usedcol = 256;
				}
				else
					return FALSE;

			for (UINT col = 0; col < rgbsize; col++)
				rgbq[col] = *(pImage + 54 + col);

		}
		else
			if (m_ComboIndex == 1)
			{
				TIM_HEADER THead_read;

				memcpy(&THead_read, pImage, sizeof(TIM_HEADER));

				if (THead_read.type == TIM_4Bit)
				{
					depth = 4;
					usedcol = 16;
					totalheader = TOTAL_HEADER_SIZE16;
					rgbsize = RGB_SIZE16;
				}
				else
					if (THead_read.type == TIM_8Bit)
					{
						depth = 8;
						usedcol = 256;
						totalheader = TOTAL_HEADER_SIZE256;
						rgbsize = RGB_SIZE256;
					}
					else
						return FALSE;

				for (WORD col = 0; col < rgbsize; col += 4)
				{
					WORD* tempword = new WORD;
					memcpy(tempword, pImage + 20 + (col / 2), 2);
					rgbq[col] = ((WORD)(*tempword >> 10)) << 3;
					rgbq[col + 1] = ((WORD)(*tempword >> 5) & 0x1f) << 3;
					rgbq[col + 2] = ((WORD)(*tempword) & 0x1f) << 3;
					rgbq[col + 3] = 0;

					delete tempword;
				}

			}
			else
				return FALSE;

	}

	m_ActualColorsNumber = usedcol;

	// image reading
	if (m_ComboIndex == 0)
	{
		BITMAPINFOHEADER bmih_read;

		memcpy(&bmih_read, pImage + BMFH_SIZE, sizeof(BITMAPINFOHEADER));
		xsize = bmih_read.biWidth;
		ysize = bmih_read.biHeight;
		comprflag = bmih_read.biCompression;
		ImageOffset = totalheader;
		ImageLength = xsize*ysize;

		if (depth == 4)
			ImageLength = ImageLength / 2;

	}
	else
		if (m_ComboIndex == 1)
		{
			TIM_DATAINFO TData_read;

			memcpy(&TData_read, pImage + 20 + usedcol * 2, sizeof(TIM_DATAINFO));

			xsize = TData_read.xsize * 2;
			ysize = TData_read.ysize;
			comprflag = BI_RGB;
			ImageLength = xsize*ysize;
			if (depth == 4)
				xsize = xsize * 2;

			ImageOffset = 32 + usedcol * 2;

		}
		else
		{
			xsize = 128;
			ysize = 128;
			comprflag = BI_RGB;
			ImageLength = xsize*ysize;
			if (depth == 4)
				ImageLength = ImageLength / 2;
			ImageOffset = 0;

		}

	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;

	bmfh.bfType = 0x4D42;// BM
	bmfh.bfSize = totalheader + (xsize*ysize*depth) / 8;
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = totalheader;

	NewFileBMP.Write(&bmfh, sizeof(BITMAPFILEHEADER));

	bmih.biSize = BMIH_SIZE;
	bmih.biWidth = xsize;
	bmih.biHeight = ysize;
	bmih.biPlanes = 1;
	bmih.biBitCount = depth;
	bmih.biCompression = comprflag;
	bmih.biSizeImage = (xsize*ysize*depth) / 8;
	bmih.biXPelsPerMeter = 0;
	bmih.biYPelsPerMeter = 0;
	bmih.biClrUsed = usedcol;
	bmih.biClrImportant = 0;

	NewFileBMP.Write(&bmih, sizeof(BITMAPINFOHEADER));

	// write converted CLUT RGB table (psx uses 15bit RGB)
	NewFileBMP.Write(rgbq, rgbsize);

	BYTE* pImageData = new BYTE[ImageLength];
	if (m_ComboIndex == 0)
	{
		memcpy(pImageData, pImage + ImageOffset, ImageLength);

	}
	else
		//if (m_ComboIndex == 1)
	{
		BYTE* pData = pImage + ImageOffset;
		j = 0;
		if (depth == 4)
		{
			// 4 bit
			xtemp = xsize / 2;
			for (long y1 = ysize - 1; y1 >= 0; y1--)
			{
				for (unsigned long x1 = 0; x1<xtemp; x1++)
				{
					pImageData[j] = (pData[(y1*xtemp) + x1]) >> 4;
					pImageData[j] |= ((pData[(y1*xtemp) + x1] << 4) & 0xF0);
					j++;
				}
			}

		}
		else
		{
			// 8 bit
			xtemp = xsize;
			for (long y1 = ysize - 1; y1 >= 0; y1--) {
				for (unsigned long x1 = 0; x1<xtemp; x1++)
					pImageData[j++] = pData[(y1*xtemp) + x1];
			}
		}

	}

	// write Data block
	NewFileBMP.Write(pImageData, ImageLength);

	delete ImageBuf;
	delete PaletteBuf;
	delete pImageData;

	NewFileBMP.Close();

	return TRUE;

}

BOOL DecodeNewImage(BYTE *BufSrc, BYTE **BufDest, ULONG xsize, ULONG ysize,
	BYTE depth, BYTE ComprFlag, int m_ComboIndex, int m_ComboPalIndex, bool m_AutomaticPal)
{
	ULONG xtemp;
	UINT j;

	BYTE *pDest = *BufDest;

	j = 0;
	if (depth == 4)
	{
		// 4 bit
		xtemp = xsize / 2;
		if (ComprFlag == BI_RGB)
		{
			for (long y1 = ysize - 1; y1 >= 0; y1--)
			{
				for (unsigned long x1 = 0; x1<xtemp; x1++)
				{
					pDest[j] = (BufSrc[(y1*xtemp) + x1]) >> 4;
					pDest[j] |= ((BufSrc[(y1*xtemp) + x1] << 4) & 0xF0);
					j++;
				}
			}
		}
		else
		{
			// BI_RLE4
			BOOL bEOB = FALSE;
			BYTE *pSrc = BufSrc;

			int code1, code2, i, k, hi = 0, abs_cou = 0, adj_cou = 0;

			BYTE* pTempData = new BYTE[xtemp*ysize];
			pDest = pTempData;

			BYTE *sta_ptr = pDest;
			for (i = 0; i<xtemp*ysize && !bEOB; i += 2)
			{
				code1 = *pSrc++;
				code2 = *pSrc++;

				if (abs_cou)
				{
					if (hi)
						*pDest++ |= (code1 >> 4);
					else
						*pDest = (code1 & 0xF0);
					abs_cou--;
					hi ^= 1;

					if (abs_cou)
					{
						if (hi)
							*pDest++ |= (code1 & 0x0F);
						else
							*pDest = (code1 << 4);
						abs_cou--;
						hi ^= 1;
					}

					if (abs_cou)
					{
						if (hi)
							*pDest++ |= (code2 >> 4);
						else
							*pDest = (code2 & 0xF0);
						abs_cou--;
						hi ^= 1;
					}

					if (abs_cou)
					{
						if (hi)
							*pDest++ |= (code2 & 0x0F);
						else
							*pDest = (code2 << 4);
						abs_cou--;
						hi ^= 1;
					}
					continue;

				}

				if (code1 == 0)  // RLE_COMMAND
				{
					switch (code2) // Escape
					{
					case 0:	// End of line escape EOL
						if (!adj_cou)  adj_cou = 3 - ((pDest - sta_ptr + 3) % 4);
						for (i = 0; i<adj_cou; i++) *pDest++ = 0;
						continue;
					case 1: // End of block escape EOB
						if (!adj_cou)  adj_cou = 3 - ((pDest - sta_ptr + 3) % 4);
						for (i = 0; i<adj_cou; i++) *pDest++ = 0;
						bEOB = TRUE;
						break;
					case 2: // Delta escape. RLE_DELTA								
						break;
					default: // Literal packet
						abs_cou = code2;
						break;
					}
					continue;
				}

				if (!bEOB) // Literal
				{
					for (k = 0; k < code1 / 2; k++)
					{
						if (hi)
						{
							*pDest++ |= (code2 >> 4);
							*pDest = (code2 & 0x0F);
						}
						else
							*pDest++ = code2;
					}

					if (code1 % 2)
					{
						if (hi)
							*pDest++ |= (code2 >> 4);
						else
							*pDest = (code2 & 0xF0);
						hi ^= 1;
					}

				}
			}

			pDest = *BufDest;
			for (long y1 = ysize - 1; y1 >= 0; y1--)
			{
				for (unsigned long x1 = 0; x1<xtemp; x1++)
				{
					pDest[j] = (pTempData[(y1*xtemp) + x1]) >> 4;
					pDest[j] |= ((pTempData[(y1*xtemp) + x1] << 4) & 0xF0);
					j++;
				}
			}

			delete pTempData;

		}
	}
	else
	{
		// 8 bit

		xtemp = xsize;
		if (ComprFlag == BI_RGB)
		{
			for (long y1 = ysize - 1; y1 >= 0; y1--) {
				for (unsigned long x1 = 0; x1<xtemp; x1++)
					pDest[j++] = BufSrc[(y1*xtemp) + x1];
			}
		}
		else
		{
			// BI_RLE8
			BOOL bEOB = FALSE;
			BYTE *pSrc = BufSrc;

			int code1, code2, i, k, abs_cou = 0, adj_cou = 0;

			BYTE* pTempData = new BYTE[xtemp*ysize];
			pDest = pTempData;

			BYTE *sta_ptr = pDest;
			for (i = 0; i<xtemp*ysize && !bEOB; i += 2)
			{
				code1 = *pSrc++;
				code2 = *pSrc++;

				if (abs_cou)
				{
					*pDest++ = code1;
					abs_cou--;
					if (abs_cou)
					{
						*pDest++ = code2;
						abs_cou--;
					}
					continue;
				}

				if (code1 == 0)  // RLE_COMMAND
				{
					switch (code2) // Escape
					{
					case 0:	// End of line escape EOL
						if (!adj_cou)  adj_cou = 3 - ((pDest - sta_ptr + 3) % 4);
						for (i = 0; i<adj_cou; i++) *pDest++ = 0;
						continue;
					case 1: // End of block escape EOB
						if (!adj_cou)  adj_cou = 3 - ((pDest - sta_ptr + 3) % 4);
						for (i = 0; i<adj_cou; i++) *pDest++ = 0;
						bEOB = TRUE;
						break;
					case 2: // Delta escape. RLE_DELTA								
						break;
					default: // Literal packet
						abs_cou = code2;
						break;
					}
					continue;
				}

				if (!bEOB) // Literal
					for (k = 0; k < code1; k++)
						*pDest++ = code2;
			}

			pDest = *BufDest;
			for (long y1 = ysize - 1; y1 >= 0; y1--) {
				for (unsigned long x1 = 0; x1<xtemp; x1++)
					pDest[j++] = pTempData[(y1*xtemp) + x1];
			}

			delete pTempData;
		}
	}

	return TRUE;
}
