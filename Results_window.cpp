#include "fltk/GUI.h"
#include "fltk/std_lib_facilities_4.h"
#include "fltk/Window.h"
#include "fltk/Graph.h"
#include "Results_window.h"

using namespace Graph_lib;

bool Results_window::replay_bool = false;

Results_window::Results_window(Point xy, int w, int h, const string& title, const int& score)
	:Graph_lib::Window{xy,w,h,title},
	
	// This creates different buttons on the Results_window and also displays the score
	
	user_score{score},
	play_again_btn{Point(x_max()/2-140,y_max()/2),140,100,"Play Again",[](Address, Address pw){reference_to<Results_window>(pw).play_again(replay_bool);}},
	quit_btn{Point(x_max()/2,y_max()/2),140,100,"Quit Game",[](Address, Address pw){reference_to<Results_window>(pw).quit(replay_bool);}},
	score_out{Point(x_max()/2-75,y_max()/3) ,140,70,"Your Score:"}
{
	attach(score_out);
	attach(play_again_btn);
	attach(quit_btn);

	score_out.put(to_string(user_score));
}

void Results_window::quit(bool& replay_bool)
// This is the function to end program
{
	replay_bool = false;
	hide();
}

void Results_window::play_again(bool& replay_bool)
// This is the function to loop back to input window and so you can play the game again
{
	replay_bool = true;
	hide();
}

