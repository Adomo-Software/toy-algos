#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct Node {
	int value;
	struct Node* next;
};

struct Queue {
	struct Node* head;
	struct Node* tail;
};

void queue_init(struct Queue q) {
	q.head = NULL;
	q.tail = NULL;
}

void enqueue(struct Queue* q, int value) {
	struct Node* new = malloc(sizeof(struct Node));
	new->value = value;
	if (q->head == NULL) {
		q->head = new;
		q->tail = new;
	}
	q->tail->next = new;
	q->tail = new;
}


void dequeue(struct Queue* q) {
	if (q->head == NULL) {
		return;
	}
	struct Node* this = q->head;
	q->head = q->head->next;
	free(this);
}

int queue_peek(struct Queue q) {
	return q.head->value;
}

void queue_print(struct Queue q) {
	struct Node* iter = q.head;
	do {
		printf("%d\n", iter->value);
		iter = iter->next;
	} while (iter != q.tail);
	printf("%d\n", iter->value);
}

void queue_print_visual(struct Queue q) {
	struct Node* iter = q.head;
	do {
		printf("%d -> ", iter->value);
		iter = iter->next;
	} while (iter != q.tail);
	printf("%d", iter->value);
	if (iter->next == NULL) {
		printf(" -> NULL");
	}
	printf("\n");

	iter = q.head->next;
	printf("h");
	while (iter != q.tail) {
		printf("     ");
		iter = iter->next;
	}
	if(iter = q.tail)
		printf("    t\n");
	else if (q.head == q.tail)
		printf("t\n");
	/*printf("%d\n", iter->value);*/
}
int main (int argc, char *argv[]) {
	/*struct Node node = {.value = 4};*/
	/*struct Node node2 = {.value = 69};*/
	struct Queue q;
	queue_init(q);
	enqueue(&q, 5);
	enqueue(&q, 6);
	enqueue(&q, 21);
	/*enqueue(&q, 69);*/
	queue_print_visual(q);
	printf("\n");
	/*dequeue(&q);*/
	printf("queue_peek: %d\n", queue_peek(q));
	dequeue(&q);
	queue_print_visual(q);
	return 0;
}
