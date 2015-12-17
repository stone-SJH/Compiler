#include <iostream>
#include <vector>
using namespace std;

enum stype{//symbol type
	FUNCTION,
	ATYPE,
	VARIABLE
};

//overall
class SymbolTable{
public:
	vector<string> symbolName;
	vector<stype> symbolType;
};
//for class & array
class TypeTable{
public:
	vector<string> typeName;
	vector<int> typeNum;
	vector<string> typeInfo;
};
class VariableTable{
public:
	vector<string> variableName;
	vector<string> variableType;
};
class FunctionTable{
public:
	vector<string> functionName;
	//vector<string> functionReturn;
	vector<int> functionParaNum;
	vector<vector<string>> functionParaType;
	vector<vector<string>> functionParaName;
	vector<VariableTable*> functionVariable;
	vector<bool> functionState;
};