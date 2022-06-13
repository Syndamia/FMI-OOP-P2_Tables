#include "CellDouble.h"
#include <cstring>

CellDouble::CellDouble(double value) {
	this->value = value;
}

CellDouble::CellDouble(const char* str) {
	value = 0;
	bool negative = *str == '-';
	if (*str == '-' || *str == '+') str++;

	while (*str != '.')
		value = value * 10 + '0' - *(str++);
	str++;
	for (unsigned div = 10; *str != '\0'; div *= 10)
		value += (double)('0' - *(str++)) / div;

	if (negative) value *= -1;
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
