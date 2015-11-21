#ifndef __DEFINATION_H__
#define __DEFINATION_H__
//----------------------------------------------------
struct pcdata{
	void* scaninfo;
	struct symbol** symtab;
	struct ast* ast;
};
struct symbol{
	char* name;
	int datatype;  //数据类型
	int intval;
	double doubval;
	char charval;
	
	int size;

	struct ast* func;
	struct symlist* syms;
};
struct symlist{
	char* name;
	struct symlist* next;
};
#define MAX 9997


struct symbol* lookup(struct pcdata*, char*);
void insert(struct pcdata*, struct symbol* s);
struct symlist* newsymlist(struct pcdata*, char* sym, struct symlist* next);
//----------------------------------------------------
enum  bifs
{
	B_sqrt=1,
	B_exp,
	B_log,
	B_print
};
struct un{
	int type;
	char ch;
	int num;
	double doub;
};
//-----------------------------------------------------
struct ast{
	int nodetype;
	struct ast* l;
	struct ast* r;
};
struct flow:public ast{
	struct ast* cond;
	struct ast* tl;
	struct ast* el;
};
struct _for:public ast{
	char* index;
	int start;
	int end;
	int step;
	struct ast* tl;
};

struct _foreach:public ast{
	char* index;
	char* arr;
	struct ast* tl;
};

struct fncall:public ast{
	//0
	struct ast* tl;
	enum bifs functype;
};
struct ufncall:public ast {
	//1
	struct ast* tl;
	char* name;
};
struct charcons:public ast{
		//2
	char ch;
};
struct intcons:public ast{
		//3
	int num;
};
struct doubcons:public ast{
		//4
	double doub;
};
struct var:public ast{
	  //5
	int datatype;
	char* name;
};
struct arr:public ast{           
	//6
	int datatype;
	char* name;
	int size;
};
struct fndec:public ast{
	//7;
	char* name;
	struct symlist* s;
	struct ast* tl;
};
struct csdec :public ast{
	 //8;
	char* vname;
	char* cname;
};
struct csdef :public ast{
	//9;
	char* cname;
	char* fname;
	struct ast* tl;
};
struct csget :public ast{
	//10
	char* cname;
	char* kname;
	int func;
	struct ast* explist;
	struct ast* index;
};
struct symasgn:public ast{
	char* name;
	struct ast* v;
	struct ast* index;
};
struct symref :public ast{
	char* name;
	struct ast* index;
};

// by chenjianan for drawing
// nodetype = 128
struct singlestring :public ast{
	char* str;
};

struct ast* newfunc(struct pcdata*, int functype, struct ast* l);
struct ast* newcall(struct pcdata*, char* s, struct ast* l);
struct ast* newint(struct pcdata*, int num);
struct ast* newdoub(struct pcdata*, double d);
struct ast* newchar(struct pcdata*, char ch);
struct ast* newvar(struct pcdata*,char* name, int type);
struct ast* newarr(struct pcdata*, char* name, int type, int size);
struct ast* newclass(struct pcdata*, char* vname, char* cname);
struct ast* newclassdef(struct pcdata*, char* cname, char* fname, struct ast* tl);
struct ast* newcsget(struct pcdata*, char* cname, char* kname,int func,struct ast* explist,struct ast* index);
struct ast* newasgn(struct pcdata*, char* name, struct ast* v,struct ast* index);
struct ast* dodef(struct pcdata*, char* name, struct symlist* syms, struct ast* stmts);
struct ast* newref(struct pcdata*, char* name,struct ast* index);

struct ast* newast(struct pcdata*, int nodetype,struct ast* l, struct ast* r);
struct ast* newflow(struct pcdata*, int nodetype, struct ast* cond, struct ast* tl, struct ast* tr);
struct ast* newfor(struct pcdata*, char* index, int start, int end, int step, struct ast* tl);
struct ast* newforeach(struct pcdata*, char* index, char* arr, struct ast* tl);
struct ast* newcmp(struct pcdata*, int cmptype, struct ast* l, struct ast* r);

struct un eval(struct pcdata*, struct ast*);
void treefree(struct pcdata*, struct ast*);
void yyerror(struct pcdata* pp, char* s, ...);

void show(int);

#endif