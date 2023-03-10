#ifndef PRINT_CONTROLLER_HPP
#define PRINT_CONTROLLER_HPP

#include "controller.hpp"

class PrintController : public Controller
{
private:
	char c;

public:
    PrintController() = default;
    virtual ~PrintController() override;
    PrintController(const PrintController&) = delete;
    PrintController& operator=(const PrintController&) = delete;
    virtual Command getInput() override;
	virtual void setInput() override;
};

#endif // PRINT_CONTROLLER_HPP
