#include "CellFormula.h"
#include <cstring>

double CellFormula::calculate(unsigned index) {
	switch(formula[index].right) {
		case none: return formula[index].left;
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
