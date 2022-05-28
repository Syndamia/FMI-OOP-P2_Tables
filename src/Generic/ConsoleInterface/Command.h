#ifndef HEADER_CONSOLEINTERFACE_COMMAND
#define HEADER_CONSOLEINTERFACE_COMMAND

/*! \file Command.h
 *  \brief Stores the declaration of class Command
 */

/*! \brief Stores a 256 character name and a function pointer to be executed when calling run()
 *
 * Menu uses this class for a more generic implementation of it's navigate function.
 */
class Command {
	char name[256];
	void (*exec)(const char* params);

public:
	//! Leaves name empty and exec function pointer to nullptr
	Command();
	//! Copies contents of nameInMenu and stores exec
	Command(const char* name, void (*exec)(const char* params));
	//! Executes the stored function pointer
	void run(const char* params) const;

	const char* get_name() const;
};

#endif
