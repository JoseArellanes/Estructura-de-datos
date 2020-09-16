 /*
 * rational.h
 *
 *  Created on: 05/08/2015
 *      Author: pperezm
 */

#ifndef RATIONAL_H_
#define RATIONAL_H_

#include "exception.h"
#include <string>
#include <sstream>

using namespace std;

class Rational {
private:
	int numerator;
	int denominator;

	void normalize();

public:
	Rational();
	Rational(int);
	Rational(int, int);
	Rational(const Rational&);

	int getNumerator() const;
	int getDenominator() const;
	std::string toString() const;

	void operator=   (const Rational&);
	void operator+=  (const Rational&);

	operator double () const;
};

Rational::Rational() {
    numerator = 0;
    denominator = 1;
}

Rational::Rational(int num){
    numerator = num;
    denominator = 1;
}


Rational::Rational(int num, int dem){
  if(dem<0)
  {
    denominator=dem*-1;
    numerator=num*-1;
    normalize();
     if (dem == 0){
        numerator = 0;
        denominator = 1;
    }
  }
  else
  {
    if (dem == 0){
        numerator = 0;
        denominator = 1;
        throw RangeError();      
    }else{
        numerator = num;
        denominator = dem;
        normalize();
    }
  }
}





int Rational::getNumerator() const {
	return numerator;
}

int Rational::getDenominator() const {
	return denominator;
}

std::string Rational::toString() const {
	std::stringstream aux;

	aux << numerator << "/" << denominator;
	return aux.str();
}

Rational::operator double () const {
double Fracc;
Fracc = (double) numerator / (double) denominator;
	return Fracc ;
}

//Greatest common divisor
int gcd(int a, int b) {
	int aux;

	while (b != 0) {
		aux = b;
		b = a % b;
		a = aux;
	}
	return a;
}

void Rational::normalize() {
  //Para numeros pares
  while(numerator%2==0 && denominator%2==0)
  {
    numerator=numerator/2;
    denominator=denominator/2;
  }
  //para números impares 
  while(numerator%3==0 && denominator%3==0)
  {
    numerator=numerator/3;
    denominator=denominator/3;
  }

}

void Rational::operator= (const Rational &right) {
  numerator=right.numerator;
  denominator=right.denominator;
}

void Rational::operator+= (const Rational &right) {
  numerator=(denominator*right.numerator)+(numerator*right.denominator);
  denominator= denominator*right.denominator;
normalize();
}

Rational operator+ (const Rational &left, const Rational &right) {
int num1, dem1;

  num1 = (left.getDenominator() * right.getNumerator())+(left.getNumerator() * right.getDenominator());
  dem1 = left.getDenominator() * right.getDenominator();
	return Rational(num1, dem1);
}

Rational operator- (const Rational &left, const Rational &right) {
int num1, dem1;

  num1 = -(left.getDenominator() * right.getNumerator())+(left.getNumerator() * right.getDenominator());
  dem1 = left.getDenominator() * right.getDenominator();
	return Rational(num1, dem1);
}

Rational operator- (const Rational &right) {
 int num1, dem1;
  num1 = -right.getNumerator();
  dem1 = right.getDenominator();
	return Rational(num1, dem1);
}

bool operator== (const Rational &left, const Rational &right) {
int com;

com = (left.getNumerator()*right.getDenominator())==(left.getDenominator()*right.getNumerator());

	return com;
}

bool operator<  (const Rational &left, const Rational &right) {
int com;

com = (left.getNumerator()*right.getDenominator())<(left.getDenominator()*right.getNumerator());

	return com;
}

#endif /* RATIONAL_H_ */
