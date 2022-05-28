#include "Command.h"
#include <cstring>

Command::Command() : Command("", nullptr) {}

/*! \param name C-style string, class stores at most 255 characters (last character is always terminating zero)
 *  \param exec Function pointer that will be executed when run() is called. Can be nullptr.
 */
Command::Command(const char* name, void (*exec)(const char* params)) {
	strncpy(this->name, name, 255);
	this->name[255] = '\0';
	this->exec = exec;
}

/*! Executes the stored function pointer, when it's not nullptr. Otherwise does nothing.
 */
void Command::run(const char* params) const {
	if (exec != nullptr)
		exec(params);
}

const char* Command::get_name() const {
	return name;
}
