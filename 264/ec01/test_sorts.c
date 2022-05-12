#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "sorts.h"

int main(int argc, char* argv[]) {
	int test[6] = {6, 6, 4, 2, 8, 1};
	quick_sort_array(test, 6);
	for(int i = 0; i < 6; i++){
		printf("%d ", test[i]);
	}
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
