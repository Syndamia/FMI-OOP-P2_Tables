#include "UserInterface.h"
#include "../Generic/List/List.hpp"
#include "../Generic/String/String.h"
#include "../Generic/ConsoleInterface/Toolbox.hpp"
#include <stdexcept>

/* Private (static) */

Table* UserInterface::table = nullptr;

void UserInterface::com_open(const char* params) {
	if (table != nullptr) {
		printLine("A file has already been opened!");
		return;
	}

	try {
		table = new Table(params);
	}
	catch (std::logic_error err) {
		printLine(err.what());
	}
}
void UserInterface::com_close(const char* params) {
}
void UserInterface::com_save(const char* params) {
}
void UserInterface::com_saveas(const char* params) {
}

void UserInterface::com_help(const char* params) {
	std::cout << "The following commands are supported:" << std::endl
			  << "open <file>      opens <file>" << std::endl
			  << "close            closes currently opened file" << std::endl
			  << "save             saves the currently open file" << std::endl
			  << "saveas <file>    saves the currently open file in <file>" << std::endl
			  << "help             prints this information" << std::endl
			  << "exit             exists the program" << std::endl;
}

void UserInterface::com_exit(const char* params) {
}

void UserInterface::com_print(const char* params) {
	List<String> cells = table->getAllCells();
	printTable(cells, table->get_cols());
}

void UserInterface::com_edit(const char* params) {
	while (*params == ' ') params++;

	unsigned row = atoi(++params);
	while (*params != 'C') params++;
	unsigned col = atoi(++params);
	while (*params != ' ') params++;

	table->putCell(row, col, params);
}

/* Public */

UserInterface::UserInterface(Table* inTable) : menu() {
	if (table == nullptr)
		table = inTable;

	menu.addCommand(Command("help", com_help));
	menu.addCommand(Command("print", com_print));
	menu.addCommand(Command("edit", com_edit));
}

void UserInterface::run() {
	menu.navigate();
}
