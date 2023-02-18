#include <river\types\string.h>

int main() {
	String x("A? B? ", false);
	x = x.add("C? ");
	x.display();
	return 0;
}