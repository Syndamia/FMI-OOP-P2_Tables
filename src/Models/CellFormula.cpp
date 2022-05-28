#ifndef HEADER_CELLFORMULA
#define HEADER_CELLFORMULA

#include "Cell.h"
#include "../Generic/List/List.hpp"

class CellFormula : public Cell {
	List<Cell*> referencedCells;
	String rawFormula;
	double value;

public:
	CellFormula() = default;

	String getValueForPrint() override;
	void parseAndSetValue(const char* str) override;
	void readFromFile(std::ifstream& file) override;
	void writeToFile(std::ofstream& file) override;
};

#endif
