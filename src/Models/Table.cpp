#include "Table.h"
#include "CellDouble.h"
#include "CellInt.h"
#include "CellString.h"
#include "CellFormula.h"
#include <cstring>

Table::Table(unsigned rows, unsigned cols) {
	if (rows == 0 || cols == 0)
		return;

	cells = List<List<Cell*>>(rows);
	for (unsigned i = 0; i < rows; i++)
		cells[i] = List<Cell*>(cols);
}

unsigned Table::get_cols() const {
	return cells[0].get_length();
}

bool containsNumber(const char*& str) {
	while (*str == ' ') str++;
	return ((*str == '+' || *str == '-') && (*(str + 1) >= '0' && *(str + 1) <= '9')) ||
		   (*str >= '0' && *str <= '9'); // + or -, followed by digit, or it just a digit
}

void Table::putCell(unsigned row, unsigned col, const char* rawValue) {
	Cell* newCell;

	if (containsNumber(rawValue)) {
		double intParse = atoi(rawValue);
		double doubleParse = atof(rawValue);

		newCell = (doubleParse - intParse > 0.00001 && doubleParse > 0.00001)
					? (Cell*)new CellDouble(doubleParse) : (Cell*)new CellInt(intParse);
	}
	else {
		newCell = (*rawValue == '=')
					? (Cell*)new CellFormula(rawValue, &cells) : (Cell*)new CellString(rawValue);
	}

	cells[row][col] = newCell;
}

List<String> Table::getAllCells() const {
	List<String> toRet;
	for (unsigned i = 0; i < cells.get_length(); i++) {
		for (unsigned j = 0; j < cells[i].get_length(); j++)
			if (cells[i][j] == nullptr)
				toRet.add("");
			else toRet.add(cells[i][j]->getValueForPrint());
	}
	return toRet;
}
