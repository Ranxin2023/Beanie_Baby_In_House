C++Flag=g++ -Wall -Werror -g -std=c++11
files=main.cpp item.cpp map_segment.cpp curses_controller.cpp print_controller.cpp curses_view.cpp print_view.cpp game.cpp view.cpp building.cpp 
O=-o
main=main
curses=-lcurses
all:
	$(C++Flag) $(files) $(O) $(main) $(curses)
clean:
	rm -rf $(main)
