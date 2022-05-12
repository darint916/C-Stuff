#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "miniunit.h"
#include "frequencies.h"
#include "clog.h"
int _test(){
	mu_start();
	Frequencies freq = {0};
	const char* path = "expected.txt";
	const char* a_error;
	FILE* file;
	uchar c = 244;
	file = fopen(path, "w");
	fputc(c, file);
	fclose(file);

	calc_frequencies(freq, path, &a_error);
	
	for(uint64_t i = 0; i <= 255; i++){
		if(freq[i] != 0){
			printf(" %ld : #%4ld\n", i,freq[i]);
		}
	}
	
	const char* path2 = "agh";
	calc_frequencies(freq, path2, &a_error);
	mu_check(1 == 1);
	mu_check_strings_equal(a_error, "No such file or directory");
	
	const char* path3 = "text.txt";
	Frequencies freq2 = {0};
	calc_frequencies(freq2,path3, &a_error);
	printf("test 2\n");
	for(uint64_t i = 0; i <= 255; i++){
		if(freq2[i] != 0){
			printf(" %ld : #%4ld\n", i,freq2[i]);
		}
	}
	mu_end();
}
	
int main(int argc, char* argv[]) {
	mu_run(_test);
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
