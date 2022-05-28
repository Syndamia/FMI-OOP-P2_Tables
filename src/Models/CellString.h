#ifndef HEADER_CELLSTRING
#define HEADER_CELLSTRING

#include "Cell.h"

class CellString : public Cell {
	String value;

public:
	CellString() = default;

	String getValueForPrint() override;
	void parseAndSetValue(const char* str) override;
	void readFromFile(const char* filePath) override;
	void saveToFile(const char* filePath) override;
};

#endif
