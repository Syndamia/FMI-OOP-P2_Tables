#include "UserInterface/UserInterface.h"

int main() {
	Table table(5, 5);
	UserInterface ui(&table);
	ui.run();
}
