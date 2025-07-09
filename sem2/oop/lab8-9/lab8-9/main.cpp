#include <iostream>
#include <crtdbg.h>
#include "util.h"
#include "tests.h"


int main() {
	TestAll();
	Console c;
	c.Run();
	_CrtDumpMemoryLeaks();
}