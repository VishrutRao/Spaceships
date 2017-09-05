#include "fltk/Window.h"
#include "fltk/GUI.h"
#include "fltk/std_lib_facilities_4.h"
#include "fltk/Graph.h"

#include "Splash_window.h"
#include "Input_window.h"
#include "Game_window.h"
#include "Instruction_window.h"
#include "Results_window.h"

int main()
try {
	
	// This is the game data:
	string user_initials;
	int user_difficulty{0};
	int user_score{0};
	bool running = true;

	// This is the window data aka screen size
	constexpr int x_max = 800;
	constexpr int y_max = 600;
	Point tl{500,100};

	Splash_window splash_window(tl,x_max,y_max,"Alien Invasion - Splash Window");

	gui_main();

	Instruction_window instruction_window(tl,x_max,y_max,"Alien Invasion - Instruction Window");

	gui_main();

	// It begins the game loop:
	while (running) {
		Input_window Input_window(tl,x_max,y_max,"Alien Invasion - Input Window");	

		gui_main();

		// Gets the user input from input window:
		user_initials = Input_window.initials();
		user_difficulty = Input_window.difficulty();

		Game_window Game_window(tl,x_max,y_max,"Alien Invasion - Game Window",user_initials,user_difficulty);

		gui_main();

		// Gets the score from game window:
		user_score = Game_window.score();

		Results_window Results_window(tl,x_max,y_max,"Alien Invasion - Game Over Window",user_score);

		gui_main();

		// Basically says if you want to play again or quit?
		running = Results_window.replay();
	}
} 
catch (exception& e) {
	cerr << "Exception: " << e.what() << "\n";
	return 1;
}
catch (...) {
	cerr << "Unknown exception\n";
	return 2;
}

