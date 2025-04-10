#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data; 
    struct Node *next;
} Node;
Node *head = NULL;

void append(int value);
void insert(Node *ptr, int value);
void delete(Node *ptr);
Node *find(int value);
void traverse(void);
int length(void);
void freeList(void);
void reverseList(void);

void main() {
	traverse();
	for(int i = 0; i < 5; i++){ // [41,67,34,0,69,24,78,58,62,64]
		append(rand()%100);
	}
	printf("原始串列: ");
	traverse();
	
	reverseList();
	
	printf("反轉後串列: ");
	traverse();
}

void reverseList() {
    Node *prev = NULL;
    Node *curr = head;
    Node *p = NULL; // 用來存下一個節點，避免丟失鏈結

    while (curr != NULL) {
        p = curr->next;  // 先存下一個node
        curr->next = prev;  // 反轉鏈結方向
        prev = curr;        // prev 往前推
        curr = p;        // curr 繼續往前
    }
    
    head = prev; // 更新 head，指向新的第一個節點 
}


/* append tail Node with value */ 
void append(int value) {
	Node *node = (Node*)malloc(sizeof(Node)); 
    node->data = value;
	node->next = NULL;
		
	if (head == NULL) {
		head = node;
	} else {
		Node *p = head;
		while (p->next != NULL) 
			p = p->next;
		p->next = node;
	}
}

/* insert a Node with value before ptr Node */ 
void insert(Node *ptr, int value) {
	Node *node = (Node*)malloc(sizeof(Node)); 
    node->data= value;
	node->next = NULL;
	
	if (ptr == NULL) { 
        append(value);
    } else {
    	node->next = ptr;
		if (ptr == head)
		    head = node;
		else {
			Node *p = head;
			while (p->next != ptr)
				p = p->next;
			p->next = node;
		}
	}
}

void delete(Node *ptr) { 
    if (ptr == NULL) return;
    if (ptr == head) { // 第一種情況: 刪除第一個節點 
    	head = head->next; 
    } else { 
    	Node *p = head; 
        while (p->next != ptr) // 找節點ptr的前節點
        	p = p->next; 
        p->next = ptr->next;
    }
    free(ptr);
}

Node *find(int value) { 
    Node *p = head;
    while (p != NULL) {
        if (p->data == value) 
        	return p; 
       	p = p->next;
	}		
    return p; 
}

void traverse() {
	printf("[");
	Node *p = head;
	while (p != NULL) {
		if (p != head)	printf(",");
		printf("%d", p->data);
		p = p->next;
	}
	printf("]\n");
}

int length() { 
	int count = 0; 
    Node *p = head; 
    while (p != NULL) { 
		count++;
		p = p->next;
	} 
    return count; 
}

void freeList() { 
    Node *p = head; 
    while (p != NULL) { 
		Node *next = p->next;
		free(p);
		p = next;
	} 
}
