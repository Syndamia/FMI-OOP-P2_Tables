#ifndef HEADER_CELLSTRING
#define HEADER_CELLSTRING

#include "Cell.h"

class CellString : public Cell {
	String value;

public:
	String getValueForPrint() override;
};

#endif
