#include "Random.h"

int GenerateRandNumInRange(int start, int end) {
	return start + rand() % (end - start);
}