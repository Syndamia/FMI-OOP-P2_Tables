#ifndef HEADER_USERINTERFACE
#define HEADER_USERINTERFACE

#include "../Generic/ConsoleInterface/Menu.h"
#include "../Models/Table.h"

class UserInterface {
	Menu menu;

	static Table& table;

	static void com_open(const char* params);
	static void com_close(const char* params);
	static void com_save(const char* params);
	static void com_saveas(const char* params);
	static void com_help(const char* params);
	static void com_exit(const char* params);

	static void com_print(const char* params);
	static void com_edit(const char* params);

public:
	UserInterface(Table& table);
	void run();
};

#endif
