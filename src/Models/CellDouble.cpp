#include "CellDouble.h"
#include <cstring>

CellDouble::CellDouble(double value) {
	this->value = value;
}

CellDouble::CellDouble(const char* str) {
	value = 0;

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

void CellDouble::writeToFile(std::ofstream& file) {
	file << value;
}
