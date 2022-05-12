#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "huffman.h"
#include "bit_writer.h"

typedef struct {
	uint8_t bits;
	int num_bits;
} _Bitcode;

static int _compare_freq(const void* a, const void* b){
	return ((TreeNode*)a) -> frequency - ((TreeNode*)b) -> frequency;
}

Node* make_huffman_pq(Frequencies freqs){
	Node* head = NULL;
	Node** a_head = &head;
	TreeNode* new;
	for(int i = 0; i <= 255; i++){
		if(freqs[i] > 0){
			new = malloc(sizeof(*new));
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
	TreeNode* newNode = malloc(sizeof(*newNode));
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

void write_coding_table(TreeNode* root, BitWriter* a_writer){
	if(root == NULL){
		return;
	}
	write_coding_table(root -> left, a_writer);
	write_coding_table(root -> right, a_writer);
	if(root -> character == '\0'){
		write_bits(a_writer, 0, 1);
	} else{
		write_bits(a_writer, 0x1, 1);
		write_bits(a_writer, root -> character, 8);
	}
}

static void _find_bit(TreeNode* root, uint8_t route, uint8_t count, _Bitcode* character_code){
	if(root -> right == NULL && root -> left == NULL){
		character_code[root -> character] = (_Bitcode){.bits = route, .num_bits = count};
		return;
	}
	_find_bit(root -> left, route << 1, count + 1, character_code);
	_find_bit(root -> right, ~((~route) << 1), count + 1, character_code);
}

void write_compressed(TreeNode* root, BitWriter* a_writer, uint8_t* uncompressed_bytes){
	_Bitcode char_map[256];
	for(int i = 0; i < 256; i++){
		char_map[i] = (_Bitcode){.bits = 0, .num_bits = 0};
	}
	_find_bit(root, 0, 0, char_map);
	for(int i = 0; *(uncompressed_bytes + i) != '\0'; i++){
		write_bits(a_writer, char_map[*(uncompressed_bytes + i)].bits, char_map[*(uncompressed_bytes + i)].num_bits);
	}
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
