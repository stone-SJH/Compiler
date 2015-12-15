#include "TableType.h"

class SymbolTableAnalyse{
private:
	SymbolTable st;
	TypeTable tt;
	VariableTable vt;
	FunctionTable ft;

	void AnalyseType();
	void AnalyseFunction();
	void AnalyseMain();
	
	void PrintSymbolTable();
	
public:
	SymbolTableAnalyse();
	void Analyse();
};