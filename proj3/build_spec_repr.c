#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

#include "build_spec_repr.h"
#include "list.h"

#define BUFSIZE 1024


List * find_target(build_spec * node, List *allNodes){
	//printf("in find target\n");
	
	List * allCurr;
	
	allCurr = allNodes;
	List *curr;

	while(allCurr->next != NULL){
		if(strcmp(node->target, ((build_spec*)allCurr->element)->target) != 0){		
			curr = node->dependencies;
			while(curr != NULL && curr->element != NULL){
				if(strcmp(((build_spec*)allCurr->element)->target, (curr->element)) == 0){
					node->children = add(node->children, allCurr->element);
				}
				curr = curr->next;
			}
		}
		allCurr = allCurr->next;
	}
	
	return allNodes;
}

