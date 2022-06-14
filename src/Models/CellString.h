#ifndef HEADER_CELLSTRING
#define HEADER_CELLSTRING

/*! \file CellString.h
 *  \brief Stores the declaration of class CellString
 */

#include "Cell.h"

/*! \brief A table cell which contains a String value
 */
class CellString : public Cell {
	String value;

public:
	CellString() = default;
	CellString(const char* str);

	double getNumeralValue() const override;
	String getValueForPrint() const override;
	void parseAndSetValue(const char* str) override;
	void writeToFile(std::ofstream& file) override;
};

#endif
