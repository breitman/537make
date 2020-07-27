
#ifndef build_spec_graph
#define build_spec_graph

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>

#include "text_parsing.h"
#include "build_spec_repr.h"
#include "list.h"

#define BUFSIZE 1024

List * create_graph();
void traverse(List *allNodes, List * parent); //traverse through array of nodes in a post-order 

#endif
