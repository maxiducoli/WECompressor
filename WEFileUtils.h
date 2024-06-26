#pragma once

class WeUtils
{
public:
    WeUtils();
    ~WeUtils();

private:

};

WeUtils::WeUtils()
{
}

WeUtils::~WeUtils()
{
}

// Métodos originales Walxer
extern "C" __declspec(dllimport) BOOL CreateBMP(CString NameFile);
extern "C" __declspec(dllimport) BOOL CreateFiles();
extern "C" __declspec(dllimport) BOOL DecodeImage(BYTE* BufSrc, BYTE** BufDest, ULONG xsize, ULONG ysize, BYTE depth, BYTE ComprFlag);

// Métodos adaptados
extern "C" __declspec(dllimport) BOOL CreateNewBMP(CString NameFile, int m_ComboIndex, int m_ComboPalIndex, bool m_AutomaticPal);
extern "C" __declspec(dllimport) BOOL DecodeNewImage(BYTE* BufSrc, BYTE** BufDest, ULONG xsize, ULONG ysize, BYTE depth, BYTE ComprFlag, int m_ComboIndex, int m_ComboPalIndex, bool m_AutomaticPal);
extern "C" __declspec(dllimport) BOOL CreateNewFiles(CString m_ImageFile, CString m_PaletteFile, CString m_SourceImageFile, CString m_SourcePaletteFile, int m_ComboIndex, int m_ComboPalIndex, bool m_AutomaticPal);