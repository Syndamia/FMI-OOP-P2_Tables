#include "Table.h"
#include "CellDouble.h"
#include "CellInt.h"
#include "CellString.h"
#include "CellFormula.h"
#include <cstring>
#include <fstream>
#include <exception>
#include <stdexcept>

unsigned countOfCommas(std::ifstream& file) {
	unsigned commaCount = 0;
	while (file.peek() != '\n') {
		if (file.get() == ',') commaCount++;
	}
	return commaCount;
}

#define abs(a) ((a < 0) ? -a : a)
#define isDigit(a) (a >= '0' && a <= '9')
#define fileLocationExceptionMsg(mainMessage, lines, columns) (((String(mainMessage) += (unsigned)(lines)) += " and col ") += (unsigned)(columns)).get_cstr()

bool containsNumber(const char*& str) {
	while (*str == ' ') str++;
	return ((*str == '+' || *str == '-') && (*(str + 1) >= '0' && *(str + 1) <= '9')) ||
		   (*str >= '0' && *str <= '9'); // + or -, followed by digit, or it just a digit
}

Cell* Table::createCellByParsing(const char* rawValue) {
	if (containsNumber(rawValue)) {
		double doubleParse = atof(rawValue);
		unsigned intPart = abs(doubleParse);

		return (abs(doubleParse) - intPart > 0.00001)
					? (Cell*)new CellDouble(doubleParse) : (Cell*)new CellInt(intPart);
	}

	return (*rawValue == '=')
				? (Cell*)new CellFormula(rawValue, &cells) : (Cell*)new CellString(rawValue);
}

void Table::readFromFile(std::ifstream& inFile) {
	unsigned commaCount = countOfCommas(inFile);
	unsigned colInd = 0;
	cells.add(List<Cell*>());
	while (!inFile.eof()) {
		while (inFile.peek() == ' ') inFile.get();

		if (inFile.peek() == ',') {
			colInd++;
			inFile.get();
		}
		else if (inFile.peek() == '\n') {
			cells.add(List<Cell*>(commaCount));
			colInd = 0;
			inFile.get();
		}
		else if (inFile.peek() == '-' || inFile.peek() == '+' || isDigit(inFile.peek())) {
			unsigned numberStart = inFile.tellg();

			if (inFile.peek() == '-' || inFile.peek() == '+') inFile.get();
			if (isDigit(inFile.peek()))
				throw std::logic_error(fileLocationExceptionMsg("Error: Expected digit but got something else at row ", cells.get_count(), inFile.tellg() % cells.get_count() + 1));
			while (isDigit(inFile.peek())) inFile.get();
			if (inFile.peek() != '.') {
				inFile.get();
				while (isDigit(inFile.peek())) inFile.get();
			}
			if (inFile.peek() != ' ' && inFile.peek() != ',' && inFile.peek() != '\n')
		}
	}
}

Table::Table(const char* filePath) {
	std::ifstream inFile(filePath);
	if (inFile.is_open())
		throw std::logic_error("Could now open file!");
	cells = List<List<Cell*>>();
	readFromFile(inFile);
	inFile.close();
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

void Table::putCell(unsigned row, unsigned col, const char* rawValue) {
	Cell* newCell = createCellByParsing(rawValue);
	
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
