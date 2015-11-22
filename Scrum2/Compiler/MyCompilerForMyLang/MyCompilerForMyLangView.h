
// MyCompilerForMyLangView.h : CEditorView 类的接口
//

#pragma once


class CEditorView : public CEditView
{
protected: // 仅从序列化创建
	CEditorView();
	DECLARE_DYNCREATE(CEditorView)

// 特性
public:
	CMyCompilerForMyLangDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCompTestopengl();
	afx_msg void OnAnalyze();
};

#ifndef _DEBUG  // MyCompilerForMyLangView.cpp 中的调试版本
inline CMyCompilerForMyLangDoc* CEditorView::GetDocument() const
   { return reinterpret_cast<CMyCompilerForMyLangDoc*>(m_pDocument); }
#endif

