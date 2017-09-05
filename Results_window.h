#ifndef RESULTS_WINDOW_H
#define RESULTS_WINDOW_H

#include "fltk/GUI.h"
#include "fltk/std_lib_facilities_4.h"
#include "fltk/Window.h"
#include "fltk/Graph.h"

using namespace Graph_lib;

struct Results_window : Graph_lib::Window
{
	// This is the constructor
	Results_window (Point xy,int w,int h, const string& title, const int& score);
	
	// This is also the outgoing data
	bool replay() {return replay_bool;}
	
	private:
		// Game data
		int user_score;
		static bool replay_bool;

		// Three buttons are placed onto the screen and are displayed
		
		Point score_xy{535,337};
		Point play_again_xy{228,442};
		Point quit_xy{413,442};

		// Three buttons are placed onto the screen and are displayed
		
		Button play_again_btn;
		Button quit_btn;
		Out_box score_out;

		// These are the functions for buttons
		void quit(bool& replay_bool);
		void play_again(bool& replay_bool);
};

#endif