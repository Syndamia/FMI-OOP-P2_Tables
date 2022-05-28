#ifndef MODELS_TABLE
#define MODELS_TABLE

#include "Cell.h"
#include "../Generic/List/List.hpp"

class Table {
	Cell** cells;
	List<List<Cell>> constantsCells;

public:
	Table(unsigned rows, unsigned cols);

	void putCell(unsigned row, unsigned col, const char* rawValue);
	String getAllCells();
};

#endif
