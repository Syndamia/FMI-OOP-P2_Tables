#include "CellDouble.h"
#include <cstring>

CellDouble::CellDouble(int val) {
	value = val;
}

CellDouble::CellDouble(const String& str) {
	value = atof(str.get_cstr());
}

double CellDouble::getValue() {
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
