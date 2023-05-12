#ifndef __STACK__
#define __STACK__

#include <stddef.h>  /* size_t */
#include <stdbool.h> /* bool   */
#include "stdlib.h"
#include "stdio.h"

typedef enum { SUCCESS = 0, FAIL } Result;

typedef struct stack *pstack_t;
typedef void *elem_t;

typedef elem_t (*clone_t)(elem_t e);
typedef void (*destroy_t)(elem_t e);
typedef void (*print_t)(elem_t e);

/**
 * @brief Creates a new stack.
 * 
 * This function creates a new stack with the specified maximum number
 * of elements.
 * 
 * @param max_num_of_elem The maximum number of elements the stack can hold.
 * @param clone Function pointer to the clone function for stack elements.
 * @param destroy Function pointer to the destroy function for stack elements.
 * @param print The function pointer to the print function for stack elements.
 * @return A pointer to the new stack, or NULL if memory allocation failed.
 */
pstack_t stack_create(size_t max_num_of_elem, clone_t clone, destroy_t destroy,
					  print_t print);

/**
 * @fn void stack_destroy(pstack_t s);
 * @brief destroys the user_stack. free all the memory of the elements in the
 * stack. user_stack must be a stack created by StackCreate otherwise
 * undefined behavior)
 * @param stack - pointer to the stack to destroy
 * @return none
 */
Result stack_destroy(pstack_t stack);

/**
 * @brief Pushes an element onto the top of the stack.
 * @param stack A pointer to the stack.
 * @param e The element to push onto the stack.
 * @return SUCCESS if the element was successfully pushed, FAIL otherwise.
 */
Result stack_push(pstack_t stack, elem_t e);

/**
 * @brief This function removes the top element from the stack.
 * @param stack A pointer to the stack.
 */
void stack_pop(pstack_t stack);

/**
 * @brief Retrieves the top element from the stack.
 * @param stack A pointer to the stack.
 * @return A pointer to the top element of the stack,
 * or NULL if the stack is empty or invalid.
 */
void* stack_peek(pstack_t stack);

/**
 * @brief Returns the number of elements in the stack.
 * @param stack A pointer to the stack.
 * @return The number of elements in the stack.
 */
size_t stack_size(pstack_t stack);

/**
 * @brief Checks if the stack is empty.
 * @param stack A pointer to the stack.
 * @return true if the stack is empty, false otherwise.
 */
bool stack_is_empty(pstack_t stack);

/**
 * @brief Returns the remaining capacity of the stack.
 * @param stack A pointer to the stack.
 * @return The remaining capacity of the stack.
 */
size_t stack_capacity(pstack_t stack);

/**
 * @brief Prints the elements of the stack.
 * @param stack A pointer to the stack.
 */
void stack_print(pstack_t stack);

#endif /* __STACK__ */