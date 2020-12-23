#include "cut.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void cut_bytes(opt_t *opt)
{
	char *line;
	//char *substring;
	size_t len = 0;
	ssize_t read;
	while((read = getline(&line, &len, opt -> input)) != EOF)
	{
		//strncpy(substring, line, )
		printf("%.*s", (opt -> end - opt -> start + 1), line + opt -> start - 1);
	}
}

void cut_chars(opt_t *opt)
{
	char *line;
	//char *substring;
	size_t len = 0;
	ssize_t read;
	while((read = getline(&line, &len, opt -> input)) != EOF)
	{
		//strncpy(substring, line, )
		printf("%.*s", (opt -> end - opt -> start + 1), line + opt -> start - 1);
	}
}

void cut_fields(opt_t *opt)
{
}
