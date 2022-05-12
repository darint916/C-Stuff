#include "print_integer.h"
#include <stdio.h>

void print_integer(int n, int radix, char* prefix) {
	if(n < 0) {   				
		fputc('-', stdout);
	}
	for(int i = 0; prefix[i] != '\0'; i++) {
		fputc(prefix[i], stdout);
	}
	 //Finds largest divider that is a multiple of radix
	int largestDiv = 1;
	while(n / largestDiv / radix != 0) {  
		largestDiv *= radix;
	}
	//Finds equivalent base value of inputted number and outputs starting from most significant digit 
	while(largestDiv != 0) {
		int dig = n / largestDiv;
		if(dig < 0) {
			dig *= -1;
		}
		if(dig > 9) {
			fputc((dig - 10) + 'a', stdout);
		}else {
			fputc(dig + '0', stdout);
		}
		n %= largestDiv;
		largestDiv /= radix;
	}
}
// vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab:
