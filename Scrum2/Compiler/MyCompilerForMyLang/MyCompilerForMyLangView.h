
// MyCompilerForMyLangView.h : CEditorView ��Ľӿ�
//

#pragma once


class CEditorView : public CEditView
{
protected: // �������л�����
	CEditorView();
	DECLARE_DYNCREATE(CEditorView)

// ����
public:
	CMyCompilerForMyLangDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCompTestopengl();
	afx_msg void OnAnalyze();
};

#ifndef _DEBUG  // MyCompilerForMyLangView.cpp �еĵ��԰汾
inline CMyCompilerForMyLangDoc* CEditorView::GetDocument() const
   { return reinterpret_cast<CMyCompilerForMyLangDoc*>(m_pDocument); }
#endif

