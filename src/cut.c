#include "cut.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void cut_bytes(opt_t *opt)
{
	char *line;
	size_t len = 0;
	int start = opt -> start;
	int end = opt -> end;
	FILE *input = opt -> input;

	char buffer[BUFSIZ];
	setvbuf(stdout, buffer, _IOFBF, BUFSIZ);
	while(getline(&line, &len, input) != EOF)
	{
		printf("%.*s\n", (end - start + 1), (line + start - 1));
	}

	free(line);
}

void cut_chars(opt_t *opt)
{
	cut_bytes(opt); // TODO: seperate -b -c
}

void cut_fields(opt_t *opt)
{
}
