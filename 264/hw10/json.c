#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "clog.h"
#include <stdbool.h>

bool parse_int(int* a_value, char** a_pos){
	int res = 0;
	int flag = 1;
	int negative = 1;
	if(**a_pos == '-'){
		++*a_pos;
		negative = -1;
	}
	if(!isdigit(**a_pos)){
		return false;
	}
	while(**a_pos != '\0' && flag){
		if(isdigit(**a_pos)){
			res = res * 10 + **a_pos - '0';
			++*a_pos;
		} else{
			flag = 0;
		}
	}
	*a_value = res * negative;
	return true;
}
