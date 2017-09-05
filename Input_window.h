#ifndef INPUT_WINDOW_H
#define INPUT_WINDOW_H

#include "fltk/Window.h"
#include "fltk/GUI.h"
#include "fltk/std_lib_facilities_4.h"
#include "fltk/Graph.h"
#include "Score.h"

using namespace Graph_lib;

struct Input_window : Graph_lib::Window {
	Input_window(Point xy, int w, int h, const string& title);
	string initials() {return user_initials;}
	int difficulty() {return user_difficulty;}

	private:
		int num_of_scores{5};
		static string user_initials;
		static int user_difficulty;

		// User input
		In_box initials_in;		
		Vector_ref<Button> difficulty_menu;

		// Labels
		Text difficulty_text;
		Text high_scores_text;
		Text rank_header;
		Text initials_header;
		Text score_header;

		// High scores vectors
		Vector<Score> scores_data;
		Vector_ref<Out_box> rank_out;
		Vector_ref<Out_box> initials_out;
		Vector_ref<Out_box> high_scores_out;	

		// Functions for User input
		void btn_pressed(int& user_difficulty, string& user_initials, int difficulty);
		string get_initials();

		// Functions for high scores
		void fill_vectors(Point p, Vector<Score> sv, Vector_ref<Out_box>& rv, Vector_ref<Out_box>& iv, Vector_ref<Out_box>& hsv);
		void put_vectors(Vector<Score> sv, Vector_ref<Out_box>& rv, Vector_ref<Out_box>& iv, Vector_ref<Out_box>& hsv);		
};

#endif