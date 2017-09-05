#ifndef INTERVAL_H
#define INTERVAL_H

#include "fltk/std_lib_facilities_4.h"

struct Interval {
	Interval(int x, int y);
	int min() const;
	int max() const;
	int length() const;
	bool contains(int x) const;

	private:
		int minimum;
		int maximum;
};

#endif