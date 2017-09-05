#ifndef SPLASH_WINDOW_H
#define SPLASH_WINDOW_H

#include "fltk/Window.h"
#include "fltk/GUI.h"
#include "fltk/std_lib_facilities_4.h"
#include "fltk/Graph.h"

using namespace Graph_lib;

struct Splash_window : Graph_lib::Window {
	
	// This is the constructor
	Splash_window(Point xy, int w, int h, const string& title);

	private:
	
		// On - screen Buttons
		Button next_btn;
		Rectangle cover_btn;
		Text next_txt;
		Image splash_image;

		// Function to hide window and go to the next window which is the Instruction_window:
		void next();
};

#endif