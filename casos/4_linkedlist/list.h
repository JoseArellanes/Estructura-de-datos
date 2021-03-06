/*
 * linkedlist.h
 *
 *  Created on: 05/08/2015
 *      Author: pperezm
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <string>
#include <sstream>
#include "exception.h"

template <class T> class List;
template <class T> class ListIterator;

template <class T>
class Link {
private:
	Link(T);
	Link(T, Link<T>*);
	Link(const Link<T>&);

	T	    value;
	Link<T> *next;

	friend class List<T>;
	friend class ListIterator<T>;
};

template <class T>
Link<T>::Link(T val) {
  value = val;
  next = NULL;
}

template <class T>
Link<T>::Link(T val, Link* nxt) {
  value = val;
  next = nxt;
} 

template <class T>
Link<T>::Link(const Link<T> &source) {
  value = source.val;
  next = source.nxt;
}

template <class T>
class List {
public:
	List();
	List(const List<T>&) throw (OutOfMemory);
	~List();

	void addFirst(T) throw (OutOfMemory);
	void add(T) throw (OutOfMemory);
	T    getFirst() const throw (NoSuchElement);
	T    removeFirst() throw (NoSuchElement);
	int  length() const;
	T    get(int) const throw (IndexOutOfBounds, NoSuchElement);
	bool contains(T) const;
	bool empty() const;
	void clear();
	std::string toString() const;
	void operator= (const List&) throw (OutOfMemory);

	void addBefore(ListIterator<T>&, T) throw (IllegalAction, OutOfMemory);
	void addAfter(ListIterator<T>&, T) throw (IllegalAction, OutOfMemory);
	T    removeCurrent(ListIterator<T>&) throw (IllegalAction);

	bool set(int, T) throw (IndexOutOfBounds);
	int  indexOf(T) const;
	int  lastIndexOf(T) const;
	T    remove(int) throw (IndexOutOfBounds);
	bool removeFirstOcurrence(T);
	bool removeLastOcurrence(T);

private:
	Link<T> *head;
	int 	size;

	friend class ListIterator<T>;
};

template <class T>
List<T>::List(){
  head = NULL;
  size = 0;
}

template <class T>
List<T>::~List() {
  clear();
  head = NULL;
  size = 0;
}
//Regresa verdadero si la lista está vacia, de lo contrario 
//regresa falso
//@return true: si la lista está vacía
//@return false: si la lista no está vacía
template <class T>
bool List<T>::empty() const {
  if (head == NULL){
    return true;
  }
	return false;
}

template <class T>
int List<T>::length() const {

  int i = 0;

  if (head == NULL){
    return i;
  }

  Link<T> * apuntador = head;
  i++;

  while(apuntador->next != NULL){
    apuntador = apuntador->next;
    i++;
  }
  return i;

  //alternativa
	return size;
}

template <class T>
bool List<T>::contains(T val) const {
  //Apuntador que apunte a head
  Link<T> * apuntador = head;

  //Mientras el apuntador sea diferente a 0
  while (apuntador != 0){
    //Si el valor del apuntador es igual a val regresar un true
    if (apuntador->value == val){
      return true;
    }
    apuntador = apuntador->next;
  }
	return false;
}

template <class T>
T List<T>::getFirst() const throw (NoSuchElement) {
//Si la lista está vacia regresar que no existe tal elemento
if (empty()){
  throw NoSuchElement();
}
//Regresar el valor del head
	return head->value;
}

template <class T>
void List<T>::addFirst(T val) throw (OutOfMemory) {
  //Crear nuevo nodo con el valor val
  Link<T> * nuevo = new Link<T>(val);

  if (nuevo == NULL){
    throw OutOfMemory();
  }
  //Apuntar el siguiente del nuevo nodo a head
  nuevo->next = head;

  //head apuntar al nuevo nodo
  head = nuevo;

  //Incrementar tamaño
  size++;
}

template <class T>
void List<T>::add(T val) throw (OutOfMemory) {
//Si la lista está vacía agregar al principio
   if (empty()){
    addFirst(val);
    return;
  }
//Crear un nuevo nodo
  Link<T> * nuevo = new Link<T>(val);

  if(nuevo == NULL){
    throw OutOfMemory();
  }

//Crear un apuntador actual 
Link<T> * actual = head;

//Recorrer la lista hasta el final
while (actual->next != NULL){
  actual = actual->next;
}

//Apuntar actual al nuevo nodo
actual->next = nuevo;

//Aumentar el tamaño
size++;
}

template <class T>
T List<T>::removeFirst() throw (NoSuchElement) {
  //Apuntador que apunte a head
  Link<T> * victima= head;
  T val;

  //Si la lista está vacía agregar al principio
if (empty()){
  throw NoSuchElement();
}  
  head = victima->next;
  val = victima->value;
  //Eliminar el apuntador y reducir el tamño del size
  delete victima;
  size--;
	
  return val;
}

template <class T>
T List<T>::get(int index) const throw (IndexOutOfBounds, NoSuchElement) {
  //Apuntador que apunte a head
  Link<T> * apuntador = head;

//Si el index es menor a 0 o mayor a size regresar que esta fuera de los limites
 if (index < 0 || index >= size) {
  throw IndexOutOfBounds();
}
//inicializar un entero para lo posicion 
int posicion = 0;
//Mientras la posicion sea diferente del index el apuntador guardará ala posicion del siguiente elemento
  while (posicion != index){
    apuntador = apuntador->next;
    posicion++;
  }

  //Regresar el valor del apuntador
	return apuntador->value;
}

template <class T>
void List<T>::clear() {
//Apuntador y victima que apunte a head
Link<T> * apuntador = head;
Link<T> * victima = head;
//Si el apuntador es diferente a NULL entonces leer la lista y eliminarla
while(apuntador != NULL){
  victima = apuntador;
  apuntador = apuntador->next;
  delete victima;
}
//Limpiar la lista
head = NULL;
size = 0;
}

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
List<T>::List(const List<T> &source) throw (OutOfMemory) {
 
  head = NULL;
  size = 0;

 //Si la lista está vacía
  if (source.empty()){
    return;
  }
  
  //Recorrer la lista sourse
  Link<T> * actual = source.head;
  
  //Por cada nodo que se visita, crear un nuevo nodo al final
  while (actual != NULL){
    add(actual->value);
    actual = actual->next;
  }
}

template <class T>
void List<T>::operator=(const List<T> &source) throw (OutOfMemory) {
//Se crean dos apuntadores que serán temporales
	Link<T> *p, *q;

  //Se limpia la lista para que no contenga ningun tipo de elementos en ella ni nada que interfiera
  clear();
  
  //Si la lista está vacía se declaran size y head como 0, mostrando que no hay nada en ella
	if (source.empty()) {
		size = 0;
		head = NULL;
  }

   //Si la lista no está vacia entonces el pauntador p apuntara al head del source, b1
	 else {
		p = source.head;
    
    //El head de la lista b2 se volverá en un nuevo nodo que contendrá el valor del apuntador p, el cual al head de b1
		head = new Link<T>(p->value);

    //Si el head es igual a 0 entonces arrojará el comentario OutOfMemory
		if (head == NULL) {
			throw OutOfMemory();
		}

    //El apuntador q ahora guardará el valor del head de b2
		q = head;

    //El apuntador p ahora contiene el siguiente valor de la lista
		p = p->next;

    //Mientas p sea diferente de 0 recorrera la lista del source
		while(p != 0) {

      //El siguiente elemento del apuntador q guardará el nuevo nodo que contiene el valor del apuntador p
			q->next = new Link<T>(p->value);

      //Si el apuntador q es igual a 0 se arrojará el comentario de OutOfMemory
			if (q->next == 0) {
				throw OutOfMemory();
			}
      
      //El apuntador p apunta ahora a la siguiente posicion de la lista
			p = p->next;
			
      //El apuntador q apunta ahora a la siguiente posicion de la lista      
      q = q->next;
		}

    //Se iguala el tamaño de la listas, pues deben de ser iguales
		size = source.size;
	}
}

template <class T>
void List<T>::addBefore(ListIterator<T> &itr, T val) throw (IllegalAction, OutOfMemory) {
}

template <class T>
void List<T>::addAfter(ListIterator<T> &itr, T val) throw (IllegalAction, OutOfMemory) {
}

template <class T>
T List<T>::removeCurrent(ListIterator<T> &itr) throw (IllegalAction) {
	return 0;
}

template <class T>
bool List<T>::set(int index, T val) throw (IndexOutOfBounds) {
	return false;
}

template <class T>
int List<T>::indexOf(T val) const {
	return -1;
}

template <class T>
int List<T>::lastIndexOf(T val) const {
	return -1;
}

template <class T>
T List<T>::remove(int index) throw (IndexOutOfBounds) {
	return 0;
}

template <class T>
bool List<T>::removeFirstOcurrence(T val) {
	return false;
}

template <class T>
bool List<T>::removeLastOcurrence(T val) {
	return false;
}

template <class T>
class ListIterator {
public:
	ListIterator(List<T>*);
	ListIterator(const ListIterator<T>&);

	bool begin();
	bool end();
	T&   operator() () throw (NoSuchElement);
	bool operator++ ();
	void operator= (T) throw (NoSuchElement);

private:
	Link<T> *current;
	Link<T> *previous;
	List<T> *theList;

	friend class List<T>;
};

template <class T>
ListIterator<T>::ListIterator(List<T> *aList) : theList(aList) {
	begin();
}

template <class T>
ListIterator<T>::ListIterator(const ListIterator<T> &source) : theList(source.theList) {
	begin();
}

template <class T>
bool ListIterator<T>::begin() {
	previous = 0;
	current = theList->head;
	return (current != 0);
}

template <class T>
T& ListIterator<T>::operator() () throw (NoSuchElement) {
	if (current == 0) {
		throw NoSuchElement();
	}
	return current->value;
}

template <class T>
bool ListIterator<T>::end() {
	if (current == 0) {
		if (previous != 0) {
			current = previous->next;
		}
	}
	return (current == 0);
}

template <class T>
bool ListIterator<T>::operator++ () {
	if (current == 0) {
		if (previous == 0) {
			current = theList->head;
		} else {
			current = previous->next;
		}
	} else {
		previous = current;
		current = current->next;
	}
	return (current != 0);
}

template <class T>
void ListIterator<T>::operator= (T val) throw (NoSuchElement) {
	if (current == 0) {
		throw NoSuchElement();
	}
	current->value = val;
}

#endif /* LINKEDLIST_H_ */
