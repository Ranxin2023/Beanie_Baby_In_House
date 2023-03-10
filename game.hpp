#ifndef GAME_HPP
#define GAME_HPP

#include "controller.hpp"
#include "view.hpp"
#include "interface_type.hpp"
#include "map_segment.hpp"
using namespace std;
class Game
{
public:  // public methods
    /**
     * DO NOT change the prototype of this function.
     * The autograder WILL call this function.
     */
    Game(const std::string& filename, InterfaceType interfaceType);

    ~Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    
    /**
     * DO NOT change the prototype of this function.
     * The autograder WILL call this function.
     */
    void run();

private:  // private methods
    /**
     * You DO NOT need to have any of the private methods below.
     * I just left some commented out declarations in case it
     * helps guide your thinking, but you don't need to use them.
     */

    /**
     * Set up the 1D vector of strings that is then given to the draw()
     * method of an instance of a subclass of View.
     */
    void draw();

    /**
     * Loop until the game is over. On each iteration, use the controller
     * to get input from the user.
     */
    void doGameLoop();

    /**
     * Update matters related to game logic, e.g. collisions, level completion.
     */
    void update();

    /**
     * Load information related to new level into member variables,
     * being careful to not leave traces of information from previous levels. 
     */
    void loadLevel();
	void printInfo();

private:
    static const int MIN_VIEW_HEIGHT;
    static const int MIN_VIEW_WIDTH;
    static const char HERO_ICON_LEFT;
    static const char HERO_ICON_RIGHT;
    static const char HERO_ICON_UP;
    static const char HERO_ICON_DOWN;

    /**
     * Because one of the constructor parameters must be checked in order
     * to determine the subclass types for the below members, they can't
     * be references, because there's no default constructors for them.
     * (Recall that each member in a class must either be initialized by an
     * initializer list in the constructor OR have a default constructor.)
     */
    View* mView;
    Controller* mController;
    InterfaceType mInterfaceType;
	MapSegment ** map_s;
	int numOfLevels;
	string * levelFiles;
	int currentLevel=0;
	//int oldLevel=0;
	int * movesRemaining;
	int * itemsRemaining;
	int ** numOfItemCaught;
	int ***catch_item_pos_y;
	int ***catch_item_pos_x;
	//vector<string>lines;
};

#endif // GAME_HPP
