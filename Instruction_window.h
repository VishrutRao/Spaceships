#ifndef INSTRUCTION_WINDOW_H
#define INSTRUCTION_WINDOW_H

#include "fltk/std_lib_facilities_4.h"
#include "fltk/Window.h"
#include "fltk/Graph.h"
#include "fltk/GUI.h"

using namespace Graph_lib;

struct Instruction_window : Graph_lib :: Window{
	Instruction_window(Point xy, int w, int h, const string& title);
	
	private:
	
		// This is what is on the screen:
		Button next_btn;
		Rectangle cover_btn;
		Text next_txt;
		Image instruction_image;

		// Function to hide window and go to the next window which is the Input_window:
		void next();
};

#endif