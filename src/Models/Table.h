#ifndef MODELS_TABLE
#define MODELS_TABLE

/*! \file Table.h
 *  \brief Stores the declaration of class Table
 */

#include "Cell.h"
#include "../Generic/List/List.hpp"
#include <fstream>

/*! \brief A 2D collection of Cell instances
 */
class Table {
	List<List<Cell*>> cells;
	unsigned longestRow;
	void readFromFile(std::ifstream& inFile);

public:
	Table(const char* filePath);
	~Table();

	//! Returns count of rows
	unsigned get_rows() const;
	//! Returns largest count of columns in all rows
	unsigned get_cols() const;

	//! Parses rawValue and replaces the value at row and col with it
	void putCell(unsigned row, unsigned col, const char* rawValue);

	//! Returns a List of String with String representation of every cell in order
	List<String> getAllCells() const;
	//! Saves all cells to a text file
	void saveToFile(const char* filePath) const;
};

#endif
