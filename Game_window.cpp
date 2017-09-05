#include "fltk/Window.h"
#include "fltk/GUI.h"
#include "fltk/std_lib_facilities_4.h"
#include "fltk/Graph.h"
#include "Game_window.h"
  
using namespace Graph_lib;

// This initializes the user_score. It is required for the static members that were written.
int Game_window::user_score{0};

Game_window::Game_window(Point xy, int w, int h, const string& title, const string& initials, const int& difficulty)
	:Window{xy,w,h,title},
	
	// There are a few variables involved in the game_window, and they would be as follows:
	current_angle{20},
	moves_left{50},
	seconds{seconds_per_sat*difficulty},
	user_initials{initials},
	user_difficulty{difficulty},
	
	// This is the map image that is displayed in the game_window. 
	map{map_top_left,"map.jpg",Suffix::Encoding::jpg},
	
	// These are the buttons that are displayed on the game_window screen.
	quit_btn{quit_btn_start,long_w,widget_h,"Quit",[](Address,Address pw){reference_to<Game_window>(pw).quit();}},
	up_btn{up_start,up_w,up_h,n_label,cb_take_turn},
	right_btn{right_start,up_h,up_w,e_label,cb_take_turn},
	left_btn{left_start,up_h,up_w,w_label,cb_take_turn},
	down_btn{down_start,up_w,up_h,s_label,cb_take_turn},
	
	// Out Boxes are displayed on the screen displaying what is actually going on in the game:
	active_satellite_out{active_sat_start,widget_h,widget_h,"Active Satellite"},
	score_out{score_out_start,long_w,widget_h,"Score:"},
	initials_out{Point{100,y_max()-75},50,20,"Initials:"},
	moves_left_out{Point{100,y_max()-50},75,20,"Moves Left:"},
	angle_out{Point{100,y_max()-25},75,20,"Current Angle:"},
	timer_out{timer_start,long_w,widget_h,"Time Left:"}
{	
	attach(map);
	attach(quit_btn);
	attach(up_btn);
	attach(right_btn);
	attach(left_btn);
	attach(down_btn);
	attach(active_satellite_out);
	attach(score_out);
	attach(initials_out);
	attach(moves_left_out);
	attach(angle_out);
	attach(timer_out);


	angle_out.put(to_string(current_angle));
	moves_left_out.put(to_string(moves_left));
	initials_out.put(user_initials);

	// This attaches the satellites at random locations on the map:
	for (int i = 0; i < user_difficulty; ++i) {
		construct_satellite(i,satellite_cover_vec,satellite_btn_vec,satellite_label_vec);
		satellite_bool_vec.push_back(0);

		attach(satellite_btn_vec[i]);
		attach(satellite_cover_vec[i]);
		attach(satellite_label_vec[i]);
	}	

	// This initializes the game data
	create_interval_vecs(pixel_interval_vec,lat_interval_vec);
	initialize_distance_vec(distance_vec);
	update_score(user_score);
	
}

void Game_window::cb_take_turn(Address flb,Address pw)
// This is a callback function for the direction buttons.
{
	string label(static_cast<Fl_Widget *>(flb)->label());
	reference_to<Game_window>(pw).take_turn(label[0]); // This calls move_satellite with the character label
}


void Game_window::quit()
// This currents the on-going game and displays/prints out the current score.
{
	// This prints out the score of the current game to the the high scores text file
	Vector<Score> score_vec;
	Score::get_scores("highscores.txt",score_vec);
	score_vec.push_back(Score(user_initials,user_score));
	Score::sort_scores(score_vec);
	score_vec.erase(score_vec.begin()+num_of_scores);
	Score::write_out_scores("highscores.txt",score_vec);
	hide();
}

void Game_window::determine_direction(int& x, int& y, char direction, const Point p)
// Changes move_x and move_y according to direction that was selected.
{
	switch(direction) {
		case 'N': y = -distance_vertical(1,p); x = 0; break;
		case 'E': x = distance_horizontal(); y = 0; break;
		case 'S': y = distance_vertical(0,p); x = 0; break;
		case 'W': x = -distance_horizontal(); y = 0; break;
		default: break;
	}
}

Point Game_window::random_point(Point top_left,int x_max, int y_max,int shape_boundary)
// This simply generates a random point within the map.
{
	Point rand_xy{rand() % (x_max-shape_boundary) + (top_left.x+shape_boundary),
                  rand() % (y_max-shape_boundary) + (top_left.y+shape_boundary)};
	return rand_xy;
}

