/*
 * timer.h
 *
 *  Created on: 05/08/2015
 *      Author: pperezm
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <string>
#include <sstream>

using namespace std;

class Timer {
private:
	int hours, minutes;

public:
	Timer();
	Timer(int, int);
	Timer(const Timer&);

	int getHours() const;
	int getMinutes() const;
	std::string toString() const;

	void operator= (const Timer&);
	void operator+= (const Timer&);
};

Timer::Timer() : hours(0), minutes(0) {}

Timer::Timer(int hh, int mm) {
  
	minutes = mm % 60;
	hours = (hh + (mm / 60)) % 24;

}

Timer::Timer(const Timer &t) {}

int Timer::getHours() const {
  
  return hours;
}

int Timer::getMinutes() const {

  return minutes;
}

std::string Timer::toString() const {
	 std::stringstream aux;

	 if (hours < 10) {
		 aux << "0";
	 }
	 aux << hours << ":";
	 if (minutes < 10) {
		 aux << "0";
	 }
	 aux << minutes;
	 return aux.str();
}

void Timer::operator= (const Timer &right) {

  hours = right.hours;
  minutes = right.minutes;
}

void Timer::operator+= (const Timer &right) {
int min;

  min = minutes + right.minutes;
  minutes = min % 60;
  hours = hours + min / 60;

  hours = hours + right.hours;
  hours = hours % 24;
}

bool operator== (const Timer &left, const Timer &right) {

int comp;

comp=(left.getHours()==right.getHours()) && (left.getMinutes()==right.getMinutes());

return (comp);
}

bool operator> (const Timer &left, const Timer &right) {
	if (left.getHours() == right.getHours()) {
		return (left.getMinutes() > right.getMinutes());
	} else {
		return (left.getHours() > right.getHours());
	}
}

#endif /* TIMER_H_ */