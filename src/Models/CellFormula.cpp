#include "CellFormula.h"
#include <cstring>

String CellFormula::getValueForPrint() {
	Cell* a = 3;
	return String() += value;
}

void CellFormula::parseAndSetValue(const char* str) {
}

void CellFormula::readFromFile(std::ifstream& file) {
	file >> rawFormula;
}

void CellFormula::writeToFile(std::ofstream& file) {
	file << rawFormula;
}
