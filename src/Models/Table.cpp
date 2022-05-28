#include "Table.h"

Table::Table(unsigned rows, unsigned cols) {
	cells = List<List<Cell*>>(rows);
}
