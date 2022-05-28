#ifndef HEADER_CELLFORMULA
#define HEADER_CELLFORMULA

#include "Cell.h"
#include "../Generic/List/List.hpp"
#include "../Generic/Pair/Pair.hpp"

class CellFormula : public Cell {
	enum Op {
		none   = 0b0000000,
		branch = 0b0000001,
		plus   = 0b0000010,
		minus  = 0b0,
		mult   = 0b0,
		div    = 0b0,
		pow    = 0b0,
	};

	List<Cell*> referencedCells;
	List<Pair<Cell*, Op>> formula;
	String rawFormula;

	double calculate(unsigned index = 0);

public:
	CellFormula() = default;
	CellFormula(const char* str);

	double getNumeralValue() override;
	String getValueForPrint() override;
	void parseAndSetValue(const char* str) override;
	void readFromFile(std::ifstream& file) override;
	void writeToFile(std::ofstream& file) override;
};

#endif
