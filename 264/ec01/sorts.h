#ifndef __SORTS_H__
#define __SORTS_H__

#include <stdlib.h>  // needed here for size_t

void quick_sort_array(int* array, size_t size);
int _compare_fn_for_qsort(const void* o1, const void* o2);
#endif /* end of include guard: __SORTS_H__ */
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
