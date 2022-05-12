#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "miniunit.h"
#include "smintf.h"
#define mu_check_smintf(expected, ...)              \
	do {                                            \
		char* actual = smintf(__VA_ARGS__);         \
		mu_check_strings_equal((expected), (actual));  \
		free(actual);                               \
	} while(false)\

int _test() {
	mu_start();
	mu_check_smintf("agh", "agh");
	mu_check_smintf("%", "%");
    mu_check_smintf("-12aghh", "%daghh", -12);
    mu_check_smintf("%z%", "%z%");
    mu_check_smintf("-$4.12noot%", "%$noot%", -412);
	mu_end();
}
int _test2() {
	mu_start();
	mu_check_smintf("Hex: 0x20d, Dec: 525, Bin: 0b1000001101","Hex: %x, Dec: %d, Bin: %b", 525,525,525);
	mu_check_smintf("-$0.01 agh c %%", "%$ %s %c %%%", -1, "agh", 'c');
	mu_end();
}
	
int main(int argc, char* arg[]) {
	char* ag = smintf("Hex: %x, Dec: %d, Bin: %b", INT_MAX,INT_MAX,-INT_MAX);
	printf("%s\n", ag);
	free(ag);
	mintf("%d, %x, %b\n", INT_MAX, INT_MAX, -INT_MAX);
	mintf("%d, %x, %b\n", INT_MIN, INT_MIN, INT_MIN);
	mintf("%s %c\n%", "agh", 'c');
	mintf("%$, 100%, %%, %_\n", -1);	
	mu_run(_test);
	mu_run(_test2);
	return EXIT_SUCCESS;
}
