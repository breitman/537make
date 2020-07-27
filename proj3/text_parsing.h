#ifndef text_parsing
#define text_parsing

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "list.h"
#define BUFSIZE 1024


typedef struct build_spec{
	char * target;
	struct List * dependencies;
	struct List * commands;
	struct List * children;
	int visited;
}build_spec;

FILE* checkDirectory();
struct List* target_dependencies();
char** split(char string[], char* delim);

#endif
