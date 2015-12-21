#ifndef _SERROR_
#define _SERROR_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;


enum etype{
	SYNTAXERR, //?
	TYPEMISMATCH,
	PARAMISMATCH,
	VARUNDECLARE,
	FUNCUNDECLARE,
	VARREDEFINED,
	FUNCREDEFINED
};

struct serr{
	etype errortype;
	int errorpos;
	string errorinfo;
};

class SemanticError{
private:
	vector<serr*> errlist;
	int errnos;
	string getInt(int value);

public:
	SemanticError();
	void addErrs(serr* err);
	bool checkErrs();//whether have semantic error
	string showErrs();
};

#endif