#include "cut.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cut_bytes(options_t *options)
{
	char *line;
	size_t len = 0;
	ssize_t read;
	while((read = getline(&line, &len, options -> input)) != EOF)
	{
		printf("%.*s\n", (options -> bytes.end - options -> bytes.start + 1), line + options -> bytes.start - 1);
	}
}

void cut_chars(options_t *options)
{
	return;
}

void cut_fields(options_t *options)
{
	return;
}
