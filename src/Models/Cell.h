#ifndef HEADER_CELL
#define HEADER_CELL

/*! \file Cell.h
 *  \brief Stores the declaration of class Cell
 */

#include <fstream>
#include "../Generic/String/String.h"

/*! \brief Generic class for each cell in a table
 */
class Cell {
public:
	//! Returns the value of the cell as a double-precision floating point number
	virtual double getNumeralValue() const = 0;
	//! Returns the value of the cell as a String
	virtual String getValueForPrint() const = 0;
	//! Parses given C-style string and stores value
	virtual void parseAndSetValue(const char* str) = 0;
	//! Writes value to a text file
	virtual void writeToFile(std::ofstream& file) = 0;

	virtual ~Cell() = default;
};

#endif
