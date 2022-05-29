#include "UserInterface.h"
#include "../Generic/List/List.hpp"
#include "../Generic/String/String.h"
#include <stdexcept>

/* Private (static) */

void UserInterface::com_print(const char* params) {
	List<String> cells = table.getAllCells();
}

/* Public */

UserInterface::UserInterface(Table& table) : menu() {
	if (!instantiated) {
		this->table = table;
		instantiated = true;
	}

	menu.addCommand(Command("print", com_print));
	menu.addCommand(Command("edit", com_edit));
}

void UserInterface::run() {
	menu.navigate();
}
