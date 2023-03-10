#ifndef CURSES_CONTROLLER_HPP
#define CURSES_CONTROLLER_HPP

#include "controller.hpp"

class CursesController : public Controller
{
private:
	char c;
	char d;
	char e;
public:
    CursesController() = default;
    virtual ~CursesController() override;
    CursesController(const CursesController&) = delete;
    CursesController& operator=(const CursesController&) = delete;
    virtual Command getInput() override;
	virtual void setInput() override;
};

#endif // CURSES_CONTROLLER_HPP
