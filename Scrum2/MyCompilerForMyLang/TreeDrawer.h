/*
* Filename: TreeDrawer.h
* FileDes : In this file you can see the declaration of class TreeDrawer and its member functions.
*/

// TreeDrawer�÷���
// TreeDrawer treeDrawer;
// ast* root = ...
// treeDrawer.LoadTree(root);
// treeDrawer.Draw();
// ����
// TreeDrawer treeDrawer;
// ast* root = ...;
// treeDrawer.printTextTree(root);
// treeDrawer.printGraphicTree(root);

#ifndef __DRAW_TREE_H__
#define __DRAW_TREE_H__

#include "defination.h"			// In this file are the tree types
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>

class TreeDrawer
{
public:
	TreeDrawer();
	//TreeDrawer(ast* root);
	//TreeDrawer(TreeDrawer& t);
	~TreeDrawer();

private:
	ast* root;

private:
	void deleteTreeNode(ast* node);
	ast* copyTreeNode(ast* node);

private:
	void printTextTreeNodeHelper(ast* node);
	void printGraphicTreeNodeHelper(ast* node);

private:

public:


private:
	void printTextTreeNode(ast* node);
	void printGraphicTreeNode(ast* node);

public:
	bool printTextTree(ast* node);			// ��ӡ�����͵���
	bool printGraphicTree(ast* node);		// ��ӡͼ����
	bool printTextTree();
	bool printGraphicTree();

public:
	bool LoadTree(ast* root);	// Load an ast Tree from an existing tree
	ast* CopyTree(ast* root);	// Copy an ast Tree from root
	bool Draw();				// Draw the tree saved in the file
	bool Draw(ast* root);		// Draw the tree saved in root
};

#endif // __DRAW_TREE_H__