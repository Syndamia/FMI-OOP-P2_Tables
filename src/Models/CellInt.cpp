#include "CellInt.h"
#include <cstring>

CellInt::CellInt(int value) {
	this->value = value;
}

String CellInt::getValueForPrint() {
	return String() += value;
}

void CellInt::parseAndSetValue(const char* str) {
	value = atoi(str);
}

void CellInt::readFromFile(std::ifstream& file) {
	file >> value;
}

void CellInt::writeToFile(std::ofstream& file) {
	file << value;
}
