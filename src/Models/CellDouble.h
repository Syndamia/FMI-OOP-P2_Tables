#ifndef HEADER_CELLDOUBLE
#define HEADER_CELLDOUBLE

/*! \file Cell.h
 *  \brief Stores the declaration of class CellDouble
 */

#include "Cell.h"

/*! \brief A table cell which contains a double-precision floating point number
 *
 * Implements the Cell class by implementing a value of type double.
 */
class CellDouble : public Cell {
	double value;

public:
	CellDouble() = default;
	CellDouble(double value);
	CellDouble(const char* str);

	double getNumeralValue() const override;
	String getValueForPrint() const override;
	void parseAndSetValue(const char* str) override;
	void writeToFile(std::ofstream& file) override;
};

#endif
