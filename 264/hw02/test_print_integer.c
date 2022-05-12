#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "print_integer.h"
int main(int argc, char* argv[])
{
	print_integer(-1, 8, "a");
	fputc('\n', stdout);
	print_integer(0x80000000,10,"c");
	fputc('\n', stdout);
	print_integer(INT_MAX,2,"$");
	fputc('\n', stdout);
	print_integer(INT_MIN,16, "0x");
	fputc('\n', stdout);
	print_integer(INT_MIN,10,"");
	fputc('\n', stdout);
	return EXIT_SUCCESS;
}
