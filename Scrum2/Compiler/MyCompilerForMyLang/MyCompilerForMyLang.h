
// MyCompilerForMyLang.h : MyCompilerForMyLang Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMyCompilerForMyLangApp:
// �йش����ʵ�֣������ MyCompilerForMyLang.cpp
//

class CMyCompilerForMyLangApp : public CWinApp
{
public:
	CMyCompilerForMyLangApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyCompilerForMyLangApp theApp;
