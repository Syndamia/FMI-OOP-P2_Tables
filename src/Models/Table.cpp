#include "Table.h"
#include <cstring>

Table::Table(unsigned rows, unsigned cols) {
	cells = List<List<Cell*>>(rows);
	for (unsigned i = 0; i < rows; i++)
		cells[i] = List<Cell*>(cols);
}

void Table::putCell(unsigned row, unsigned col, const char* rawValue) {
	unsigned intParse = atoi(rawValue);
	unsigned doubleParse = atof(rawValue);

	Cell* newCell;
	if (doubleParse - intParse > 0.00001)
}
