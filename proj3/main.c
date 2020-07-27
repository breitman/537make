#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "text_parsing.h"
#include "list.h"
#include "build_spec_repr.h"
#include "build_spec_graph.h"
#include "proc_creation_prog_exe.h"

#define BUFSIZE 1024

int main() {
	List * structList;
	structList = create_graph();
	traverse(structList, NULL);
	return 0;
}
