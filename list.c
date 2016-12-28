#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
	unsigned int data;

	struct node *prev;
	struct node *next;
};

static void _alloc_node(struct node **t_node) {
	*t_node = malloc(sizeof(struct node));

	if ( *t_node == (struct node *)NULL ) {
		return;
	}
}

static void _destroy_node(struct node **t_node) {
	free((*t_node)->next);
	free((*t_node)->prev);
	free((*t_node));

	return;
}

static void _insert(struct node **t_node, unsigned int data) {
	struct node *head;

	if ( (*t_node)->prev != (*t_node)->next && (*t_node)->next != (*t_node) ) {
		_alloc_node(t_node);

		memset(*t_node, 0, sizeof(struct node));

		(*t_node)->data = data;
		(*t_node)->next = (*t_node);
		(*t_node)->prev = (*t_node)->next;
	}
	else {
		head = (*t_node);

		while ( (*t_node)->next != head ) {
			(*t_node) = (*t_node)->next;
		}

		_alloc_node(&(*t_node)->next);

		(*t_node)->next->prev = (*t_node);
		(*t_node) = (*t_node)->next;
		(*t_node)->data = data;
		(*t_node)->next = head;
		head->prev = (*t_node);

		(*t_node) = head;
	}
}

static void _insert_after(struct node **t_node, unsigned int _after, unsigned int data) {
	struct node *q_node, *head, *tail;

	head = (*t_node);

	while ( (*t_node)->data != _after ) {
		if ( (*t_node)->next == head )
			break;

		(*t_node) = (*t_node)->next;
	}

	if ( (*t_node)->data == _after ) {
		_alloc_node(&q_node);

		memset(q_node, 0, sizeof(struct node));

		q_node->data = data;
		q_node->prev = (*t_node);
		q_node->next = (*t_node)->next;

		(*t_node)->next->prev = q_node;
		(*t_node)->next = q_node;

		(*t_node) = head;
	}
}

static void _insert_begin(struct node **t_node, unsigned int data) {
	struct node *head, *tail, *tmp;

	head = (*t_node);

	(*t_node) = (*t_node)->prev;

	_alloc_node(&(*t_node)->next);

	(*t_node)->next->prev = (*t_node);
	(*t_node)->next->next = head;

	tail = (*t_node);

	tmp = (*t_node)->next;

	while ( 1 ) {
		if ( (*t_node)->prev == tail ) {
			(*t_node)->next->data = (*t_node)->data;

			break;
		}

		(*t_node)->next->data = (*t_node)->data;

		(*t_node) = (*t_node)->prev;
	}

	head->data = data;
	head->prev = tmp;

	(*t_node) = head;
}

static void _insert_end(struct node **t_node, unsigned int data) {
	struct node *head;

	head = (*t_node);

	(*t_node) = (*t_node)->prev;

	_alloc_node(&(*t_node)->next);

	(*t_node)->next->data = data;
	(*t_node)->next->prev = (*t_node);
	(*t_node)->next->next = head;

	head->prev = (*t_node)->next;

	(*t_node) = head;
}

static void _print_overall_node(struct node **t_node) {
#ifdef CONFIG_PRINT_NODE
	struct node *head;

	head = (*t_node);

	while ( 1 ) {
		if ( (*t_node)->next == head ) {
			printf("t_node: %p, t_node->prev: %p, t_node->next: %p, t_node->data: %u\n", (*t_node), (*t_node)->prev, (*t_node)->next, (*t_node)->data);

			break;
		}

		printf("t_node: %p, t_node->prev: %p, t_node->next: %p, t_node->data: %u\n", (*t_node), (*t_node)->prev, (*t_node)->next, (*t_node)->data);

		(*t_node) = (*t_node)->next;
	}

	(*t_node) = head;
#endif
}

int main(void) {
	struct node *t_node;

	_insert(&t_node, 200);
	_insert(&t_node, 1337);
	_insert(&t_node, 31337);

	_insert_after(&t_node, 1337, 400);
	_insert_begin(&t_node, 4141);

	_insert_end(&t_node, 4242);

	_print_overall_node(&t_node);

	return ( 0 );
}
