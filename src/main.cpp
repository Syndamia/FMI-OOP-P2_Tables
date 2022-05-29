#include "UserInterface/UserInterface.h"

int main() {
	Table table(5, 5);
	table.putCell(0, 0, "Test");
	UserInterface ui(&table);
	ui.run();
}
