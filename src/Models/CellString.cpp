#include "CellString.h"

String CellString::getValueForPrint() {
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
