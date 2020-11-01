/*
 * tree.h
 *
 *  Created on: 20/10/2015
 *      Author: clase
 */

#ifndef TREE_H_
#define TREE_H_

#include <string>
#include <sstream>
#include "exception.h"

class SimpleTree;

class TreeNode {
private:
	int value;
	TreeNode *left, *right;

	int depth() const;
	void removeChilds();
	bool isLeaf() const;

public:
	TreeNode(int);
	TreeNode(int, TreeNode*, TreeNode*);

	bool isFull() const;
	int internalNodes() const;
	bool isPerfect() const;
	bool isDegenerate() const;

	friend class SimpleTree;
};

TreeNode::TreeNode(int val) : value(val), left(0), right(0) {}

TreeNode::TreeNode(int val, TreeNode* le, TreeNode* ri)
	: value(val), left(le), right(ri) {}

void TreeNode::removeChilds() {
	if (left != 0) {
		left->removeChilds();
		delete left;
		left = 0;
	}
	if (right != 0) {
		right->removeChilds();
		delete right;
		right = 0;
	}
}

/**
 * Devuelve true si este árbol binario está lleno, o false en caso
 * contrario.
 * Un árbol binario lleno es aquel en el que cada nodo tiene cero o dos
 * hijos. Como caso especial, un árbol vacío se considera lleno.
 * @return true Si el árbol está lleno
 * @return false Si el árbol no está lleno
 **/
bool TreeNode::isFull() const {
  //Si no tiene hijos, está lleno
  if (left == NULL && right == NULL) {
    return true;
  }

  //Si tiene hijo izquierdo y está lleno y tiene hijo derecho y está lleno, entonces está lleno
  if(left != NULL && right != NULL
     && left->isFull() && right->isFull()) {
    return true;
  }

  //De lo contrario, devolver falso
	return false;
}

/**
 * Devuelve el número de nodos internos con los que cuenta este árbol
 * binario.
 * Un nodo se considera interno si cuenta con al menos un hijo.
 * Por lo tanto, un nodo hoja no es un nodo interno.
 * @return La cantidad de nodos internos
 */
int TreeNode::internalNodes() const {
  //Si es hoja regresa 0
  if (isLeaf()) {
    return 0;
  }

  int result = 1;
  //Si tiene un hijo, regresa los nodos internos del hijo
  if (left != NULL) {
    result = result + left->internalNodes();
  }

  if (right != NULL) {
    result = result + right->internalNodes();
  }

	return result;
}

int TreeNode::depth() const {
	int le = -1;
	int ri = -1;
	int de = -1;

	if (left != NULL) {
		le = left->depth();
	}
	if (right != NULL) {
		ri = right->depth();
	}

  if (le > ri) {
    return le + 1;
  } else {
    return ri + 1;
  }

}

bool TreeNode::isPerfect() const {
    //Si left es igual a 0 y right es igual a 0, regresar true
    if (left == 0 && right == 0){
        return true;
    }

    //Declarar variables ri y le
    int le;
    int ri;

    //Si left y right son diferentes a 0
    if (left != 0 && right != 0){

        //le igual a la profundidad de left
        le = left->depth();

        //ri igual a la profundidad de right
        ri = right->depth();

        return (le == ri);
    }
	return false;
}

bool TreeNode::isLeaf() const {
	return (left == 0 && right == 0);
}


bool TreeNode::isDegenerate() const {
    //Si es una hoja, regresar false
    if (isLeaf()){
        return false;
    }

    //Si left y right son diferentes de 0, regresar false
    if ( left != 0 && right != 0){
        return false;
    }

    //
    	if (left != 0) {
		if (left->isLeaf()) {
			return true;
		} else {
			return left->isDegenerate();
		}
	}

	if (right != 0) {
		if (right->isLeaf()) {
			return true;
		} else {
			return right->isDegenerate();
		}
	}

	return true;

}

class SimpleTree {
private:
	TreeNode *root;
	void caseOne();
	void caseTwo();
	void caseThree();
	void caseFour();

public:
	SimpleTree(int);
	~SimpleTree();
	bool empty() const;
	bool isFull() const;
	int internalNodes() const;
	bool isPerfect() const;
	bool isDegenerate() const;
};

SimpleTree::SimpleTree(int option) {
	switch (option) {
		case  1: caseOne(); break;
		case  2: caseTwo(); break;
		case  3: caseThree(); break;
		default: caseFour(); break;
	}
}

void SimpleTree::caseOne() {
	TreeNode *a, *b, *c, *d;

	a = new TreeNode(4);
	b = new TreeNode(5);
	c = new TreeNode(2, a, b);

	a = new TreeNode(6);
	b = new TreeNode(7);
	d = new TreeNode(3, a, b);

	root = new TreeNode(1, c, d);
}

void SimpleTree::caseTwo() {
	TreeNode *a, *b, *c, *d, *e;

	a = new TreeNode(8);
	b = new TreeNode(9);
	c = new TreeNode(4, a, b);

	a = new TreeNode(10);
	b = new TreeNode(11);
	d = new TreeNode(5, a, b);

	e = new TreeNode(2, c, d);

	a = new TreeNode(6);
	b = new TreeNode(7);
	c = new TreeNode(3, a, b);

	root = new TreeNode(1, e, c);
}

void SimpleTree::caseThree() {
	TreeNode *a, *b, *c;

	a = new TreeNode(6);

	b = new TreeNode(5, a, 0);

	c = new TreeNode(4, 0, b);

	a = new TreeNode(3, c, 0);

	b = new TreeNode(2, 0, a);

	root = new TreeNode(1, b, 0);
}

void SimpleTree::caseFour() {
	root = new TreeNode(1);
}

SimpleTree::~SimpleTree() {
	if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
}

bool SimpleTree::empty() const {
	return (root == 0);
}

bool SimpleTree::isFull() const {
	if (!empty()) {
		return root->isFull();
	}
	return false;
}

int SimpleTree::internalNodes() const {
	if (!empty()) {
		return root->internalNodes();
	}
	return 0;
}

bool SimpleTree::isPerfect() const {
	if (!empty()) {
		return root->isPerfect();
	}
	return false;
}

bool SimpleTree::isDegenerate() const {
	if (!empty()) {
		return root->isDegenerate();
	}
	return false;
}

#endif /* EVALTREE_H_ */
