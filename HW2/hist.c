#include <stdio.h>	
#include <stdlib.h>	
#include <string.h>	

static FILE *f;	
static int nbins = 10;	
	
void operate_hist(int *bins);
void parse_arg(int arge, char **argv);

int main(int argc, char **argv) {
	parse_arg(argc, argv);
	if (!f) {	
		fprintf(stderr,	"File not found: \"%s\"\n", argv[1]);
		return 1;
	}
	int *bins = (int*)calloc(nbins, sizeof(int)*nbins);
	if (bins == NULL) {
		fprintf(stderr,	"Calloc failed");
	}
	operate_hist(bins);
	free(bins);
}

/**
 * @breif Print the histogram of grade from FILE
 * @param *bins An array that represents the bins of the histogram grades
*/
void operate_hist(int *bins) {
	int grade, line_n = 0, retval;
	double pace;

	while (1) {
		retval = fscanf(f, "%d", &grade);
		if (retval == EOF) {
			break;
		} else if ((retval != 1) || (grade < 0) || (grade > 100)) {
			fprintf(stderr, "Error: invalid grade, line: %d\n", line_n + 1);
			continue;
		}
		int n = grade / (100 / nbins);
		// Put 100 in the last bin
		n = (grade == 100) ? n-1 : n;
		bins[n]++;
		line_n++;
	}
	pace = 100.0 / nbins;
	for (int i = 0; i < nbins; i++) {
		printf("%.0lf-%.0lf\t%d\n",
		i * pace,
		(i < nbins - 1) ? ((i + 1) * pace - 1) : 100,
		bins[i]);
	}
}	

/**
 * @breif Parser for input arguments
 * @param argc Number of arguments that passed in
 * @param argv Array of arguments that passed in
*/
void parse_arg(int argc, char **argv) {
	f = stdin;

	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-")) {
				f = stdin;
		} else if (!strcmp(argv[i], "-n_bins")) {
			nbins = (i < argc - 1) ? atoi(argv[i+1]) : 10;
			i++;	
		} else {	
			f = fopen(argv[i], "r");
		}
	}
}
