CXX=g++
CXXFLAGS=-std=c++14 -g -lfltk -lfltk_images

all:  fltk/Graph.o fltk/GUI.o fltk/Window.o fltk/Simple_window.o Score.o Interval.o Input_window.o Game_window.o Results_window.o Splash_window.o Instruction_window.o main 

main: fltk/Graph.o fltk/GUI.o fltk/Window.o fltk/Simple_window.o Score.o Interval.o Input_window.o Game_window.o Results_window.o Splash_window.o Instruction_window.o main.cpp

run:
	./main

db:
	gdb main