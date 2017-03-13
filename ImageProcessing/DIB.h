#ifndef __CDIB_H
#define __CDIB_H

class CDib :public CObject
{
public:
	CString m_fileName;						// ͼ���ļ���
	BITMAPFILEHEADER m_bitmapFileHeader;	// λͼ�ļ�ͷ
	BITMAPINFO* m_pBitmapInfo;				// λͼ��Ϣ
	BITMAPINFOHEADER* m_pBitmapInfoHeader;	// λͼ��Ϣͷ
	RGBQUAD* m_pRGB;						// ��ɫ���׵�ַ

	BYTE* m_pData;							// ͼ�����������׵�ַ
	BYTE* m_pDib;							// λͼ�׵�ַ(ȥ��λͼ�ļ�ͷ��ͼ����׵�ַ)
	BOOL m_valid;							// IsValid�����ķ���ֵ
public:
	CDib();
	~CDib();
	//void LoadFile(const char* dibFileName);// �����ļ�
	void ReadFile(CString  dibFileName);// ��ȡ�ļ�
	BOOL IsValid();		// �����Ƿ������bmp��ʽͼƬ. ��, ����TRUE, ���򷵻�FALSE
	CString GetFileName();  // ��ȡ�ļ���
	
	BITMAPINFO* GetInfo();// ��ȡͼ����Ϣͷ
	DWORD GetSize();// ��ȡͼ���С
	UINT GetWidth();// ��ȡͼ����
	UINT GetHeight();// ��ȡͼ��߶�

	RGBQUAD* GetRGB();// ��ȡ��ɫ��
	UINT GetNumberOfColors();// ��ȡ��ɫ��Ŀ
	WORD GetPaletteSize(LPBYTE lpDIB);// ��ɫ���С

	BYTE* GetData();// ��ȡͼ�����������

	WORD DIBNumColors(LPBYTE lpDIB);
	//void SaveFile(const char* filename);
public:
	
};

#endif // !__CDIB_H
