#include <iostream>
#include <vector>
using namespace std;

enum stype{//symbol type
	FUNCTION,
	TYPE,
	VARIABLE
};
enum type{
	INT,
	BOOLEAN,
	CHAR
};
//overall
class SymbolTable{
	vector<string> symbolName;
	vector<stype> symbolType;
};
//for class
class TypeTable{
	vector<string> typeName;
	vector<int> typeNum;
	vector<string> typeInfo;
};
class VariableTable{
	vector<string> variableName;
	vector<string> variableType;
	vector<string> variableValue;
};
class FunctionTable{
	vector<string> functionName;
	vector<string> functionReturn;
	vector<int> functionParaNum;
	vector<vector<string>> functionParaType;
	vector<vector<string>> functionParaName;
	vector<VariableTable> functionVariable;
	vector<bool> functionState;
};