#include "CellFormula.h"
#include "CellDouble.h"
#include <cstring>
#include <iostream>
#include <stdexcept>

const Cell* CellFormula::ptrByInd(Pair<int, int> loc) const {
	return (loc.left < 0) ? &localCells[loc.right] : (*tableCells)[loc.left][loc.right];
}

double pow(double x, unsigned y) {
	if (y == 0) return 1;

	double res = x;
	for (unsigned i = 1; i < y; i++)
		res *= x;
	return res;
}

double CellFormula::calculate(unsigned index) const {
	const Cell* currCell = ptrByInd(formula[index].left);
	double numVal = currCell->getNumeralValue();

	while (formula[index].right < 0) {
		switch (-formula[index].right) {
			case '+' : numVal += ptrByInd(formula[index].left)->getNumeralValue(); break;
			case '*' : numVal *= ptrByInd(formula[index].left)->getNumeralValue(); break;
			case '/' : if (ptrByInd(formula[index].left)->getNumeralValue() == 0) throw std::logic_error("");
					   numVal /= ptrByInd(formula[index].left)->getNumeralValue(); break;
			case '^' : numVal  = pow(numVal, ptrByInd(formula[index].left)->getNumeralValue()); break;
		}
	}

	double temp;
	switch(formula[index].right) {
		case '+'  : return numVal + calculate(++index);
		case '*'  : return numVal * calculate(++index);
		case '/'  : temp = calculate(++index);
					if (temp == 0) throw std::logic_error("");
					return numVal / temp;
		case '^'  : return pow(numVal, calculate(++index));
		case '\0' :
		default   : return numVal;
	}
}

CellFormula::CellFormula(const char* str, const List<List<Cell*>>* tableCells) : localCells(), formula(), rawFormula() {
	this->tableCells = tableCells;
	CellFormula::parseAndSetValue(str);
}

#include <iostream>

double CellFormula::getNumeralValue() const {
	try {
		return calculate();
	}
	catch (std::logic_error) {
		return 0;
	}
}

String CellFormula::getValueForPrint() const {
	try {
		return String() += calculate();
	}
	catch (std::logic_error) {
		return "Error";
	}
}

void CellFormula::parseAndSetValue(const char* str) {
	rawFormula = String(str);

	CellLoc cellToAdd;
	char currOp;

	while (*str != '\0') {
		str++;
		while (*str == ' ') str++;
		if (*str == 'R') {
			int row = atoi(++str);
			while (*str != 'C') str++;
			int col = atoi(++str);
			while (*str != ' ' && *str != '\0') str++;
			while (*str == ' ') str++;

			currOp = *str;
			cellToAdd = {row, col};
		}
		else {
			double val = atof(str);
			while ((*str >= '0' && *str <= '9') || *str == ' ' || *str == '.') str++;

			currOp = *str;
			localCells.add(CellDouble(val));
			cellToAdd = {-1, (int)(localCells.get_count() - 1)};
		}

		if (currOp == '^') currOp *= -1;
		else if ((currOp == '+' || currOp == '-') && formula.get_count() != 0) {
			for (unsigned i = formula.get_count() - 1; i < formula.get_count() && (formula[i].right == '*' || formula[i].right == '/'); i--)
				if (formula[i].right > 0) formula[i].right *= -1;
		}

		if (currOp == '-') {
			formula.add({cellToAdd, '+'});
			localCells.add(CellDouble(-1.0));
			formula.add({{-1, (int)(localCells.get_count() - 1)}, '*' * -1});
		}
		else formula.add({cellToAdd, currOp});
	}
}

void CellFormula::readFromFile(std::ifstream& file) {
	file >> rawFormula;
}

void CellFormula::writeToFile(std::ofstream& file) {
	file << rawFormula;
}
