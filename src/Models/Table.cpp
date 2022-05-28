#include "Table.h"

Table::Table(unsigned rows, unsigned cols) {
	cells = List<List<Cell*>>(rows);
	for (unsigned i = 0; i < rows; i++)
		cells[i] = List<Cell*>(cols);
}
