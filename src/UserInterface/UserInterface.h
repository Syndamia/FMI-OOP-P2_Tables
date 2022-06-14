#ifndef HEADER_USERINTERFACE
#define HEADER_USERINTERFACE

/*! \file UserInterface.h
 *  \brief Stores the declaration of class UserInterface
 */

#include "../Generic/ConsoleInterface/Menu.h"
#include "../Generic/String/String.h"
#include "../Models/Table.h"

/*! \brief The class that contains and via which the user controls the application's user interface
 */
class UserInterface {
	Menu menu;

	static Table* table;
	static String fileName;
	static bool saved;

	static void com_open(const char* params);
	static void com_close(const char* params);
	static void com_save(const char* params);
	static void com_saveas(const char* params);
	static void com_help(const char* params);
	static void com_exit(const char* params);

	static void com_print(const char* params);
	static void com_edit(const char* params);

public:
	UserInterface();
	//! Starts the user interface
	void run();
};

#endif
