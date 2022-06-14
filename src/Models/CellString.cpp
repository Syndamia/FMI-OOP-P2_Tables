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

void CellString::writeToFile(std::ofstream& file) {
	file << '"';
	const char* strCpy = value.get_cstr();
}
