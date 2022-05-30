#include "CellString.h"
#include <cstring>

CellString::CellString(const char* str) {
	value = String(str);
}

double CellString::getNumeralValue() const {
	return atof(value.get_cstr());
}

String CellString::getValueForPrint() const {
	return value;
}

void CellString::parseAndSetValue(const char* str) {
	value = String(str);
}

void CellString::readFromFile(std::ifstream& file) {
	value.read(file);
}

void CellString::writeToFile(std::ofstream& file) {
	value.write(file);
}
