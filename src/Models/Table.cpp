#include "Table.h"
#include "CellDouble.h"
#include "CellInt.h"
#include "CellString.h"
#include "CellFormula.h"
#include <cstring>
#include <fstream>
#include <exception>
#include <stdexcept>

#define FLOATING_POINT_PRECISION 0.00001f

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

void Table::readFromFile(std::ifstream& inFile) {
	unsigned commaCount = countOfCommas(inFile);
	unsigned colInd = 0;
	cells.add(List<Cell*>());
	while (inFile.peek() != EOF) {
		while (inFile.peek() == ' ') inFile.get();

		// Entering a new cell on the current row
		if (inFile.peek() == ',') {
			colInd++;
			inFile.get();
			if (inFile.peek() == ',' || inFile.peek() == '\n')
				cells[cells.get_count() + 1].add(nullptr);
		}
		// Entering a new row
		else if (inFile.peek() == '\n') {
			cells.add(List<Cell*>(commaCount));
			colInd = 0;
			inFile.get();
		}
		// Parsing number
		else if (inFile.peek() == '-' || inFile.peek() == '+' || isDigit(inFile.peek())) {
			int whole = 0;
			unsigned exponent = 1;

			if (inFile.peek() == '-' || inFile.peek() == '+') {
				inFile.get();
				if (inFile.peek() == '-') whole *= -1;
			}

			if (isDigit(inFile.peek()))
				throw std::logic_error(fileLocationExceptionMsg("Error: Expected digit but got something else at row ", cells.get_count(), inFile.tellg() % cells.get_count() + 1));

			// Parsing digits of whole number/whole part of floating point number
			while (isDigit(inFile.peek())) {
				(whole *= 10) += inFile.get() - '0';
			}
			// Parsing digits of potential floating point number
			if (inFile.peek() != '.') {
				inFile.get();
				while (isDigit(inFile.peek())) {
					inFile.get();
					exponent *= 10;
				}
			}

			if (inFile.peek() != ' ' && inFile.peek() != ',' && inFile.peek() != '\n')
				throw std::logic_error(fileLocationExceptionMsg("Error: Expected space, comma or newline but got something else at row ", cells.get_count(), inFile.tellg() % cells.get_count() + 1));

			if (exponent == 1)
				cells[cells.get_count() - 1].add(new CellInt(whole));
			else
				cells[cells.get_count() - 1].add(new CellDouble((double)whole / exponent));
		}
		// Parsing string or formula
		else if (inFile.peek() == '"') {
			String res;
			inFile.get();
			while (inFile.peek() != '"') {
				if (inFile.peek() == '\\') {
					inFile.get();
				}
				res += inFile.get();
			}
			
			if (*res.get_cstr() == '=')
				cells[cells.get_count() - 1].add(new CellFormula(res.get_cstr(), &cells));
			else
				cells[cells.get_count() - 1].add(new CellString(res.get_cstr()));
		}
		else
			throw std::logic_error(fileLocationExceptionMsg("Error: Could not determine type of value at row ", cells.get_count(), inFile.tellg() % cells.get_count() + 1));
	}
}
#include <iostream>
Table::Table(const char* filePath) {
	std::ifstream inFile(filePath);
	if (!inFile.is_open())
		throw std::logic_error("Could not open file!");
	cells = List<List<Cell*>>();
	readFromFile(inFile);
	inFile.close();
}

Table::~Table() {
	for (unsigned i = 0; i < cells.get_length(); i++) {
		for (unsigned j = 0; j < cells.get_length(); j++) {
			delete cells[i][j];
		}
	}
}

unsigned Table::get_rows() const {
	return cells.get_length();
}

unsigned Table::get_cols() const {
	return cells[0].get_length();
}

void Table::putCell(unsigned row, unsigned col, const char* rawValue) {
	Cell* newCell;

	if (containsNumber(rawValue)) {
		double doubleParse = atof(rawValue);
		unsigned intPart = abs(doubleParse);

		newCell = (abs(doubleParse) - intPart > FLOATING_POINT_PRECISION)
					? (Cell*)new CellDouble(doubleParse) : (Cell*)new CellInt(intPart);
	}
	else if (*rawValue == '"') {
		rawValue++;
		newCell = (*rawValue == '=')
					? (Cell*)new CellFormula(rawValue, &cells) : (Cell*)new CellString(rawValue);
	}
	else
		throw std::logic_error("Error: Could not determine data type.");

	
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

void Table::saveToFile(const char* filePath) const {
	std::ofstream outFile(filePath);
	if (!outFile.is_open())
		throw std::logic_error("Could not open file!");

	for (unsigned i = 0; i < cells.get_count(); i++) {
		for (unsigned j = 0; j < cells.get_count(); j++) {
			if (cells[i][j] != nullptr)
				cells[i][j]->writeToFile(outFile);
			outFile << ',';
		}
		outFile << '\n';
	}
	outFile.close();
}
