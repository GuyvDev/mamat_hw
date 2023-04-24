#include <stdio.h>	
#include <stdlib.h>	
#include <string.h>	

void median_operate(FILE *f);

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
	median_operate(f);
}

/**
 * @breif Print the median grade from FILE, by creating a grade histogram
 * @param *f Pointer to input file
*/
void median_operate(FILE *f) {
	int line_n, sum, i, grade, retval, num_grades, inputs[101] = {0};
	num_grades = sum = i = line_n = 0;
	
	while (1) {
		retval = fscanf(f, "%d", &grade);
		if (retval == EOF) {
			break;
		} else if ((retval != 1) || (grade < 0) || (grade > 100)) {
			fprintf(stderr, "Error: invalid grade, line: %d\n", line_n + 1);
			line_n++;
			continue;
		}
		line_n++;
		num_grades++;
		inputs[grade]++;
	}

	/* inputs[] represents the grade histogram.
		We sum all the instances of every grade to the middle instance */
	while ((sum < ((num_grades+1)/2)) && (i <= 100)) {
		sum += inputs[i];
		i++;
	}

	/* We broke the loop with i++, so we need to decrease it by 1 */
	printf("%d\n", i - 1);
}