#ifndef __STUDENT__
#define __STUDENT__

#include "stack.h"
#include "stdlib.h"

typedef struct student {
	char *name;
	int age;
	int id;
}*pstudent_t, student_t;

/**
 * @brief Clones a student object. 
 * @param e The student object to clone.
 * @return The cloned student object.
 */
elem_t student_clone(elem_t e);

/**
 * @brief This function frees the memory allocated for a student object.
 * @param e The student object to destroy.
 */
void student_destroy(elem_t e);

/**
 * @brief Prints a student object.
 * @param e The student object to print.
 */
void student_print(elem_t e);

#endif /* __STUDENT__ */