#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

enum class Command
{
    // Changing how player is facing.
    Left,
    Right,

    // Movement.
    Forward,

    Quit,
    Invalid
};

class Controller
{
private:
	Command command;
public:
    Controller() = default;
    virtual ~Controller() = default;
    Controller(const Controller&) = delete;
    Controller& operator=(const Controller&) = delete;
	void setCommand(Command com){command=com;}
	Command getCommand(){return command;}
    virtual Command getInput() = 0;
	virtual void setInput()=0;
};

#endif // CONTROLLER_HPP
