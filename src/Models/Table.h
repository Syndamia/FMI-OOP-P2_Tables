#ifndef MODELS_TABLE
#define MODELS_TABLE

#include "Cell.h"
#include "../Generic/List/List.hpp"

class Table {
	List<List<Cell*>> cells;

public:
	Table(const char* filePath);
	Table(unsigned rows, unsigned cols);
	unsigned get_cols() const;

	void putCell(unsigned row, unsigned col, const char* rawValue);
	List<String> getAllCells() const;
};

#endif
