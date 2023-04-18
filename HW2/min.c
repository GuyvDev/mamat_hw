#include <stdio.h>	
#include <stdlib.h>	
#include <string.h>	

void min_operate(FILE *f);

int main(int argc, char **argv) {
	FILE *f;
	if (argc == 1 || !strcmp("-", argv[1])) {
		f = stdin;
	} else {
		f = fopen(argv[1], "r");
	}	

	if (!f) {
		fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
		return 1;
	}
	min_operate(f);
}

/**
 * @breif Print the minimum grade from FILE
 * @param *f Pointer to input file
*/
void min_operate(FILE *f) {
	int retval, grade, line_n = 0, min = 100;

	while (1) {
		retval = fscanf(f, "%d", &grade);
		if (retval == EOF) {
			break;
		} else if ((retval != 1) || (grade < 0) || (grade > 100)) {
			fprintf(stderr, "Error: invalid grade, line: %d\n", line_n + 1);
			continue;
		}
		min = (grade < min) ? grade : min;
		line_n++;
	}
	printf("%d\n", min);
}