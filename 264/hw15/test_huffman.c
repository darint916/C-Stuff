#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "huffman.h"
#include "miniunit.h"

int cmp_fn(const void* a, const void* b){
	return *(int*)a - *(int*)b;
}

void destroy_int(void* a) {
}

int _test(){
	mu_start();
	Node* head = NULL;
	int val = 10;
	Node* new = pq_enqueue(&head, &val, cmp_fn);
	printf("\n%d\n", *(int*)(head -> a_value));
	int val2 = 5;
	new = pq_enqueue(&head, &val2, cmp_fn);
		printf("%d %d\n", *(int*)(head -> a_value), *(int*)(head -> next -> a_value));
		
	int val3 = 7;
	int val4 = 11;
	new = pq_enqueue(&head, &val3, cmp_fn);
	printf("new node3: %d\n", *(int*)(new -> a_value));
	new = pq_enqueue(&head, &val4, cmp_fn);
	printf("new node4: %d\n", *(int*)(new -> a_value));
	
	for(int i = 0; i < 5; i++){
		new = pq_dequeue(&head);
		//printf("freed stack node: %d\n", *(int*)((new) -> a_value));
		destroy_list(&new, destroy_int);
	}
	printf("done deq\n");
	pq_enqueue(&head, &val2, cmp_fn);
	pq_enqueue(&head, &val4, cmp_fn);
	
	printf("list: ");
	Node* temp = head;
	while(temp != NULL){
		printf("%d, ", *(int*)(temp -> a_value));
		temp = temp -> next;	
	}
	printf("\n");

	destroy_list(&head, destroy_int);
	new = stack_push(&head, &val);
	
	printf("new node stack: %d\n", *(int*)((head) -> a_value));
	stack_push(&head, &val2);
	stack_push(&head, &val3);
	new = stack_pop(&head);
	mu_check( *(int*)((new) -> a_value) == 7);
	destroy_list(&new, destroy_int);

	temp = head;
	while(temp != NULL){
		printf("%d, ", *(int*)(temp -> a_value));
		temp = temp -> next;	
	}
	printf("\n");
	
	destroy_list(&head, destroy_int);
	mu_end();
}

int main(int argc, char* argv[]) {
	mu_run(_test);
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
