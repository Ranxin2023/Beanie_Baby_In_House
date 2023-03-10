#include "curses_controller.hpp"
#include<iostream>
#include <curses.h>

CursesController::~CursesController()
{
}

Command CursesController::getInput()
{
    // TODO: Implement.
    // Don't forget about the arrow keys.

    // To prevent a compiler error in the starter files...
	
    return getCommand();
}

void CursesController::setInput(){
	std::cout<<"Enter input: ";
	std::cin>>c;
	std::cin>>d;
	std::cin>>e;
	if(c==27){
		if(e==65){
			setCommand(Command::Forward);
		}
		if(e==67){
			setCommand(Command::Right);
		}
		if(e==68){
			setCommand(Command::Left);
		}
	}
	else{
		if(c=='a')
		{
			setCommand(Command::Left);
		}
		else if(c=='d')
		{
			setCommand(Command::Right);
		}
		else if(c=='w')
		{
			setCommand(Command::Forward);
		}
		else if(c=='q')
		{
			setCommand(Command::Quit);
		}
		else{
			setCommand(Command::Invalid);
		}
	}
}