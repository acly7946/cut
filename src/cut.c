#include "cut.h"
#include <stdio.h>

void cut_bytes(opt_t *opt)
{
	char c;
	int column = 0;
	int start = opt -> start;
	int end = opt -> end;
	FILE *input = opt -> input;
	
	while((c = getc(input)) != EOF)
	{
		column++;
		if(c == '\n')
		{
			putchar(c);
			column = 0;
		}
		if((column >= start) && (column <= end))
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
