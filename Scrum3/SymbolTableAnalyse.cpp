#include"SymbolTableAnalyse.h"

void 
SymbolTableAnalyse::AnalyseVariable(ast* node){
	struct var* v = (struct var*) node;
	string _type, _name;
	int size = st->symbolName.size();
	bool error = false;
	string retype;
	for (int i = 0; i < size; i++){
		if (st->symbolName[i] == _name){
			error = true;
			retype = st->symbolType[i];
			break;
		}
	}
	if (!error){
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
	}
	else {
		serr* err = new serr();
		err->errortype = VARREDEFINED;
		err->errorpos = node->lineno;
		err->errorinfo = "Variable '" + _name + "' redefined with " + retype + " '" + _name + "'\n";
		se->addErrs(err);
	}
	return;
}
void 
SymbolTableAnalyse::AnalyseType(ast* node){
	struct arr* a = (struct arr*) node;
	string _name, _info;
	int _num;
	int size = st->symbolName.size();
	bool error = false;
	string retype;
	for (int i = 0; i < size; i++){
		if (st->symbolName[i] == _name){
			error = true;
			retype = st->symbolType[i];
			break;
		}
	}
	if (!error){
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
	}
	else {
		serr* err = new serr();
		err->errortype = VARREDEFINED;
		err->errorpos = node->lineno;
		err->errorinfo = "AType '" + _name + "' redefined with " + retype + " '" + _name + "'\n";
		se->addErrs(err);
	}
	return;
}

void 
SymbolTableAnalyse::FuncAnalyseVariable(ast*node, VariableTable* fvt, TypeTable* ftt, int index){
	struct var* v = (struct var*) node;
	string _type, _name; 
	bool error = false;
	string retype;
	int size;
	_name = v->name;
	size = fvt->variableName.size();
	for (int i = 0; i < size; i++){
		if (fvt->variableName[i] == _name){
			error = true;
			retype = "VARIABLE";
			break;
		}
	}
	if (!error){
		size = ftt->typeName.size();
		for (int i = 0; i < size; i++){
			if (ftt->typeName[i] == _name){
				error = true;
				retype = "ATYPE";
				break;
			}
		}
		if (!error){
			size = ft->functionParaName[index].size();
			for (int i = 0; i < size; i++){
				if (ft->functionParaName[index][i] == _name){
					error = true;
					retype = "PARAMETER";
					break;
				}
			}
			if (!error){
				if (ft->functionName[index] == _name){
					error = true;
					retype = "FUNCTION";
				}
			}
		}
	}

	if (!error){
		if (v->datatype == 1)
			_type = "integer";
		if (v->datatype == 2)
			_type = "double";
		if (v->datatype == 0)
			_type = "char";
		//[TODO]class type check 

		fvt->variableName.push_back(_name);
		fvt->variableType.push_back(_type);
	}
	else {
		serr* err = new serr();
		err->errortype = VARREDEFINED;
		err->errorpos = node->lineno;
		err->errorinfo = "Variable '" + _name + "' redefined with " + retype + " '" + _name + "'\n";
		se->addErrs(err);
	}
	return;
}

void SymbolTableAnalyse::FuncAnalyseType(ast* node, VariableTable* fvt, TypeTable* ftt, int index){
	struct arr* a = (struct arr*) node;
	string _name, _info;
	int _num;
	bool error = false;
	string retype;
	int size;
	_name = a->name;
	size = fvt->variableName.size();
	for (int i = 0; i < size; i++){
		if (fvt->variableName[i] == _name){
			error = true;
			retype = "VARIABLE";
			break;
		}
	}
	if (!error){
		size = ftt->typeName.size();
		for (int i = 0; i < size; i++){
			if (ftt->typeName[i] == _name){
				error = true;
				retype = "ATYPE";
				break;
			}
		}
		if (!error){
			size = ft->functionParaName[index].size();
			for (int i = 0; i < size; i++){
				if (ft->functionParaName[index][i] == _name){
					error = true;
					retype = "PARAMETER";
					break;
				}
			}
			if (!error){
				if (ft->functionName[index] == _name){
					error = true;
					retype = "FUNCTION";
				}
			}
		}
	}

	if (!error){
		if (a->datatype == 1)
			_info = "integer";
		if (a->datatype == 2)
			_info = "double";
		if (a->datatype == 0)
			_info = "char";
		_num = a->size;
		ftt->typeName.push_back(_name);
		ftt->typeNum.push_back(_num);
		ftt->typeInfo.push_back(_info);
	}
	else{
		serr* err = new serr();
		err->errortype = VARREDEFINED;
		err->errorpos = node->lineno;
		err->errorinfo = "AType '" + _name + "' redefined with " + retype + " '" + _name + "'\n";
		se->addErrs(err);
	}
	return;
}

void 
SymbolTableAnalyse::FuncRead(ast* node, VariableTable* fvt, TypeTable* ftt, int index){
	if (node->nodetype == 5){
		FuncAnalyseVariable(node, fvt, ftt, index);
		return;
	}
	if (node->nodetype == 6){
		FuncAnalyseType(node, fvt, ftt, index);
		return;
	}
	if (node->nodetype == 'L'){
		FuncRead(node->l, fvt, ftt, index);
		FuncRead(node->r, fvt, ftt, index);
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
	int size = st->symbolName.size();
	bool error = false;
	string retype;
	for (int i = 0; i < size; i++){
		if (st->symbolName[i] == _name){
			error = true;
			retype = st->symbolType[i];
			break;
		}
	}

	if (!error){
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

		int index = ft->functionParaName.size() - 1;

		ast*  cur = f->tl;
		FuncRead(cur, fvt, ftt, index);
		ft->functionVariable.push_back(fvt);
		ft->functionType.push_back(ftt);
	}
	else{
		serr* err = new serr();
		err->errortype = VARREDEFINED;
		err->errorpos = node->lineno;
		err->errorinfo = "Function '" + _name + "' redefined with " + retype + " '" + _name + "'\n";
		se->addErrs(err);
	}
	return;
}

void
SymbolTableAnalyse::FuncConstant(){
	string _name;
	int _return_type;
	int _para_num;
	vector<string> _para_name;
	vector<int> _para_size;
	vector<string> _para_type;
	/*printa*/
	_name = "printa";
	_return_type = 0;
	_para_num = 2;
	_para_name.push_back("arr");
	_para_name.push_back("n");
	_para_size.push_back(10000);
	_para_size.push_back(-1);
	_para_type.push_back("integer");
	_para_type.push_back("integer");
	ft->functionName.push_back(_name);
	ft->functionReturn.push_back(_return_type);
	st->symbolName.push_back(_name);
	st->symbolType.push_back(FUNCTION);
	ft->functionParaNum.push_back(_para_num);
	ft->functionParaName.push_back(_para_name);
	ft->functionParaSize.push_back(_para_size);
	ft->functionParaType.push_back(_para_type);
	/*...*/

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
	FuncConstant();
}

SymbolTableAnalyse::SymbolTableAnalyse(SemanticError* semerr){
	se = semerr;
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
			f->index = i;
			f->returntype = ft->functionReturn[i];
			f->paranum = ft->functionParaNum[i];
			break;
		}
	}
	return f;
}

para*
SymbolTableAnalyse::getFuncPara(int funcindex, int paraindex){
	para* p = new para();
	p->name = ft->functionParaName[funcindex][paraindex];
	p->size = ft->functionParaSize[funcindex][paraindex];
	p->type = ft->functionParaType[funcindex][paraindex];
	return p;
}