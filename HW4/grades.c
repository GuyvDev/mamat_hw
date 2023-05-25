#include <stdlib.h>
#include <stdio.h>
#include "linked-list.h"
#include "grades.h"
#include <string.h>

typedef struct grades {
	struct list *l_students;
}*pgrades_t, grades_t;

typedef struct n_student {
	char *student_name;
	int id;
	struct list *l_course;
}student_t; 

typedef struct n_course {
	char *course_name;
	int course_grade;
}course_t; 

course_t* init_course_node(const char *name, int grade);
student_t* search_student(struct grades* grades, int id);
student_t* init_student_node(const char *name, int id);
int student_clone(void *element, void **output);
void student_destroy(void *element);
int course_clone(void *element, void **output);
void course_destroy(void *element);

int student_clone(void *element, void **output) {
	if (element == NULL) {
		return 1;
	}

	student_t *c_student, *new_student;
	c_student = (student_t*)element;
	new_student = init_student_node(c_student->student_name,c_student->id);
	if (new_student == NULL) {
		return 1;
	}

	struct iterator* it;
	for (it = list_begin(c_student->l_course); it != NULL; it = list_next(it)) {
		course_t *tmp = (course_t*)list_get(it);
		if (tmp == NULL) {
			return 1;
		}
		if (list_push_back(new_student->l_course, tmp) != 0) {
			return 1;
		}
	}

	*output = new_student;
	return 0;
}

void student_destroy(void *element) {
	if (element == NULL) {
		return;
	}

	student_t *c_student;
	c_student = (student_t*)element;

	list_destroy(c_student->l_course);
	free(c_student->student_name);
	free(c_student);
}

int course_clone(void *element, void **output) {
	if (element == NULL) {
		return 1;
	}

	course_t *c_course, *new_course;
	c_course = (course_t*)element;
	new_course = init_course_node(c_course->course_name, 
								  c_course->course_grade);
	if (new_course == NULL) {
		return 1;
	}

	*output = new_course;
	return 0;
}

void course_destroy(void *element) {
	if (element == NULL) {
		return;
	}

	course_t *c_course;
	c_course = (course_t*)element;
	free(c_course->course_name);
	free(c_course);
}

struct grades* grades_init() {
	grades_t *grades;
	grades = (grades_t*)malloc(sizeof(grades_t));
	if (grades == NULL) {
		return NULL;
	}

	struct list *tmp_l_students;
	tmp_l_students = list_init(student_clone, student_destroy);
	if (tmp_l_students == NULL) {
		return NULL;
	}

	grades->l_students = tmp_l_students;
	return grades;
}

void grades_destroy(struct grades *grades) {
	if (grades == NULL) {
		return;
	}

	list_destroy(grades->l_students);
	free(grades);
}

int grades_add_student(struct grades *grades, const char *name, int id) {
	if (grades == NULL || name == NULL) {
		return 1;
	}
	if (search_student(grades, id) != NULL) {
		return 1;
	}

	student_t *new_student;
	new_student = init_student_node(name, id);
	if (new_student == NULL) {
		return 1;
	}

	int flag = list_push_back(grades->l_students, new_student);
	student_destroy(new_student);
	return flag;
}

int grades_add_grade(struct grades *grades,
					 const char *name,
					 int id,
					 int grade) {
	if (grades == NULL || name == NULL) {
		return 1;
	}

	student_t *c_student = search_student(grades, id);
	if (c_student == NULL) {
		return 1;
	}
	
	course_t *new_course;
	new_course = init_course_node(name, grade);
	if (new_course == NULL) {
		return 1;
	}

	int flag = list_push_back(c_student->l_course, new_course);
	course_destroy(new_course);
	return flag;
}

float grades_calc_avg(struct grades *grades, int id, char **out) {
	student_t *c_student = search_student(grades, id);
	if (c_student == NULL) {
		out = NULL;
		return -1;
	}
	
	*out = (char*)malloc(strlen(c_student->student_name) + 1);
	if (out == NULL) {
		return -1;
	}
	strcpy(*out, c_student->student_name);
	
	size_t l_size = list_size(c_student->l_course);
	if (l_size == 0) {
		return 0;
	}

	struct iterator* it;
	int sum_grades = 0;
	for (it = list_begin(c_student->l_course); it != NULL; it = list_next(it)) {
		course_t *tmp = (course_t*)list_get(it);
		if (tmp == NULL) {
			return -1;
		}
		sum_grades += tmp->course_grade;
	}
	return ((float)sum_grades / l_size);
}

int grades_print_student(struct grades *grades, int id) {
	student_t *c_student = search_student(grades, id);
	if (c_student == NULL) {
		return 1;
	}
	
	fprintf(stdout, "%s %d:", c_student->student_name, c_student->id);

	struct iterator* it = list_begin(c_student->l_course);
	if (it == NULL) {
		fprintf(stdout, "\n");
		return 0;
	}

	for (;it != NULL; it = list_next(it)) {
		course_t *tmp = (course_t*)list_get(it);
		if (tmp == NULL) {
			return 1;
		}
		fprintf(stdout, " %s %d", tmp->course_name, tmp->course_grade);
		if (list_next(it) != NULL) {
			fprintf(stdout, ",");
		}
		else {
			fprintf(stdout, "\n");
		}
	}
	return 0;
}

int grades_print_all(struct grades *grades) {
	if (grades == NULL) {
		return 1;
	}
	
	struct iterator* it;
	for (it = list_begin(grades->l_students); it != NULL; it = list_next(it)) {
		student_t *tmp = (student_t*)list_get(it);
		if (tmp == NULL) {
			return 1;
		}
		if (grades_print_student(grades, tmp->id) != 0) {
			return 1;
		}
	}
	return 0;
}

student_t* init_student_node(const char *name, int id) {
	if (id < 0 || name == NULL) {
		return NULL;
	}

	student_t *t_student;
	t_student = (student_t*)malloc(sizeof(student_t));
	if (t_student == NULL) {
		return NULL;
	}

	t_student->student_name = (char*)malloc(strlen(name) + 1);
	if (t_student->student_name == NULL) {
		return NULL;
	}

	strcpy(t_student->student_name, name);
	t_student->id = id;
	t_student->l_course = list_init(course_clone, course_destroy);
	return t_student;
}

student_t* search_student(struct grades* grades, int id) {
	if (grades == NULL || id < 0) {
		return NULL;
	}

	struct iterator* it;
	for (it = list_begin(grades->l_students); it != NULL; it = list_next(it)) {
		student_t *tmp = list_get(it);
		if (tmp == NULL) {
			return NULL;
		}
		if (tmp->id == id) {
			return tmp;
		}
	}
	return NULL;
}

course_t* init_course_node(const char *name, int grade) {
	if (name == NULL || grade < 0 || grade > 100) {
		return NULL;
	}
	
	course_t *t_course;
	t_course = (course_t*)malloc(sizeof(course_t));
	if (t_course == NULL) {
		return NULL;
	}

	t_course->course_name = (char*)malloc(strlen(name) + 1);
	if (t_course->course_name == NULL) {
		return NULL;
	}

	strcpy(t_course->course_name, name);
	t_course->course_grade = grade;
	return t_course;
}