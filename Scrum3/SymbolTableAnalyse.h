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
	
	bool checkSymbol(string name);
	bool checkType(string name);
	bool checkVariable(string name);
	bool checkFunction(string name);
	int findType(string name);
	int findVariable(string name);

	void FuncAnalyseVariable(ast*node, VariableTable* fvt);
	void FuncReadVariable(ast* node, VariableTable* fvt);
	void _Analyse(ast* node);
	
	void PrintSymbolTable();
	
public:
	void AnalyseType(ast* node);
	void AnalyseFunction(ast* node);
	void AnalyseMain(ast* node);
	void AnalyseVariable(ast* node);

	SymbolTableAnalyse();
	void Analyse(ast* root);
};