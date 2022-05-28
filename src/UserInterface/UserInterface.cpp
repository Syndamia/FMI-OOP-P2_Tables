#include "UserInterface.h"

UserInterface::UserInterface(Table& table) : table(table), menu() {
	menu.addCommand(Command("print", com_print));
}
