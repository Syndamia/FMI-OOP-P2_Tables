#ifndef HEADER_CELLFORMULA
#define HEADER_CELLFORMULA

/*! \file CellFormula.h
 *  \brief Stores the declaration of class CellFormula
 */

#include "Cell.h"
#include "CellDouble.h"
#include "../Generic/List/List.hpp"
#include "../Generic/Pair/Pair.hpp"

/*! \brief A table cell which contains a formula
 *
 * Implements the Cell class by storing a formula as a String and in a dynamic List
 */
class CellFormula : public Cell {
	const List<List<Cell*>>* tableCells;
	List<CellDouble> localCells;

	List<Pair<Pair<int, int>, char>> formula;
	String rawFormula;

	const Cell* ptrByInd(Pair<int, int> loc) const;
	double calculate(unsigned index = 0) const;

public:
	CellFormula() = default;
	CellFormula(const char* str, const List<List<Cell*>>* tableCells);

	double getNumeralValue() const override;
	String getValueForPrint() const override;
	void parseAndSetValue(const char* str) override;
	void writeToFile(std::ofstream& file) override;
};

#endif
