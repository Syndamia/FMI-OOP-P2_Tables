#include "Menu.h"
#include "Toolbox.hpp"
#include <cstring>

Menu::Menu() : menuOptions() {}

unsigned indexOfCommandEnd(char* str) {
	unsigned ind = 0;
	while (str[ind] != ' ') ind++;
	return ind;
}

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

	char buffer[MAX_LINE_WIDTH];

	while (strncmp(buffer, "quit", 4) != 0) {
		clear();
		inputLineBox("> ", buffer, MAX_LINE_WIDTH);

		while (*buffer == ' ') buffer++;
		unsigned commandEnd = indexOfCommandEnd(buffer),
				 index = menuOptions.get_count();
		for (unsigned i = 0; i < menuOptions.get_count(); i++) {
			if (strncmp(buffer, menuOptions[i].get_name(), commandEnd) == 0) {
				index = i;
				break;
			}
		}

		if (index > menuOptions.get_count()) {
			printLine("Invalid menu option!");
			continue;
		}

		menuOptions[index].run(buffer + commandEnd);
	}
}
