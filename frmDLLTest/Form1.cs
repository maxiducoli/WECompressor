using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace frmDLLTest
{
    public partial class Form1 : Form
    {
        [DllImport("Utils.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool CreateFiles();
        //BOOL CreateBMP(CString NameFile)
        [DllImport("Utils.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool CreateNewFiles(string newImageFile,string newPaletteFile,string sourceImageFile, string sourcePaletteFile);
        //BOOL CreateNewFiles(CString m_ImageFile, CString m_PaletteFile, CString m_SourceImageFile, CString m_SourcePaletteFile)
        [DllImport("Utils.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool CreateBMP(string filePath);
        [DllImport("Utils.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool DecodeImage(IntPtr buffSource, IntPtr buffDest,ulong xSize,ulong ySize,byte depth,byte comprFlag);
        //BOOL DecodeImage(BYTE *BufSrc,BYTE **BufDest,ULONG xsize,ULONG ysize,BYTE depth, BYTE ComprFlag)
        public Form1()
        {
            InitializeComponent();
        }

        private void TestDLL()
        {

        }
    }
}
