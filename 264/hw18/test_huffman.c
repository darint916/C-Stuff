#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "miniunit.h"
#include "huffman.h"
static int _test(){
	mu_start();

	const char* path = "expected.txt";
	const char* a_error;
	const char* a_error2;
	
	Frequencies freq2 = {0};
	calc_frequencies(freq2, "", &a_error2);
	
	Node* nullNode = make_huffman_pq(freq2);
	mu_check(nullNode == NULL);
	TreeNode* nullTree = make_huffman_tree(nullNode);
	mu_check(nullTree == NULL);

	Frequencies freq = {0};
	mu_check(calc_frequencies(freq, path, &a_error));
	for(uint64_t i = 0; i <= 255; i++){
		if(freq[i] != 0){
			printf(" %ld : #%4ld\n", i,freq[i]);
		}
	}
	
	Node* node = make_huffman_pq(freq);
	printf("sec freq: %ld\n", ((TreeNode*)(node -> next -> a_value)) -> frequency);
	
	TreeNode* treeHead = make_huffman_tree(node);
	printf("tree: %ld\n", treeHead -> frequency);
	printf("tree second: %c %ld\n", treeHead->right->right->right->character,treeHead -> right ->right -> frequency);
	destroy_huffman_tree(&treeHead);
	mu_check(treeHead == NULL);
	//destroy_list(&node, _destroy_tree);
	mu_end();
}

int main(int argc, char* argv[]) {
	mu_run(_test);
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
