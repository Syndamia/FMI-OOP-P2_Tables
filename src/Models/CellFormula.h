#ifndef HEADER_CELLFORMULA
#define HEADER_CELLFORMULA

#include "Cell.h"
#include "CellDouble.h"
#include "../Generic/List/List.hpp"
#include "../Generic/Pair/Pair.hpp"

class CellFormula : public Cell {
	const List<List<Cell*>>* tableCells;
	List<CellDouble> localCells;

	List<Pair<Pair<int, int>, char>> formula;
	String rawFormula;

	const Cell* ptrByInd(int firstInd, int secondInd) const;
	double calculate(unsigned index = 0) const;

public:
	CellFormula() = default;
	CellFormula(const char* str, const List<List<Cell*>>* tableCells);

	double getNumeralValue() const override;
	String getValueForPrint() const override;
	void parseAndSetValue(const char* str) override;
	void readFromFile(std::ifstream& file) override;
	void writeToFile(std::ofstream& file) override;
};

#endif
