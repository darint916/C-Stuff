#include <stdbool.h>
#include <string.h>
#include "clog.h"

#define mu_start() int __mu_line_num_first_fail = 0

#define mu_check(n) do{\
	if(!(n) && !(__mu_line_num_first_fail)) {\
			__mu_line_num_first_fail = __LINE__; \
	} \
} while(false)

#define mu_run(n) do{\
	if((n)()) {\
		logf_red("Test failed: %s at line %d\n", #n, (n)()); \
	}\
	else {\
		logf_green("Test passed: %s\n", #n); \
	}\
}while(false)

#define mu_end() return __mu_line_num_first_fail

#define mu_check_strings_equal(s1, s2) mu_check(strcmp((s1),(s2)) == 0)

