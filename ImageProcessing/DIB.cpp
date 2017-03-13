#include "stdafx.h"
#include "Dib.h"
#include "windowsx.h"

CDib::CDib()
{
}

CDib::~CDib()
{
	GlobalFreePtr(m_pBitmapInfo);
}

void CDib::ReadFile(CString  dibFileName)
{
	m_fileName = dibFileName;
	CFile dibFile((LPCTSTR)m_fileName, CFile::modeRead);// �����ļ�����ֻ����ʽ
	dibFile.Read((void *)&m_bitmapFileHeader, sizeof(BITMAPFILEHEADER));// ��ȡ�ļ�ͷ
	if (m_bitmapFileHeader.bfType == 0x4d42) // �ļ����ͱ���Ϊ��BM��B=66=0x42 M=77=0x4d
	{
		/************************ȥ���ļ�ͷ************************/
		// ���ļ��ĳ��ȼ�ȥ�ļ�ͷ�ĳ��ȼ�Ϊͼ��ĳ���
		DWORD ImageSize = dibFile.GetLength() - sizeof(BITMAPFILEHEADER);
		m_pDib = (BYTE*)GlobalAllocPtr(GMEM_MOVEABLE, ImageSize);	// �Ӷ��з����ض��ֽڵĿռ�
		dibFile.Read((void*)m_pDib, ImageSize);						// ��λͼ�׵�ַ��ʼ��ȡ
		dibFile.Close();											// �ͷ��ļ�

		/************************��ȡͼ�������Ϣ*****************/
		m_pBitmapInfo = (BITMAPINFO*)m_pDib;							// λͼ��Ϣͷ����ɫ�����λͼ��Ϣ
		m_pBitmapInfoHeader = (BITMAPINFOHEADER*)m_pDib;				// λͼ��Ϣͷ��ǰ
		m_pRGB = (RGBQUAD*)(m_pDib + m_pBitmapInfoHeader->biSize);		// ��ɫ���ں�
		int m_numberOfColors = GetNumberOfColors();						// ��ɫ��Ŀ
		if (m_pBitmapInfoHeader->biClrUsed == 0)						// λͼʵ��ʹ�õ���ɫ���е���ɫ��
			m_pBitmapInfoHeader->biClrUsed = m_numberOfColors;
		DWORD colorTableSize = m_numberOfColors*sizeof(RGBQUAD);		// ��ɫ���С
		// ͼ�����������׵�ַΪλͼ�׵�ַ��ƫ������ƫ����=��Ϣͷ+��ɫ�壩
		m_pData = m_pDib + m_pBitmapInfoHeader->biSize + colorTableSize;// ͼ��������
		// û�е�ɫ��
		if (m_pRGB == (RGBQUAD*)m_pData)	 
			m_pRGB = NULL;

		m_pBitmapInfoHeader->biSizeImage = GetSize();					// ͼ��Ĵ�С
		m_valid = TRUE;
	}
	else
	{ // λͼ�ļ�����ʧ��
		m_valid = FALSE;
		AfxMessageBox(L"This isn't a bitmap file!");
	}
}

BOOL CDib::IsValid()
{
	return m_valid;
}

CString CDib::GetFileName()
{
	return m_fileName;
}

// ����ͼ��Ŀ��
UINT CDib::GetWidth()
{
	return (UINT)m_pBitmapInfoHeader->biWidth;
}

// ����ͼ��ĸ߶�
UINT CDib::GetHeight()
{
	return (UINT)m_pBitmapInfoHeader->biHeight;
}

// ��ȡͼ��Ĵ�С
DWORD CDib::GetSize()
{
	if (m_pBitmapInfoHeader->biSizeImage != 0)
		return m_pBitmapInfoHeader->biSizeImage;
	else
	{
		DWORD height = (DWORD)GetHeight();
		DWORD width = (DWORD)GetWidth();
		return height*width;
	}
}

// ����λͼ����ɫ��Ŀ
UINT CDib::GetNumberOfColors()
{
	int numberOfColors;
	// ͼ����ʹ�õ���ɫ��Ϊ0�������ص�λ��С��9
	if ((m_pBitmapInfoHeader->biClrUsed == 0) &&
		(m_pBitmapInfoHeader->biBitCount < 9))
	{
		switch (m_pBitmapInfoHeader->biBitCount)
		{
		case 1:
			numberOfColors = 2; break;
		case 4:
			numberOfColors = 16; break;
		case 8:
			numberOfColors = 256;
		}
	}
	else
		numberOfColors = (int)m_pBitmapInfoHeader->biClrUsed;
	return numberOfColors;
}

// ������Ϣ����ʼ��ַ
BITMAPINFO* CDib::GetInfo()
{
	return m_pBitmapInfo;
}

// ����ÿ�����ص�λ��
WORD CDib::DIBNumColors(LPBYTE lpDIB)
{
	WORD wBitCount; // DIB bit count
	wBitCount = ((LPBITMAPCOREHEADER)lpDIB)->bcBitCount;
	switch (wBitCount)
	{
	case 1:
		return 2;
	case 4:
		return 16;
	case 8:
		return 256;
	default:
		return 0;
	}
}

// ���ص�ɫ�����ʼ��ַ
RGBQUAD* CDib::GetRGB()
{
	return m_pRGB;
}

// ���ص�ɫ��Ĵ�С
WORD CDib::GetPaletteSize(LPBYTE lpDIB)
{
	return (DIBNumColors(lpDIB)*sizeof(RGBTRIPLE));
}

// �����������ݵ���ʼ��ַ
BYTE* CDib::GetData()
{
	return m_pData;
}





//void CDib::SaveFile(const char* filename)
//{// �˺���ֻ�ܱ��澭������ȡ��߶Ⱦ�û�иı��С��ͼ��
//	strcpy_s(m_fileName, filename);
//	CFile dibFile((LPCTSTR)m_fileName, CFile::modeCreate | CFile::modeWrite);
//	dibFile.Write((void*)&bitmapFileHeader, sizeof(BITMAPFILEHEADER));
//	dibFile.Write((void*)pDib, size);
//	dibFile.Close();
//}





