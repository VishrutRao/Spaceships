#ifndef FINAL_DISTANCE_H
#define FINAL_DISTANCE_H

struct Final_distance {
	int hint_1;
	int hint_2;
	int distance;
	
	// These are the constructors 
	
	Final_distance(int h1, int h2, int d) : hint_1(h1), hint_2(h2), distance(d) { }
	Final_distance() :hint_1(0), hint_2(0), distance(0) { }
}; 

#endif