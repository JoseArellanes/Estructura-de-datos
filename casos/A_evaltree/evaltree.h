/*
 * evaltree.h
 *
 *  Created on: 20/10/2015
 *      Author: clase
 */

#ifndef EVALTREE_H_
#define EVALTREE_H_

#include <cctype>
#include <string>

#include <sstream>
#include <queue>
#include <stack>
#include "exception.h"

class EvalTree;

class TreeNode {
private:
	char value;
	TreeNode *left, *right;

	bool isOperator() const;
	bool isVariable() const;
	bool isOperand() const;

public:
	TreeNode(char);
	TreeNode(char, TreeNode*, TreeNode*);
	int depth() const;
	void inorder(std::stringstream&) const;
	void postorder(std::stringstream&) const;
	void preorder(std::stringstream&) const;
	void levelOrder(std::stringstream&) const;
	int howManyLeaves() const;
	char minValue() const;
	bool find(char) const;
	double eval(double x) const;
	TreeNode* derive() const;
	void removeChilds();
	TreeNode* copy() const;
	friend class EvalTree;
};

TreeNode::TreeNode(char c) {
    value = c;
    right = NULL;
    left = NULL;
}

TreeNode::TreeNode(char c, TreeNode* le, TreeNode* ri) {
    value = c;
    right = ri;
    left = le;
}

bool TreeNode::isOperator() const {
    if (value == '+' || value == '-' || value == '*' || value == '/'){
        return true;
    }

	return false;
}

bool TreeNode::isVariable() const {
    if (value == 'x'){
        return true;
    }
	return false;
}

bool TreeNode::isOperand() const {
    if (value >= '0' && value <= '9'){
        return true;
    }
	return false;
}

int TreeNode::depth() const {


//Encontrar la profundidad de la rama izquierda
    int left_depth = -1;
    if ( left != NULL){
        left_depth = left->depth();
    }

//Encontrar la profundidad de la rama derecha
    int right_depth = -1;
    if ( right != NULL){
        right_depth = right->depth();
    }
//Regresar la mayor de las dos profundidades
    int depth = left_depth;
    if (right_depth > left_depth){
        depth = right->depth ();
    }
	return depth + 1;
}

void TreeNode::inorder(std::stringstream &aux) const {
    //Recorrido in order rama izquierda
    if (left != NULL){
    left->inorder(aux);
    }
    //Imprimir el valor del nodo
	aux << value << " ";

	//Recorrido in order rama derecha
    if (right != NULL){
    right->inorder(aux);
    }
}

void TreeNode::postorder(std::stringstream &aux) const {
    //Recorrido in order rama izquierda
    if (left != NULL){
    left->postorder(aux);
    }

	//Recorrido in order rama derecha
    if (right != NULL){
    right->postorder(aux);
    }

    //Imprimir el valor del nodo
	aux << value << " ";
}

void TreeNode::preorder(std::stringstream &aux) const {

    //Imprimir el valor del nodo
	aux << value << " ";

    //Recorrido in order rama izquierda
    if (left != NULL){
    left->preorder(aux);
    }

	//Recorrido in order rama derecha
    if (right != NULL){
    right->preorder(aux);
    }
}

int TreeNode::howManyLeaves() const {
    //Declarar variables que contendran el número de hojas por subárbol y otra variable
    //que tendrá la suma de las hojas del subárbol derecho y el subárbol izquierdo
    int left_contador = 0;
    int right_contador = 0;
    int contador_total = 0;

    //Mientras el subárbol izquierdo no sea NULL contará cuantas hojas tiene
    if (left != NULL){
        left_contador = left->howManyLeaves();
    }

    //Mientras el subárbol derecho no sea NULL contará cuantas hojas tiene
    if (right != NULL){
        right_contador = right->howManyLeaves();
    }

    //Guradar la suma de lso subárboles en la variable contador_total
    contador_total = right_contador + left_contador;

    //Si el contador_total es igual a 0, entocnes regresar como valor 1
    if (contador_total == 0){
        return 1;
    }

    //regresar contador_total
	return contador_total;
}

char TreeNode::minValue() const {
    //Declarar las varibles para los valores del subárbol izquierdo, derecho y del mínimo valor
    char valor_izqdo = '9';
    char valor_dcho = '9';
    char min_valor = '9';

    //Si el valor es un operando entonces min_valor seria igual al valor del operando
    if (isOperand()){
        min_valor = value;

    //Sin,  si el valor es un operador
    } else {

        //Si left no es Null entonces valor_izqdo guardará el mínimo valor
        if (left != NULL){
            valor_izqdo = left->minValue();
        }

        //Si right no es Null entonces valor_izqdo guardará el mínimo valor
        if (right != NULL){
            valor_dcho = right->minValue();
        }

        //Si el valor_izqdo es menor a valor_dcho guardarlo en min_valor
        if (valor_izqdo < valor_dcho){
            min_valor = valor_izqdo;


        //Sino guardar valor_dcho en min_valor
        } else {
        valor_dcho = min_valor;
        }
    }
	return min_valor;
}

