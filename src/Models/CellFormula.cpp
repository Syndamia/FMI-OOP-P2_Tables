#include "CellFormula.h"
#include "CellDouble.h"
#include <cstring>

double CellFormula::calculate(unsigned index) {
	double lval = CellDouble(formula[index].left->getValue()).getNumeralValue();

	switch(formula[index].right) {
		case plus:  return lval + calculate(index++);
		case minus: return lval - calculate(index++);
		case mult:  return lval * calculate(index++);
		case div:   return lval / calculate(index++);
		default: return lval;
	}
}

String CellFormula::getValueForPrint() {
	return String() += calculate();
}

void CellFormula::parseAndSetValue(const char* str) {
	//TODO
}

void CellFormula::readFromFile(std::ifstream& file) {
	file >> rawFormula;
}

void CellFormula::writeToFile(std::ofstream& file) {
	file << rawFormula;
}
