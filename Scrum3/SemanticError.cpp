#include "SemanticError.h"

SemanticError::SemanticError(){
	errnos = 0;
}

void
SemanticError::addErrs(serr* err){
	errlist.push_back(err);
	errnos++;
	return;
}

bool 
SemanticError::checkErrs(){
	if (errnos != 0)
		return true;
	else
		return false;
}

string
SemanticError::getInt(int n){
	stringstream ss;
	ss << n;
	string ret = ss.str();
	return ret;
}

string
SemanticError::showErrs(){
	int size = errlist.size();
	string sr;
	sr = ""; 
	for (int i = 0; i < size; i++){
		string et;
		switch (errlist[i]->errortype)
		{ 
		case SYNTAXERR:
			et = "SYNTAX ERROR";
			break;
		case TYPEMISMATCH:
			et = "TYPE MISMATCH";
			break;
		case PARAMISMATCH:
			et = "PARAMETER MISMATCH";
			break;
		case VARUNDECLARE:
			et = "VARIABLE UNDECLARE";
			break;
		case FUNCUNDECLARE:
			et = "FUNCTION UNDECLARE";
			break;
		default:
			et = "OTHER ERROR";
			break;
		}
		sr += "[Error" + getInt(i + 1) + "] : ";
		sr += et + " in Line" + getInt(errlist[i]->errorpos) + " \n";
		sr += errlist[i]->errorinfo + "\n\n";
	}
	return sr;
}