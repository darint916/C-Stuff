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
	//int arr2[1] = {2};
	//tree_sort_array(arr2, 1);
	//printf("\n\n%d\n\n", arr2[0]);
	//mu_check(arr2[0] == 2);
	tree_sort_array(arr2, 0);
	tree_sort_array(arr, 6);
	/*for(int i = 0; i < 6; i++){
		printf("%d\n", arr[i]);
	}*/
	mu_check(arr[0] == 2);
	mu_check(arr[5] == 8);
	mu_end();
}

int main(int argc, char* argv[]) {
	mu_run(_treetest);
	return EXIT_SUCCESS;
}

