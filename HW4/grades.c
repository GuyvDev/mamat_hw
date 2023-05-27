#include <stdlib.h>
#include <stdio.h>
#include "linked-list.h"
#include "grades.h"
#include <string.h>

/*The grade struct is a list of students (l_student), the list consists of
n_students elements, every student has its own list of courses (l_course),
and the list consists of n_course elements */

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

	/*Copy all the courses from c_student to new_student*/
	struct list *l_course = c_student->l_course;
	struct iterator *it = list_begin(l_course);
	if (it == NULL && list_size(l_course) != 0) {
		return 1;
	}
	while (it != NULL) {
		course_t *it_course = (course_t*)list_get(it);
		if (it_course == NULL) {
			continue; /*If one course is corrupted, move to the next.*/
		}
		if (list_push_back(new_student->l_course, it_course) != 0) {
			return 1;
		}
		
		it = list_next(it);
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
	/*list_push_back pushes copy of new_student,
	therefore we need to destroy new_studnet*/
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
	/*list_push_back pushes copy of new_course,
	therefore we need to destroy new_course*/
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
		/*If the list of courses is empty, the avg is 0*/
		return 0;
	}

	/*Iterate every course and sum up the grades*/
	struct list *l_course = c_student->l_course;
	struct iterator *it = list_begin(l_course);
	if (it == NULL && list_size(l_course) != 0) {
		return -1;
	}
	int sum_grades = 0;
	while (it != NULL) {
		course_t *it_course = (course_t*)list_get(it);
		if (it_course == NULL) {
			continue; /*If one course is corrupted, move to the next.*/
		}
		sum_grades += it_course->course_grade;

		it = list_next(it);
	}
	return ((float)sum_grades / l_size);
}

int grades_print_student(struct grades *grades, int id) {
	student_t *c_student = search_student(grades, id);
	if (c_student == NULL) {
		return 1;
	}
	
	fprintf(stdout, "%s %d:", c_student->student_name, c_student->id);

	struct list *l_course = c_student->l_course;
	struct iterator *it = list_begin(l_course);
	if (list_size(l_course) == 0) {
		/*If there are no courses for c_student*/
		fprintf(stdout, "\n");
		return 0;
	}
	else if (it == NULL) {
		return 1; /*If there are courses, but there is an error*/
	}

	while (it != NULL) {
		course_t *it_course = (course_t*)list_get(it);
		if (it_course == NULL) {
			continue; /*If one course is corrupted, move to the next*/
		}
		fprintf(stdout, " %s %d", it_course->course_name,
								  it_course->course_grade);
		if (list_next(it) != NULL) {
			fprintf(stdout, ",");
		}
		else {
			fprintf(stdout, "\n");
		}

		it = list_next(it);
	}
	return 0;
}

int grades_print_all(struct grades *grades) {
	if (grades == NULL) {
		return 1;
	}
	
	struct list *l_student = grades->l_students;
	struct iterator *it = list_begin(l_student);
	if (it == NULL && list_size(l_student) != 0) {
		return 1;
	}

	while (it != NULL) {
		student_t *it_student = (student_t*)list_get(it);
		if (it_student == NULL) {
			continue; /*If one student is corrupted, move to the next.*/
		}
		if (grades_print_student(grades, it_student->id) != 0) {
			return 1;
		}

		it = list_next(it);
	}
	return 0;
}

/*Parser inputs and allocate corresponding memory*/
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

/*Search for a given id in the grades structure,
and return a pointer to the student structure*/
student_t* search_student(struct grades* grades, int id) {
	if (grades == NULL || id < 0) {
		return NULL;
	}

	struct list *l_student = grades->l_students;
	struct iterator *it = list_begin(l_student);
	if (it == NULL && list_size(l_student) != 0) {
		return NULL;
	}
	while (it != NULL) {
		student_t *it_student = list_get(it);
		if (it_student == NULL) {
			continue; /*If one student is corrupted, move to the next*/
		}
		if (it_student->id == id) {
			return it_student;
		}

		it = list_next(it);
	}
	/*If the student not founded*/
	return NULL;
}

/*Parser inputs and allocate corresponding memory*/
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