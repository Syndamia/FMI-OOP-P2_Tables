#include "CellDouble.h"
#include <cstring>

CellDouble::CellDouble(double value) {
	this->value = value;
}

double CellDouble::getNumeralValue() const {
	return value;
}

String CellDouble::getValueForPrint() const {
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
