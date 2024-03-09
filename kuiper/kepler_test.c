#include "kepler.h"

int main(int argc, char** argv) {
	kepler_instruction test = ki_as_struct(0xDEADBEEF);
	raw_instruction raw = ki_as_raw(0xDEADBEEF);
	char* test2 = ki_as_string(0xDEADBEEF);
	printf("%s\n", test2);
	return 0;
}