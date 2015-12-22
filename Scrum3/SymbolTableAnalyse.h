#include "TableType.h"
#include "parser.h"
#include "lexer.h"
#include "defination.h"
using namespace std;

class SymbolTableAnalyse{
private:
	SymbolTable* st;
	TypeTable* tt;
	VariableTable* vt;
	FunctionTable* ft;

	void AnalyseType(ast* node);
	void AnalyseFunction(ast* node);
	void AnalyseMain(ast* node);
	void AnalyseVariable(ast* node);

	void FuncAnalyseVariable(ast* node, VariableTable* fvt);
	void FuncAnalyseType(ast* node, TypeTable* ftt);
	void FuncRead(ast* node, VariableTable* fvt, TypeTable* ftt);
	void FuncConstant();//change to get more support system function call
	void _Analyse(ast* node);
	
	void PrintSymbolTable();
	
public:
	para* checkFuncPara(string name, int index);
	para* checkFuncVar(string name, int index);
	para* checkFuncType(string name, int index);
	para* checkVariable(string name);
	para* checkType(string name);
	func* checkFunc(string name);

	SymbolTableAnalyse();
	void Analyse(ast* root);
};