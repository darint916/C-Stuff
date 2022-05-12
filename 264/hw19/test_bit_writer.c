#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "miniunit.h"
#include "bit_writer.h"

static int _test(){
	mu_start();
	const char* path = "expected.txt";
	BitWriter writer = open_bit_writer(path);
	write_bits(&writer, 0x48, 8);
	write_bits(&writer, 0x69, 8);
	write_bits(&writer, 0x2, 3);
	//write_bits(&writer, 0xf3, 3);
	write_bits(&writer, 0x2, 3);
	write_bits(&writer, 0, 2);
	write_bits(&writer, 104, 8);
	write_bits(&writer, 0x5, 3);
	write_bits(&writer, 0x5, 7);

	close_bit_writer(&writer);
	
	writer = open_bit_writer(path);
	close_bit_writer(&writer);

	mu_end();
}

int main(int argc, char* argv[]) {
	mu_run(_test);	
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
