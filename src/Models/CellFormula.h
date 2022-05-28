#ifndef HEADER_CELLFORMULA
#define HEADER_CELLFORMULA

#include "Cell.h"
#include "../Generic/List/List.hpp"
#include "../Generic/Pair/Pair.hpp"

class CellFormula : public Cell {
	enum Op {
		none   = 0b000000,
		branch = 0b000001,
		plus   = 0b000010,
		minus  = 0b000100,
		mult   = 0b001000,
		div    = 0b010000,
		pow    = 0b100000,
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
