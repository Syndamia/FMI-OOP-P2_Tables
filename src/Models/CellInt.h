#ifndef HEADER_CELLINT
#define HEADER_CELLINT

/*! \file CellInt.h
 *  \brief Stores the declaration of class Cell
 */

#include "Cell.h"

/*! \brief  A table cell which contains an integer
 *
 * Impelements the Cell class by implementing a value of type int
 */
class CellInt : public Cell {
	int value;

public:
	CellInt() = default;
	CellInt(int value);
	CellInt(const char* str);

	double getNumeralValue() const override;
	String getValueForPrint() const override;
	void parseAndSetValue(const char* str) override;
	void writeToFile(std::ofstream& file) override;
};

#endif
