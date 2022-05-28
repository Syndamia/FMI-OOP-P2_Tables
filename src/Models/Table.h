#ifndef MODELS_TABLE
#define MODELS_TABLE

#include "Cell.h"
#include "../Generic/List/List.hpp"

class Table {
	List<List<Cell>> cells;
	List<List<Cell>> constantsCells;
};

#endif
