#include "stack.h"

struct elem_t {
	struct elem_t *prev;
	void *element;
};

struct stack {
	struct elem_t *head;
	size_t max_num_of_elem;
	size_t num_of_elem;
	clone_t clone;
	destroy_t destroy;
	print_t print;
};

pstack_t stack_create(size_t max_num_of_elem, clone_t clone, destroy_t destroy,
					  print_t print) {
	struct stack *pstack_t;
	pstack_t = (struct stack*)malloc(sizeof(*pstack_t));
	if (pstack_t == NULL) {
		fprintf(stderr, "Can't allocate memory\n");
		return NULL;
	}
	pstack_t->head = NULL;
	pstack_t->max_num_of_elem = max_num_of_elem;
	pstack_t->num_of_elem = 0;
	pstack_t->clone = clone;
	pstack_t->destroy = destroy;
	pstack_t->print = print;
	return pstack_t;
}

Result stack_destroy(pstack_t stack) {
	if (stack == NULL) {
		fprintf(stderr, "The stack is not initiated\n");
		return FAIL;
	}

	struct elem_t *cursor;
	struct elem_t *tmp;

	cursor = stack->head;
	while (cursor != NULL) {
		tmp = cursor;
		cursor = cursor->prev;
		stack->destroy(tmp->element);
		free(tmp);
	}
	free(stack);
	return SUCCESS;
}

Result stack_push(pstack_t stack, elem_t e) {
	if (stack == NULL) {
		fprintf(stderr, "The stack is not initiated\n");
		return FAIL;
	}
	else if (e == NULL) {
		fprintf(stderr, "The object is not valid\n");
		return FAIL;
	}

	struct elem_t *elem_tmp;
	void *clone;

	elem_tmp = (struct elem_t*)malloc(sizeof(*e));
	if (elem_tmp == NULL) {
		fprintf(stderr, "Can't allocate memory\n");
		return FAIL;
	}

	clone = stack->clone(e);
	if (clone == NULL) {
		stack->destroy(clone);
		free(elem_tmp);
		return FAIL;
	}

	elem_tmp->prev = stack->head;
	elem_tmp->element = clone;
	stack->head = elem_tmp;
	stack->num_of_elem += 1;
	return SUCCESS;
}

void stack_pop(pstack_t stack) {
	if (stack == NULL || stack->head == NULL) {
		fprintf(stderr, "The stack is empty, nothing to pop\n");
		return;
	}
	struct elem_t *tmp;
	tmp = stack->head;
	stack->head = stack->head->prev;
	stack->destroy(tmp->element);
	free(tmp);
	stack->num_of_elem -= 1;
}

void* stack_peek(pstack_t stack) {
	if (stack == NULL || stack->head == NULL) {
		fprintf(stderr, "The stack is empty, nothing to return\n");
		return NULL;
	}

	return stack->head->element;
}

size_t stack_size(pstack_t stack) {
	return stack->num_of_elem;
}

bool stack_is_empty(pstack_t stack) {
	return (stack->num_of_elem == 0);
}

size_t stack_capacity(pstack_t stack) {
	return (stack->max_num_of_elem - stack->num_of_elem);
}

void stack_print(pstack_t stack) {
	if (stack == NULL || stack->head == NULL) {
		fprintf(stderr, "The stack is empty, nothing to print\n");
		return;
	}

	struct elem_t *cursor;
	for (cursor = stack->head; cursor != NULL; cursor = cursor->prev) {
		stack->print(cursor->element);
	}
}