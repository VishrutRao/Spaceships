#include "fltk/Window.h"
#include "fltk/GUI.h"
#include "fltk/std_lib_facilities_4.h"
#include "fltk/Graph.h"
#include "Input_window.h"

using namespace Graph_lib;

int Input_window::user_difficulty = 0;
string Input_window::user_initials = "";

Input_window::Input_window(Point xy, int w, int h, const string& title)
	:Window{xy,w,h,title},
	
	// This creates different buttons on the input window
	
	initials_in{Point(x_max()/2,y_max()/4),50,25,"Initials:"},
	difficulty_text{Point(x_max()/2-65,y_max()/4+75),"Difficulty: "},
	high_scores_text{Point(x_max()/2-50,y_max()/2+25),"High Scores"},
	rank_header{Point(x_max()/2-50,y_max()/2+50),"Rank"},
	initials_header{Point(x_max()/2,y_max()/2+50),"Initials"},
	score_header{Point(x_max()/2+50,y_max()/2+50),"Score"}
{
	high_scores_text.set_font_size(15);


	constexpr int min_difficulty = 2;
	constexpr int max_difficulty = 8;
	int menu_x = x_max()/2;	
	int menu_y = y_max()/4+60;
	
	for (int i = min_difficulty; i <= max_difficulty; ++i) {
		difficulty_menu.push_back(new Button(Point((i-2)*25+menu_x,menu_y),25,25,to_string(i),
			[](Address flb,Address pw){
				
				// Take label from button and pass into btn_pressed function
				
				string label(static_cast<Fl_Widget *>(flb)->label());
				int difficulty{stoi(label)};
				reference_to<Input_window>(pw).btn_pressed(user_difficulty,user_initials,difficulty);
		}));

		attach(difficulty_menu[difficulty_menu.size() - 1]);
	}	


	/************ attaching high scores to the menu ******************/
	
	Score::get_scores("highscores.txt",scores_data);
	Score::sort_scores(scores_data);
	fill_vectors(Point(x_max()/2-50,y_max()/2+50),scores_data,rank_out,initials_out,high_scores_out);

	for (int i = 0; i < num_of_scores; ++i) {
		attach(rank_out[i]);
		attach(initials_out[i]);
		attach(high_scores_out[i]);
	}
			
	put_vectors(scores_data,rank_out,initials_out,high_scores_out);

	attach(difficulty_text);
	attach(high_scores_text);
	attach(rank_header);
	attach(initials_header);
	attach(score_header);
	attach(initials_in);
}

void Input_window::btn_pressed(int& user_difficulty, string& user_initials, int difficulty)
// Passes data letting it know what difficulty the game is on
{
	string test_initials = get_initials();

	if (!test_initials.empty()) {	
		user_difficulty = difficulty;
		user_initials = test_initials;
		hide();
	}
}

string Input_window::get_initials()
// Get first 3 characters of entered initials
{
	string initials = initials_in.get_string();
	int initials_length = initials.length();

	for (int i = 0; i < initials.length(); ++i) 
		initials[i] = toupper(initials[i]);

	return (initials_length > 3) ?  initials.substr(0,3) : initials.substr(0,initials_length);
}

void Input_window::fill_vectors(Point p, Vector<Score> sv, Vector_ref<Out_box>& rv, Vector_ref<Out_box>& iv, Vector_ref<Out_box>& hsv)
// Fills the initials_out vector and the high_scores_out vector with sorted Out_boxes
{
	for (int i=0; i < num_of_scores; ++i) {
		rv.push_back(new Out_box{Point{p.x,p.y+i*20},50,20,""});
		iv.push_back(new Out_box{Point{p.x+50,p.y+i*20},50,20,""});
		hsv.push_back(new Out_box{Point{p.x+100,p.y+i*20},70,20,""});
	}
}

void Input_window::put_vectors(Vector<Score> sv, Vector_ref<Out_box>& rv, Vector_ref<Out_box>& iv, Vector_ref<Out_box>& hsv)
// Puts strings into the Out_box vectors
{
	if (num_of_scores > sv.size()) {
		for (int i =0, n = sv.size(); i < n; ++i) {
			rv[i].put(to_string(i+1));
			iv[i].put(sv[i].initials);
			hsv[i].put(to_string(sv[i].score));
		}
	}
	else {
		for (int i =0, n = num_of_scores; i < n; ++i) {
			rv[i].put(to_string(i+1));
			iv[i].put(sv[i].initials);
			hsv[i].put(to_string(sv[i].score));
		}
	}
}