
// MyCompilerForMyLangView.cpp : CEditorView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MyCompilerForMyLang.h"
#endif

#include "MyCompilerForMyLangDoc.h"
#include "MyCompilerForMyLangView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEditorView

IMPLEMENT_DYNCREATE(CEditorView, CEditView)

BEGIN_MESSAGE_MAP(CEditorView, CEditView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditView::OnFilePrintPreview)
	ON_COMMAND(ID_COMP_TESTOPENGL, &CEditorView::OnCompTestopengl)
	ON_COMMAND(ID_32777, &CEditorView::OnAnalyze)
END_MESSAGE_MAP()

// CEditorView ����/����

CEditorView::CEditorView()
{
	// TODO:  �ڴ˴���ӹ������

}

CEditorView::~CEditorView()
{
}

BOOL CEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// ���û���

	return bPreCreated;
}


// CEditorView ��ӡ

BOOL CEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ׼��
	return CEditView::OnPreparePrinting(pInfo);
}

void CEditorView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ��ʼ��ӡ
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CEditorView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ������ӡ
	CEditView::OnEndPrinting(pDC, pInfo);
}


// CEditorView ���

#ifdef _DEBUG
void CEditorView::AssertValid() const
{
	CEditView::AssertValid();
}

void CEditorView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMyCompilerForMyLangDoc* CEditorView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyCompilerForMyLangDoc)));
	return (CMyCompilerForMyLangDoc*)m_pDocument;
}
#endif //_DEBUG


// CEditorView ��Ϣ�������

#include "TreeDrawer.h"
void CEditorView::OnCompTestopengl()
{
	fncall* rl = new fncall();
	rl->l = NULL;
	rl->r = NULL;
	rl->nodetype = 0;

	var* rr = new var();
	rr->l = NULL;
	rr->r = NULL;
	rr->nodetype = 5;
	rr->datatype = 1;
	rr->name = "var1";

	ufncall* r = new ufncall();
	r->l = rl;
	r->r = rr;
	r->nodetype = 1;

	TreeDrawer td;
	td.printGraphicTree((ast*)r);

	if (r)
		delete r;
	// TODO:  �ڴ���������������
}


#include "defination.h"
#include "parser.h"
#include "lexer.h"
#include "TreeDrawer.h"
#include <fstream>
using std::ofstream;
void CEditorView::OnAnalyze()
{
	// TODO:  �ڴ���������������
	CString ttext;
	GetEditCtrl().GetWindowTextA(ttext);
	MessageBox(ttext);

	/*
	ofstream fout("code_to_analyze.txt");
	fout << ttext.GetBuffer(ttext.GetLength());
	fout.close();
	*/

	struct pcdata p = {
		NULL,
		NULL,
		NULL
	};
	static symbol* symtab[MAX];
	if (yylex_init_extra(&p, &p.scaninfo)){
		perror("init failed\n");
		MessageBox(LPCTSTR("Init failed"));
		return;
	}

	p.symtab = symtab;

	for (int i = 0; i < MAX; i++)
		p.symtab[i] = NULL;

	TreeDrawer td;
	/*FILE* f;
	fopen_s(&f, "code_to_analyze.txt", "r");
	yyset_in(f, p.scaninfo);*/
	yy_switch_to_buffer(yy_scan_string((LPCSTR)(LPCTSTR)ttext,p.scaninfo),p.scaninfo);
	//YY_BUFFER_STATE buf = yy_scan_string((LPCSTR)(LPCTSTR)ttext, p.scaninfo);
	yyparse(&p);

	if (p.ast){

		td.printTextTree(p.ast);
		td.printGraphicTree(p.ast);

		//eval(&p, p.ast);
		//treefree(&p, p.ast);
		p.ast = NULL;
	}
	else
	{
		MessageBox(LPCTSTR("0"));
	}

}
