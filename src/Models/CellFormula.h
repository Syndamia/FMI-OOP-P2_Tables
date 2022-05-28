#ifndef HEADER_CELLFORMULA
#define HEADER_CELLFORMULA

#include "Cell.h"
#include "../Generic/List/List.hpp"
#include "../Generic/Pair/Pair.hpp"

class CellFormula : public Cell {
	enum Op {
		none,
		plus,
		minus,
		mult,
		div,
		pow,
	};

	List<Cell*> referencedCells;
	List<Pair<Cell*, Op>> formula;
	String rawFormula;

	double calculate(unsigned index = 0);

	double getNumeralValue() override;
public:
	CellFormula() = default;

	String getValueForPrint() override;
	void parseAndSetValue(const char* str) override;
	void readFromFile(std::ifstream& file) override;
	void writeToFile(std::ofstream& file) override;
};

#endif
