#include "CellString.h"

String CellString::getValueForPrint() {
	return value;
}

void CellString::parseAndSetValue(const char* str) {
	value = String(str);
}
