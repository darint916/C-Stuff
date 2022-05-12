#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sorts.h"

void _insert(BSTNode** root, int val){
	BSTNode* node = malloc(sizeof(BSTNode));
	node -> value = val;
	node -> right = NULL;
	node -> left = NULL;
	if(*root == NULL){
		*root = node;
		return;
	}
	BSTNode* trav = *root;
	bool notSet = true;
	while(notSet){
		if((trav) -> value > val){
			if((trav) -> left != NULL) {
				(trav) = (trav) -> left;
			} else{
				(trav) -> left = node;
				notSet = false;
			}
		} else{
			if((trav) -> right != NULL) {
				(trav) = (trav) -> right;
			} else{
				(trav) -> right = node;
				notSet = false;
			}
		}
	}
}

void empty_bst(BST* a_bst){
	_destroy(a_bst -> root);
	a_bst -> root = NULL;
	a_bst -> size = 0;
}

void _fill_arr(int** array, int size, BSTNode* root){
	if(root == NULL){
		return;
	}
	_fill_arr(array, size, root -> left);
	**array = root -> value;
	(*array)++; 
	_fill_arr(array, size, root -> right);
}

BST create_bst(const int* array, int size){
	BST tree;
	tree.root = NULL;  
	tree.size = size;
	for(int i = 0; i < size; i++){
		_insert(&(tree.root), array[i]);
	}
	return tree;
}

void _destroy(BSTNode* root){
	if(root == NULL){
		return;
	}
	_destroy(root -> left);
	_destroy(root -> right);
	free(root);
}


void tree_sort_array(int* array, size_t size){
	BST tree = create_bst(array, size);
	_fill_arr(&array, size, tree.root);
	empty_bst(&tree);
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
