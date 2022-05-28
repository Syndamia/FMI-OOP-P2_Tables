#ifndef HEADER_CONSOLEINTERFACE_TOOLBOX
#define HEADER_CONSOLEINTERFACE_TOOLBOX

#include <iostream>

/*! \file Toolbox.hpp
 *  \brief Stores a wide range of functions for simpler/more automated printing.
 *
 * Adds a lot of functions for printing.
 *
 * \remark iostream is included by necessity (templated functions), you should only use the provided functions, if you can.
 */

#define MAX_LINE_WIDTH 1024

//! Clears the console screen
void clear();
//! Prints a title box
void titleBox(const char* title);
//! Prints a title sub box
void subTitleBox(const char* title);

//! Prints label, gets a whole line of input and stores it to output
void inputLineBox(const char* label, char* output, unsigned maxWidth, bool ignore = true);
//! Waits for user to press enter
void pressEnterToContinue(bool ignore = true);

//! Resets the ordered list starting number
void resetOrderedList(int starter = 1);

//! Prints a string as a table
void table(unsigned startNumber, unsigned columns, const char* items);

//! Semi-internal function that prints the spacing for sub boxes
void _printSubBoxSpacing();
//! Semi-internal function that prints the label of an input box
void _printInputBoxLabel(const char* label);
//! Semi-internal function that prints the latest ordered list index
void _printOrderedListBeginning();

//! Reads user input and stores it
template <typename T>
void read(T* storage) {
	std::cin >> storage;
}

//! Reads user input and stores it
template <typename T>
void read(T& storage) {
	std::cin >> storage;
}

//! Prints given item
template <typename T>
void print(const T* item) {
	std::cout << item;
}

//! Prints given item
template <typename T>
void print(const T& item) {
	std::cout << item;
}

//! Prints given item and an endline character
template <typename T>
void printLine(const T* item) {
	std::cout << item << std::endl;
}

//! Prints given item and an endline character
template <typename T>
void printLine(const T& item) {
	std::cout << item << std::endl;
}

//! Prints a label and then reads user input and stores it
template <typename T>
void inputBox(const char* label, T* output) {
	_printInputBoxLabel(label);
	std::cin >> *output;
}

//! Prints a label with sub box spacing and then reads user input and stores it
//! \sa _printSubBoxSpacing()
template <typename T>
void inputSubBox(const char* label, T* output) {
	_printSubBoxSpacing();
	_printInputBoxLabel(label);
	std::cin >> *output;
}

#endif
