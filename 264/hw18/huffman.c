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

TreeNode* make_huffman_tree(Node* head){
	//Terminators
	if(head == NULL){
		return NULL;
	}else if(head -> next == NULL){
		TreeNode* root = (TreeNode*)(head -> a_value);
		free(head);
		return root;
	} 
	
	//Creating combination freq node
	TreeNode* tNode1 = (TreeNode*)(head -> a_value);
	TreeNode* tNode2 = (TreeNode*)(head -> next -> a_value);
	TreeNode* newNode = malloc(sizeof(TreeNode));
	*newNode = (TreeNode) {.character = '\0', .frequency = tNode1 -> frequency + tNode2 -> frequency, .left = tNode1, .right = tNode2};
	
	//Queueing combo node and destroying original 2 pointers
	pq_enqueue(&head, newNode, _compare_freq);
	Node* prevHead;
	for(int i = 0;i < 2; i++){
		prevHead = pq_dequeue(&head);
		free(prevHead);
	}
	return make_huffman_tree(head);
}

static void _destroy_treeNode(TreeNode* root){
	if(root == NULL){
		return;
	}
	_destroy_treeNode(root -> left);
	_destroy_treeNode(root -> right);
	free(root);
}

void destroy_huffman_tree(TreeNode** a_root){
	_destroy_treeNode(*a_root);
	*a_root = NULL;
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
