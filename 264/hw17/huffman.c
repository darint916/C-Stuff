#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "huffman.h"

static int _compare_freq(const void* a, const void* b){
	return ((TreeNode*)a) -> frequency - ((TreeNode*)b) -> frequency;
}

Node* make_huffman_pq(Frequencies freqs){
	Node* head = NULL;
	Node** a_head = &head;
	TreeNode* new;
	for(int i = 0; i <= 255; i++){
		if(freqs[i] > 0){
			new = malloc(sizeof(TreeNode));
			*new = (TreeNode) {.character = i, .frequency = freqs[i], .right = NULL, .left = NULL};
			pq_enqueue(a_head, new, _compare_freq);
		}
	}
	return *a_head;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
