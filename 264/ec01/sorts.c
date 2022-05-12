#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int _compare_fn_for_qsort(const void* o1, const void* o2){
	return (*(int*)o1 - *(int*)o2);
}

void quick_sort_array(int* array, size_t size) {
	qsort(array, size, sizeof(int), _compare_fn_for_qsort);
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
