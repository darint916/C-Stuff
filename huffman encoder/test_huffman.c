#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "miniunit.h"
#include "huffman.h"
#include "bit_writer.h"

static int _test(){
	mu_start();

	const char* path = "actual.txt";
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
	/*for(uint64_t i = 0; i <= 255; i++){
		if(freq[i] != 0){
			printf(" %c, %ld : #%4ld\n",(char)i, i, freq[i]);
		}
	}*/
	Node* node = make_huffman_pq(freq);
	//printf("sec freq: %ld\n", ((TreeNode*)(node -> next -> a_value)) -> frequency);
	
	TreeNode* treeHead = make_huffman_tree(node);
	const char* path2 = "expected.txt";
	BitWriter writer = open_bit_writer(path2);
	uint8_t* txt = (uint8_t*)"huffman fluffs many mums";
	write_compressed(treeHead, &writer, txt);
	
	write_coding_table(treeHead, &writer);
 	close_bit_writer(&writer);
	destroy_huffman_tree(&treeHead);
	mu_check(treeHead == NULL);
	mu_end();
}

int main(int argc, char* argv[]) {
	mu_run(_test);
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
