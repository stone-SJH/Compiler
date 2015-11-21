#include "stdafx.h"

#include "defination.h"
#include <iostream>
using namespace std;
#include "parser.h"
#include "lexer.h"
#include <string>

#include "TreeDrawer.h"


/*
int filein()
{
	struct pcdata p = {
		NULL,
		NULL,
		NULL
	};
	static symbol* symtab[MAX];
	if (yylex_init_extra(&p, &p.scaninfo)){
		perror("init failed\n");
		return 0;
	}
	p.symtab = symtab;
	
	for (int i = 0; i < MAX; i++)
			p.symtab[i] = NULL;
	string filename;

	TreeDrawer td;

	for (;;){
		cout << "input the filename>";
		cin >> filename;
		FILE* f;
		fopen_s(&f,filename.c_str(), "r");
		yyset_in(f, p.scaninfo);
		yyparse(&p);
		if (p.ast){

			td.printTextTree(p.ast);
			td.printGraphicTree(p.ast);

			//eval(&p, p.ast);
			//treefree(&p, p.ast);
			p.ast = NULL;
		}
	}
}*/