bool TreeNode::find(char val) const {
    //Declarar una variable booleana
    bool encontrado = false;

    //Si el valor a buscar es igual a val entonces regresar true
    if(value == val){
        return true;
	}
    //Si el subarbol izquierdo no es 0
    if (left != 0){

        //Si el subárbol izquierdo contiene el valor regresar true
        if (encontrado || left->find(val)){
            encontrado = true;
        } else {
        encontrado = false;
        }
    }
    //Si el subarbol derecho no es 0
    if (right != 0){

        //Si el subárbol derecho contiene el valor regresar true
        if (encontrado || right->find(val)){
            encontrado = true;
        } else {
        encontrado = false;
        }
    }
    return encontrado;
}

double TreeNode::eval(double x) const {
	return 0;
}

void TreeNode::removeChilds() {
}

TreeNode* TreeNode::derive() const {
	return 0;
}

TreeNode* TreeNode::copy() const {
	return 0;
}

class EvalTree {
private:
	TreeNode *root;

	std::queue<std::string> tokenize(std::string);

public:
	EvalTree();
	EvalTree(std::string) throw (IllegalAction);
	~EvalTree();
	bool empty() const;
	int height() const;
	std::string inorder() const;
	std::string postorder() const;
	std::string preorder() const;
	std::string levelOrder() const;
	int howManyLeaves() const;
	char minValue() const throw (IllegalAction);
	bool find(char) const;
	double eval(double) const throw (IllegalAction) ;
	EvalTree* derive() const;
	void removeAll();
	bool isFull() const;
	int internalNodes() const;
	bool isPerfect() const;
	bool isDegenerate() const;
};

EvalTree::EvalTree() {
}

std::queue<std::string> EvalTree::tokenize(std::string str) {
	int i = 0;
	int length = str.size();
	std::string aux;
	std::queue<std::string> result;

	while (i < length) {
		if (isdigit(str[i])) {
			aux.clear();
			do {
				aux += str[i];
				i++;
			} while(isdigit(str[i]));
			result.push(aux);
		} else if (isspace(str[i])) {
			i++;
		} else {
			aux.clear();
			aux += str[i];
			result.push(aux);
			i++;
		}
	}
	return result;
}

EvalTree::EvalTree(std::string str) throw (IllegalAction) {
	root = 0;
	std::stack<TreeNode*> s;
	std::queue<std::string> tokens = tokenize(str);
	std::string aux;
	TreeNode *left, *right, *newNode;

	while (!tokens.empty()) {
		aux = tokens.front(); tokens.pop();
		if (aux == "+" || aux == "-" || aux == "*" || aux == "/") {
			if (s.empty()) {
				throw IllegalAction();
			}
			left = s.top(); s.pop();
			if (s.empty()) {
				throw IllegalAction();
			}
			right = s.top(); s.pop();
			newNode = new TreeNode(aux[0], left, right);
			s.push(newNode);
		} else if (aux[0] == 'x' || isdigit(aux[0])) {
			newNode = new TreeNode(aux[0]);
			s.push(newNode);
		}
	}
	newNode = s.top(); s.pop();
	if (!s.empty()) {
		throw IllegalAction();
	}
	root = newNode;
}

EvalTree::~EvalTree() {
}

bool EvalTree::empty() const {
    if (root == NULL){
        return true;
    }
    return false;
}

int EvalTree::height() const {
    if (empty()){
        return 0;
    }
	return root->depth() + 1;
}

std::string EvalTree::inorder() const {
	std::stringstream aux;

	root->inorder(aux);

	return aux.str();
}

std::string EvalTree::preorder() const {
	std::stringstream aux;

	root->preorder(aux);

	return aux.str();
}

std::string EvalTree::postorder() const {
	std::stringstream aux;

	root->postorder(aux);

	return aux.str();
}

std::string EvalTree::levelOrder() const {
	std::stringstream aux;

	//Necesitamos una fila para hacer un recorrido por niveles
	std::queue<TreeNode*> q;

	//Metemos a la fila la raíz
	TreeNode * node = root;
	q.push(node);

	//Mientras la fila no esté vacía
	while (!q.empty()){
        //Imprimir el frente de la fila
        node = q.front();
        aux<<node->value << " ";
        //Sacar el elemento de la fila
        q.pop();
        //Si tiene hijo izquierdo, meter el hijo izquierdo a la fila
        if (node->left != NULL){
            q.push(node->left);
        }
        //Si tiene hijo derecho, mete el hijo derechoa a la fila
        if (node->right != NULL){
            q.push(node->right);
        }
	}
	return aux.str();
}

int EvalTree::howManyLeaves() const {
    //Si está vacío se regresa el valor de 0
    if (empty()){
	return 0;
    }

    //regresar la cantidad de hojas
    return root->howManyLeaves();
}

char EvalTree::minValue() const throw (IllegalAction) {
    //Si está vacio regresdar la excepción IllegalAction
    if (empty()){
        throw IllegalAction();
    }
    //Regresar el mínimo valor
	return root->minValue();
}

bool EvalTree::find(char c) const {
	return root->find(c);
}

double EvalTree::eval(double x) const throw (IllegalAction) {
	return 0.0;
}

EvalTree* EvalTree::derive() const {
	return 0;
}

void EvalTree::removeAll() {
}
#endif /* EVALTREE_H_ */
