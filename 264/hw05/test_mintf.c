/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
#include <stdlib.h>
#include "mintf.h"
#include <limits.h>

int main(int argc, char *argv[]){
	// Test 00: empty test
	// Expect: ""
	
	// Test 01: empty string
	mintf("");
	// Expect: ""

	// Test 02: phrase with no format
	mintf("Hello World\n");
	// Expect: "Hello World"
	
	// Test 03: decimal integer
	mintf("%d\n", 3);
	// Expect: "3"
	
	// Test 04: hexadecimal max integer
	mintf("%x\n", 2147483647);
	// Expect: "0x7fffffff"

	// Test 05: binary print
	mintf("%b\n%b\n", INT_MIN,INT_MAX);
	
	// Test 06: $sign print
	mintf("%$\n", -2);
	
	// Test 07: character print
	mintf("%c %c\n", 65, 'B');

	// Test 08: String print
	mintf("%s\n", "agh", "extra");
	print_integer(INT_MIN, 2, "0b");
	// Test 09: percent sign
	mintf("\n%% %\n");
	
	// Test 10: limits and escape combination
	mintf("All 3 forms dec: %d, hex %x, bin %b, should not work %o, \n", INT_MIN, INT_MIN, INT_MIN, 7);
	return EXIT_SUCCESS;
}
