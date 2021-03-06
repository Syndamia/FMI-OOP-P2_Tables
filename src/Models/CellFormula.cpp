#include "CellFormula.h"
#include "CellDouble.h"
#include <cstring>
#include <iostream>
#include <stdexcept>

const Cell* CellFormula::ptrByInd(Pair<int, int> loc) const {
	if (loc.left < 0) {
		if (loc.right < 0 || localCells.get_count() - 1 < loc.right) return nullptr;
		return &localCells[loc.right];
	}
	
	if (loc.right < 0
		|| (*tableCells).get_count() - 1 < loc.left || (*tableCells)[loc.left].get_count() - 1 < loc.right)
		return nullptr;
	return (*tableCells)[loc.left][loc.right];
}

double pow(double x, int y) {
	if (y <= 0) return 1;

	double res = x;
	for (unsigned i = 1; i < y; i++)
		res *= x;
	return res;
}

double CellFormula::calculate(unsigned index) const {
	const Cell* currCell = ptrByInd(formula[index].left);
	double numVal = (currCell == nullptr) ? 0 : currCell->getNumeralValue();

	// Handle prioritised operation
	while (formula[index].right < 0) {
		switch (-formula[index++].right) { // Prioritized operations are stored as negative characters
			case '+' : numVal += ptrByInd(formula[index].left)->getNumeralValue(); break;
			case '*' : numVal *= ptrByInd(formula[index].left)->getNumeralValue(); break;
			case '/' : if (ptrByInd(formula[index].left)->getNumeralValue() == 0) throw std::logic_error("Error: Divion by zero!");
					   numVal /= ptrByInd(formula[index].left)->getNumeralValue(); break;
			case '^' : numVal  = pow(numVal, ptrByInd(formula[index].left)->getNumeralValue()); break;
		}
	}

	double temp;
	switch(formula[index].right) {
		case '+'  : return numVal + calculate(++index);
		case '*'  : return numVal * calculate(++index);
		case '/'  : temp = calculate(++index);
					if (temp == 0) throw std::logic_error("Error: Division by zero!");
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

/*!
 * Value is recalculated every time this function is called (in case a referenced cell is changed).
 *
 * \return 0 \if Calculation failed
 * \return Calculated value \otherwise
 */
double CellFormula::getNumeralValue() const {
	try {
		return calculate();
	}
	catch (std::logic_error e) {
		return 0;
	}
}

/*!
 * Value is recalculated every time this function is called (in case a referenced cell is changed).
 *
 * \return "Error" \if Calculation failed
 * \return Calculated value as a String \otherwise
 */
String CellFormula::getValueForPrint() const {
	try {
		return String() += calculate();
	}
	catch (std::logic_error e) {
		return "Error";
	}
}

// Rough implementation of the grammar
//
// S -> WDWOS | WD.DWOS | WRDCDWOS | W
// O -> + | - | * | / | ^
// D -> D0 | D1 | ... | D9 | 0 | 1 | ... | 9
// W -> W | epsilon
//
// over the string

void W(const char*& str) {
	while (*str == ' ') str++;
}

void D(const char*& str, List<char>& buffer) {
	while (*str >= '0' && *str <= '9')
		buffer.add(*(str++));
}

void O(const char*& str, char& buffer) {
	if (*str == '+' || *str == '-' || *str == '*' || *str == '/' || *str == '^' || *str == '\0')
		buffer = *(str++);
	else buffer = -2;
}

/*!
 * Each math operation is represented with a Pair that holds indecies of cell reference
 * and a character for the operation.
 *
 * Negatve value for the operation character means it's with priority and the result get's calculated
 * immediately (rather than recursively, taking into account other values).
 *
 * \exception std::logic_error("Error: Invalid column character!") Thrown when there is something between Rx and C in cell references
 * \exception std::logic_error("Error: Invalid value!") Thrown when met value isn't a cell reference or number
 * \exception throw std::logic_error("Error: Could not find operand!") Thrown when there isn't an operator character between two values
 */
void CellFormula::parseAndSetValue(const char* str) {
	rawFormula = String(str);

	formula.clear();
	localCells.clear();
	Pair<int, int> loc;
	char currOp = -2;

	str++; // Removes = from the beginning
	while (*str != '\0') {
		List<char> buffer;
		W(str);
		if (*str == 'R') {
			D(++str, buffer);
			loc.left = atoi(buffer.raw_data()) - 1;
			if (*str != 'C') throw std::logic_error("Error: Invalid column character!");
			str++;
			buffer.clear();
			D(str, buffer);
			loc.right = atoi(buffer.raw_data()) - 1;
		}
		else if (*str >= '0' && *str <= '9') {
			D(str, buffer);
			if (*str == '.') {
				buffer.add(*str);
				D(++str, buffer);
				localCells.add(CellDouble(atof(buffer.raw_data())));
			}
			else
				localCells.add(CellDouble(atoi(buffer.raw_data())));

			loc.left = -1;
			loc.right = (int)(localCells.get_count() - 1);
		}
		else
			throw std::logic_error("Error: Invalid value!");

		W(str);
		O(str, currOp);
		if (currOp == -2) throw std::logic_error("Error: Could not find operand!");

		// Operator priority magic
		if (currOp == '^') currOp *= -1;
		else if ((currOp == '+' || currOp == '-') && formula.get_count() != 0) {
			for (unsigned i = formula.get_count() - 1; i < formula.get_count() && (formula[i].right == '*' || formula[i].right == '/'); i--)
				if (formula[i].right > 0) formula[i].right *= -1;
		}

		if (currOp == '-') { // a - b turns into a + -1 * b
			formula.add({loc, '+'});
			localCells.add(CellDouble(-1.0));
			loc.left = -1;
			loc.right = (int)(localCells.get_count() - 1);
			currOp = '*' * -1;
		}

		formula.add(Pair<Pair<int, int>, char>(loc, currOp));
	}
}

void CellFormula::writeToFile(std::ofstream& file) {
	file << '"' << rawFormula << '"';
}
