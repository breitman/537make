#ifndef build_spec_repr
#define build_spec_repr

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>

#include "text_parsing.h"

#define BUFSIZE 1024


List * find_target(build_spec *node, List *allNodes);

#endif

