#include "mintf.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
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

void mintf(const char *format, ...)
{
	//variable arguments list
	va_list vaList;
	va_start(vaList, format);
	//Loops through to find format specifiers and prints accordingly
	for(int i = 0; format[i] != '\0'; i++){
		if(format[i] == '%'){
			i++;
			//Placeholder variables for manipulation within switch
			int numPlace;    
			char * charPlace;
			switch(format[i]){
				case 'd':
					print_integer(va_arg(vaList, int), 10, ""); 
					break;
				case 'x':
					print_integer(va_arg(vaList, int), 16, "0x");
					break;
				case 'b':
					print_integer(va_arg(vaList, int), 2, "0b");
					break;
				case '$':
					numPlace = va_arg(vaList, int);
					if(numPlace < 0 && abs(numPlace) < 100){
						fputc('-', stdout);
					}
					print_integer(numPlace / 100, 10, "$");
					numPlace = abs(numPlace) % 100;
					if(numPlace < 10){
						print_integer(numPlace, 10, ".0");
					}
					else{
						print_integer(numPlace, 10, ".");
					}
					break;
				case '%':
					fputc('%', stdout);
					break;
				case '\0':
					fputc('%', stdout);
					return;
				case 's':
					charPlace = va_arg(vaList, char *);
					for(int j = 0; charPlace[j] != '\0'; j++){
						fputc(charPlace[j], stdout);
					}
					break;
				case 'c':
					fputc(va_arg(vaList, int), stdout);
					break;
				default:
					fputc('%', stdout);
					fputc(format[i], stdout);
			}
		}
		else{
			fputc(format[i], stdout);
		}
	}
	va_end(vaList);
	return;
}
// vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab:
