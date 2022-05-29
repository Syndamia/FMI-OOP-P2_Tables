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

void __printTableColumnHeader(unsigned start, unsigned count) {
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

void __printPadded(const String& str) {

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
void table(const List<String>& items) {
	unsigned *paddings = new unsigned[items.get_count()];
	__printTableColumnHeader(startNumber, columns);

	__printTableHeaderNumber(startNumber);
	for (unsigned i = 0, colInd = 0, rowInd = 0; items[i] != '\0'; i++, (++colInd) %= columns) {
		if (colInd == 0 && i != 0) {
			std::cout << ":" << std::endl;
			__printTableLine(columns);
			__printTableHeaderNumber((++rowInd) + startNumber);
		}

		std::cout << ((colInd == 0) ? "║ " : "| ") << items[rowInd * columns + colInd] << " ";
	}
	std::cout << ":" << std::endl;
}

