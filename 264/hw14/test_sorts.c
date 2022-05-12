#include <stdio.h>
#include "sorts.h"
#include <stdbool.h>
#include <stdlib.h>
#include "clog.h"
#include "miniunit.h"

int _treetest(){
	mu_start();
	int arr2[0] = {};
	int arr[6] = {4, 3, 6, 2, 5, 8};
	tree_sort_array(arr2, 0);
	tree_sort_array(arr, 6);
	mu_check(arr[0] == 2);
	mu_check(arr[5] == 8);
	mu_end();
}

int main(int argc, char* argv[]) {
	mu_run(_treetest);
	return EXIT_SUCCESS;
}

