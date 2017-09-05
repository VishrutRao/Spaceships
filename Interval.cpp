#include "Interval.h"
#include "fltk/std_lib_facilities_4.h"

Interval::Interval(int x, int y) {
	if (y < x) error("Bad input for Interval constructor");
	minimum = x;
	maximum = y;
}

int Interval::min() const {return minimum;}

int Interval::max() const {return maximum;}

int Interval::length() const {return maximum - minimum;}

bool Interval::contains(int x) const {return minimum <= x && x <= maximum;}