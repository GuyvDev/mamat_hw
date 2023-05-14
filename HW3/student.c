#include "student.h"
#include <string.h>

static Result check_input(student_t* t_student);

elem_t student_clone(elem_t e) {
	if (e == NULL) {
		return NULL;
	}

	student_t *c_student, *tmp;
	tmp = (student_t*) e;
	if (check_input(tmp) == FAIL) {
		return NULL;
	}

	c_student = (student_t*) malloc(sizeof(*e));
	if (c_student == NULL) {
		fprintf(stderr, "Can't allocate memory\n");
		return NULL;
	}

	c_student->name = (char*) malloc(strlen(tmp->name) + 1);
	if (c_student->name == NULL) {
		fprintf(stderr, "Can't allocate memory\n");
		return NULL;
	}
	strcpy(c_student->name, tmp->name);
	c_student->age = tmp->age;
	c_student->id = tmp->id;
	return c_student;
}

void student_destroy(elem_t e) {
	if (e == NULL) {
		return;
	}

	student_t *tmp;
	tmp = (student_t*) e;
	free(tmp->name);
	free(tmp);
}

void student_print(elem_t e) {
	if (e == NULL) {
		return;
	}

	student_t *tmp;
	tmp = (student_t*)e;
	printf("student name: %s, age: %d, id: %d.\n", tmp->name, 
												   tmp->age, tmp->id);
}

/**
 * @brief Check if the inputs are valid.
 * @param t_student The student object with inputs to check.
 * @return SUCCESS if the inputs are valid, FAIL otherwise.
 */
static Result check_input(student_t* t_student) {
	if (t_student->age < 0) {
		fprintf(stderr, "The age is not a valid number\n");
		return FAIL;
	}
	if (t_student->name == NULL) {
		fprintf(stderr, "The Name is not a valid string\n");
		return FAIL;
	}
	if (t_student->id < 0) {
		fprintf(stderr, "The id is not a valid number\n");
		return FAIL;
	}

	return SUCCESS;
}