#include"SymbolTableAnalyse.h"

void SymbolTableAnalyse::AnalyseVariable(ast* node){
	struct var* v = (struct var*) node;
	string _type, _name;
	if (v->datatype == 0)
		_type = "integer";
	if (v->datatype == 1)
		_type = "double";
	if (v->datatype == 2)
		_type = "char";
	//[TODO]class type check 
	_name = v->name;
	vt->variableName.push_back(_name);
	vt->variableType.push_back(_type);
	st->symbolName.push_back(_name);
	st->symbolType.push_back(VARIABLE);
	return;
}
void SymbolTableAnalyse::AnalyseType(ast* node){
	struct arr* a = (struct arr*) node;
	string _name, _info;
	int _num;
	if (a->datatype == 0)
		_info = "integer";
	if (a->datatype == 1)
		_info = "double";
	if (a->datatype == 2)
		_info = "char";
	_name = a->name;
	_num = a->size;
	tt->typeName.push_back(_name);
	tt->typeNum.push_back(_num);
	tt->typeInfo.push_back(_info);
	st->symbolName.push_back(_name);
	st->symbolType.push_back(ATYPE);
	return;
}

void SymbolTableAnalyse::FuncAnalyseVariable(ast*node, VariableTable* fvt){
	struct var* v = (struct var*) node;
	string _type, _name;
	if (v->datatype == 0)
		_type = "integer";
	if (v->datatype == 1)
		_type = "double";
	if (v->datatype == 2)
		_type = "char";
	//[TODO]class type check 
	_name = v->name;
	fvt->variableName.push_back(_name);
	fvt->variableType.push_back(_type);
	return;
}

void SymbolTableAnalyse::FuncReadVariable(ast* node, VariableTable* fvt){
	if (node->nodetype == 5){
		FuncAnalyseVariable(node, fvt);
		return;
	}
	if (node->nodetype == 'L'){
		FuncReadVariable(node->l, fvt);
		FuncReadVariable(node->r, fvt);
	}
}

void SymbolTableAnalyse::AnalyseFunction(ast* node){
	struct fndec* f = (struct fndec*) node;
	string _name;
	//string _return;
	int _para_num;
	vector<string> _para_name;
	vector<string> _para_type;
	VariableTable* fvt = new VariableTable();
	bool _funcstate;

	_name = f->name;
	ft->functionName.push_back(_name);
	st->symbolName.push_back(_name);
	st->symbolType.push_back(FUNCTION);

	_para_num = 0;
	symlist* it = f->s;
	while (it != NULL){
		_para_name.push_back(it->cur->name);
		if (it->cur->datatype == 0)
			_para_type.push_back("integer");
		if (it->cur->datatype == 1)
			_para_type.push_back("double");
		if (it->cur->datatype == 2)
			_para_type.push_back("char");
		_para_num++;
		it = it->next;
	}
	ft->functionParaNum.push_back(_para_num);
	ft->functionParaName.push_back(_para_name);
	ft->functionParaType.push_back(_para_type);

	ast*  cur = f->tl;
	FuncReadVariable(cur, fvt);
	ft->functionVariable.push_back(fvt);
}

void SymbolTableAnalyse::_Analyse(ast* node){
	if (node == NULL)
		return;
	switch (node->nodetype)
	{
	case 5:
	{
		//cout << "variable" << endl;
		AnalyseVariable(node);
		return;
	}
	case 6:
	{
		//cout << "type" << endl;
		AnalyseType(node);
		return;
	}
	case 7:
	{
		//cout << "func" << endl;
		AnalyseFunction(node);
		return;
	}
	case 'L':
	{
		_Analyse(node->l);
		_Analyse(node->r);
		return;
	}
	}
}

void SymbolTableAnalyse::Analyse(ast* root){
	_Analyse(root);
}

SymbolTableAnalyse::SymbolTableAnalyse(){
	st = new SymbolTable();
	tt = new TypeTable();
	vt = new VariableTable();
	ft = new FunctionTable();
}