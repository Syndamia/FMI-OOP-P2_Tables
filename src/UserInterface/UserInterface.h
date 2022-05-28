#ifndef HEADER_USERINTERFACE
#define HEADER_USERINTERFACE

#include "../Generic/ConsoleInterface/Menu.h"
#include "../Models/Table.h"

class UserInterface {
	Menu menu;
	Table& table;

public:
	UserInterface(Table& table);
	void run();
};

#endif
