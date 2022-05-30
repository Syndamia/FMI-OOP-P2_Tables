#include "UserInterface.h"
#include "../Generic/List/List.hpp"
#include "../Generic/String/String.h"
#include "../Generic/ConsoleInterface/Toolbox.hpp"
#include <stdexcept>

/* Private (static) */

Table* UserInterface::table = nullptr;
String UserInterface::fileName = String();
bool UserInterface::saved = false;


void UserInterface::com_open(const char* params) {
	if (table != nullptr) {
		printLine("A file has already been opened!");
		return;
	}

	try {
		table = new Table(params);
		fileName = params;
		saved = true;
		printLine("Successfully opened file!");
	}
	catch (std::logic_error err) {
		printLine(err.what());
	}
}
void UserInterface::com_close(const char* params) {
	if (table == nullptr) {
		printLine("No file has been opened!");
		return;
	}

	delete table;
}
void UserInterface::com_save(const char* params) {
	com_saveas(fileName.get_cstr());
}
void UserInterface::com_saveas(const char* params) {
	if (table == nullptr) {
		printLine("No file has been opened!");
		return;
	}

	try {
		table->saveToFile(params);
		saved = true;
		printLine("Successfully saved to file!");
	}
	catch (std::logic_error err) {
		printLine(err.what());
	}
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
	if (!saved && table != nullptr) {
		printLine("You have an open file with unsaved changes, please select close or save first.");
		return;
	}

	throw std::logic_error("Exiting program..."); // stupid way of making the program stop
}

void UserInterface::com_print(const char* params) {
	if (table == nullptr) {
		printLine("You need to open a file!");
		return;
	}

	List<String> cells = table->getAllCells();
	printTable(cells, table->get_cols());
}

#define isDigit(a) (a >= '0' && a <= '9')

void UserInterface::com_edit(const char* params) {
	if (*params != 'R') {
		printLine("Error: Invalid cell position format! Expected R<number>C<number>");
		return;
	}

	unsigned row = atoi(++params);
	while (*params != 'C') {
		if (*params == '\0') {
			printLine("Error: End of line reached. Expected row number.");
			return;
		}
		if (!isDigit(*params)) {
			printLine("Error: Found a non-digit character. Exptected row number.");
			return;
		}

		params++;
	}
	unsigned col = atoi(++params);
	while (*params != ' ') {
		if (*params == '\0') {
			printLine("Error: End of line reached. Expected columns number.");
			return;
		}
		if (!isDigit(*params)) {
			printLine("Error: Found a non-digit character. Exptected column number.");
			return;
		}

		params++;
	}

	try {
		table->putCell(row, col, params);
		saved = false;
		printLine("Successfully edited cell!");
	}
	catch (std::logic_error err) {
		printLine(err.what());
	}
}

/* Public */

UserInterface::UserInterface() : menu() {
	menu.addCommand(Command("open", com_open));
	menu.addCommand(Command("close", com_close));
	menu.addCommand(Command("save", com_save));
	menu.addCommand(Command("saveas", com_saveas));
	menu.addCommand(Command("help", com_help));
	menu.addCommand(Command("exit", com_exit));
	menu.addCommand(Command("print", com_print));
	menu.addCommand(Command("edit", com_edit));
}

void UserInterface::run() {
	menu.navigate();
}
