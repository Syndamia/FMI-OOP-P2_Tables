#include "UserInterface.h"
#include "../Generic/List/List.hpp"
#include "../Generic/String/String.h"
#include <stdexcept>

/* Private (static) */

void UserInterface::com_print(const char* params) {
	List<String> cells = table.getAllCells();
}

/* Public */

UserInterface::UserInterface(Table& inTable) : menu() {
	if (!instantiated) {
		table = inTable;
		instantiated = true;
	}

	menu.addCommand(Command("print", &UserInterface::com_print));
	menu.addCommand(Command("edit", &UserInterface::com_edit));
}

void UserInterface::run() {
	menu.navigate();
}
