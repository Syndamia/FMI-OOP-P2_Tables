#include "CellFormula.h"
#include "CellDouble.h"
#include <cstring>

double CellFormula::calculate(unsigned index) {
	double lval = CellDouble(formula[index].left->getValue()).getValue();

	switch(formula[index].right) {
		plus: return lval + calculate(index++);
		minus: return lval - calculate(index++);
		mult: return lval * calculate(index++);
		div: return lval / calculate(index++);
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
