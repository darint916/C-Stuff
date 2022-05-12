#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__
#include "frequencies.h"
#include <stdlib.h>
#include "priority_queue.h"

typedef struct _TreeNode{
	uchar character;
	size_t frequency;
	struct _TreeNode* left;
	struct _TreeNode* right;
} TreeNode;

TreeNode* make_huffman_tree(Node* head);
void destroy_huffman_tree(TreeNode** a_root);
Node* make_huffman_pq(Frequencies freqs);

#endif
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
