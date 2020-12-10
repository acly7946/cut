#include "cut.h"
#include <errno.h>
#include <getopt.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPTSTR "b:c:d:f:hv"
#define VERSION "cut version NULL (Mon 7 Dec)\n"

void usage(char *program_name);
void parseList(char *input, int *start, int *end);

int main(int argc, char *argv[])
{
	int opt;
	options_t options =
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
	while((opt = getopt_long(argc, argv, OPTSTR, long_options, NULL)) != EOF)
	{
		switch(opt)
		{
			case 'b':
				options.mode += 'b';
				break;

			case 'c':
				options.mode += 'c';
				break;

			case 'f':
				options.mode += 'f';
				break;

			case 'd':
				if(strlen(optarg) > 1)
				{
					fprintf(stderr, "%s: delimiter must be a single character\n", basename(argv[0]));
					return EXIT_FAILURE;
				}
				sscanf(optarg, "%c", &options.delimiter);
				break;

			case 'v':
				printf(VERSION);
				return EXIT_SUCCESS;

			case 'h':
			default:
				usage(basename(argv[0]));
				break;
		}
	}

	// Error checking
	if(!options.mode) // no mode specified
	{
		fprintf(stderr, "%s: specify bytes, characters or fields\n", basename(argv[0]));
		return EXIT_FAILURE;
	}

	if(!(options.mode == 'b' || options.mode =='c' || options.mode == 'f')) // multiple mode specified
	{
		fprintf(stderr, "%s: only one type of list may be specified\n", basename(argv[0]));
		return EXIT_FAILURE;
	}

	if(optind < argc) // filename
	{
		if(!(options.input = fopen(argv[optind++], "r")))
		{
			fprintf(stderr, "%s: cannot access '%s': ", basename(argv[0]), argv[--optind]);
			perror(NULL);
			return EXIT_FAILURE;
		}
	}

	switch(options.mode)
	{
		case 'b':
			cut_bytes(&options);
			break;
		
		case 'c':
			cut_chars(&options);
			break;
		
		case 'f':
			cut_fields(&options);
			break;
	}

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

	char *usage = malloc(strlen("Usage: ") + strlen(program_name) + strlen(" OPTIONS [FILE]\n") + strlen(usage_format) + 1);
	sprintf(usage, "Usage: %s <OPTIONS> [FILE]\n%s", program_name, usage_format);

	printf("%s", usage);
	free(usage);
	exit(EXIT_FAILURE);
}

void parseList(char *input, int *start, int *end)
{

}
