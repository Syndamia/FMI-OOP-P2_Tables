#include "CellInt.h"
#include <cstring>

String CellInt::getValueForPrint() {
	return value;
}

void CellInt::parseAndSetValue(const char* str) {
	value = String(str);
}

void CellInt::readFromFile(std::ifstream& file) {
	value.read(file);
}

void CellInt::writeToFile(std::ofstream& file) {
	value.write(file);
}
