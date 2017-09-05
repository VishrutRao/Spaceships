#include "fltk/std_lib_facilities_4.h"
#include "fltk/Window.h"
#include "fltk/Graph.h"
#include "fltk/GUI.h"
#include "Splash_window.h"

using namespace Graph_lib;

Splash_window::Splash_window(Point xy, int w, int h, const string& title)
	:Window{xy,w,h,title},
	
	// This creates different buttons on the Splash_window and also displays the background JPG
	
	splash_image{Point{0,0},"Splash_image.jpg",Suffix::Encoding::jpg},
	next_btn{Point{x_max()-50,0},50,20,"",[](Address, Address pw){reference_to<Splash_window>(pw).next();}},
	next_txt{Point{x_max()-40,15},"Next"},
	cover_btn{Point{x_max()-50,0},50,20}
{
	cover_btn.set_fill_color(Color::white);

	attach(splash_image);
	attach(next_btn);
	attach(cover_btn);
	attach(next_txt);
}

void Splash_window::next()
// Goes to next window which would be the instruction_window.
{
	hide();
}