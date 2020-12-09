#ifndef CUT_H
#define CUT_H

#include <stdio.h>

typedef struct
{
	int start;
	int end;
}	list_t;

typedef struct
{
	list_t bytes;
	list_t chars;
	list_t fields;
	char delimiter;
	char mode;
	FILE *input;
}	options_t;

void cut_bytes(options_t *options);
void cut_chars(options_t *options);
void cut_fields(options_t *options);
char *subString(const char *input, int start, int end);

#endif
