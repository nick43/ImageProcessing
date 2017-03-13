
// ImageProcessingView.h : CImageProcessingView ��Ľӿ�
//

#pragma once
#include "DIB.h"

class CImageProcessingView : public CView
{
protected: // �������л�����
	CImageProcessingView();
	DECLARE_DYNCREATE(CImageProcessingView)

// ����
public:
	CImageProcessingDoc* GetDocument() const;
	CDib m_Dib;
// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CImageProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnFileOpen();
};

#ifndef _DEBUG  // ImageProcessingView.cpp �еĵ��԰汾
inline CImageProcessingDoc* CImageProcessingView::GetDocument() const
   { return reinterpret_cast<CImageProcessingDoc*>(m_pDocument); }
#endif

