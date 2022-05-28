#include "CellDouble.h"
#include <cstring>

double CellDouble::getNumeralValue() {
	return value;
}

String CellDouble::getValueForPrint() {
	return String() += value;
}

void CellDouble::parseAndSetValue(const char* str) {
	value = atof(str);
}

void CellDouble::readFromFile(std::ifstream& file) {
	file >> value;
}

void CellDouble::writeToFile(std::ofstream& file) {
	file << value;
}
