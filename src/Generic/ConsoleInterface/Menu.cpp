#include "Menu.h"
#include "Toolbox.hpp"
#include <cstring>

Menu::Menu() : menuOptions() {}

/*!
 * Prints the title, then an Error/Warning/Sucess message (if set),
 * prints all command names as an ordered list (starting from 1),
 * waits for user input to select one of those commands (by list number)
 * and finally executes the appropriate command's run() function.
 *
 * After the run() function exists, everything is reprinted.
 * The 0 list index is always "Go Back"/"Exit" and it always stops the reprinting loop.
 *
 * If there are no commands, prints "Menu is empty!".
 * If user input doesn't correspond to any command, registers an error message and reprints.
 */
void Menu::navigate() const {
	if (menuOptions.get_count() == 0) {
		printLine("Menu is empty!");
		return;
	}

	unsigned buffer = 1; // We immedeately read the value of buffer, so this is fine

	while (buffer != 0) {
		clear();
		print("> ");
		readLine();

		resetOrderedList(0);
		if (backExistsApp)
			printOrderedListElem("Exit");
		else
			printOrderedListElem("Go Back");

		for (unsigned i = 0; i < menuOptions.get_count(); i++)
			printOrderedListElem(menuOptions[i].get_nameInMenu());

		_printInputBoxLabel("Execute No [0-");
		print(menuOptions.get_count());
		print("]: ");
		read(buffer);

		if (buffer > menuOptions.get_count())
			registerError("Invalid menu option!");
		else if (buffer > 0)
			menuOptions[buffer - 1].run();
	}
}
