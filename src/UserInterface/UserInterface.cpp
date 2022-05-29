#include "UserInterface.h"
#include "../Generic/List/List.hpp"
#include "../Generic/String/String.h"
#include <stdexcept>

/* Private (static) */

Table* UserInterface::table = nullptr;

void UserInterface::com_print(const char* params) {
	List<String> cells = table->getAllCells();
}

void UserInterface::com_edit(const char* params) {
	//TODO
}

/* Public */

UserInterface::UserInterface(Table* inTable) : menu() {
	if (table == nullptr)
		table = inTable;

	menu.addCommand(Command("print", com_print));
	menu.addCommand(Command("edit", com_edit));
}

void UserInterface::run() {
	menu.navigate();
}
