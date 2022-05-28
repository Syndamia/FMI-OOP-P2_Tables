#include "CellFormula.h"
#include "CellDouble.h"
#include <cstring>

CellFormula::CellFormula(const char* str, const List<List<Cell*>>* tableCells) : referencedCells(), formula(), rawFormula() {
	this->tableCells = tableCells;
	parseAndSetValue(str);
}

double CellFormula::calculate(unsigned index) {
	double lval = formula[index].left->getNumeralValue();

	if (formula[index].right & branch) {
		switch (formula[index++].right & !branch) {
			case plus   : lval += formula[index].left->getNumeralValue(); break;
			case minus  : lval -= formula[index].left->getNumeralValue(); break;
			case mult   : lval *= formula[index].left->getNumeralValue(); break;
			case div    : lval /= formula[index].left->getNumeralValue(); break;
			// case pow : lval += formula[index].left->getNumeralValue(); break;
		}
	}

	switch(formula[index].right) {
		case plus  : return lval + calculate(index++);
		case minus : return lval - calculate(index++);
		case mult  : return lval * calculate(index++);
		case div   : return lval / calculate(index++);
		case pow   :
		case none  :
		default    : return lval;
	}
}

String CellFormula::getValueForPrint() {
	return String() += calculate();
}

void CellFormula::parseAndSetValue(const char* str) {
	rawFormula = String(str);

	str++;
	while (*str == ' ') str++;
	if (*str == 'R') {
		unsigned row = atoi(++str);
	}
}

void CellFormula::readFromFile(std::ifstream& file) {
	file >> rawFormula;
}

void CellFormula::writeToFile(std::ofstream& file) {
	file << rawFormula;
}
