#include "Table.h"
#include "CellDouble.h"
#include "CellInt.h"
#include "CellString.h"
#include "CellFormula.h"
#include <cstring>
#include <fstream>
#include <exception>

Table::Table(const char* filePath) {
	std::ifstream inFile(filePath);
	if (inFile.is_open())
		throw new std::logic_error("Could now open file!");
	cells = List<List<Cell*>>();
}

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

#define abs(a) ((a < 0) ? -a : a)
#include <iostream>
void Table::putCell(unsigned row, unsigned col, const char* rawValue) {
	Cell* newCell;

	if (containsNumber(rawValue)) {
		double doubleParse = atof(rawValue);
		unsigned intPart = abs(doubleParse);

		newCell = (abs(doubleParse) - intPart > 0.00001)
					? (Cell*)new CellDouble(doubleParse) : (Cell*)new CellInt(intPart);
	}
	else {
		newCell = (*rawValue == '=')
					? (Cell*)new CellFormula(rawValue, &cells) : (Cell*)new CellString(rawValue);
	}

	if (cells[row][col] != nullptr)
		delete cells[row][col];
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
