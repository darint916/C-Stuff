#include <stdio.h>
#include <stdlib.h>
#include "json.h"
#include "miniunit.h"

int _test_parse_int_valid(){
	mu_start();
	int result;
	char* input = "0123";
	char* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(is_success);
	mu_check(pos == input + 4);
	mu_check(result == 123);
	mu_end();
}

int _test_parse_int_invalid(){
	mu_start();
	int   result;  // will be initialized in parse_int(…)
    char* input = "A";
	char* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(!is_success);  // because the input is valid
	mu_check(pos == input);
	mu_end();
}
int _test_parse_int(){
	mu_start();
	int result;
	char* input = "-1245AB";
	char* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(is_success);
	mu_check(pos = input + 6);
	mu_check(result == -1245);
	mu_end();
}

int main(int argc, char* argv[]) {
	mu_run(_test_parse_int_valid);
	mu_run(_test_parse_int);
	mu_run(_test_parse_int_invalid);
	return EXIT_SUCCESS;
}
