#include "Toolbox.hpp"

/*!
 * Erases display and moves cursor to top left corner via ANSI escape sequences: \c ESC[2J \c ESC[1;1H
 *
 * \warning Not all terminals support any or all ANSI escape sequences
 *
 * \note Source: https://stackoverflow.com/a/52895729/12036073
 */
void clear() {
	std::cout << u8"\033[2J\033[1;1H"; 
}

/* Input line boxes */

void __inputLineBoxGetInput(char* output, unsigned maxWidth, bool ignore) {
	if (ignore)
		std::cin.ignore();
	std::cin.getline(output, maxWidth);
}

/*! \param label C-style string, there are no size check so it could wrap
 *  \param output Pointer to a char array
 *  \param maxWidth Maximum count of characters to read from user input. output MUST be able to hold that many characters!
 *  \param ignore Whether or not to ignore the first new-line delimiter.
 *         true by default, should be set to false only when an inputLineBox/SubBox has been issued directly prior or when it's the very first issued box command.
 *
 *  Prints "(+)" before the label.
 */
void inputLineBox(const char* label, char* output, unsigned maxWidth, bool ignore) {
	print(label);
	__inputLineBoxGetInput(output, maxWidth, ignore);
}

/* Table */

void __printTableHeaderNumber(unsigned number) {
	std::cout << ":" << ((number < 100) ? " " : "") << number << ((number < 10) ? " " : "");
}

void __printTableColumnHeader(unsigned count, unsigned start = 1) {
	std::cout << ":   ";
	for (unsigned i = 0; i < count; i++)
		__printTableHeaderNumber(start++);
	std::cout << ":" << std::endl;

	for (unsigned i = 0; i <= count; i++)
		std::cout << "====";
	std::cout << "=" << std::endl;
}

void __printTableLine(unsigned columns) {
	std::cout << ":===";
	for (unsigned i = 0; i < columns; i++)
		std::cout << "+---";
	std::cout << ":" << std::endl;
}

void __printPadded(const String& str, unsigned width) {
	while (str.get_length() - width > 0) {
		width--;
		print(" ");
	}
	print(str.get_cstr());
}

/*! \param startNumber The number by which column and row enumeration begins
 *  \param columns How many columns the table should have
 *  \param items C-style string, each cell is a single character from the string
 *
 * Prints a string as a grid/table of characters from top to bottom, left to right.
 * The first character is on the top left, the last one is on the bottom right.
 *
 * Table is printed until a terminating zero is encountered.
 * The rows are "calculated" from the columns count and the items length.
 */
void table(const List<String>& items, unsigned columns) {
	unsigned *colWidths = new unsigned[columns];
	for (unsigned i = 0; i < items.get_count(); i++) {
		if (colWidths[i % columns] < items[i].get_length())
			colWidths[i % columns] = items[i].get_length();
	}

	// __printTableColumnHeader(columns);

	for (unsigned i = 0; i < items.get_count(); i++) {
		__printPadded(items[i], colWidths[i % columns]);
		if (i > 0 && i % columns == 0)
			printLine("");
		else if (i % columns > 0 && i % columns < columns - 1)
			print("|");
	}

	delete[] colWidths;
}

