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
	//Checks for null and accumulates the next integer
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

bool parse_list(Node** a_head, char const** a_pos){
	if(**a_pos != '[' && *a_head == NULL){
		return false;
	} else if (**a_pos == '['){
		++*a_pos;
		char const * pos = *a_pos;
		int brack = 1;
		while(brack != 0){		//Checks if bracket count valid at beginning
			if(*pos == '['){
				brack++;
			} else if (*pos == ']'){
				brack--;
			} else if (*pos == '"'){
				pos++;
				while(*pos != '"' || *pos == '\0'){
					pos++;
				}
			} else if(*pos == '\0'){
				return false;
			}
			pos++;
		}
	}
	bool result = true;
	if(**a_pos != ']' && **a_pos != '\0'){  //Creates new node if valid element
		Element element;
		result = parse_element(&element, a_pos);
		while(isspace(**a_pos)){
			++*a_pos;
		}
		if(!result || **a_pos == '\0'){ //valid next confirmation
			return false;
		}else if(**a_pos == ','){
			++*a_pos;
			if(**a_pos == ']' || **a_pos == ','){
				free_element(element);
				return false;
			}
		} else if(**a_pos != ']'){
			free_element(element);
			return false;
		} //Proceeds to create and append node
		Node* newNode = malloc(sizeof(Node));
		newNode -> element = element;
		newNode -> next = NULL;
		if(*a_head != NULL){
			Node* travNode = *a_head;
			while(travNode -> next != NULL) {
				travNode = travNode -> next;
			}
			travNode -> next = newNode;
		} else {
			*a_head = newNode;
		}
		result = parse_list(a_head, a_pos);
		if(!result){
			free_element(newNode->element);
			free(newNode);
		}
	} else if(**a_pos == ']'){
		++*a_pos;
	}
	return result;
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
	} else if (**a_pos == '[') {
		a_element -> type = ELEMENT_LIST;
		a_element -> as_list = NULL;
		return parse_list(&(a_element -> as_list), a_pos);
	}
	return false;
}

void print_element(Element element) { //Assumes valid input
	if(element.type == ELEMENT_INT){
		printf("%d", element.as_int);
	} else if(element.type == ELEMENT_STRING){
		printf("\"%s\"", element.as_string);
	} else if(element.type == ELEMENT_LIST){
		printf("[");
		while(element.as_list != NULL) {
			print_element(element.as_list -> element);
			element.as_list = element.as_list -> next;
			if(element.as_list != NULL){
				printf(",");
			}
		}
		printf("]");
	}
}

void free_element(Element element){
	if(element.type == ELEMENT_STRING){
		free(element.as_string);
	} else if(element.type == ELEMENT_LIST){
		if(element.as_list != NULL){
			Node* temp = element.as_list;
			free_element(element.as_list -> element);
			element.as_list = element.as_list -> next;
			free(temp);
			free_element(element);
		}
	}
}
