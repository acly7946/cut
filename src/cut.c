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
	char c;
	int field;
	char *line;
	ssize_t line_length;
	size_t line_size = 0;
	int start = opt -> start;
	int end = opt -> end;
	FILE *input = opt -> input;
	char delimiter = opt -> delimiter;

	while((line_length = getline(&line, &line_size, input)) != EOF)
	{
		field = 1;
		for(int i = 0; i <= line_length; i++)
		{
			c = line[i];
			if(c == delimiter)
			{
				field++;
			}
			if((field >= start) && (field <= end))
			{
				if(c != '\n')
				{
					putchar(c);
				}
			}
		}
		putchar('\n');
	}
}
