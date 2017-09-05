#include "std_lib_facilities_4.h"
#include "Window.h"

int main() {
	Graph_lib::Window win{Point(200,200), 600, 600, "Game"};
	return Graph_lib::gui_main();
}
