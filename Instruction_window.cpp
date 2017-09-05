#include "fltk/std_lib_facilities_4.h"
#include "fltk/Window.h"
#include "fltk/Graph.h"
#include "fltk/GUI.h"
#include "Instruction_window.h"

Instruction_window::Instruction_window(Point xy, int w, int h, const string& title)
	:Window{xy,w,h,title},
	
	// This creates different buttons on the Instruction_image
	
	instruction_image{Point{0,0},"Instruction_image.jpg",Suffix::Encoding::jpg},
	next_btn{Point{x_max()-50,0},50,20,"",[](Address, Address pw){reference_to<Instruction_window>(pw).next();}},
	next_txt{Point{x_max()-40,15},"Next"},
	cover_btn{Point{x_max()-50,0},50,20}
{
	cover_btn.set_fill_color(Color::white);

	attach(instruction_image);
	attach(next_btn);
	attach(cover_btn);
	attach(next_txt);
}

void Instruction_window::next()
// Goes to the next window which is the Input_window:
{
	hide();
}