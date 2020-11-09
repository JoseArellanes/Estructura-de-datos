/*
 * hash.h
 *
 *  Created on: 20/10/2015
 *      Author: clase
 */

#ifndef HASH_H_
#define HASH_H_

#include <string>
#include <sstream>
#include "exception.h"

template <class Key, class Value>
class HashTable {
private:
  //Apuntador hacia la funci�n de hash
	unsigned int (*func) (const Key);
  //Tama�o de la tabla de hash
	unsigned int size;
  //N�mero de elementos que contiene la tabla de hash
	unsigned int count;

  //Vector de llaves de la tabla de hash
	Key *keys;
  //Valor inicial o por defecto de las llaves de la tabla
	Key initialValue;
  //Vector de valores de la tabla de hash
	Value *values;

  //Funci�n que devuelve el �ndice de una llave en la tabla de hash
	long indexOf(const Key) const;

public:
	HashTable(unsigned int, Key, unsigned int (*f) (const Key)) throw (OutOfMemory);
	~HashTable();
	bool full() const;
	bool put(Key, Value) throw (Overflow);
	bool contains(const Key) const;
	Value get(const Key) throw (NoSuchElement);
	void clear();
	std::string toString() const;
};

/**
 * Constructor de la tabla de hash.
 * Inicializa la tabla con el valor indicado
 * @param unsigned int sze: El valor que tendr� el tama�o de la tabla de hash
 * @param Key init: El valor por defecto de las llaves de la tabla
 * @param unsignedint (*f): La funci�n de hash a utilizar en la tabla
 **/
template <class Key, class Value>
HashTable<Key, Value>::HashTable(unsigned int sze, Key init, unsigned int (*f) (const Key)) throw (OutOfMemory) {
	//Inicializar las variables con los par�metros
  size = sze;
  initialValue = init;

  //Asignar la funci�n de hash al apuntador func
  func = f;

  //Asegurarse que hay memoria disponible, de lo contrario mandar la excepci�n de que no hay memoria
  values = new Value[size];
  if (values == NULL) {
    throw OutOfMemory();
  }

  keys = new Key[size];
  if (keys == NULL) {
    throw OutOfMemory();
  }

  //Asignarle a las llaves su valor inicial
  for (int i = 0; i < size; i++) {
    keys[i] = init;
  }

  //Asignarle a los valores el valor inicial de 0
  count = 0;

}

/**
 * Elimina la tabla de hash
 **/
template <class Key, class Value>
HashTable<Key, Value>::~HashTable() {
    //Libera la memoria de los arreglos asignados
    delete [] keys;
	keys = 0;

    //Pone en nulo las variables miembro
	delete [] values;
	values = 0;
	size = 0;
	func = 0;
	count = 0;
}

/**
 * Pregunta su la tabla de hash est� llena
 * @return true: Si la tabla est� llena
 * @return false: Si la tabla no est� llena
 **/
template <class Key, class Value>
bool HashTable<Key, Value>::full() const {
  if (count == size) {
    return true;
  }
	return false;
}

/**
 * Obtiene el �ndice de una llave en la tabla de hash
 * @param const Key k: El valor de la llave del que se quiere obtener el �ndice
 * @return: El �ndice de la llave en la tabla de hash
 **/
template <class Key, class Value>
long HashTable<Key, Value>::indexOf(const Key k) const {
  //Aplica la funci�n de hash y verifica que la llave sea igual a la llave que se est� buscando, si es as� devuelve el �ndice
  int inicio_busqueda = func(k) % size;
  int i = inicio_busqueda;

  //De lo contrario, aplica el sondeo linear, si encuentra el valor devuelve el �ndice
  do {
    if (keys[i] == k) {
      return i;
    }
    i = (i + 1) % size;
  } while (i != inicio_busqueda);

  //Si no encuentra el valor despu�s de recorrer toda la tabla, devuelve -1 para indicar que no se encontr�
	return -1;
}

/**
 * Inserta o actualiza un valor en la tabla de hash
 * @param Key k: La llave que se va a insertar o actualizar
 * @param Value v: El nuevo valor
 * @return true: Si se pudo insertar o actualizar la llave
 * @return false: Si la tabla est� llena y no se pudo insertar el valor
 **/
template <class Key, class Value>
bool HashTable<Key, Value>::put(Key k, Value v) throw (Overflow) {

  //Obtener la posici�n en la tabla de la llave k
  int posicion_tabla = indexOf(k);

  //Si la llave ya tiene un �ndice, actualizar su valor y devolver verdadero
  if (posicion_tabla != -1) {
    values[posicion_tabla] = v;
    return true;
  }

  //Si la tabla est� llena, lanzar la excepci�n
  if (full()) {
    throw Overflow();
  }

  //Obtengo el valor de hash
  int valor_hash = func(k) % size;
  int i = valor_hash;

  //Inserta la llave y el valor en la posici�n de la tabla del valor de hash, pero si est� ocupado, busca un lugar por sondeo linear
  do {
    if (keys[i] == initialValue) {
      keys[i] = k;
      values[i] = v;
      count++;
      return true;
    }
    i = (i + 1) % size;
  } while (i != valor_hash);

	return false;
}

/**
 * Devuelve verdadero si la tabla contiene la llave k
 * @param const Key k: El valor de la llave a buscar
 * @return true: Si se encuentra la lleve
 * @return false: Si no se encuentra la llave
 **/
template <class Key, class Value>
bool HashTable<Key, Value>::contains(const Key k) const {
    //Regresa falso si el valor el �ndice de la llave es -1
    int posicion_tabla = indexOf(k);

      if (posicion_tabla != -1){
        return true;
      }
        return false;
}

/**
 * Obtiene el valor de una llave
 * @param const Key k: El valor de la llave a buscar
 * @return Value: El valor de la llave
 **/
template <class Key, class Value>
Value HashTable<Key, Value>::get(const Key k) throw (NoSuchElement) {
	Value v;
    //Obtener el �ndice de la llave
    int posicion_tabla = indexOf(k);
    //Si el valor es -1, lanzar la excepci�n
    if (posicion_tabla != -1){
        //Devolver el valor de la posici�n del �ndice de la llave en el vector de valores
        return values[posicion_tabla];
    }
    throw NoSuchElement();
}

/**
 * Reinicia al valor inicial las llaves de la tabla de hash
 **/
template <class Key, class Value>
void HashTable<Key, Value>::clear() {
	//Recorre el vector de llaves y les asigna el valor inicial
    for (unsigned int i = 0; i < size; i++) {
		keys[i] = initialValue;
	}
    //Asigna 0 al contador de elementos
    count = 0;
}

template <class Key, class Value>
std::string HashTable<Key, Value>::toString() const {
	std::stringstream aux;

	for (unsigned int i = 0; i < size; i++) {
		aux << "[ " << i << ", " << keys[i] << ", " << values[i] << "]\n";
	}
	return aux.str();
}
#endif /* HASH_H_ */



