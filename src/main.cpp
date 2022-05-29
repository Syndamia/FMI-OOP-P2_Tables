#include "UserInterface/UserInterface.h"

int main() {
	Table table(5, 5);
	table.putCell(0, 0, "8");
	table.putCell(0, 1, "3");
	table.putCell(0, 2, "= 9 * 10 + R0C0 * R0C1");
	UserInterface ui(&table);
	ui.run();
}
