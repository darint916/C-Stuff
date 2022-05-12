/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#define HW09_BONUS

void _lenReplacer(const char *format, va_list vaList, int *resLen, char *res);
void _printc(char);

//If entered with length 0, calculates length, if given length, reformat input into provided radix and saves into pointer.
void _change_integer(int n, int radix, char* prefix, int * length, char* result) {	
	int count = 0;
	if(n < 0) {   				
		if(*length > 0){
			result[count] = '-';
		} else if(*length == -1) {
			_printc('-');
		}
		count++;
	}
	for(int i = 0; prefix[i] != '\0'; i++) {
		if(*length > 0){
			result[count] = prefix[i];
		} else if(*length == -1) {
			_printc(prefix[i]);
		}
		count++;
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
			if(*length > 0){
				result[count] = (dig - 10) + 'a';
			} else if(*length == -1) {
				_printc((dig - 10) + 'a');
			}
			count++;
		}else {
			if(*length > 0){
				result[count] = dig + '0';
			} else if(*length == -1) {
				_printc(dig + '0');
			}
			count++;
		}
		n %= largestDiv;
		largestDiv /= radix;
	}
	*length = count;
}

//printer help function
void _printc(char in){ 
	fputc(in, stdout);
}

//format and allocates memory instead of output
char* smintf(const char *format, ...){
	va_list vaList, vaListCpy;
	va_start(vaList, format);
	va_copy(vaListCpy, vaList);
	int length = 0;
	_lenReplacer(format, vaListCpy, &length, "");
	char* res = malloc(length * sizeof(char)+1);
	if(res != NULL) {
		_lenReplacer(format, vaList, &length, res);
	}
	return res; 
}

//format and outputs into stdout
void mintf(const char *format, ...){
	va_list vaList, vaListCpy;
	va_start(vaList, format);
	va_copy(vaListCpy, vaList);
	int length = -1;
	_lenReplacer(format, vaListCpy, &length, "");
}

//replaces format specifiers with specified result if length is defined, if not, finds length.
void _lenReplacer(const char *format, va_list vaList, int *resLen, char *res){
	//Loops through to find format specifiers and prints accordingly
	int tempLen = 0;
	int totLen = 0;
	for(int i = 0; format[i] != '\0'; i++){
		if(format[i] == '%'){
			i++;
			//Placeholder variables for manipulation within switch
			int numPlace;    
			char * charPlace;
			switch(format[i]){
				case 'd':
					tempLen = *resLen;
					_change_integer(va_arg(vaList, int), 10, "", &tempLen, res + totLen);
					totLen += tempLen;
					tempLen = 0;
					break;
				case 'x':
					tempLen = *resLen;
					_change_integer(va_arg(vaList, int), 16, "0x", &tempLen, res + totLen);
					totLen += tempLen;
					tempLen = 0;
					break;
				case 'b':
					tempLen = *resLen;
					_change_integer(va_arg(vaList, int), 2, "0b", &tempLen, res + totLen);
					totLen += tempLen;
					tempLen = 0;
					break;
				case '$':
					numPlace = va_arg(vaList, int);
					if(numPlace < 0 && abs(numPlace) < 100){
						if(*resLen > 0){
							*(res + totLen) = '-';
						} else if(*resLen == -1){
							_printc('-');
						}
						totLen++;
					}
					tempLen = *resLen;
					_change_integer(numPlace / 100, 10, "$", &tempLen, res + totLen);
					totLen += tempLen;
					tempLen = 0;

					numPlace = abs(numPlace) % 100;
					if(numPlace < 10){
						tempLen = *resLen;
						_change_integer(numPlace, 10, ".0", &tempLen, res + totLen);
						totLen += tempLen;
						tempLen = 0;
					}
					else{
						tempLen = *resLen;
						_change_integer(numPlace, 10, ".", &tempLen, res + totLen);
						totLen += tempLen;
						tempLen = 0;
					}
					break;
				case '%':
					if(*resLen > 0){
						*(res + totLen) = '%';
					} else if(*resLen == -1){
						_printc('%');
					}
					totLen++;
					break;
				case '\0':
					if(*resLen > 0){
						*(res + totLen) = '%';
						*(res + totLen + 1) = '\0';
					} else if(*resLen == -1) {
						_printc('%');
					}
					totLen += 2;
					*resLen = totLen;
					return;
				case 's':
					charPlace = va_arg(vaList, char *);
					for(int j = 0; charPlace[j] != '\0'; j++){
						if(*resLen > 0){
							*(res + totLen) = charPlace[j];
						} else if(*resLen == -1) {
							_printc(charPlace[j]);
						}
						totLen++;
					}
					break;
				case 'c':
					if(*resLen > 0){
						*(res + totLen) = (char)va_arg(vaList, int);
					} else if(*resLen == -1) {
						_printc((char)va_arg(vaList, int));
					}
					totLen++;
					break;
				default:
					if(*resLen > 0){
						*(res + totLen) = '%';
					} else if(*resLen == -1) {
						_printc('%');
					}
					totLen++;
					if(*resLen > 0){
						*(res + totLen) = format[i];
					} else if(*resLen == -1) {
						_printc(format[i]);
					}
					totLen++;
			}
		}
		else{
			if(*resLen > 0){
				*(res + totLen) = format[i];
			} else if(*resLen == -1) {
				_printc(format[i]);
			}
			totLen++;
		}
	}
	if(*resLen > 0){
		*(res + totLen) = '\0';
	}
	*resLen = totLen;
	return;
}
