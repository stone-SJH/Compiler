#include "defination.h"
#include <iostream>
using namespace std;
#include "parser.h"
#include "lexer.h"
#include <string>
#include "SymbolTableAnalyse.h"

void _read(ast* cur){
	if (cur->nodetype == 5){
		struct var* v = (struct var*)cur;
		cout << v->name << endl;
		return;
	}
	if (cur->nodetype == 'L'){
		_read(cur->l);
		_read(cur->r);
	}
}

void read(ast* node){
	if (node == NULL)
		return;
	switch (node->nodetype)
	{
	case 5:
	{
		struct var* v = (struct var*)node;
		cout << v->name << endl;
		return;
	}
	case 6:
	{
		struct arr* array = (struct arr*)node;
		cout << array->name << endl;
		return;
	}
	case 7:
	{
		struct fndec* fn = (struct fndec*)node;
		cout << fn->name << endl;
		//read(fn->tl);
		//cout << (char)fn->tl->nodetype << endl;
		//cout << node->r->nodetype << endl;
		ast* cur = fn->tl;

		_read(cur);
		return;
	}
	case 'L':
	{
		read(node->l);
		read(node->r);
		return;
	}
	}
}

int main()
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
	for (;;){
		cout << "input the filename>";
		cin >> filename;
		FILE* f;
		fopen_s(&f,filename.c_str(), "r");
		yyset_in(f, p.scaninfo);
		yyparse(&p);
		ast* root = p.ast;
		SymbolTableAnalyse* sta = new SymbolTableAnalyse();
		sta->Analyse(root);
		/*if (p.ast){
			eval(&p, p.ast);
			//treefree(&p, p.ast);
			p.ast = NULL;
		}*/
		/*if (root != NULL){
			cout << root->nodetype << endl;
			read(root);
			//cout << root->l->nodetype << endl;
			//read(root->r);
		}*/
		//cout << "done" << endl;
	}
}