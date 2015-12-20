#include "TableType.h"
#include "SymbolTableAnalyse.h"
#include "parser.h"
#include "lexer.h"
#include "defination.h"
#include <iostream>
#include <sstream>
using namespace std;

class IRGeneration{
private:
	ast* root;

	SymbolTableAnalyse* sta;
	int index;
	bool infunc;
	int arrayindex;
	int ifindex;
	int elseindex;
	int whileindex;
	int cmpindex;
	int funcindex;

	string getInt(int n);

	int getCodeAss(ast* node, int& index, string& ir);
	string getAllocaInt(string name);
	string getAllocaIntPointer(string name);
	string getAllocaIntArray(string name, int size);
	string getLoadInt(string name);
	string getLoadIntPointer(string name);
	string getStoreInt(string name, string value);
	string getStoreIntPointer(string name, string value);
	string getAllocaChar(string name);
	string getAllocaCharPointer(string name);
	string getAllocaCharArray(string name, int size);
	string getLoadChar(string name);
	string getLoadCharPointer(string name);
	string getStoreChar(string name, string value);
	string getStoreCharPointer(string name, string value);
	string getCmp(ast* node, int curwhileindex);
	string getWhile(ast* node);
	string getIfCmp(ast* node, bool elseexist, int curifindex, int curelseindex);
	string getIf(ast* node);
	string getFunction(ast* node);
	void getCallAss(ast* node, string& ir1, string& ir2);
	string getCall(ast* node);
public:
	IRGeneration(ast* root);
	string Generate();

};