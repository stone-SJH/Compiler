#include "stdafx.h"
#include "IRGeneration.h"
#include <limits.h>

int
IRGeneration::getCodeAss(ast* node, int& index0, string& ir, char& ch, double& db){
	if (node == NULL)
		return INT_MAX;
	switch (node->nodetype){
	case 1:
	{
		string ir1;
		ir1 = getCall(node, index0);
		ir += ir1;
		return INT_MAX;
	}
	case 2:
	{
		struct charcons* cc = (struct charcons*)node;
		ch = cc->ch;
		return INT_MAX;
	}
	case 3:
	{
		struct intcons* ic = (struct intcons*)node;
		int ret = ic->num;
		return ret;
	}
	case 4:
	{

	}
	case 5:
	{
		struct var* v = (struct var*) node;
		string varname = v->name;
		int vartype = v->datatype;
		if (vartype == 0){//char
			index0 = index;
			ir += getAllocaChar(varname);
		}
		else if (vartype == 1){
			index0 = index;
			ir += getAllocaInt(varname);
		}
		else if (vartype == 2){
		}
		return	INT_MAX;
	}
	case 6:{
		struct arr* a = (struct arr*) node;
		string arrname = a->name;
		int arrtype = a->datatype;
		int arrsize = a->size;
		if (arrtype == 0){
			ir += getAllocaCharArray(arrname, arrsize);
		}
		if (arrtype == 1){
			ir += getAllocaIntArray(arrname, arrsize);
		}
		if (arrtype == 2){

		}
		return INT_MAX;
	}
	case 7:
	{
		string ir1;
		ir1 = getFunction(node);
		ir += ir1;
		return INT_MAX;
	}


#define CHENJIANAN
#ifdef  CHENJIANAN
		/* start of Chen Jianan's part: IR Generation of class definition, declaration & member fetching*/
	case 8:
	{
			  /* 类实例的声明 var tt as a, a 是一个类名
			  /* 该实例是一个全局变量*/
			  struct csdec* cnode = (struct csdec*)node;
			  if (cnode == NULL)
				  return INT_MAX;

			  string vname = cnode->vname;
			  string cname = cnode->cname;

			  string ir1;

			  if (vname == "" || cname == "")
			  {
				  // Syntax Error
				  return INT_MAX;
			  }
			  // 确认符号表中存在cname和vname,该实例应该在全局符号表、变量表中能够找到
			  // 否则就是一个Syntax Error

			  // 构造llvm IR
			  ir1 = getAllocaClass(cname, vname);
			  ir += ir1;
			  return INT_MAX;
	}

	case 9:	/* 类定义 */
	{
				//
				struct csdef* cnode = (struct csdef*)node;
				if (cnode == NULL)
					return INT_MAX;
				string cname = cnode->cname;
				string fname = "";
				if (cnode->fname)
					fname = cnode->fname;
				if (cname == "")
				{
					// Syntax Error
					return INT_MAX;
				}

				string ir1 = "";

				ir1 += " %class." + cname + " = type{";
				// 如果有父类，加进来
				if (fname != "")
				{
					ir1 += " %class." + fname + ",";
				}
				// 首先对于成员变量的处理
				// 其次对于成员数组的处理
				// 最后对于成员函数的处理
				// 设计关键在于将这个函数变为全局的
				// 虽然我们自己的语言是把成员函数放在全局类表类表子函数表里面
				// llvm IR却要求成员函数是一个全局函数的指针
				// 所以如果遇到成员函数，可以按照如下规则构造一个不会重名（只要前面做好了）的全局函数
				// 类名_返回类型_函数名()
				// 例子：a->func();
				// ==>   def void @a_void_func(@class.A* %this,paralist......){
				//			entry:
				//			......
				//
				/* 示例llvm IR如下
				Function Attrs: nounwind uwtable
				define linkonce_odr i32 @_ZN1B3addEv(%class.B* %this) #3 comdat align 2 {
				entry:
				%this.addr = alloca %class.B*, align 8
				store %class.B* %this, %class.B** %this.addr, align 8
				%this1 = load %class.B*, %class.B** %this.addr
				%0 = bitcast %class.B* %this1 to %class.A*
				%a = getelementptr inbounds %class.A, %class.A* %0, i32 0, i32 0
				%1 = load i32, i32* %a, align 4
				%b = getelementptr inbounds %class.B, %class.B* %this1, i32 0, i32 1
				%2 = load i32, i32* %b, align 4
				%add = add nsw i32 %1, %2
				ret i32 %add
				}
				*/
				// 另外，关于构建的顺序： 顺序是很重要的，因为要通过getelementptr来获取成员
				// 按照变量,数组,函数的顺序
				// 这三大类型内部按照各个子表中的顺序
				// 全部align 4对齐
				// 使用getMemberIndex(membername)获取相应的下标

				// 在全局类表内获取相应的三张表
				ClassTable*		gct = sta->getClassTable();
				int classIndex = sta->findClass(cname);
				VariableTable*	cvt = gct->classVariable[classIndex];
				TypeTable*		ctt = gct->classType[classIndex];
				FunctionTable*	cft = gct->classFunction[classIndex];
				// 先处理cvt中所有变量
				if (cvt)
				{

					vector<string> varname, vartype;
					varname = cvt->variableName;
					vartype = cvt->variableType;

					// 其实现在并不关心变量名称，只需要类型就可以了
					int vartypeSize = vartype.size();
					for (int idx = 0; idx < vartypeSize; idx++)
					{
						if (vartype[idx] == "integer")
						{
							ir1 += " i32";
						}
						if (vartype[idx] == "char")
						{
							ir1 += " i8";
						}
						if (vartype[idx] == "double")
						{
							// not implemented
						}
						if (idx != vartypeSize - 1)
						{
							ir1 += ",";
						}
					}
				}

				if (ctt)
				{

					// 处理数组
					vector<string> typeName, typeType;
					vector<int> typeSize;
					typeName = ctt->typeName;
					typeSize = ctt->typeNum;
					typeType = ctt->typeInfo;
					int typeNum = typeType.size();
					for (int idx = 0; idx < typeNum; idx++)
					{
						//"[ typeSize[idx] x"." i32|i8] "的形式
						if (idx == 0)
							ir1 += ",";
						ir1 += "[ ";
						ir1 += getInt(typeSize[idx]);
						ir1 += " x ";

						if (typeType[idx] == "integer")
						{
							ir1 += "i32";
						}
						if (typeType[idx] == "char")
						{
							ir1 += "i8";
						}
						if (typeType[idx] == "double")
						{
							// Not Implemented
						}

						ir1 += " ]";

						if (idx != typeNum - 1)
							ir1 += ",";
					}
				}

				// 至此已经处理完类里面的变量和数组了
				ir1 += " }\n";
				ir += ir1;

				// 开始处理成员函数
				// abracdabra

				return INT_MAX;
	}
	case 10:
	{
			   // 对于变量和数组，只在最新的寄存器内放入相应的指针，干什么事情还是由其他的去处理吧
			   string ir1 = "";
			   struct csget* cnode = (struct csget*)node;
			  
			   string vname = cnode->cname;
			   string cname = sta->getVariableType(vname);
			   string kname = cnode->kname;
			   /*int func;             //内置的函数的类型
			   struct ast* explist; //函数的参数链表，不是函数则是NULL
			   struct ast* index;  //数组的下标，不是数组则为NULL
			   */
			   struct ast* cidx = cnode->index;
			   // 类获取成员 :a->tt;
			   // 从类表里面根据类型找子表并查找是否存在tt
			   // 按“子类->父类->父类的父类……”的顺序
			   // 判断该成员是父类中的还是子类中的
			   // 如果都找不到的话认为a类没有成员tt

			   // 确认上下文相关语法后
			   // 如果是父类的成员，获取父类的fname并且将指针转换为父类的指针
			   // bitcast @class.B* @b to class.A*
			   // 其中@b是一个class指针
			   // 否则的话，直接使用:
			   // 1)变量
			   // @v = getelementptr inbounds @class.A, @class.A* @a, i32 0, i32 X
			   // 2)数组
			   // @arr = getelementptr inbounds @class.A, @class.A* @a, i32 0, i32 X
			   // 3)函数
			   // call void @function_name(@class.A* @a)
			   // 值得注意的是，成员函数也要变成全局函数
			   // 可以按照如下规则构造一个不会重名（只要前面做好了）的全局函数
			   // 类名_返回类型_函数名()，然后在调用函数的时候，如:
			   // a->func()
			   // 则 call void @a_void_func(@class.A* @a)
			   // @a_func 会在case 9当中生成相应的IR

			   // 首先判断是子类独有的还是父类里面也有
			   string className = cname;
			   int idxOfK = sta->findVariableAndTypeInClass(kname, className);

			   ClassTable* gct = sta->getClassTable();
			   int classIndex = sta->findClass(className);
			   TypeTable* ctt = gct->classType[classIndex];
			   VariableTable* cvt = gct->classVariable[classIndex];
			   FunctionTable* cft = gct->classFunction[classIndex];

			   bool isFather = (className != cname);		// 判断是不是父类里面的元素
			   if (isFather)
			   {
				   // 是父类的，转换指针为父类指针
				   ir1 += " %" + getInt(index) + "= bitcast %class." + cname + "* " + "%" + vname + " to %class." + className + "*\n";
				   index0 = index;
				   index++;
			   }

			   // 判断是变量还是数组
			   // 如果是变量
			   if (cidx == NULL)
			   {
				   ir1 += " %" + getInt(index) + " = getelementptr inbounds %class." + className + ", %class." + className + "* ";
				   if (isFather)
					   ir1 += " %" + getInt(index - 1);
				   else
					   ir1 += " %" + vname;

				   ir1 += ", i32 0, i32 " + getInt(idxOfK) + "\n";
				   index0 = index;
				   index++;

				   ir += ir1;
				   

				   return INT_MAX;
			   }
			   // 如果是数组
			   else
			   {
				   // 先算出index的值
				   string ir2 = "";
				   char ch;
				   double db;
				   int retIdx = 0;
				   int oindex0 = index0;
				   getCodeAss(cidx, index0, ir, ch, db);
				   ir1 += ir2;
				   int arrIDX = index0;

				   //" %arr = getelementptr inbounds %class.B, %class.B* %b, i32 0, i32 2";
				   ir1 += " %" + getInt(index) + " = getelementptr inbounds %class." + className + ", %class." + className + "* ";
				   if (isFather)
					   ir1 += " %" + getInt(index - 1);
				   else
					   ir1 += " %" + vname;
				   ir1 += ", i32 0, i32 " + getInt(idxOfK) + "\n";
				   index0 = index;
				   int arrReg = index0;
				   index++;

				   string strIdx = "";
				  // char ch;
				   //double db;
				   retIdx = getCodeAss(cidx, index0, strIdx, ch, db);
				   // 判断返回的下标
				   if (retIdx != INT_MAX)	// 常数作为下标，直接返回常数了
				   {
					   strIdx = getInt(retIdx);
				   }
				   else if (oindex0 != index - 1)	// 计算表达式并保存在了%index0这个寄存器中
				   {
					   strIdx = "%" + getInt(index0);
				   }

				   else
				   {
					   // Syntax Error
					   return INT_MAX;
				   }
				   // 构造arrType，也就是定义里面的[size x i32/i8]

				   string arrType = "";


				   int cvtSize = cvt->variableName.size();
				   string arrOfType = ctt->typeInfo[idxOfK - cvtSize];
				   int arrOfSize = ctt->typeNum[idxOfK - cvtSize];

				   arrType = "[ " + getInt(arrOfSize) + " x ";
				   if (arrOfType == "integer")
					   arrType += "i32 ]";
				   if (arrOfType == "char")
					   arrType += "i8 ]";
				   if (arrOfType == "double")
				   {
					   // Not Implemented...
				   }

				   //  %arrayidx = getelementptr inbounds [10 x i32], [10 x i32]* %arr, i32 0, i64 0
				   ir1 += " %" + getInt(index) + " = getelementptr inbounds " + arrType + ", " + arrType
					   + "* %" + getInt(arrReg) + ", i32 0, i64 " + strIdx + "\n";
				   index0 = index;
				   index++;

				   ir += ir1;
				   return INT_MAX;
				   // 
			   }

				// 函数调用
				// 预计不支持

			   ir += ir1;

			   return INT_MAX;
	}
#endif
		/*End of Chen Jianan's Part.*/

	case '+':
	{
		int r1 = INT_MAX;
		int r2 = INT_MAX;
		char c1;
		char c2;
		double d1;
		double d2;
		int curindex1;
		int curindex2;
		string ir1;
		r1 = getCodeAss(node->l, index0, ir, c1, d1);
		curindex1 = index0;
		r2 = getCodeAss(node->r, index0, ir, c2, d2);
		curindex2 = index0;
		if (r1 != INT_MAX && r2 != INT_MAX){
			ir1 = "  %" + getInt(index) + " = add nsw i32 " + getInt(r1) + ", " + getInt(r2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 == INT_MAX && r2 != INT_MAX){
			ir1 = "  %" + getInt(index) + " = add nsw i32 %" + getInt(curindex1) + ", " + getInt(r2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 != INT_MAX  && r2 == INT_MAX){
			ir1 = "  %" + getInt(index) + " = add nsw i32 " + getInt(r1) + ", %" + getInt(curindex2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 == INT_MAX && r2 == INT_MAX){
			ir1 = "  %" + getInt(index) + " = add nsw i32 %" + getInt(curindex1) + ", %" + getInt(curindex2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		return INT_MAX;
	}
	case '-':
	{
		int r1 = INT_MAX;
		int r2 = INT_MAX;
		char c1;
		char c2;
		double d1;
		double d2;
		int curindex1;
		int curindex2;
		string ir1;
		r1 = getCodeAss(node->l, index0, ir, c1, d1);
		curindex1 = index0;
		r2 = getCodeAss(node->r, index0, ir, c2, d2);
		curindex2 = index0;
		if (r1 != INT_MAX && r2 != INT_MAX){
			ir1 = "  %" + getInt(index) + " = sub nsw i32 " + getInt(r1) + ", " + getInt(r2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 == INT_MAX && r2 != INT_MAX){
			ir1 = "  %" + getInt(index) + " = sub nsw i32 %" + getInt(curindex1) + ", " + getInt(r2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 != INT_MAX  && r2 == INT_MAX){
			ir1 = "  %" + getInt(index) + " = sub nsw i32 " + getInt(r1) + ", %" + getInt(curindex2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 == INT_MAX && r2 == INT_MAX){
			ir1 = "  %" + getInt(index) + " = sub nsw i32 %" + getInt(curindex1) + ", %" + getInt(curindex2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		return INT_MAX;
	}
	case '*':
	{
		int r1 = INT_MAX;
		int r2 = INT_MAX;
		char c1;
		char c2;
		double d1;
		double d2;
		int curindex1;
		int curindex2;
		string ir1;
		r1 = getCodeAss(node->l, index0, ir, c1, d1);
		curindex1 = index0;
		r2 = getCodeAss(node->r, index0, ir, c2, d2);
		curindex2 = index0;
		if (r1 != INT_MAX && r2 != INT_MAX){
			ir1 = "  %" + getInt(index) + " = mul nsw i32 " + getInt(r1) + ", " + getInt(r2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 == INT_MAX && r2 != INT_MAX){
			ir1 = "  %" + getInt(index) + " = mul nsw i32 %" + getInt(curindex1) + ", " + getInt(r2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 != INT_MAX  && r2 == INT_MAX){
			ir1 = "  %" + getInt(index) + " = mul nsw i32 " + getInt(r1) + ", %" + getInt(curindex2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 == INT_MAX && r2 == INT_MAX){
			ir1 = "  %" + getInt(index) + " = mul nsw i32 %" + getInt(curindex1) + ", %" + getInt(curindex2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		return INT_MAX;
	}
	case '/':
	{
		int r1 = INT_MAX;
		int r2 = INT_MAX;
		char c1;
		char c2;
		double d1;
		double d2;
		int curindex1;
		int curindex2;
		string ir1;
		r1 = getCodeAss(node->l, index0, ir, c1, d1);
		curindex1 = index0;
		r2 = getCodeAss(node->r, index0, ir, c2, d2);
		curindex2 = index0;
		if (r1 != INT_MAX && r2 != INT_MAX){
			ir1 = "  %" + getInt(index) + " = sdiv i32 " + getInt(r1) + ", " + getInt(r2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 == INT_MAX && r2 != INT_MAX){
			ir1 = "  %" + getInt(index) + " = sdiv i32 %" + getInt(curindex1) + ", " + getInt(r2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 != INT_MAX  && r2 == INT_MAX){
			ir1 = "  %" + getInt(index) + " = sdiv i32 " + getInt(r1) + ", %" + getInt(curindex2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 == INT_MAX && r2 == INT_MAX){
			ir1 = "  %" + getInt(index) + " = sdiv i32 %" + getInt(curindex1) + ", %" + getInt(curindex2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		return INT_MAX;
	}
	case '%':
	{
		int r1 = INT_MAX;
		int r2 = INT_MAX;
		char c1;
		char c2;
		double d1;
		double d2;
		int curindex1;
		int curindex2;
		string ir1;
		r1 = getCodeAss(node->l, index0, ir, c1, d1);
		curindex1 = index0;
		r2 = getCodeAss(node->r, index0, ir, c2, d2);
		curindex2 = index0;
		if (r1 != INT_MAX && r2 != INT_MAX){
			ir1 = "  %" + getInt(index) + " = srem i32 " + getInt(r1) + ", " + getInt(r2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 == INT_MAX && r2 != INT_MAX){
			ir1 = "  %" + getInt(index) + " = srem i32 %" + getInt(curindex1) + ", " + getInt(r2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 != INT_MAX  && r2 == INT_MAX){
			ir1 = "  %" + getInt(index) + " = srem i32 " + getInt(r1) + ", %" + getInt(curindex2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		else if (r1 == INT_MAX && r2 == INT_MAX){
			ir1 = "  %" + getInt(index) + " = srem i32 %" + getInt(curindex1) + ", %" + getInt(curindex2) + "\n";
			ir += ir1;
			index0 = index;
			index++;
		}
		return INT_MAX;
	}
	case '=':
	{
		struct symasgn* sa = (struct symasgn*)node;
		string varname = sa->name;
		ast* indexnode = sa->index;
		if (sa->cname == NULL)
		{
			if (indexnode == NULL){
				if (infunc){
					int typecode = 1;
					para* p = sta->checkFuncPara(varname, funcindex);
					if (p->name != ""){
						varname += ".var";
						typecode = 0;
					}
					else {
						p = sta->checkFuncVar(varname, funcindex);
						if (p->name != ""){
							typecode = 0;
						}
					}
					if (typecode == 0){
						if (p->type == "integer"){
							int r = INT_MAX;
							char c;
							double d;
							r = getCodeAss(sa->v, index0, ir, c, d);
							if (r != INT_MAX){
								string ir1 = "  store i32 " + getInt(r) + ", i32* %" + varname + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else{
								string ir1 = "  store i32 %" + getInt(index0) + ", i32* %" + varname + "\n";
								ir += ir1;
								return INT_MAX;
							}
						}
						else if (p->type == "char"){
							int r = INT_MAX;
							char c = 0;
							double d;
							r = getCodeAss(sa->v, index0, ir, c, d);
							if (c == 0){
								string ir1 = "  store i8 %" + getInt(index0) + ", i8* %" + varname + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else{
								string ir1 = "  store i8 " + getInt((int)c) + ", i8* %" + varname + "\n";
								ir += ir1;
								ch = 0;
								return INT_MAX;
							}
						}
					}
					else {
						serr* err = new serr();
						err->errortype = VARUNDECLARE;
						err->errorpos = sa->lineno;
						err->errorinfo = "Variable '" + varname + "' use without declaration.\n";
						se->addErrs(err);
						return INT_MAX;
					}
				}
				else{
					para* p = sta->checkVariable(varname);
					if (p->name != ""){
						if (p->type == "integer"){
							int r = INT_MAX;
							char c;
							double d;
							r = getCodeAss(sa->v, index0, ir, c, d);
							if (r != INT_MAX){
								string ir1 = "  store i32 " + getInt(r) + ", i32* %" + varname + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else{
								string ir1 = "  store i32 %" + getInt(index0) + ", i32* %" + varname + "\n";
								ir += ir1;
								return INT_MAX;
							}
						}
						else if (p->type == "char"){
							int r = INT_MAX;
							char c = 0;
							double d;
							r = getCodeAss(sa->v, index0, ir, c, d);
							if (c == 0){
								string ir1 = "  store i8 %" + getInt(index0) + ", i8* %" + varname + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else{
								string ir1 = "  store i8 " + getInt((int)ch) + ", i8* %" + varname + "\n";
								ir += ir1;
								ch = 0;
								return INT_MAX;
							}
						}
					}
					else{
						serr* err = new serr();
						err->errortype = VARUNDECLARE;
						err->errorpos = sa->lineno;
						err->errorinfo = "Variable '" + varname + "' use without declaration.\n";
						se->addErrs(err);
						return INT_MAX;
					}
				}
			}
			else {
				if (infunc){
					int typecode = 1;
					para* p = sta->checkFuncPara(varname, funcindex);
					if (p->name != ""){
						varname += ".var";
						typecode = 0;
					}
					else {
						p = sta->checkFuncType(varname, funcindex);
						if (p->name != ""){
							typecode = -1;
						}
					}
					if (typecode == 0){
						if (p->type == "integer"){
							string ir1;
							int r = INT_MAX;
							char c1;
							double d1;
							r = getCodeAss(indexnode, index0, ir1, c1, d1);
							int curindex = index0;
							int rr = INT_MAX;
							char c2;
							double d2;
							rr = getCodeAss(sa->v, index0, ir1, c2, d2);
							int curindexx = index0;
							if (r != INT_MAX && rr != INT_MAX){
								int curindex = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i32 " + getInt(rr) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r != INT_MAX && rr == INT_MAX){
								int curindex = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i32 %" + getInt(curindexx) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && rr != INT_MAX){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex0) + " to i64\n";
								curindex0 = index;
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex1) + " , i64 %" + getInt(curindex0) + "\n";
								index0 = index;
								index++;

								ir1 += "  store i32 " + getInt(rr) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && rr == INT_MAX){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex) + " to i64\n";
								curindex0 = index;
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex1) + " , i64 %" + getInt(curindex0) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i32 %" + getInt(curindexx) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
						}
						else if (p->type == "char"){
							string ir1;
							int r = INT_MAX;
							char c1 = 0;
							double d1;
							r = getCodeAss(indexnode, index0, ir1, c1, d1);
							int curindex = index0;
							int rr = INT_MAX;
							char c2 = 0;
							double d2;
							rr = getCodeAss(sa->v, index0, ir1, c2, d2);
							int curindexx = index0;
							if (r != INT_MAX && c2 != 0){
								int curindex = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 " + getInt((int)c2) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r != INT_MAX && c2 == 0){
								int curindex = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 %" + getInt(curindexx) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && c2 != 0){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex0) + " to i64\n";
								curindex0 = index;
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex1) + " , i64 %" + getInt(curindex0) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 " + getInt((int)ch) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && c2 == 0){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex) + " to i64\n";
								curindex0 = index;
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex1) + " , i64 %" + getInt(curindex0) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 %" + getInt(curindexx) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
						}
					}
					else if (typecode == -1){
						if (p->type == "integer"){
							string ir1;
							int r = INT_MAX;
							char c1;
							double d1;
							r = getCodeAss(indexnode, index0, ir1, c1, d1);
							int curindex = index0;
							int rr = INT_MAX;
							char c2;
							double d2;
							rr = getCodeAss(sa->v, index0, ir1, c2, d2);
							int curindexx = index0;
							if (r != INT_MAX && rr != INT_MAX){
								int curindex = index;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i32]* %" + varname + ", i32 0, i32 0\n";
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i32 " + getInt(rr) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r != INT_MAX && rr == INT_MAX){
								int curindex = index;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i32]* %" + varname + ", i32 0, i32 0\n";
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i32 %" + getInt(curindexx) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && rr != INT_MAX){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i32]* %" + varname + ", i32 0, i32 0\n";
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i32 " + getInt(rr) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && rr == INT_MAX){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i32]* %" + varname + ", i32 0, i32 0\n";
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i32 %" + getInt(curindexx) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
						}
						else if (p->type == "char"){
							string ir1;
							int r = INT_MAX;
							char c1 = 0;
							double d1;
							r = getCodeAss(indexnode, index0, ir1, c1, d1);
							int curindex = index0;
							int rr = INT_MAX;
							char c2 = 0;
							double d2;
							rr = getCodeAss(sa->v, index0, ir1, c2, d2);
							int curindexx = index0;
							if (r != INT_MAX && c2 != 0){
								int curindex = index;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i8]* %" + varname + ", i32 0, i32 0\n";
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 " + getInt((int)c2) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r != INT_MAX && c2 == 0){
								int curindex = index;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i8]* %" + varname + ", i32 0, i32 0\n";
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 %" + getInt(curindexx) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && c2 != 0){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i8]* %" + varname + ", i32 0, i32 0\n";
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 " + getInt((int)c2) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && c2 == 0){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i8]* %" + varname + ", i32 0, i32 0\n";
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 %" + getInt(curindexx) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
						}
					}
					else {
						serr* err = new serr();
						err->errortype = VARUNDECLARE;
						err->errorpos = sa->lineno;
						err->errorinfo = "Variable '" + varname + "' use without declaration.\n";
						se->addErrs(err);
						return INT_MAX;
					}
				}
				else{
					para* p = sta->checkType(varname);
					if (p->name != ""){
						if (p->type == "integer"){
							string ir1;
							int r = INT_MAX;
							char c1;
							double d1;
							r = getCodeAss(indexnode, index0, ir1, c1, d1);
							int curindex = index0;
							int rr = INT_MAX;
							char c2;
							double d2;
							rr = getCodeAss(sa->v, index0, ir1, c2, d2);
							int curindexx = index0;
							if (r != INT_MAX && rr != INT_MAX){
								int curindex = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i32 " + getInt(rr) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r != INT_MAX && rr == INT_MAX){
								int curindex = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex) + ", i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i32 %" + getInt(curindexx) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && rr != INT_MAX){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex0) + " to i64\n";
								curindex0 = index;
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex1) + ", i64 %" + getInt(curindex0) + "\n";
								index0 = index;
								index++;

								ir1 += "  store i32 " + getInt(rr) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && rr == INT_MAX){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex) + " to i64\n";
								curindex0 = index;
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex1) + ", i64 %" + getInt(curindex0) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i32 %" + getInt(curindexx) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
						}
						else if (p->type == "char"){
							string ir1;
							int r = INT_MAX;
							char c1 = 0;
							double d1;
							r = getCodeAss(indexnode, index0, ir1, c1, d1);
							int curindex = index0;
							int rr = INT_MAX;
							char c2 = 0;
							double d2;
							rr = getCodeAss(sa->v, index0, ir1, c2, d2);
							int curindexx = index0;
							if (r != INT_MAX && c2 != 0){
								int curindex = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 " + getInt((int)c2) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r != INT_MAX && c2 == 0){
								int curindex = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 %" + getInt(curindexx) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && c2 != 0){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex0) + " to i64\n";
								curindex0 = index;
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex1) + " , i64 %" + getInt(curindex0) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 " + getInt((int)ch) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && c2 == 0){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex) + " to i64\n";
								curindex0 = index;
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex1) + " , i64 %" + getInt(curindex0) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 %" + getInt(curindexx) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
						}
					}
					else{
						serr* err = new serr();
						err->errortype = VARUNDECLARE;
						err->errorpos = sa->lineno;
						err->errorinfo = "Variable '" + varname + "' use without declaration.\n";
						se->addErrs(err);
						return INT_MAX;
					}
				}
			}
		}
		else
		{
			// 类成员
			if (indexnode == NULL){
				if (infunc){
					int typecode = 1;
					para* p = sta->checkFuncPara(varname, funcindex);
					if (p->name != ""){
						varname += ".var";
						typecode = 0;
					}
					else {
						p = sta->checkFuncVar(varname, funcindex);
						if (p->name != ""){
							typecode = 0;
						}
					}
					if (typecode == 0){
						if (p->type == "integer"){
							int r = INT_MAX;
							char c;
							double d;
							r = getCodeAss(sa->v, index0, ir, c, d);
							if (r != INT_MAX){
								string ir1 = "  store i32 " + getInt(r) + ", i32* %" + varname + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else{
								string ir1 = "  store i32 %" + getInt(index0) + ", i32* %" + varname + "\n";
								ir += ir1;
								return INT_MAX;
							}
						}
						else if (p->type == "char"){
							int r = INT_MAX;
							char c = 0;
							double d;
							r = getCodeAss(sa->v, index0, ir, c, d);
							if (c == 0){
								string ir1 = "  store i8 %" + getInt(index0) + ", i8* %" + varname + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else{
								string ir1 = "  store i8 " + getInt((int)c) + ", i8* %" + varname + "\n";
								ir += ir1;
								ch = 0;
								return INT_MAX;
							}
						}
					}
					else {
						serr* err = new serr();
						err->errortype = VARUNDECLARE;
						err->errorpos = sa->lineno;
						err->errorinfo = "Variable '" + varname + "' use without declaration.\n";
						se->addErrs(err);
						return INT_MAX;
					}
				}
				else{
					para* p = sta->checkVariable(varname);
					if (p->name != ""){
						if (p->type == "integer"){
							int r = INT_MAX;
							char c;
							double d;
							r = getCodeAss(sa->v, index0, ir, c, d);
							if (r != INT_MAX){
								string ir1 = "  store i32 " + getInt(r) + ", i32* %" + varname + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else{
								string ir1 = "  store i32 %" + getInt(index0) + ", i32* %" + varname + "\n";
								ir += ir1;
								return INT_MAX;
							}
						}
						else if (p->type == "char"){
							int r = INT_MAX;
							char c = 0;
							double d;
							r = getCodeAss(sa->v, index0, ir, c, d);
							if (c == 0){
								string ir1 = "  store i8 %" + getInt(index0) + ", i8* %" + varname + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else{
								string ir1 = "  store i8 " + getInt((int)ch) + ", i8* %" + varname + "\n";
								ir += ir1;
								ch = 0;
								return INT_MAX;
							}
						}
					}
					else{
						serr* err = new serr();
						err->errortype = VARUNDECLARE;
						err->errorpos = sa->lineno;
						err->errorinfo = "Variable '" + varname + "' use without declaration.\n";
						se->addErrs(err);
						return INT_MAX;
					}
				}
			}
			else {
				// 构造一个csget,获取指针
				struct csget* cnode = (csget*)newcsget(NULL, sa->cname, sa->name, 0, NULL, sa->index);
				string ir1 = "";
				char ch;
				double db;
				getCodeAss(cnode, index0, ir1, ch, db);
				ir += "========================\n";
				ir += ir1;
				ir += "\\======================\n";
				return INT_MAX;


				/*string className;
				int idxOfK = sta->findVariableAndTypeInClass(varname,className);
				
				// 检查类里面是否有这个变量的存在，如果存在的话同时获取类和index
				if (className == "")
				{
					serr* err = new serr();
					err->errortype = VARUNDECLARE;
					err->errorinfo = "Variable '" + varname + "' use without declaration.\n";
					se->addErrs(err);
					return INT_MAX;
				}*/


				
				if (infunc){
					int typecode = 1;
					para* p = sta->checkFuncPara(varname, funcindex);
					if (p->name != ""){
						varname += ".var";
						typecode = 0;
					}
					else {
						p = sta->checkFuncType(varname, funcindex);
						if (p->name != ""){
							typecode = -1;
						}
					}
					if (typecode == 0){
						if (p->type == "integer"){
							string ir1;
							int r = INT_MAX;
							char c1;
							double d1;
							r = getCodeAss(indexnode, index0, ir1, c1, d1);
							int curindex = index0;
							int rr = INT_MAX;
							char c2;
							double d2;
							rr = getCodeAss(sa->v, index0, ir1, c2, d2);
							int curindexx = index0;
							if (r != INT_MAX && rr != INT_MAX){
								int curindex = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i32 " + getInt(rr) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r != INT_MAX && rr == INT_MAX){
								int curindex = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i32 %" + getInt(curindexx) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && rr != INT_MAX){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex0) + " to i64\n";
								curindex0 = index;
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex1) + " , i64 %" + getInt(curindex0) + "\n";
								index0 = index;
								index++;

								ir1 += "  store i32 " + getInt(rr) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && rr == INT_MAX){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex) + " to i64\n";
								curindex0 = index;
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex1) + " , i64 %" + getInt(curindex0) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i32 %" + getInt(curindexx) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
						}
						else if (p->type == "char"){
							string ir1;
							int r = INT_MAX;
							char c1 = 0;
							double d1;
							r = getCodeAss(indexnode, index0, ir1, c1, d1);
							int curindex = index0;
							int rr = INT_MAX;
							char c2 = 0;
							double d2;
							rr = getCodeAss(sa->v, index0, ir1, c2, d2);
							int curindexx = index0;
							if (r != INT_MAX && c2 != 0){
								int curindex = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 " + getInt((int)c2) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r != INT_MAX && c2 == 0){
								int curindex = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 %" + getInt(curindexx) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && c2 != 0){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex0) + " to i64\n";
								curindex0 = index;
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex1) + " , i64 %" + getInt(curindex0) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 " + getInt((int)ch) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && c2 == 0){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex) + " to i64\n";
								curindex0 = index;
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex1) + " , i64 %" + getInt(curindex0) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 %" + getInt(curindexx) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
						}
					}
					else if (typecode == -1){
						if (p->type == "integer"){
							string ir1;
							int r = INT_MAX;
							char c1;
							double d1;
							r = getCodeAss(indexnode, index0, ir1, c1, d1);
							int curindex = index0;
							int rr = INT_MAX;
							char c2;
							double d2;
							rr = getCodeAss(sa->v, index0, ir1, c2, d2);
							int curindexx = index0;
							if (r != INT_MAX && rr != INT_MAX){
								int curindex = index;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i32]* %" + varname + ", i32 0, i32 0\n";
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i32 " + getInt(rr) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r != INT_MAX && rr == INT_MAX){
								int curindex = index;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i32]* %" + varname + ", i32 0, i32 0\n";
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i32 %" + getInt(curindexx) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && rr != INT_MAX){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i32]* %" + varname + ", i32 0, i32 0\n";
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i32 " + getInt(rr) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && rr == INT_MAX){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i32]* %" + varname + ", i32 0, i32 0\n";
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i32 %" + getInt(curindexx) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
						}
						else if (p->type == "char"){
							string ir1;
							int r = INT_MAX;
							char c1 = 0;
							double d1;
							r = getCodeAss(indexnode, index0, ir1, c1, d1);
							int curindex = index0;
							int rr = INT_MAX;
							char c2 = 0;
							double d2;
							rr = getCodeAss(sa->v, index0, ir1, c2, d2);
							int curindexx = index0;
							if (r != INT_MAX && c2 != 0){
								int curindex = index;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i8]* %" + varname + ", i32 0, i32 0\n";
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 " + getInt((int)c2) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r != INT_MAX && c2 == 0){
								int curindex = index;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i8]* %" + varname + ", i32 0, i32 0\n";
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 %" + getInt(curindexx) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && c2 != 0){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i8]* %" + varname + ", i32 0, i32 0\n";
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 " + getInt((int)c2) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && c2 == 0){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i8]* %" + varname + ", i32 0, i32 0\n";
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(index - 1) + ", i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 %" + getInt(curindexx) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
						}
					}
					else {
						serr* err = new serr();
						err->errortype = VARUNDECLARE;
						err->errorpos = sa->lineno;
						err->errorinfo = "Variable '" + varname + "' use without declaration.\n";
						se->addErrs(err);
						return INT_MAX;
					}
				}
				else{
					para* p = sta->checkType(varname);
					if (p->name != ""){
						if (p->type == "integer"){
							string ir1;
							int r = INT_MAX;
							char c1;
							double d1;
							r = getCodeAss(indexnode, index0, ir1, c1, d1);
							int curindex = index0;
							int rr = INT_MAX;
							char c2;
							double d2;
							rr = getCodeAss(sa->v, index0, ir1, c2, d2);
							int curindexx = index0;
							if (r != INT_MAX && rr != INT_MAX){
								int curindex = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i32 " + getInt(rr) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r != INT_MAX && rr == INT_MAX){
								int curindex = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex) + ", i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i32 %" + getInt(curindexx) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && rr != INT_MAX){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex0) + " to i64\n";
								curindex0 = index;
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex1) + ", i64 %" + getInt(curindex0) + "\n";
								index0 = index;
								index++;

								ir1 += "  store i32 " + getInt(rr) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && rr == INT_MAX){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex) + " to i64\n";
								curindex0 = index;
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex1) + ", i64 %" + getInt(curindex0) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i32 %" + getInt(curindexx) + ", i32* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
						}
						else if (p->type == "char"){
							string ir1;
							int r = INT_MAX;
							char c1 = 0;
							double d1;
							r = getCodeAss(indexnode, index0, ir1, c1, d1);
							int curindex = index0;
							int rr = INT_MAX;
							char c2 = 0;
							double d2;
							rr = getCodeAss(sa->v, index0, ir1, c2, d2);
							int curindexx = index0;
							if (r != INT_MAX && c2 != 0){
								int curindex = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 " + getInt((int)c2) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r != INT_MAX && c2 == 0){
								int curindex = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 %" + getInt(curindexx) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && c2 != 0){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex0) + " to i64\n";
								curindex0 = index;
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex1) + " , i64 %" + getInt(curindex0) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 " + getInt((int)ch) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
							else if (r == INT_MAX && c2 == 0){
								int curindex0 = index0;
								int curindex1 = index;
								ir1 += getLoadIntPointer(varname);
								ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex) + " to i64\n";
								curindex0 = index;
								index++;
								ir1 += "  %" + getInt(index) + " = getelementptr inbounds i8* %" + getInt(curindex1) + " , i64 %" + getInt(curindex0) + "\n";
								index0 = index;
								index++;
								ir1 += "  store i8 %" + getInt(curindexx) + ", i8* %" + getInt(index0) + "\n";
								ir += ir1;
								return INT_MAX;
							}
						}
					}
					else{
						serr* err = new serr();
						err->errortype = VARUNDECLARE;
						err->errorpos = sa->lineno;
						err->errorinfo = "Variable '" + varname + "' use without declaration.\n";
						se->addErrs(err);
						return INT_MAX;
					}
				}
			}

			return INT_MAX;
		}
	}
	case 'N':
	{
		struct symref* sr = (struct symref*)node;
		string varname = sr->name;
		ast* indexnode = sr->index;
		if (indexnode == NULL){
			if (infunc){
				int typecode = 1;//1 for error
				para* p = sta->checkFuncPara(varname, funcindex);
				if (p->name != ""){
					varname += ".var";
					typecode = 0;
					if (p->size != -1){
						arrayindex++;
						typecode = -1;
					}
				}
				else {
					p = sta->checkFuncVar(varname, funcindex);
					if (p->name != ""){
						typecode = 0;
					}
					else {
						p = sta->checkFuncType(varname, funcindex);
						if (p->name != ""){
							typecode = -2;
							arrayindex++;
						}
					}
				}

				if (typecode != 1){
					string ir1;
					if (p->type == "integer"){
						index0 = index;
						if (typecode == 0)
							ir1 = getLoadInt(varname);
						else if (typecode == -1)
							ir1 = getLoadIntPointer(varname);
						else if (typecode == -2){
							ir1 = "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i32]* %" + varname + ", i32 0, i32 0\n";
							index++;
						}
						ir += ir1;
						return INT_MAX;
					}
					else if (p->type == "char"){
						index0 = index;
						if (typecode == 0)
							ir1 = getLoadChar(varname);
						else if (typecode == -1)
							ir1 = getLoadCharPointer(varname);
						else if (typecode == -2){
							ir1 = "  %" + getInt(index) + " = getelementptr inbounds[" + getInt(p->size) + " x i8]* %" + varname + ", i32 0, i32 0\n";
							index++;
						}
						ir += ir1;
						return INT_MAX;
					}
				}
				else{
					serr* err = new serr();
					err->errortype = VARUNDECLARE;
					err->errorpos = sr->lineno;
					err->errorinfo = "Variable '" + varname + "' use without declaration.\n";
					se->addErrs(err);
					return INT_MAX;
				}
			}
			else{
				para* p = sta->checkVariable(varname);
				if (p->name != ""){
					string ir1;
					if (p->type == "integer"){
						index0 = index;
						ir1 = getLoadInt(varname);
						ir += ir1;
						return INT_MAX;
					}
					else if (p->type == "char"){
						index0 = index;
						ir1 = getLoadChar(varname);
						ir += ir1;
						return INT_MAX;
					}
				}
				else{
					p = sta->checkType(varname);
					if (p->name != ""){
						string ir1;
						if (p->type == "integer"){
							index0 = index;
							ir1 = getLoadIntPointer(varname);
							ir += ir1;
							return INT_MAX;
						}
						else if (p->type == "char"){
							index0 = index;
							ir1 = getLoadCharPointer(varname);
							ir += ir1;
							return INT_MAX;
						}
					}
					else{
						serr* err = new serr();
						err->errortype = VARUNDECLARE;
						err->errorpos = sr->lineno;
						err->errorinfo = "Variable '" + varname + "' use without declaration.\n";
						se->addErrs(err);
						return INT_MAX;
					}
				}
			}

		}
		else{//array
			if (infunc){
				int typecode = 1;
				para* p = sta->checkFuncPara(varname, funcindex);
				if (p->name != ""){
					varname += ".var";
					typecode = -1;
				}
				else {
					p = sta->checkFuncType(varname, funcindex);
					if (p->name != ""){
						typecode = 0;
					}
				}
				if (typecode != 1){
					string ir1;
					int r = INT_MAX;
					char c;
					double d;
					r = getCodeAss(indexnode, index0, ir1, c, d);
					if (r != INT_MAX){
						if (p->type == "integer"){
							int curindex = index;
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
							index++;
							ir1 += getLoadInt(getInt(index - 1));
							index0 = index - 1;
							ir += ir1;
							return INT_MAX;
						}
						else{
							serr* err = new serr();
							err->errortype = TYPEMISMATCH;
							err->errorpos = sr->lineno;
							err->errorinfo = "Only an integer can be an index.\n";
							se->addErrs(err);
							return INT_MAX;
						}
					}
					else{
						int curindex0 = index0;
						int curindex1 = index;
						if (p->type == "integer"){
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex0) + " to i64\n";
							curindex0 = index;
							index++;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex1) + " , i64 %" + getInt(curindex0) + "\n";
							index++;
							ir1 += getLoadInt(getInt(index - 1));
							index0 = index - 1;
							ir += ir1;
							return INT_MAX;
						}
						else if (p->type == "char"){
							serr* err = new serr();
							err->errortype = TYPEMISMATCH;
							err->errorpos = sr->lineno;
							err->errorinfo = "Variable '" + varname + "' can not be an index.\n";
							se->addErrs(err);
							return INT_MAX;
						}
					}
				}
				else{
					serr* err = new serr();
					err->errortype = VARUNDECLARE;
					err->errorpos = sr->lineno;
					err->errorinfo = "Variable '" + varname + "' use without declaration.\n";
					se->addErrs(err);
					return INT_MAX;
				}
			}
			else{
				para* p = sta->checkType(varname);
				if (p->name != ""){
					string ir1;
					int r = INT_MAX;
					char c = 0;
					double d;
					r = getCodeAss(indexnode, index0, ir1, c, d);
					if (r != INT_MAX){
						if (p->type == "integer"){
							int curindex = index;
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex) + " , i64 " + getInt(r) + "\n";
							index++;
							ir1 += getLoadInt(getInt(index - 1));
							index0 = index - 1;
							ir += ir1;
							return INT_MAX;
						}
						else{
							serr* err = new serr();
							err->errortype = TYPEMISMATCH;
							err->errorpos = sr->lineno;
							err->errorinfo = "Only an integer can be an index.\n";
							se->addErrs(err);
							return INT_MAX;
						}
					}
					else{
						int curindex0 = index0;
						int curindex1 = index;
						if (p->type == "integer"){
							ir1 += getLoadIntPointer(varname);
							ir1 += "  %" + getInt(index) + " = sext i32 %" + getInt(curindex0) + " to i64\n";
							curindex0 = index;
							index++;
							ir1 += "  %" + getInt(index) + " = getelementptr inbounds i32* %" + getInt(curindex1) + " , i64 %" + getInt(curindex0) + "\n";
							index++;
							ir1 += getLoadInt(getInt(index - 1));
							index0 = index - 1;
							ir += ir1;
							return INT_MAX;
						}
						else if (p->type == "char"){
							serr* err = new serr();
							err->errortype = TYPEMISMATCH;
							err->errorpos = sr->lineno;
							err->errorinfo = "Variable '" + varname + "' can not be an index.\n";
							se->addErrs(err);
							return INT_MAX;
						}
					}
				}
				else{
					serr* err = new serr();
					err->errortype = VARUNDECLARE;
					err->errorpos = sr->lineno;
					err->errorinfo = "Variable '" + varname + "' use without declaration.\n";
					se->addErrs(err);
					return INT_MAX;
				}
			}
		}
	}
	case 'I':
	{
		string ir1;
		ir1 = getIf(node);
		ir += ir1;
		return INT_MAX;
	}
	case 'W':
	{
		string ir1;
		ir1 = getWhile(node);
		ir += ir1;
		return INT_MAX;
	}
	case 'R':
	{
		if (infunc){
			ast* retnode = node->l;
			int r;
			if (retnode != NULL){
				r = getCodeAss(retnode, index0, ir, ch, db);
				if (r != INT_MAX){
					index0 = r;
					retcons = 1;
				}
			}
			else
				r = INT_MAX;
			return r;
		}
		else{
			//error
			return INT_MAX;
		}
	}
	case 'L':
	{
		if (node->l != NULL)
			getCodeAss(node->l, index0, ir, ch, db);
		if (node->r != NULL)
			getCodeAss(node->r, index0, ir, ch, db);
	}
	}
	return INT_MAX;
}

string
IRGeneration::getInt(int n){
	stringstream ss;
	ss << n;
	string ret = ss.str();
	return ret;
}

string
IRGeneration::getFile(string filename){
	ifstream ifs(filename);
	ostringstream buf;
	char ch;
	while (buf && ifs.get(ch))
		buf.put(ch);
	string ret = buf.str();
	return ret;
}

string
IRGeneration::getAllocaInt(string name){
	string ir;
	ir = "  %" + name + " = alloca i32, align 4\n";
	return ir;
}

string
IRGeneration::getAllocaIntPointer(string name){
	string ir;
	ir = "  %" + name + " = alloca i32*, align 8\n";
	return ir;
}

string
IRGeneration::getAllocaIntArray(string name, int size){
	string ir;
	ir = "  %" + name + " = alloca [" + getInt(size) + " x i32], align 4\n";
	return ir;
}

string
IRGeneration::getLoadInt(string name){
	string ir;
	ir = "  %" + getInt(index) + " = load i32* %" + name + "\n";
	index++;
	return ir;
}

string
IRGeneration::getLoadIntPointer(string name){
	string ir;
	ir = "  %" + getInt(index) + " = load i32** %" + name + "\n";
	index++;
	return ir;
}

string
IRGeneration::getStoreInt(string name, string value){
	string ir;
	ir = "  store i32 %" + value + ", i32* %" + name + "\n";
	return ir;
}

string
IRGeneration::getStoreIntPointer(string name, string value){
	string ir;
	ir = "  store i32* %" + value + ", i32** %" + name + "\n";
	return ir;
}

string
IRGeneration::getAllocaChar(string name){
	string ir;
	ir = "  %" + name + " = alloca i8, align 1\n";
	return ir;
}

string
IRGeneration::getAllocaCharPointer(string name){
	string ir;
	ir = "  %" + name + " = alloca i8*, align 2\n";
	return ir;
}

string
IRGeneration::getAllocaCharArray(string name, int size){
	string ir;
	ir = "  %" + name + " = alloca [" + getInt(size) + " x i8], align 1\n";
	return ir;
}

string
IRGeneration::getLoadChar(string name){
	string ir;
	ir = "  %" + getInt(index) + " = load i8* %" + name + "\n";
	index++;
	return ir;
}

string
IRGeneration::getLoadCharPointer(string name){
	string ir;
	ir = "  %" + getInt(index) + " = load i8** %" + name + "\n";
	index++;
	return ir;
}

string
IRGeneration::getStoreChar(string name, string value){
	string ir;
	ir = "  store i8 %" + value + ", i8* %" + name + "\n";
	return ir;
}

string
IRGeneration::getStoreCharPointer(string name, string value){
	string ir;
	ir = "  store i8* %" + value + ", i8** %" + name + "\n";
	return ir;
}

string
IRGeneration::getConstant(){
	string ir;
	ir = "@_printa = internal constant [5 x i8] c\"%d  \\00\", align 1\n";
	ir += "@_printc = internal constant [2 x i8] c\"%c\", align 1\n";
	ir += "@_printn = internal constant [2 x i8] c\"\\0A\\00\", align 1\n";
	ir += "declare i32 @printf(i8*, ...)\n";

	ir += "\n";
	return ir;
}

string
IRGeneration::getLinkFunc(){
	string ir;
	ir = "";
	int size = linkfiles.size();
	if (size != 0){
		for (int i = 0; i < size; i++){
			ir += getFile(linkfiles[i]);
			ir += "\n";
		}
	}
	ir += "\n";
	return ir;
}

string
IRGeneration::getWhile(ast* node){
	string ir;
	string ir1;
	string ir2;
	int curindex = index;
	ir = "  br label %" + getInt(index) + "\n\n";
	ir += "; <label>:" + getInt(index) + "\n";
	index++;
	int curwhileindex = whileindex;
	whileindex++;
	struct flow* fl = (struct flow*)node;
	ast* cmpnode = fl->cond;
	ast* maincode = fl->tl;
	ir1 = getCmp(cmpnode, curwhileindex);
	int pos;
	ir2 = "";
	char c;
	double d;
	int r = getCodeAss(maincode, pos, ir2, c, d);
	ir += ir1;
	ir += ir2;
	ir += "  br label %" + getInt(curindex) + "\n\n";
	ir += "whileend" + getInt(curwhileindex) + ":\n";
	return ir;
}

string
IRGeneration::getCmp(ast* node, int curwhileindex){
	string ir;
	string symbol;
	switch (node->nodetype){
	case '1':
		symbol = "sgt";
		break;
	case '2':
		symbol = "slt";
		break;
	case '3':
		symbol = "ne";
		break;
	case '4':
		symbol = "eq";
		break;
	case '5':
		symbol = "sge";
		break;
	case '6':
		symbol = "sle";
		break;
	default:
		symbol = "";
		break;
	}
	int pos0, pos1;
	char c1;
	char c2;
	double d1;
	double d2;
	string ir1 = "";
	int r1 = getCodeAss(node->l, pos0, ir1, c1, d1);
	string ir2 = "";
	int r2 = getCodeAss(node->r, pos1, ir2, c2, d2);
	ir = "";
	ir += ir1;
	ir += ir2;
	if (r1 == INT_MAX && r2 == INT_MAX)
		ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 %" + getInt(pos0) + ", %" + getInt(pos1) + "\n";
	else if (r1 != INT_MAX && r2 == INT_MAX)
		ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 " + getInt(r1) + ", %" + getInt(pos1) + "\n";
	else if (r1 == INT_MAX && r2 != INT_MAX)
		ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 %" + getInt(pos0) + ", " + getInt(r2) + "\n";
	else if (r1 != INT_MAX && r2 != INT_MAX)
		ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 " + getInt(r1) + ", " + getInt(r2) + "\n";
	ir += "  br i1 %" + getInt(index) + ", label %" + getInt(index + 1) + ", label %whileend" + getInt(curwhileindex) + "\n\n";
	ir += "; <label>:" + getInt(index + 1) + "\n";
	index += 2;
	return ir;
}

string
IRGeneration::getIf(ast* node){
	string ir;
	string ir1;
	string ir2;
	string ir3;
	struct flow* fl = (struct flow*)node;
	int curifindex = ifindex;
	int curelseindex = elseindex;
	ast* cmpnode = fl->cond;
	ast* ifnode = fl->tl;
	ast* elsenode = fl->el;
	bool elseexist;
	if (elsenode)
		elseexist = 1;
	else
		elseexist = 0;
	ifindex++;
	if (elseexist) elseindex++;
	ir1 = getIfCmp(cmpnode, elseexist, curifindex, curelseindex);
	int pos0;
	int pos1;
	ir2 = "";
	char c1;
	double d1;
	int r = getCodeAss(ifnode, pos0, ir2, c1, d1);
	if (elseexist){
		ir3 = "";
		ir3 += "else" + getInt(curelseindex) + ":\n";
		string ir4 = "";
		char c2;
		double d2;
		int rr = getCodeAss(elsenode, pos1, ir4, c2, d2);
		ir3 += ir4;
		ir3 += "  br label %ifend" + getInt(curifindex) + "\n\n";
	}
	else
		ir3 = "";
	ir = "";
	ir += ir1;
	ir += ir2;
	ir += "  br label %ifend" + getInt(curifindex) + "\n\n";
	ir += ir3;
	ir += "ifend" + getInt(curifindex) + ":\n";
	return ir;
}

string
IRGeneration::getIfCmp(ast* node, bool elseexist, int curifindex, int curelseindex){
	string ir;
	string symbol;
	switch (node->nodetype){
	case '1':
		symbol = "sgt";
		break;
	case '2':
		symbol = "slt";
		break;
	case '3':
		symbol = "ne";
		break;
	case '4':
		symbol = "eq";
		break;
	case '5':
		symbol = "sge";
		break;
	case '6':
		symbol = "sle";
		break;
	default:
		symbol = "";
		break;
	}
	int pos0, pos1;
	string ir1 = "";
	string ir2 = "";
	int r1, r2;
	char c1;
	char c2;
	double d1;
	double d2;
	r1 = getCodeAss(node->l, pos0, ir1, c1, d1);
	r2 = getCodeAss(node->r, pos1, ir2, c2, d2);
	if (!elseexist){
		ir = "";
		ir += ir1;
		ir += ir2; if (r1 == INT_MAX && r2 == INT_MAX)
			ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 %" + getInt(pos0) + ", %" + getInt(pos1) + "\n";
		else if (r1 != INT_MAX && r2 == INT_MAX)
			ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 " + getInt(r1) + ", %" + getInt(pos1) + "\n";
		else if (r1 == INT_MAX && r2 != INT_MAX)
			ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 %" + getInt(pos0) + ", " + getInt(r2) + "\n";
		else if (r1 != INT_MAX && r2 != INT_MAX)
			ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 " + getInt(r1) + ", " + getInt(r2) + "\n";
		ir += "  br i1 %" + getInt(index) + ", label %" + getInt(index + 1) + ", label %ifend" + getInt(curifindex) + "\n\n";
		ir += "; <label>:" + getInt(index + 1) + "\n";
		index += 2;
	}
	else{
		ir = "";
		ir += ir1;
		ir += ir2; if (r1 == INT_MAX && r2 == INT_MAX)
			ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 %" + getInt(pos0) + ", %" + getInt(pos1) + "\n";
		else if (r1 != INT_MAX && r2 == INT_MAX)
			ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 " + getInt(r1) + ", %" + getInt(pos1) + "\n";
		else if (r1 == INT_MAX && r2 != INT_MAX)
			ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 %" + getInt(pos0) + ", " + getInt(r2) + "\n";
		else if (r1 != INT_MAX && r2 != INT_MAX)
			ir += "  %" + getInt(index) + " = icmp " + symbol + " i32 " + getInt(r1) + ", " + getInt(r2) + "\n";
		ir += "  br i1 %" + getInt(index) + ", label %" + getInt(index + 1) + ", label %else" + getInt(curelseindex) + "\n\n";
		ir += "; <label>:" + getInt(index + 1) + "\n";
		index += 2;
	}
	return ir;
}

string
IRGeneration::getFunction(ast* node){
	string ir;
	string ir1;
	string ir2;
	infunc = true;
	struct fndec* fn = (struct fndec*)node;
	struct symlist* paralist = fn->s;
	string name = fn->name;
	func* f = sta->checkFunc(name);
	if (f->name != ""){
		if (f->returntype == 0){
			ir1 = "define void @" + name + "(";
		}
		else if (f->returntype == 1){
			ir1 = "define i32 @" + name + "(";
		}
		else if (f->returntype == 2){
			ir1 = "define i8 @" + name + "(";
		}
		else if (f->returntype == 3){
			//[TODO]
		}
		ir2 = "";
		while (paralist->cur != NULL){
			string paraname = paralist->cur->name;
			int paradatatype = paralist->cur->datatype;
			//string paratname = paralist->cur->tname;//for class
			int parasize = paralist->cur->size;
			if (parasize == -1){//not array
				if (paradatatype == 0){//char
					ir1 += "i8 %" + paraname;
					string modifiedname = paraname + ".var";
					ir2 += getAllocaChar(modifiedname);
					ir2 += getStoreChar(modifiedname, paraname);
				}
				if (paradatatype == 1){//int
					ir1 += "i32 %" + paraname;
					string modifiedname = paraname + ".var";
					ir2 += getAllocaInt(modifiedname);
					ir2 += getStoreInt(modifiedname, paraname);
				}
				if (paradatatype == 2){//double

				}
			}
			else if (parasize != -1){//array
				if (paradatatype == 0){//char
					ir1 += "i8* %" + paraname;
					string modifiedname = paraname + ".var";
					ir2 += getAllocaCharPointer(modifiedname);
					ir2 += getStoreCharPointer(modifiedname, paraname);
				}
				if (paradatatype == 1){//int
					ir1 += "i32* %" + paraname;
					string modifiedname = paraname + ".var";
					ir2 += getAllocaIntPointer(modifiedname);
					ir2 += getStoreIntPointer(modifiedname, paraname);
				}
				if (paradatatype == 2){//double

				}
			}
			paralist = paralist->next;
			if (paralist != NULL)
				ir1 += ", ";
			else
				break;
		}
		ir1 += ") {\n";
		string ir3;
		int pos;
		ast* funcnode = fn->tl;
		ir3 = "";
		char c;
		double d;
		int r = getCodeAss(funcnode, pos, ir3, c, d);
		string ir4;
		if (f->returntype == 0){
			ir4 = "  ret void\n";
		}
		else if (f->returntype == 1){
			if (retcons == 0)
				ir4 += "  ret i32 %" + getInt(pos) + "\n";
			else
				ir4 += "  ret i32 " + getInt(pos) + "\n";
			retcons = 1;
		}
		else if (f->returntype == 2){
			ir4 += "  ret i8 %" + getInt(pos) + "\n";
		}
		ir4 += "}\n\n";
		ir = ir1 + ir2 + ir3 + ir4;
		infunc = false;
		index = 1;
		funcindex++;
		return ir;
	}
	else{

		return ir;
	}
}

string
IRGeneration::getCall(ast* node, int& pos){
	string ir;
	string ir1;
	string ir2;
	string ir3;
	struct ufncall* ufn = (struct ufncall*)node;
	int line = node->lineno;
	string funcname = ufn->name;
	func* f = new func();
	f = sta->checkFunc(funcname);
	if (f->name != ""){
		int findex = f->index;
		ast* paranode = ufn->tl;
		ir3 = "";
		ir2 = "";
		getCallAss(paranode, ir3, ir2, findex);

		string rettype;
		if (f->returntype == 0)
			rettype = "void";
		else if (f->returntype == 1)
			rettype = "i32";
		else if (f->returntype == 2)
			rettype = "i8";
		if (f->returntype != 0){
			pos = index;
			ir1 = "  %" + getInt(index) + " = ";
			index++;
		}
		else {
			ir1 = "  ";
		}
		ir1 += "call " + rettype + " @" + funcname + "(";
		ir1 += ir3;

		if (paraindex != f->paranum){
			serr* err = new serr();
			err->errortype = PARANUMERR;
			err->errorpos = line;
			err->errorinfo = "Call parameter number mismatch with Function parameter number\n";
			se->addErrs(err);
		}
		int length = ir1.length();
		if (paranode != NULL)
			ir1 = ir1.substr(0, length - 2);
		ir1 += ")\n\n";

		ir = ir2 + ir1;
	}
	else{
		serr* err = new serr();
		err->errortype = FUNCUNDECLARE;
		err->errorpos = node->lineno;
		err->errorinfo = "Function '" + funcname + "' called without declaration.\n";
		se->addErrs(err);
	}
	paraindex = 0;
	return ir;
}

void
IRGeneration::getCallAss(ast* node, string& ir1, string& ir2, int findex){
	if (node == NULL)
		return;
	if (node->nodetype == 'L'){
		if (node->l != NULL)
			getCallAss(node->l, ir1, ir2, findex);
		if (node->r != NULL)
			getCallAss(node->r, ir1, ir2, findex);
	}
	else{
		int pos;
		int curarrayindex = arrayindex;
		char c = 0;
		double d;
		int line = node->lineno;
		int r = getCodeAss(node, pos, ir2, c, d);
		para* p = new para();
		p = sta->getFuncPara(findex, paraindex);
		if (r == INT_MAX){
			if (curarrayindex == arrayindex){
				if (p->type == "integer")
					ir1 += "i32 %" + getInt(pos) + ", ";
				else if (p->type == "char")
					ir1 += "i8 %" + getInt(pos) + ", ";
				else{
					serr* err = new serr();
					err->errortype = PARAMISMATCH;
					err->errorpos = line;
					err->errorinfo = "Call parameter mismatch with Function parameter\n";
					se->addErrs(err);
				}
			}
			else {
				if (p->type == "integer" && p->size != -1){
					ir1 += "i32* %" + getInt(pos) + ", ";
					arrayindex++;
				}
				else if (p->type == "char" && p->size != -1){
					ir1 += "i8* %" + getInt(pos) + ", ";
					arrayindex++;
				}
				else{
					serr* err = new serr();
					err->errortype = PARAMISMATCH;
					err->errorpos = line;
					err->errorinfo = "Call parameter mismatch with Function parameter\n";
					se->addErrs(err);
				}
			}
		}
		else {
			if (p->type == "integer")
				ir1 += "i32 " + getInt(r) + ", ";
			else if (p->type == "char"){
				ir1 += "i8 " + getInt((int)c) + ", ";
			}
			else{
				serr* err = new serr();
				err->errortype = PARAMISMATCH;
				err->errorpos = line;
				err->errorinfo = "Call parameter mismatch with Function parameter\n";
				se->addErrs(err);
			}
		}
		paraindex++;
	}
}

string
IRGeneration::Generate(){
	string ir;
	string ir1 = "";
	ir += getConstant();

	int pos;
	char c;
	double d;
	int r = getCodeAss(root, pos, ir1, c, d);

	if (se->checkErrs())
		ir = se->showErrs();
	else{
		ir += ir1;
		ir += "\n";
		ir += ";link\n";
		ir += getLinkFunc();
	}
	return ir;
}

IRGeneration::IRGeneration(ast* rt){
	index = 1;
	infunc = 0;
	arrayindex = 0;
	ifindex = 0;
	elseindex = 0;
	whileindex = 0;
	cmpindex = 0;
	funcindex = 0;
	paraindex = 0;
	retcons = 0;
	root = rt;
	linkfiles.push_back("linkfile.txt");
	se = new SemanticError();
	sta = new SymbolTableAnalyse(se);
	sta->Analyse(root);
}

void
IRGeneration::AddLinkFile(string filename){
	if (filename != "")
		linkfiles.push_back(filename);
	return;
}

/* Chen Jianan added these functions*/
string IRGeneration::getAllocaClass(string cname, string vname)
{
	string ir1 = " %" + vname + " = alloca %class." + cname + ", align 4\n";
	return ir1;
}

string IRGeneration::getClassMember(string membername)
{
	string ir;
	string ir1;
	string ir2;

	return "";
}

string IRGeneration::getMemberIndex(string membername)
{
	// 首先判断该成员变量的类型

	return "";
}

/* End*/