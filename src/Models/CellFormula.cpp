#include "CellFormula.h"
#include "CellDouble.h"
#include <cstring>

double CellFormula::calculate(unsigned index) {
	double lval = CellDouble(formula[index].left->getValue()).getValue();

	switch(formula[index].right) {
		case plus:  return lval + calculate(index++);
		case minus: return lval - calculate(index++);
		case mult:  return lval * calculate(index++);
		case div:   double rval = calculate(index++);
			   if (rval == 0) throw std::overflow_error("Divide by zero exception");
			   return lval / rval;
		default: return lval;
	}
}

String CellFormula::getValueForPrint() {
	double result = calculate();

	return "";
}

void CellFormula::parseAndSetValue(const char* str) {
}

void CellFormula::readFromFile(std::ifstream& file) {
	file >> rawFormula;
}

void CellFormula::writeToFile(std::ofstream& file) {
	file << rawFormula;
}
