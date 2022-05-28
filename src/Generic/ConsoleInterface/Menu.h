#ifndef HEADER_CONSOLEINTERFACE_MENU
#define HEADER_CONSOLEINTERFACE_MENU

/*! \file Menu.h
 *  \brief Stores the declaration of class Menu
 */

#include "Command.h"
#include "../List/List.hpp"

/*! \brief Handles navigation between multiple commands
 *
 * Shows the title, then below it an Error/Warning/Success message if set,
 * lists all command options as an enumerated list, takes command index
 * and calls the chosen command's run() function.
 */
class Menu {
	List<Command> menuOptions;

public:
	//! Sets name as "Menu", leaves all flags to false and creates an empty Command list
	Menu();
	//! Copies commands
	Menu(const Command* commands, unsigned commandCount);

	//! Lists commands and after user input executes an appropriate command run() function
	void navigate() const;
};

#endif
