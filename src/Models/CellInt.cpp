#include "CellInt.h"
#include <cstring>

CellInt::CellInt(int value) {
	this->value = value;
}

CellInt::CellInt(const char* str) {
	value = 0;
	while (*str != '\0')
		value = value * 10 + '0' - *(str++);
}

double CellInt::getNumeralValue() const {
	return value;
}

String CellInt::getValueForPrint() const {
	return String() += value;
}

void CellInt::parseAndSetValue(const char* str) {
	value = atoi(str);
}

void CellInt::writeToFile(std::ofstream& file) {
	file << value;
}
