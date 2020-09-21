#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Debug.h"
#include "Sheduler.h"

int main() {
	
	srand(time(NULL));

	Sheduler sheduler = Sheduler();
	sheduler.Start();
	return 0;
}