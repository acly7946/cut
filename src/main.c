#include "cut.h"
#include <errno.h>
#include <getopt.h>
#include <libgen.h>
//#include <limits.h> // CHAR_MAX for long only opts
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "Wed 23 dec"

void usage(char *program_name);
void parse_list(char *input, int *start, int *end);

int main(int argc, char *argv[])
{
	int optc;
	void (*cut_mode)(opt_t *) = NULL;
	opt_t opt =
	{
		.delimiter='\t',
		.input=stdin,
	};
	static struct option long_options[] =
	{
		{"bytes", required_argument, NULL, 'b'},
		{"characters", required_argument, NULL, 'c'},
		{"delimiter", required_argument, NULL, 'd'},
		{"fields", required_argument, NULL, 'f'},
		{"help", no_argument, NULL, 'h'},
		{"version", no_argument, NULL, 'v'},
	};

	// Option parsing
	while((optc = getopt_long(argc, argv, "b:c:d:f:hv", long_options, NULL)) != EOF)
	{
		switch(optc)
		{
			case 'b':
				if(cut_mode)
				{
					fprintf(stderr, "%s: only one type of list may be specified\n", basename(argv[0]));
					return EXIT_FAILURE;
				}
				cut_mode = &cut_bytes;
				parse_list(optarg, &opt.start, &opt.end);
				break;

			case 'c':
				if(cut_mode)
				{
					fprintf(stderr, "%s: only one type of list may be specified\n", basename(argv[0]));
					return EXIT_FAILURE;
				}
				cut_mode = &cut_chars;
				parse_list(optarg, &opt.start, &opt.end);
				break;

			case 'f':
				if(cut_mode)
				{
					fprintf(stderr, "%s: only one type of list may be specified\n", basename(argv[0]));
					return EXIT_FAILURE;
				}
				cut_mode = &cut_fields;
				parse_list(optarg, &opt.start, &opt.end);
				break;

			case 'd':
				if(strlen(optarg) > 1)
				{
					fprintf(stderr, "%s: delimiter must be a single character\n", basename(argv[0]));
					return EXIT_FAILURE;
				}
				sscanf(optarg, "%c", &opt.delimiter);
				break;

			case 'v':
				printf("%s (%s)\n", basename(argv[0]), VERSION);
				return EXIT_SUCCESS;

			case 'h':
			default:
				usage(basename(argv[0]));
				break;
		}
	}

	if(!cut_mode)
	{
		fprintf(stderr, "%s: specify bytes, characters or fields\n", basename(argv[0]));
		return EXIT_FAILURE;
	}

	if(optind < argc) // filename
	{
		if(strcmp(argv[optind], "-") == 0)
		{
		}
		else if(!(opt.input = fopen(argv[optind], "r")))
		{
			fprintf(stderr, "%s: cannot access '%s': ", basename(argv[0]), argv[optind]);
			perror(NULL);
			return EXIT_FAILURE;
		}
	}

	cut_mode(&opt);
	fclose(opt.input);

	return EXIT_SUCCESS;
}

void usage(char *program_name)
{
	char *usage_format =
	"\n"
	"Options: \n"
	"  -b, --bytes=LIST       Select only these bytes\n"
	"  -c, --characters=LIST  Select only these characters\n"
	"  -d, --delimiter=DELIM  Character to use as field delimiter\n"
	"  -f, --fields=LIST      Select only these fields\n"
	"  -h, --help             Display this help message and quit\n"
	"  -v, --version          Display version number and quit\n";

	char *usage = malloc(strlen("Usage: ") + strlen(program_name) + strlen(" <OPTIONS> [FILE]\n") + strlen(usage_format) + 1);
	sprintf(usage, "Usage: %s <OPTIONS> [FILE]\n%s", program_name, usage_format);

	printf("%s", usage);
	free(usage);
	exit(EXIT_FAILURE);
}

void parse_list(char *input, int *start, int *end)
{
	if(input[0] == '-') // input is -M
	{
		if(!(sscanf(input, "%d", end)))
		{
			printf("ERROR\n");
		}
		*start = 1;
		*end = abs(*end);
	}
	else if(!(sscanf(input, "%d-%d", start, end)))
	{
		printf("ERROR\n");
	}
}
