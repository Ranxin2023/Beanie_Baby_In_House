#include "print_controller.hpp"

#include <iostream>

PrintController::~PrintController()
{
}

Command PrintController::getInput()
{
    // TODO: Implement.

    // To prevent a compiler error in the starter files...
    return getCommand();
}

void PrintController::setInput(){
	std::cout<<"Enter input: ";
	std::cin>>c;
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