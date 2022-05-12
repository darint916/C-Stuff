#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "priority_queue.h"

Node* pq_enqueue(Node** a_head, void* a_value, int (*cmp_fn)(const void*, const void*)) {
	Node* new = malloc(sizeof(Node));
	*new = (Node) {.a_value = a_value, .next = NULL};

	if(*a_head == NULL){
		*a_head = new;
	} else if(cmp_fn((*a_head) -> a_value, a_value) > 0) {
		//printf("pass");
		//printf("inside: %d\n", *(int*)((*a_head) -> a_value));
		new -> next = *a_head;
		*a_head = new;
	} else {
		Node* traverse = *a_head; 
		int flag = 1;
		while(flag){
			if(traverse -> next == NULL){
				flag = 0;
			 	traverse -> next = new;
				//printf("inside: %d\n", *(int*)(traverse -> a_value));
			} else if(cmp_fn(traverse -> next -> a_value, a_value) > 0){
					new -> next = traverse -> next;
					traverse -> next = new;
					flag = 0;
			} else { 
				traverse = traverse -> next;
			}
		}
	}
	return new;
}

Node* pq_dequeue(Node** a_head) {
	Node* temp = *a_head;
	if(*a_head != NULL){
		*a_head = (*a_head) -> next;
		//printf("dequeue: %d\n", *(int*)((*a_head) -> a_value));
		temp -> next = NULL;
	}
	//printf("inside deq: %d\n", *(int*)((temp) -> a_value));
	return temp;
}


Node* stack_push(Node** a_head, void* a_value) {
	Node *new = malloc(sizeof(Node));
	*new = (Node) {.a_value = a_value, .next = *a_head}; 
	*a_head = new;
	return new;
}

Node* stack_pop(Node** a_head) {
	return pq_dequeue(a_head);
}

void destroy_list(Node** a_head, void (*destroy_value_fn)(void*)) {
	Node* temp = *a_head;
	Node* next;
	while(temp != NULL){
		next = temp -> next;
		destroy_value_fn(temp -> a_value);
		free(temp);
		temp = next;
	}
	*a_head = NULL;
}
#define HUFFMAN_C_V1