void Game_window::construct_satellite(int i,Vector_ref<Circle>& cv,Vector_ref<Button>& bv,Vector_ref<Text>& tv)
// Basically creates various satellite objects to be placed on the game. 
{
	Point rand_xy = random_point(map_top_left,map_x,map_y,satellite_rad);
	Point btn_xy(rand_xy.x-satellite_rad*sqrt(2)/2,rand_xy.y-satellite_rad*sqrt(2)/2);
	Point text_xy(rand_xy.x-satellite_rad*sqrt(2)/4,rand_xy.y+satellite_rad*sqrt(2)/4);

	tv.push_back(new Text(text_xy,to_string(i+1)));
	cv.push_back(new Circle(rand_xy,satellite_rad));
	bv.push_back(new Button(btn_xy,satellite_rad*sqrt(2),satellite_rad*sqrt(2),to_string(i),
		[](Address flb,Address pw){
			string label(static_cast<Fl_Widget *>(flb)->label());
			int sat_num{stoi(label)};
			reference_to<Game_window>(pw).satellite_press(sat_num);
	})); 

	cv[i].set_fill_color(color_vec[i]);
}

void Game_window::satellite_press(int sat_num)
// We had to make a way for the program/user know which satellite was active so that's why we have this.
{
	for (int i = 0; i < user_difficulty; ++i) {
		if (i == sat_num) {
			satellite_bool_vec[i] = 1;
			active_satellite_out.put("  "+to_string(i+1));
		}
		else
			satellite_bool_vec[i] = 0;
	}
}

void Game_window::move_satellite(int x, int y, Circle& c, Button& b, Text& l)
// Moves the satellite as a unit.
{
	c.move(x,y);
	b.move(x,y);
	l.move(x,y);
}

void Game_window::check_boundaries(Circle& sc, Button& sb, Text& sl)
// Basically uses the wrap around that is written next:
{
	if (sc.center().x > map_bot_right.x) move_satellite(-map_x,0,sc,sb,sl);
	else if (sc.center().x < map_top_left.x) move_satellite(map_x,0,sc,sb,sl);
	else if (sc.center().y > map_bot_right.y) wrap_satellite_vertical(map_bot_right.y, sc, sb, sl);
	else if (sc.center().y < map_top_left.y) wrap_satellite_vertical(map_top_left.y, sc, sb, sl);
}

void Game_window::wrap_satellite_vertical(int boundary, Circle& sc, Button& sb, Text& sl) 
// Wraparound for going off the screen in the north or south direction:
{
	int translate{0};
	if (sc.center().x >= (map_top_left.x + map_bot_right.x)/2) translate = -180*pixels_per_angle;
	else translate = 180*pixels_per_angle;

	int offset = sc.center().y - boundary; 
	move_satellite(translate,-2*offset,sc,sb,sl);
}

void Game_window::take_turn(char direction)
// This is the take turn function that basically takes turns.
{
	int move_x{0};
	int move_y{0};

	for (int i = 0; i < user_difficulty; ++i) {
		if (satellite_bool_vec[i]) {
			determine_direction(move_x,move_y,direction,satellite_cover_vec[i].center());
			move_satellite(move_x,move_y,satellite_cover_vec[i],satellite_btn_vec[i],satellite_label_vec[i]);
			check_boundaries(satellite_cover_vec[i],satellite_btn_vec[i],satellite_label_vec[i]);

			update_score(user_score);
			check_moves();
			redraw();
		}
	}
}

void Game_window::check_moves()
// Checks the moves and changes the angles according the the instructions given:
{
	moves_left_out.put(to_string(--moves_left));

	if (moves_left > 40) {}
	else if (moves_left > 30) current_angle = 15;
	else if (moves_left > 20) current_angle = 10;
	else if (moves_left > 10) current_angle = 5;
	else current_angle = 1;

	angle_out.put(to_string(current_angle));

	if (moves_left <= 0) quit();
}

int Game_window::distance_vertical(int up, const Point p)
// Changes how far satellite moves vertically on the map:
{
	double scale_factor{0};
	if ((up && get_location(p).x >= 0) || (!up && get_location(p).x <= 0)) 
		scale_factor = compute_scale_factor(1,p);
	else 
		scale_factor = compute_scale_factor(0,p);

	double result = pixels_per_angle * current_angle * scale_factor;
	return round(result);
}

