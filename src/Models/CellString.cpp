#include "CellString.h"
#include <cstring>

CellString::CellString(const char* str) {
	if (*str == '"') str++;
	value = String(str);
	if (value[value.get_length() - 1] != '"')
		throw std::logic_error("Error: Missing closing bracket!");

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
	file << '"' << value << '"';
}
