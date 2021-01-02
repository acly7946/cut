#include "cut.h"
#include <stdio.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void cut_bytes(opt_t *opt)
{
	char c;
	int col = 0;
	int start = opt -> start;
	int end = opt -> end;
	FILE *input = opt -> input;
	
	while((c = getc(input)) != EOF)
	{
		col++;
		if(c == '\n')
		{
			putchar(c);
			col = 0;
		}
		if((col >= start) && (col <= end))
		{
			putchar(c);
		}
	}
}

void cut_chars(opt_t *opt)
{
	cut_bytes(opt); // TODO: seperate -b -c
}

void cut_fields(opt_t *opt)
{
}
