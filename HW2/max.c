#include <stdio.h>	
#include <stdlib.h>	
#include <string.h>	

void max_operate(FILE *f);

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
	max_operate(f);
}

/**
 * @breif Print the maximum grade from FILE
 * @param *f Pointer to input file
*/
void max_operate(FILE *f) {
	int retval, grade, max = 0, line_n = 0;

	while (1) {
		retval = fscanf(f, "%d", &grade);
		if (retval == EOF) {
			break;
		} else if ((retval != 1) || (grade < 0) || (grade > 100)) {
			fprintf(stderr, "Error: invalid grade, line: %d\n", line_n + 1);
			continue;
		}
		max = (grade > max) ? grade : max;
		line_n++;
	}
	printf("%d\n", max);
}