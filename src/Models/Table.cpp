#include "Table.h"
#include "CellDouble.h"
#include "CellInt.h"
#include "CellString.h"
#include "CellFormula.h"
#include <cstring>
#include <fstream>
#include <exception>
#include <stdexcept>

#include <iostream> // TODO: remove

// Rough implementation of the grammar
//
// S -> W"=A"W | W"A"W | WPDW | WPD.DW
// A -> Aa | Ab | ... | AZ | A0 | A1 | ... | A* | ... | a | b | ... | epsilon
// D -> D0 | D1 | ... | D9 | 0 | 1 | ... | 9
// P -> + | - | epsilon
// W -> W  | epsilon
//
// over the input file stream

void W(std::ifstream& in) {
	while (in.peek() == ' ') in.get();
}

void P(std::ifstream& in, List<char>& buffer) {
	if (in.peek() == '-' || in.peek() == '+')
		buffer.add(in.get());
}

void D(std::ifstream& in, List<char>& buffer) {
	while (in.peek() >= '0' && in.peek() <= '9')
		buffer.add(in.get());
}

void A(std::ifstream& in, List<char>& buffer) {
	while ((in.peek() >= ' ' && in.peek() <= '~') && in.peek() == '"')
		buffer.add(in.get());
}

void throwException(std::ifstream& inFile, unsigned row) {
	throw std::logic_error((
			(((((String("Error: Invalid character \"") += inFile.peek())
			+= "\" at row ") += row) += "\" and column ") += ((int)inFile.tellg() / row))
		).get_cstr());
}

void Table::readFromFile(std::ifstream& inFile) {
	unsigned row = 0;
	cells.add(List<Cell*>());

	while (inFile.peek() != EOF) {
		if (inFile.peek() == '\0') {
			row++;
			inFile.get();
			cells.add(List<Cell*>());
			continue;
		}

		List<char> buffer;

		W(inFile);
		if (inFile.peek() == '"') {
			inFile.get();
			A(inFile, buffer);
			buffer.add('\0');
			W(inFile);

			if (inFile.peek() != ',') throwException(inFile, row);

			cells[row].add((buffer[0] == '=')
				? (Cell*)new CellFormula(buffer.raw_data(), &cells)
				: (Cell*)new CellString(buffer.raw_data()));
		}
		else {
			P(inFile, buffer);
			D(inFile, buffer);
			if (inFile.peek() == '.') {
				buffer.add(inFile.get());
				D(inFile, buffer);
				cells[row].add((Cell*)new CellDouble(buffer.raw_data()));
			}
			else
				cells[row].add((Cell*)new CellInt(buffer.raw_data()));
		}
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
	return cells.get_count();
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
	for (unsigned i = 0; i < cells.get_count(); i++) {
		for (unsigned j = 0; j < cells[i].get_length(); j++) {
			std::cout << i << ' ' << j << std::endl;
			if (cells[i][j] == nullptr) toRet.add("");
			else toRet.add(cells[i][j]->getValueForPrint());
		}
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
