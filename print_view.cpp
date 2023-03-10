#include "print_view.hpp"

#include <iostream>

/**
 * The constructor and destructor shouldn't need anything added.
 */

PrintView::PrintView(int height, int width)
    : View(height, width)
{
}

PrintView::~PrintView()
{
}

void PrintView::draw(const std::vector<std::string>& lines)
{
    // TODO: Implement.
	unsigned i,j;
	for(i=0;i<lines.size();i++){
		for(j=0;j<lines[i].length();j++){
			std::cout<<lines[i][j];
		}
		std::cout<<std::endl;
	}
}
