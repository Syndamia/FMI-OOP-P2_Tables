#include "UserInterface/UserInterface.h"

int main() {
	Table table(5, 5);
	table.putCell(0, 0, "8.6");
	table.putCell(0, 1, "3");
	table.putCell(0, 2, "String");
	table.putCell(0, 3, "= 3 * R0C1 + R0C0 ^ R0C1 * 9 - 10 + 1");
	// table.putCell(0, 3, "= 1 + 2 * 3 + 4 + 5");
	UserInterface ui(&table);
	ui.run();
}
