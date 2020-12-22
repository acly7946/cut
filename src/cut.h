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
}	opt_t;

void cut_bytes(opt_t *opt);
void cut_chars(opt_t *opt);
void cut_fields(opt_t *opt);

#endif
