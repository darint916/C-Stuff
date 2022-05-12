/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
#include <stdlib.h>
#include "mintf.h"

int main(int argc, char *argv[]){
	// Test 00: empty test
	// Expect: ""
	
	// Test 01: empty string
	mintf("");
	// Expect: ""

	// Test 02: phrase with no format
	mintf("Hello World");
	// Expect: "Hello World"
	
	// Test 03: decimal integer
	mintf("%d", 3);
	// Expect: "3"
	
	// Test 04: hexadecimal max integer
	mintf("%x", 0x2147483647);
	// Expect: "7fffffff"

	// Test 05: binary print
	mintf("%b", 7);
	// Expect: "0b111"
	
	// Test 06: $sign print
	mintf("%$", -4234);
	// Expect: "-$42.34"
	
	// Test 07: character print
	mintf("%c %c", 65, 'B');
	// Expect: "A B"

	// Test 08: String print
	mintf("%s", "agh", "extra");
	// Expect: "agh"

	// Test 09: percent sign
	mintf("%% %");
	// Expect: "% %"
	
	// Test 10: limits and escape combination
	mintf("All 3 forms dec: %d, hex %x, bin %b, should not work %o, \nnewline", 7, 7, 7, 7);
	// Expect: "All 3 forms dec: 7, hex 7, bin 111, should not work %o, 
	//          newline"
	return EXIT_SUCCESS;
}
