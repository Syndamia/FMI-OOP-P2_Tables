#include "CellFormula.h"
#include "CellDouble.h"
#include <cstring>

CellFormula::CellFormula(const char* str, const List<List<Cell*>>* tableCells) : referencedCells(), formula(), rawFormula() {
	this->tableCells = tableCells;
	parseAndSetValue(str);
}

double CellFormula::calculate(unsigned index) {
	double lval = formula[index].left->getNumeralValue();

	if (formula[index].right < 0) {
		switch (-formula[index++].right) {
			case '+'    : lval += formula[index].left->getNumeralValue(); break;
			case '-'    : lval -= formula[index].left->getNumeralValue(); break;
			case '*'    : lval *= formula[index].left->getNumeralValue(); break;
			case '/'    : lval /= formula[index].left->getNumeralValue(); break;
			// case pow : lval += formula[index].left->getNumeralValue(); break;
		}
	}

	switch(formula[index].right) {
		case '+'  : return lval + calculate(index++);
		case '-'  : return lval - calculate(index++);
		case '*'  : return lval * calculate(index++);
		case '/'  : return lval / calculate(index++);
		case '^'  :
		case '\0' :
		default   : return lval;
	}
}

String CellFormula::getValueForPrint() {
	return String() += calculate();
}

void CellFormula::parseAndSetValue(const char* str) {
	rawFormula = String(str);

	Cell* cellToAdd;
	char currOp;

	while (*str != '\0') {
		str++;
		while (*str == ' ') str++;
		if (*str == 'R') {
			unsigned row = atoi(++str);
			while (*str != 'C') str++;
			unsigned col = atoi(++str);
			while (*str != ' ') str++;

			cellToAdd = (*tableCells)[row][col];
			currOp = *str;
		}
		else {
			double val = atof(str);
			while ((*str >= '0' && *str <= '9') || *str == ' ') str++;

			localCells.add(CellDouble(val));
			cellToAdd = &localCells[localCells.get_count() - 1];
			currOp = *str;
		}

		if (currOp == '^') currOp *= -1;
		else if ((currOp == '+' || currOp == '-') && formula.get_count() != 0) {
			Pair<Cell*, char>& prev = formula[formula.get_count() - 1];
			if (prev.right == '*' || prev.right == '/') prev.right *= -1;
		}

		formula.add({cellToAdd, currOp});
	}
}

void CellFormula::readFromFile(std::ifstream& file) {
	file >> rawFormula;
}

void CellFormula::writeToFile(std::ofstream& file) {
	file << rawFormula;
}
