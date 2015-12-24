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

	void AnalyseType(ast* node);
	void AnalyseFunction(ast* node);
	void AnalyseMain(ast* node);
	void AnalyseVariable(ast* node);

	void FuncAnalyseVariable(ast* node, VariableTable* fvt, TypeTable* ftt, int index);
	void FuncAnalyseType(ast* node, VariableTable* fvt, TypeTable* ftt, int index);
	void FuncRead(ast* node, VariableTable* fvt, TypeTable* ftt, int index);
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
	para* getFuncPara(int funcindex, int paraindex);

	SymbolTableAnalyse(SemanticError* semerr);
	void Analyse(ast* root);
};