#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "clog.h"
#include <stdbool.h>
#include "json.h"

bool parse_int(int* a_value, char const** a_pos){
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
	//Checks for nulll and accumulates the next integer
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

bool parse_string(char** a_string, char const** a_pos){
	if(**a_pos != '"'){
		return false;
	}
	++*a_pos;
	char const* start = *a_pos;
	int count = 1;	
	while(**a_pos != '"'){ //loops through to see if string valid
		if(**a_pos == '\0' || **a_pos == '\n'){
			return false;
		}
		count++;
		++*a_pos;
	}
	*a_string =  malloc(count * sizeof(char));
	strncpy(*a_string, start, sizeof(char) * count - 1);
	((*a_string)[count - 1]) = '\0';
	++*a_pos;
	return true;
}

bool parse_element(Element* a_element, char const** a_pos){
	while(isspace(**a_pos)){
		++*a_pos;
	} //Assigns type and then parses based on input after whitespace skip
	if(isdigit(**a_pos) || **a_pos == '-'){
		a_element -> type = ELEMENT_INT;
		return parse_int(&(a_element -> as_int), a_pos);
	} else if (**a_pos == '"'){
		a_element -> type = ELEMENT_STRING;
		return parse_string(&(a_element -> as_string), a_pos);
	}
	return false;
}

void print_element(Element element) { //Assumes valid input
	if(element.type == ELEMENT_INT){
		printf("%d", element.as_int);
	} else if(element.type == ELEMENT_STRING){
		printf("\"%s\"", element.as_string);
	}
}

void free_element(Element element){
	if(element.type == ELEMENT_STRING){
		free(element.as_string);
	}
}
