#ifndef SCORE_H
#define SCORE_H

#include "fltk/std_lib_facilities_4.h"

struct Score {
	
	// This is the constructor
	Score() {};
	Score(string init,int sc);	

	// It deals with the score vector
	static void get_scores(string file_name, Vector<Score>& sv);
	static bool compare_scores(const Score& a, const Score& b);
	static void sort_scores(Vector<Score>& sv);
	static void write_out_scores(string file_name, Vector<Score>& sv);

	// The properties of the score.h
	string initials;
	int score;
};

#endif