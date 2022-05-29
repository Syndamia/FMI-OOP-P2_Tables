#include "UserInterface.h"

UserInterface::UserInterface(Table& table) : menu() {
	this->table = table;
	menu.addCommand(Command("print", com_print));
	menu.addCommand(Command("edit", com_edit));
}
