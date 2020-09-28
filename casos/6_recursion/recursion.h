/*
 * recursion.h
 *
 *  Created on: 10/09/2015
 *      Author: pperezm
 */

#ifndef RECURSION_H_
#define RECURSION_H_

#include "exception.h"
#include <iostream>

long sum_seq(int n) {
    long resultado = 0;
    long i= 1;

    while (i <= n){
        resultado = resultado + i;
        i++;
    }
	return resultado;
}

long sum_rec(int n) {
    if (n==1){
        return 1;
    }
	return sum_rec(n-1)+n;

	//2 + sum_rec(1) => 1

	//3 + sum_rec(2)
	//3 + 2 + sum_rec(1) => 6

	//4 + sum_rec(1) => 1
	//4 + sum_rec(1) => 1
	//4 + sum_rec(1) => 1
}

long fact_seq(int n) {
    long resultado = 1;
    for (int i = 1; i <= n; i++){
        resultado = resultado * i;
    }
	return resultado;
}

long fact_rec(int n) {
    if (n==0){
	return 1;
    }
    return n * fact_rec(n-1);
}

long fib_seq(int n) {
    long resultado = 1;
    long anterior_1 = resultado;
    long anterior_2 = resultado;

    for (int i = 3; i <= n; i++){
        resultado = anterior_1 + anterior_2;
        anterior_2 = anterior_1;
        anterior_1 = resultado;
    }
	return resultado;
}

long fib_rec(int n) {
    if (n == 1 || n == 2){
        return 1;
    }

	return fib_rec(n-1) + fib_rec(n-2);
	// fib_rec(5)
	// fib_rec(4) + fib_rec(3)
	// fib_rec(3) + fib_rec(2) +fib_rec(1)
	// fib_rec(2) + fib_rec(1) + 1 + 1 + 1
	//     1      +     1      + 1 + 1 + 1 = 5
}

//Greatest common divisor
long gcd_seq(long a, long b) {
  int i = 2;

  while(a%i !=0 && b%i!=0)
  {
    i++;
  }
  if (i > 10)
  {
    i = 1;
  }
  return i;
}

long gcd_rec(long a, long b) {
  if(b == 0)
  {
    return a;
  }
  else{
  return gcd_rec(b, a%b);
  }
}

bool find_seq(int arr[], int size, int val) {
	for (int i = 0; i < size; i++) {
		if (val == arr[i]) {
			return true;
		}
	}
	return false;
}

bool find_rec(int arr[], int low, int high, int val) {
	int mid;
	bool aux;

	if ( ((high - low) + 1) == 1) {
		return (val == arr[low]);
	} else {
		aux = false;
		mid = (high + low) / 2;
		aux = find_rec(arr, low, mid, val);
		if (!aux) {
			aux = find_rec(arr, mid + 1, high, val);
		}
		return aux;
	return false;
}
}

int max_seq(int arr[], int size) {
	int n = arr[0];

	for (int i = 1; i < size; i++) {
		if (n < arr[i]) {
			n = arr[i];
		}
	}
	return n;
}

int max_rec(int arr[], int low, int high) {
    if (low == high) {
        return arr[low];
	}

	if(arr[low] > arr[high]) {
        return max_rec(arr, low, high-1);
	}

    return max_rec(arr, low+1, high);
	}


//Regresar el número de la localidad del arrreglo de mayor valor
int unimodal_seq(int arr[], int size) {
  int highest = 0;
  int ocurrencia;
  int i = 0;
  while(i < size){
    if(arr[i] > highest){
      highest = arr[i];
      ocurrencia = i;
    }
    i++;
  }
	return ocurrencia;
}

//Auxiliar
int unimodal_rec(int arr[], int low, int high) {
	int mid;

	if (low <= high) {
		mid = (high + low) / 2;
		if (arr[mid - 1] < arr[mid] && arr[mid] > arr[mid + 1]) {
			return mid;
		} else if (arr[mid - 1] < arr[mid] && arr[mid] < arr[mid + 1]) {
			return unimodal_rec(arr, mid + 1, high);
		} else if (arr[mid - 1] > arr[mid] && arr[mid] > arr[mid + 1]) {
			return unimodal_rec(arr, low, mid - 1);
		}
	}
	return -1;
}

int unimodal_rec(int arr[], int size) {
	if (size < 3) {
		return -1;
	}

	return unimodal_rec(arr, 0, size - 1);
}

//Busqueda Binaria
int bs_seq(int arr[], int size, int val) {
    int low = 0;
    int high = size - 1;
    int mid = (high + low) / 2;

    while (low < high){
        mid = (high + low) / 2;
        if (val == arr [mid]){
            return mid;
        }
        if (val < arr[mid]){
            high = mid - 1;
        }
        if (val > arr[mid]) {
        low = mid +1;
        }
    }
	return low;
}

//Función auxiliar para hacer una busqueda binaria.
//Esta función es necesaria para bs_rec
int bs_aux(int arr[], int low, int high, int val) {
    if (low > high){
        return low;
    }

    int mid = (high + low) / 2;

    if (val == arr[mid]){
        return mid;
    }
    if (val < arr[mid]){
        return bs_aux(arr, low, mid -1, val);
    } else {
        return bs_aux(arr, mid +1, high, val);
    }
}

int bs_rec(int arr[], int size, int val) {
	return bs_aux(arr, 0, size-1, val);
}
#endif /* RECURSION_H_ */
