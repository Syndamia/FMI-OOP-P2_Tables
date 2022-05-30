#ifndef HEADER_CELLFORMULA
#define HEADER_CELLFORMULA

#include "Cell.h"
#include "CellDouble.h"
#include "../Generic/List/List.hpp"
#include "../Generic/Pair/Pair.hpp"

class CellFormula : public Cell {
	struct CellLoc {
		int firstInd;
		int secondInd;
	};
	const List<List<Cell*>>* tableCells;
	List<CellDouble> localCells;

	List<Pair<CellLoc, char>> formula;
	String rawFormula;

	double calculate(unsigned index = 0);

public:
	CellFormula() = default;
	CellFormula(const char* str, const List<List<Cell*>>* tableCells);

	double getNumeralValue() override;
	String getValueForPrint() override;
	void parseAndSetValue(const char* str) override;
	void readFromFile(std::ifstream& file) override;
	void writeToFile(std::ofstream& file) override;
};

#endif
