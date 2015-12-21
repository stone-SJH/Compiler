#include"SymbolTableAnalyse.h"

void 
SymbolTableAnalyse::AnalyseVariable(ast* node){
	struct var* v = (struct var*) node;
	string _type, _name;
	if (v->datatype == 1)
		_type = "integer";
	if (v->datatype == 2)
		_type = "double";
	if (v->datatype == 0)
		_type = "char";
	//[TODO]class type check 
	_name = v->name;
	vt->variableName.push_back(_name);
	vt->variableType.push_back(_type);
	st->symbolName.push_back(_name);
	st->symbolType.push_back(VARIABLE);
	return;
}
void 
SymbolTableAnalyse::AnalyseType(ast* node){
	struct arr* a = (struct arr*) node;
	string _name, _info;
	int _num;
	if (a->datatype == 1)
		_info = "integer";
	if (a->datatype == 2)
		_info = "double";
	if (a->datatype == 0)
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

void 
SymbolTableAnalyse::FuncAnalyseVariable(ast*node, VariableTable* fvt){
	struct var* v = (struct var*) node;
	string _type, _name;
	if (v->datatype == 1)
		_type = "integer";
	if (v->datatype == 2)
		_type = "double";
	if (v->datatype == 0)
		_type = "char";
	//[TODO]class type check 
	_name = v->name;
	fvt->variableName.push_back(_name);
	fvt->variableType.push_back(_type);
	return;
}

void SymbolTableAnalyse::FuncAnalyseType(ast* node, TypeTable* ftt){
	struct arr* a = (struct arr*) node;
	string _name, _info;
	int _num;
	if (a->datatype == 1)
		_info = "integer";
	if (a->datatype == 2)
		_info = "double";
	if (a->datatype == 0)
		_info = "char";
	_name = a->name;
	_num = a->size;
	ftt->typeName.push_back(_name);
	ftt->typeNum.push_back(_num);
	ftt->typeInfo.push_back(_info);
	return;
}

void 
SymbolTableAnalyse::FuncRead(ast* node, VariableTable* fvt, TypeTable* ftt){
	if (node->nodetype == 5){
		FuncAnalyseVariable(node, fvt);
		return;
	}
	if (node->nodetype == 6){
		FuncAnalyseType(node, ftt);
		return;
	}
	if (node->nodetype == 'L'){
		FuncRead(node->l, fvt, ftt);
		FuncRead(node->r, fvt, ftt);
	}
}

void 
SymbolTableAnalyse::AnalyseFunction(ast* node){
	struct fndec* f = (struct fndec*) node;
	string _name;
	//string _return;
	int _para_num;
	vector<string> _para_name;
	vector<int> _para_size;
	vector<string> _para_type;
	VariableTable* fvt = new VariableTable();
	TypeTable* ftt = new TypeTable();
	bool _funcstate;

	_name = f->name;
	/*here need to change*/
	if (_name == "main"){
		ft->functionReturn.push_back(1);
	}
	else {
		ft->functionReturn.push_back(0);
	}
	/*end*/
	ft->functionName.push_back(_name);
	st->symbolName.push_back(_name);
	st->symbolType.push_back(FUNCTION);

	_para_num = 0;
	symlist* it = f->s;
	while (it->cur != NULL){
		_para_name.push_back(it->cur->name);
		_para_size.push_back(it->cur->size);
		if (it->cur->datatype == 1)
			_para_type.push_back("integer");
		if (it->cur->datatype == 2)
			_para_type.push_back("double");
		if (it->cur->datatype == 0)
			_para_type.push_back("char");
		_para_num++;
		it = it->next;
		if (it == NULL)
			break;
	}
	ft->functionParaNum.push_back(_para_num);
	ft->functionParaName.push_back(_para_name);
	ft->functionParaSize.push_back(_para_size);
	ft->functionParaType.push_back(_para_type);

	ast*  cur = f->tl;
	FuncRead(cur, fvt, ftt);
	ft->functionVariable.push_back(fvt);
	ft->functionType.push_back(ftt);
}

void 
SymbolTableAnalyse::_Analyse(ast* node){
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

void 
SymbolTableAnalyse::Analyse(ast* root){
	_Analyse(root);
}

SymbolTableAnalyse::SymbolTableAnalyse(){
	st = new SymbolTable();
	tt = new TypeTable();
	vt = new VariableTable();
	ft = new FunctionTable();
}

para*
SymbolTableAnalyse::checkFuncPara(string name, int index){
	para* p = new para();
	int size = ft->functionParaName[index].size();
	for (int i = 0; i < size; i++){
		if (name == ft->functionParaName[index][i]){
			p->name = name;
			p->size = ft->functionParaSize[index][i];
			p->type = ft->functionParaType[index][i];
			break;
		}
	}
	return p;
}


para*
SymbolTableAnalyse::checkFuncVar(string name, int index){
	para* p = new para();
	int size = ft->functionVariable[index]->variableName.size();
	for (int i = 0; i < size; i++){
		if (name == ft->functionVariable[index]->variableName[i]){
			p->name = name;
			p->size = -1;
			p->type = ft->functionVariable[index]->variableType[i];
			break;
		}
	}
	return p;
}

para*
SymbolTableAnalyse::checkFuncType(string name, int index){
	para* p = new para();
	int size = ft->functionType[index]->typeName.size();
	for (int i = 0; i < size; i++){
		if (name == ft->functionType[index]->typeName[i]){
			p->name = name;
			p->size = ft->functionType[index]->typeNum[i];
			p->type = ft->functionType[index]->typeInfo[i];
			break;
		}
	}
	return p;
}

para*
SymbolTableAnalyse::checkVariable(string name){
	para* p = new para();
	int size = vt->variableName.size();
	for (int i = 0; i < size; i++){
		if (name == vt->variableName[i]){
			p->name = name;
			p->size = -1;
			p->type = vt->variableType[i];
			break;
		}
	}
	return p;
}

para*
SymbolTableAnalyse::checkType(string name){
	para* p = new para();
	int size = tt->typeName.size();
	for (int i = 0; i < size; i++){
		if (name == tt->typeName[i]){
			p->name = name;
			p->size = tt->typeNum[i];
			p->type = tt->typeInfo[i];
			break;
		}
	}
	return p;
}

func*
SymbolTableAnalyse::checkFunc(string name){
	func* f = new func();
	int size = ft->functionName.size();
	for (int i = 0; i < size; i++){
		if (name == ft->functionName[i]){
			f->name = name;
			f->returntype = ft->functionReturn[i];
			break;
		}
	}
	return f;
}
