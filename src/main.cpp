#include "UserInterface/UserInterface.h"

int main() {
	Table table(5, 5);
	table.putCell(0, 0, "Test");
	table.putCell(1, 0, "3");
	UserInterface ui(&table);
	ui.run();
}
