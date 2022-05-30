#include "CellFormula.h"
#include "CellDouble.h"
#include <cstring>
#include <iostream>
#include <stdexcept>

const Cell* CellFormula::ptrByInd(int firstInd, int secondInd) const {
	return (firstInd < 0) ? &localCells[secondInd] : (*tableCells)[firstInd][secondInd];
}

double pow(double x, unsigned y) {
	if (y == 0) return 1;

	double res = x;
	for (unsigned i = 1; i < y; i++)
		res *= x;
	return res;
}

double CellFormula::calculate(unsigned index) {
	Cell* currCell = ptrByInd(formula[index].left);
	double lval = (c.firstInd == -1) ? localCells[c.secondInd].getNumeralValue() : (*tableCells)[c.firstInd][c.secondInd]->getNumeralValue();

	while (formula[index].right < 0) {
		double secondLval = (c.firstInd == -1) ? localCells[c.secondInd].getNumeralValue() : (*tableCells)[c.firstInd][c.secondInd]->getNumeralValue();
		switch (-formula[index].right) {
			case '+' : lval += secondLval; break;
			case '*' : lval *= secondLval; break;
			case '/' : if (secondLval == 0) throw std::logic_error("");
					   lval /= secondLval; break;
			case '^' : lval  = pow(lval, secondLval); break;
		}
	}

	double temp;
	switch(formula[index].right) {
		case '+'  : return lval + calculate(++index);
		case '*'  : return lval * calculate(++index);
		case '/'  : temp = calculate(++index);
					if (temp == 0) throw std::logic_error("");
					return lval / temp;
		case '^'  : return pow(lval, calculate(++index));
		case '\0' :
		default   : return lval;
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
