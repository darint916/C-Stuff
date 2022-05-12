#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "json.h"
#include "miniunit.h"
#include "clog.h"

typedef struct { 
	bool is_success;
	union{
		Element element;
		long int error_idx;
	};
} ParseResult;

static ParseResult _parse_json(char* s) {
	Element element;
	char const* pos = s;
	bool is_success = parse_element(&element, &pos);
	if(is_success){
		return (ParseResult) { .is_success = is_success, .element = element };
	} else{
		return (ParseResult) { .is_success = is_success, .error_idx = pos - s};
	}
}

static int _test_int(){
	mu_start();
	ParseResult result = _parse_json("0");
	mu_check(result.is_success);
	if(result.is_success){
		mu_check(result.element.type == ELEMENT_INT);
		mu_check(result.element.as_int == 0);
		free_element(result.element);
	}
	mu_end();
}

static int _test_string(){
	mu_start();
	ParseResult result = _parse_json("\"abc\"");
	mu_check(result.is_success);
	if(result.is_success) {
		mu_check(result.element.type == ELEMENT_STRING);
		mu_check(strcmp(result.element.as_string, "abc") == 0);
		mu_check(strlen(result.element.as_string) == 3);
		free_element(result.element);
	}
	mu_end();
}

static int _test_print_fail() {
	mu_start();
	ParseResult result = _parse_json("   --123");
	mu_check(!result.is_success);
	printf("Testing parse_element(&element, \"--123\")\n");
	printf(" - Expected: \n");
	printf(" - Actual:   ");
	print_element(result.element);
	fputc('\n', stdout);
	free_element(result.element);
	mu_end();
}	

static int _test_string2(){
	mu_start();
	ParseResult result = _parse_json("");
	mu_check(!result.is_success);
	mu_end();
}


int _test_parse_int_valid(){
	mu_start();
	int result;
	char* input = "-0123";
	char const* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(is_success);
	mu_check(pos == input + 5);
	mu_check(result == -123);
	mu_end();
}

static void _test_print_element(){
	Element element;
	char const* input = "\"d123\"";
	bool is_success = parse_element(&element, &input);
	printf("Testing parse_element(&element, \"d123\")\n");
	printf(" - Expected: d123\n");
	printf(" - Actual:   ");
	print_element(element);
	printf("\n%d", is_success); 
	fputc('\n', stdout);
	free_element(element);
}

static void _test_print_element2(){
	Element element;
	char const* input = "  1234";
	bool is_success = parse_element(&element, &input);
	printf("Testing parse_element(&element, 123)\n");
	printf(" - Expected: 1234\n");
	printf(" - Actual:   ");
	print_element(element);
	printf("\n%d", is_success); 
	fputc('\n', stdout);
	free_element(element);
}

int _test_parse_int_invalid(){
	mu_start();
	int   result;  // will be initialized in parse_int(…)
    char* input = "A";
	char const* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(!is_success);  // because the input is valid
	mu_check(pos == input);
	mu_end();
}

int _test_parse_int(){
	mu_start();
	int result;
	char* input = "-1245AB";
	char const* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(is_success);
	mu_check(pos = input + 6);
	mu_check(result == -1245);
	mu_end();
}

static int _test_parse_element_inv(){
	mu_start();
	Element element;
	char const* input = " 4 A";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(element.as_int == 4);
	mu_check(element.type == ELEMENT_INT);
	print_element(element);
	mu_check(pos == input + 2);
	mu_check(*pos == ' ');
	mu_end();
}

static int _test_parse_strings(){
	mu_start();
	char* result;
	char const* input = "\"\"";
	char const* pos = input;
	bool is_success = parse_string(&result, &pos);
	mu_check(is_success);
	mu_check(*pos == '\0');
	
	input = "d\"d";
	pos = input;
	is_success = parse_string(&result, &pos);
	mu_check(!is_success);

	input = "\"A\nB\"";
	pos = input;
	is_success = parse_string(&result, &pos);
	mu_check(!is_success);
	mu_check(pos == input + 2);
	mu_check(*pos == '\n');
	
	Element element;
	input = "\"\"";
	pos = input;
	parse_element(&element, &pos);
	//printf("|||%s|||\n", element.as_string);
	free_element(element);
	free(result);
	mu_end();
}

static int _test_list_of_ints(){
	mu_start();
	ParseResult result = _parse_json("[2, \"abccdd12\"  , 5  ]");
	mu_check(result.is_success);
	if(result.is_success){
		mu_check(result.element.type == ELEMENT_LIST);
		mu_check(result.element.as_list != NULL);
		//printf("num:%d\n", result.element.as_list -> element.as_int);
		mu_check((result.element.as_list -> element.as_int) == 2);
		mu_check(result.element.as_list -> element.type == ELEMENT_INT);
		//printf("%d", result.element.as_list -> element.as_int);
		
		mu_check(result.element.as_list -> next != NULL);
		mu_check(result.element.as_list -> next -> element.type == ELEMENT_STRING);
		//printf("string: %s\n", (result.element.as_list -> next -> element.as_string));
		
		mu_check(result.element.as_list -> next -> next!= NULL);
		mu_check(result.element.as_list -> next -> next -> element.type == ELEMENT_INT);
		mu_check(result.element.as_list -> next -> next -> element.as_int == 5);
		print_element(result.element);
		free_element(result.element);
	}

	result = _parse_json("[[2],[1]]");
	mu_check(result.is_success);
	if(result.is_success){
		mu_check(result.element.type == ELEMENT_LIST);
		mu_check(result.element.as_list != NULL);
		mu_check(result.element.as_list -> element.type == ELEMENT_LIST);		
		mu_check(result.element.as_list -> element.as_list -> element.as_int == 2);
		
		free_element(result.element);
	}

	result = _parse_json("[[");
	mu_check(!result.is_success);	

	result = _parse_json("[,]");
	mu_check(!result.is_success);

	result = _parse_json("A[]");
	mu_check(!result.is_success);
	
	result = _parse_json("[12,, [12]");
	mu_check(!result.is_success);

	result = _parse_json("[[]");
	mu_check(!result.is_success);

	result = _parse_json("[\"asdf\"[]]");
	mu_check(!result.is_success);
	result = _parse_json("[2313[]]");
	mu_check(!result.is_success);
	result = _parse_json("[213231,[]123");
	mu_check(!result.is_success);
	
	result = _parse_json("[12, 32, l, 2]");
	mu_check(!result.is_success);
	
	result = _parse_json("[23,]");
	mu_check(!result.is_success);

	Node* node = NULL;
	char const * in = "ag[]";
	bool res = parse_list(&node, &in);
	mu_check(!res);
	//free_element(result.element);

	


	mu_end();
}
int main(int argc, char* argv[]) {
	mu_run(_test_parse_int_valid);
	mu_run(_test_parse_int);
	mu_run(_test_parse_int_invalid);
	mu_run(_test_int);
	mu_run(_test_string);
	_test_print_element();
	_test_print_element2();
	mu_run(_test_string2);
    mu_run(_test_print_fail);
	mu_run(_test_parse_element_inv);
	mu_run(_test_parse_strings);
	
	mu_run(_test_list_of_ints);
	return EXIT_SUCCESS;
}