double Game_window::compute_scale_factor(int to_pole, const Point p)
// This basically returns average scale factor over the distance:
{
	double sum{0};
	// The formula for the scale factor was found on www.Wikipedia.com 
	if (to_pole) {
		for (int i = 0; i < current_angle; ++i) {
			if (abs(get_location(p).x) + i <= latitude_values[0])
				sum += 1.0/cos(deg2rad(abs(get_location(p).x) + i));
			else
				sum += 1.0/cos(deg2rad(latitude_values[0] - i));
		}
	}
	else {
		for (int i = 0; i < current_angle; ++i) {
			if (abs(get_location(p).x - i) <= latitude_values[0])
				sum += 1.0/cos(deg2rad(abs(get_location(p).x) - i));
			else
				sum += 1.0/cos(deg2rad(latitude_values[0] - i));
		}
	}
	return sum / current_angle;
}


int Game_window::distance_horizontal()
// This changes how far satellite moves horizontally across the map:
{
	double result = pixels_per_angle * current_angle;
	return round(result);
}

void Game_window::create_interval_vecs(Vector<Interval>& pv, Vector<Interval>& lv)
// This fills interval vectors.
{
	for (int i = 0; i < pixel_values.size() - 1; ++i) {
		pv.push_back(Interval(pixel_values[i],pixel_values[i+1]));
		lv.push_back(Interval(latitude_values[i+1],latitude_values[i]));
	}
}

Point Game_window::get_location(const Point p)
// Returns location of point in (latitude, longitude)
{
	Point result{get_latitude(p),get_longitude(p)};
	return result;
}

int Game_window::get_latitude(const Point p)
// This gets the latitude coordinate of point.
{
	// Determine interval in pixels
	int y_interval = determine_interval(p.y,pixel_interval_vec);
	
	// Determine proportion in pixels
	double proportion = double(p.y - pixel_interval_vec[y_interval].min()) / (pixel_interval_vec[y_interval].length());
	
	// Apply ratio to latitude
	double result = (1.0 - proportion) * lat_interval_vec[y_interval].length() + lat_interval_vec[y_interval].min();

	return round(result); 
}

int Game_window::determine_interval(int y,const Vector<Interval> iv)
// Determines which interval a number is in.
{
	for (int i = 0; i < iv.size(); ++i)
		if (iv[i].contains(y)) return i;

	error("Satellite out of range\n");
	return -1;
}

int Game_window::get_longitude(const Point p)
// This receives the longitude value of satellite
{
	double result = (p.x - map_top_left.x)*angle_per_pixel - 180;
	return round(result);
}

void Game_window::update_score(int& score)
// Updates the score and is displayed onto the screen
{
	update_distance(distance_vec);
	sort_distance(distance_vec);
	score = (distance_vec[0].distance)*user_difficulty;
	score_out.put(to_string(score));
}

void Game_window::sort_distance(Vector<Final_distance>& dv)
// Sorts in ascending order
{
	sort(dv.begin(),dv.end(),[](const Final_distance& a,const Final_distance& b){return a.distance < b.distance;});
}

void Game_window::update_distance(Vector<Final_distance>& dv)
// Update distance vector with current distances.
{
	int k = 0;
	for (int i = 0; i < user_difficulty - 1; ++i) {
		for (int j = i+1; j < user_difficulty; ++j) {
			dv[k].hint_1 = i+1;
			dv[k].hint_2 = j+1;
			dv[k].distance = calculate_distance(get_location(satellite_cover_vec[i].center()),get_location(satellite_cover_vec[j].center()));
			++k;
		}
	}
}

void Game_window::initialize_distance_vec(Vector<Final_distance>& dv)
// Fills a vector with 0.
{
	for (int i = 0; i < user_difficulty - 1; ++i)
		for (int j = i+1; j < user_difficulty; ++j)
			dv.push_back(Final_distance());
}

int Game_window::calculate_distance(Point sat_1, Point sat_2)
// This calculates distance and the formula/code was based of the idea from stackoverflow.com
{	
	const int earth_radius{3961};
	double a = calculate_haversine(sat_1,sat_2);
	double c = 2 * atan2(sqrt(a),sqrt(1-a));
	return round(c * earth_radius);
}


double Game_window::calculate_haversine(Point sat_1, Point sat_2)
// This calculates distance and the formula/code was based of the idea from stackoverflow.com
{	
	double dist_lat = deg2rad(sat_1.x - sat_2.x);
	double dist_long = deg2rad(sat_1.y - sat_2.y);
	double a = sin(dist_lat/2)*sin(dist_lat/2) + cos(deg2rad(sat_1.x)) * cos(deg2rad(sat_2.x)) *
		      sin(dist_long/2)*sin(dist_long/2);

	return a;
}

double Game_window::deg2rad(double deg)
// Converts degrees to radians 
{
	const double pi = 3.14159265358;
	return deg * pi / 180;
}