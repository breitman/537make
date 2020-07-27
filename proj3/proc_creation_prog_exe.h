#ifndef proc_creation_prog_exe
#define proc_creation_prog_exe

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "build_spec_graph.h"
#include "text_parsing.h"

#define BUFSIZE 1024

void execute_command(char *command);

#endif
