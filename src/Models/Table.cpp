#include "Table.h"

Table::Table(unsigned rows, unsigned cols) {
	cells = new Cell*[rows];
	for (unsigned i = 0; i < rows; i++)
		cells[i] = new Cell[cols];
}
