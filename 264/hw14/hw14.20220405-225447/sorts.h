#ifndef SORTS_H
#define SORTS_H
#include <stdlib.h>

typedef struct _BSTNode {
	int value;
	struct _BSTNode* right;
	struct _BSTNode* left;
} BSTNode;

typedef struct _BST{
	BSTNode* root;
	int size;
} BST;

BST create_bst(const int* array, int size);
void empty_bst(BST* bst);
void _insert(BSTNode** root, int val);
void _fill_arr(int** array, int size, BSTNode* root);
void _destroy(BSTNode* root);
void tree_sort_array(int* array, size_t size);
#endif
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
