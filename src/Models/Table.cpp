#include "Table.h"
#include "CellDouble.h"
#include "CellInt.h"
#include "CellString.h"
#include "CellFormula.h"
#include <cstring>

Table::Table(unsigned rows, unsigned cols) {
	cells = List<List<Cell*>>(rows);
	for (unsigned i = 0; i < rows; i++)
		cells[i] = List<Cell*>(cols);
}


bool containsNumber(const char*& str) {
	while (*str == ' ') str++;
	return ((*str == '+' || *str == '-') && (*(str + 1) >= '0' && *(str + 1) <= '9')) ||
		   (*str >= '0' && *str <= '9');
}

void Table::putCell(unsigned row, unsigned col, const char* rawValue) {
	unsigned intParse = atoi(rawValue);
	unsigned doubleParse = atof(rawValue);

	Cell* newCell;
	if (doubleParse - intParse > 0.00001 && doublePrase > 0.00001)
		newCell = new CellDouble(doubleParse);
	else if (intParse )
		newCell = 
}
