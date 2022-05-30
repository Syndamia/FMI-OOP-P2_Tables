#ifndef MODELS_TABLE
#define MODELS_TABLE

#include "Cell.h"
#include "../Generic/List/List.hpp"
#include <fstream>

class Table {
	List<List<Cell*>> cells;
	void readFromFile(std::ifstream& inFile);

public:
	Table(const char* filePath);
	Table(unsigned rows, unsigned cols);

	unsigned get_rows() const;
	unsigned get_cols() const;

	void putCell(unsigned row, unsigned col, const char* rawValue);

	List<String> getAllCells() const;
	void saveToFile(const char* filePath) const;
};

#endif
