#include "CellFormula.h"
#include "CellDouble.h"
#include <cstring>

CellFormula::CellFormula(const char* str) : referencedCells(), formula(), rawFormula() {
	parseAndSetValue(str);
}

double CellFormula::calculate(unsigned index) {
	double lval = formula[index].left->getNumeralValue();

	switch(formula[index].right) {
		case plus:  return lval + calculate(index++);
		case minus: return lval - calculate(index++);
		case mult:  return lval * calculate(index++);
		case div:   return lval / calculate(index++);
		case pow:
		case none:
		default:    return lval;
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
