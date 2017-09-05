#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "fltk/Window.h"
#include "fltk/GUI.h"
#include "fltk/std_lib_facilities_4.h"
#include "fltk/Graph.h"
#include "Score.h"
#include "Interval.h"
#include "Final_distance.h"

//This Game_window.h basically declares everything in one file

using namespace Graph_lib;

struct Game_window : Graph_lib::Window {
	
	// This is the constructor
	Game_window(Point xy, int w, int h, const string& title, const string& initials, const int& difficulty);

	// This is the outgoing data
	int score() {return user_score;}

	private:
		// The is the game data
		string user_initials;
		int num_of_scores{5};
		int user_difficulty;		
		int seconds_per_sat{30};
		int seconds;		
		static int user_score;
		Vector<Color> color_vec {Color::red,Color::yellow,Color::white,Color::magenta,
								 Color::cyan,Color::green,Color::dark_magenta,Color::dark_cyan};
						
		// These are the various variables for the game that are used in the calculations
		int current_angle;
		int moves_left;
		Vector<Final_distance> distance_vec;

		// This is for the map image data
		Point map_top_left{100,0};
		Point map_bot_right{700,508};
		int map_x{600};
		int map_y{508};
		int satellite_rad{10}; // Radius of each satellite
		
		// Various widgets on the game_window
		int long_w{80};
		int widget_h{30};
		int short_w{50};
		Point quit_btn_start{710,239};
		Point initials_out_start{40,545};
		Point score_out_start{250,545};
		Point moves_out_start{265,545};
		Point angle_out_start{492,545};
		Point timer_start{675,535};
		Point active_sat_start{550,535};
		int up_h{15};
		int up_w{30};
		Point up_start{386,520};
		Point down_start{386,580-up_h};
		Point left_start{371,535};
		Point right_start{431-up_h,535};

		// These are the latitude values
		Vector<int> latitude_values = {82,75,60,45,30,15,0,-15,-30,-45,-60,-75,-82};
		Vector<int> pixel_values = {0,62,129,170,202,229,254,279,306,337,379,446,508};
		Vector<Interval> lat_interval_vec;
		Vector<Interval> pixel_interval_vec;
		double pixels_per_angle = 5.0/3;
		double angle_per_pixel = 1.0/pixels_per_angle;

		// The buttons labels for direction buttons
		string n_label = "N";
		string e_label = "E";
		string s_label = "S";
		string w_label = "W";
		
		// These are the satellites that are placed into vectors
		Vector_ref<Circle> satellite_cover_vec;
		Vector_ref<Button> satellite_btn_vec;
		Vector_ref<Text> satellite_label_vec;
		Vector<int> satellite_bool_vec;

		Button quit_btn;
		Button up_btn;
		Button right_btn;
		Button left_btn;
		Button down_btn;

		//Map Image
		Image map;

		Out_box score_out;
		Out_box initials_out;
		Out_box moves_left_out;
		Out_box angle_out;
		Out_box timer_out;	
		Out_box active_satellite_out;	


		// The callback
		static void cb_take_turn(Address,Address pw);

		// The quit
		void quit();
		
		// The satellite constructing functions
		Point random_point(Point top_left,int x_max,int y_max,int shape_boundary);
		void construct_satellite(int i,Vector_ref<Circle>&,Vector_ref<Button>&,Vector_ref<Text>&);

		// The move satellite functions
		void take_turn(char direction);
		void satellite_press(int sat_num);
		void determine_direction(int& x, int& y, char direction, const Point p);	
		void move_satellite(int x, int y, Circle& c, Button& b, Text& l);

		// Checks the moves and updates the settings based on moves left
		void check_moves();
		
		// Involves the wraparound functions
		void check_boundaries(Circle& sc, Button& sb, Text& sl);
		void wrap_satellite_vertical(int boundary, Circle& sc, Button& sb, Text& sl);
		
		// Determines distance to move based on current angle and location
		int distance_vertical(int up, const Point p);
		int distance_horizontal();
		double compute_scale_factor(int to_pole, const Point p);

		// These are the location functions
		void create_interval_vecs(Vector<Interval>& pv, Vector<Interval>& lv);
		Point get_location(const Point p);
		int get_latitude(const Point p);
		int determine_interval(int y, const Vector<Interval> iv);
		int get_longitude(const Point p);

		// The score and distance calculations
		void update_score(int& score);
		void sort_distance(Vector<Final_distance>& dv);
		void update_distance(Vector<Final_distance>& dv);	
		void initialize_distance_vec(Vector<Final_distance>& dv);
		int calculate_distance(Point sat_1, Point sat_2);
		double calculate_haversine(Point sat_1, Point sat_2);	
		double deg2rad(double deg);
};

#endif