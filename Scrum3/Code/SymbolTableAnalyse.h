#include "TableType.h"
#include "parser.h"
#include "lexer.h"
#include "defination.h"
#include "SemanticError.h"
using namespace std;

class SymbolTableAnalyse{
private:
	SemanticError* se;
	SymbolTable* st;
	TypeTable* tt;
	VariableTable* vt;
	FunctionTable* ft;
	ClassTable* ct;

	void AnalyseType(ast* node);
	void AnalyseFunction(ast* node);
	void AnalyseMain(ast* node);
	void AnalyseVariable(ast* node);
	void AnalyseClassDec(ast* node);
	void AnalyseClassDef(ast* node);

	void FuncAnalyseVariable(ast* node, VariableTable* fvt, TypeTable* ftt, int index);
	void FuncAnalyseClassDec(ast* node, VariableTable* fvt, TypeTable* ftt, int index);
	void FuncAnalyseType(ast* node, VariableTable* fvt, TypeTable* ftt, int index);
	void FuncRead(ast* node, VariableTable* fvt, TypeTable* ftt, int index);
	void FuncConstant();//change to get more support system function call
	void _Analyse(ast* node);

	void ClassRead(ast* node, SymbolTable* cst,VariableTable* cvt, TypeTable* ctt, FunctionTable* cft);
	void ClassAnalyseVariable(ast* node,SymbolTable* st, VariableTable* vt);
	void ClassAnalyseClassDec(ast* node, SymbolTable* st,VariableTable* vt);
	void ClassAnalyseType(ast* node, SymbolTable* st, TypeTable* tt);
	void ClassAnalyseFunction(ast* node, SymbolTable* st, FunctionTable* cft);

public:
	para* checkFuncPara(string name, int index);
	para* checkFuncVar(string name, int index);
	para* checkFuncType(string name, int index);
	para* checkVariable(string name);
	para* checkType(string name);
	func* checkFunc(string name);

	para* getFuncPara(int funcindex, int paraindex);


	// return the index saved in tables
	// and if name is not found just return -1
	int findType(string name);
	int findVariable(string name);
	int findClass(string name);
	// className��ʾ������һ���������ҵ��ģ������໹�Ǹ��ࣿ
	// ע��className������,��ʼֵ�봫�뿪ʼѰ�ҵ�����
	// �ú�������ֵΪ�ñ������������ڵ�һ�δӵײ�����Ѱ�ҹ����г��������е�λ��
	int findVariableAndTypeInClass(const string& vname, string& className);

	// get some information
	string getVariableType(string vname);

	// get tables
	SymbolTable*	getSymbolTable();
	TypeTable*		getTypeTable();
	VariableTable*	getVariableTable();
	FunctionTable*	getFunctionTable();
	ClassTable*		getClassTable();

	SymbolTableAnalyse(SemanticError* semerr);
	void Analyse(ast* root);
	void PrintSymbolTable();
};