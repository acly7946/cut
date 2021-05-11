#include <errno.h>
#include <getopt.h>
#include <libgen.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cut.h"

#define PROGRAM "cut"
#define VERSION "Tue 11 May"
#define AUTHOR "acly7946"

static void usage();
static void parse_list(char *input, int *start, int *end);

int main(int argc, char *argv[])
{
	int optc;
	void (*cut_mode)(opt_t *) = NULL;
	opt_t opt =
	{
		.delimiter = '\t',
		.input = stdin,
	};
	static struct option long_opt[] =
	{
		{"bytes", required_argument, NULL, 'b'},
		{"characters", required_argument, NULL, 'c'},
		{"delimiter", required_argument, NULL, 'd'},
		{"fields", required_argument, NULL, 'f'},
		{"help", no_argument, NULL, 'h'},
		{"version", no_argument, NULL, 'V'},
	};

	while((optc = getopt_long(argc, argv, "b:c:d:f:hV", long_opt, NULL)) != EOF)
	{
		switch(optc)
		{
			case 'b':
				if(cut_mode)
				{
					fprintf(stderr, "%s: only one type of list may be specified\n", PROGRAM);
					return EXIT_FAILURE;
				}
				cut_mode = &cut_bytes;
				parse_list(optarg, &opt.start, &opt.end);
				break;

			case 'c':
				if(cut_mode)
				{
					fprintf(stderr, "%s: only one type of list may be specified\n", PROGRAM);
					return EXIT_FAILURE;
				}
				cut_mode = &cut_chars;
				parse_list(optarg, &opt.start, &opt.end);
				break;

			case 'f':
				if(cut_mode)
				{
					fprintf(stderr, "%s: only one type of list may be specified\n", PROGRAM);
					return EXIT_FAILURE;
				}
				cut_mode = &cut_fields;
				parse_list(optarg, &opt.start, &opt.end);
				break;

			case 'd':
				if(strlen(optarg) > 1)
				{
					fprintf(stderr, "%s: delimiter must be a single character\n", PROGRAM);
					return EXIT_FAILURE;
				}
				sscanf(optarg, "%c", &opt.delimiter);
				break;

			case 'V':
				printf("%s, %s, %s\n", PROGRAM, VERSION, AUTHOR);
				return EXIT_SUCCESS;

			default:
				usage();
				break;
		}
	}

	if(!cut_mode)
	{
		fprintf(stderr, "%s: specify bytes, characters or fields\n", PROGRAM);
		return EXIT_FAILURE;
	}

	if(optind < argc) // filename
	{
		if(strcmp(argv[optind], "-") == 0)
		{
		}
		else if(!(opt.input = fopen(argv[optind], "r")))
		{
			fprintf(stderr, "%s: cannot access '%s': ", PROGRAM, argv[optind]);
			perror(NULL);
			return EXIT_FAILURE;
		}
	}

	cut_mode(&opt);
	fclose(opt.input);

	return EXIT_SUCCESS;
}

static void usage()
{
	fprintf(stderr,
	"Usage: %s <OPTIONS> [FILE]\n"
	"\n"
	"Options:\n"
	"  -b, --bytes=LIST       Select only these bytes\n"
	"  -c, --characters=LIST  Select only these characters\n"
	"  -d, --delimiter=DELIM  Character to use as field delimiter\n"
	"  -f, --fields=LIST      Select only these fields\n"
	"  -h, --help             Display this help message and quit\n"
	"  -V, --version          Display version number and quit\n"
	"\n"
	"Lists:\n"
	"  N    Select N only\n"
	"  N-   Select N to end\n"
	"  N-M  Select N to M\n"
	"   -M  Select 1 to M\n"
	, PROGRAM);
	exit(EXIT_FAILURE);
}

static void parse_list(char *input, int *start, int *end)
{
	if(input[0] == '-') // -M
	{
		if(!(sscanf(input, "%d", end)))
		{
			fprintf(stderr, "%s: List must be numeric\n", PROGRAM);
			exit(EXIT_FAILURE);
		}
		*start = 1;
		*end = abs(*end);
	}
	else if(input[strlen(input) - 1] == '-') // N-
	{
		if(!(sscanf(input, "%d", start)))
		{
			fprintf(stderr, "%s: List must be numeric\n", PROGRAM);
			exit(EXIT_FAILURE);
		}
		*end = INT_MAX; // good enough
	}
	else if(!(sscanf(input, "%d-%d", start, end))) // N-M
	{
		fprintf(stderr, "%s: List must be numeric\n", PROGRAM);
		exit(EXIT_FAILURE);
	}
	else // N
	{
		if(!(sscanf(input, "%d", start)))
		{
			fprintf(stderr, "%s: List must be numeric\n", PROGRAM);
			exit(EXIT_FAILURE);
		}
		*end = *start;
	}
}
