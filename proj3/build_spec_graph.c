#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>

#include "text_parsing.h"
#include "build_spec_graph.h"
#include "build_spec_repr.h"
#include "proc_creation_prog_exe.h"
#include "list.h"

#define BUFSIZE 1024

//are we setting up the graph the right way
List * create_graph(){
	List * structList;
	structList = target_dependencies();
	
	List * curr;
	curr = structList;
	
	while(curr->next != NULL){
		structList = find_target(((build_spec*)curr->element), structList);
		curr = curr->next;
	}
	
	return structList;
}

/*void traverse(List *structList, List * parent){ // how to link clean commands to root node
	List * curr;
	curr = structList;

	while(curr != NULL){
		
		if(((build_spec*)curr->element)->children != NULL){

			traverse(((build_spec*)curr->element)->children, curr);
		}
		
		struct stat buf1;
		//buf1 = (struct stat*)malloc(sizeof(struct stat));
		struct stat buf2;
		//buf2 = (struct stat*)malloc(sizeof(struct stat));

		char depPName[BUFSIZE];
	       	strcpy(depPName, "./");
		
		strcat(depPName, ((build_spec*)curr->element)->target);
		
		if(stat(depPName, &buf2) != 0){
			List * temp;
			temp = ((build_spec*)curr->element)->commands;
			while(temp != NULL ){
				execute_command(((char*)temp->element));
				temp = temp->next;
			}
		}
		if(parent != NULL){
			char targPName[BUFSIZE];
			strcpy(targPName, "./");
			strcat(targPName, ((build_spec*)parent->element)->target);
			stat(targPName, &buf1);
			time_t targTime;
			targTime = buf1.st_mtime;

			time_t depTime;
			depTime = buf2.st_mtime;

			if(difftime(targTime, depTime) > 0){ //if targtime older than deptime
				List *tempComm2 = ((build_spec*)parent->element)->commands;
				while(tempComm2->next != NULL){
					tempComm2 = tempComm2->next;				
					execute_command(((char*)tempComm2->element));
					printf("executed diff time \n");
				}
			}
		}
		curr = curr->next;
	}
	free(curr);
}*/

void traverse(List *structList, List * parent){ // how to link clean commands to root node
	List * curr = New_List();
	curr = structList;
	//List * parent;

	while(curr != NULL){
		printf("%s\n", ((build_spec*)curr->element)->target);
		
		if(((build_spec*)curr->element)->children != NULL){

			traverse(((build_spec*)curr->element)->children, curr);
		}

		printf("target: %s\n", ((build_spec*)curr->element)->target);
		
		struct stat *buf1;
		buf1 = malloc(sizeof(struct stat));
		struct stat *buf2;
		buf2 = malloc(sizeof(struct stat));

		char depPName[BUFSIZE];
	       	strcpy(depPName, "./");
		
		strcat(depPName, ((build_spec*)curr->element)->target);
		
		if(stat(depPName, buf2) != 0){
			printf("hello\n");
			List * temp = New_List();
			temp = ((build_spec*)curr->element)->commands;
			while(temp->next != NULL){
				execute_command(((char*)temp->element));
				temp = temp->next;
			}

		}

		char targPName[BUFSIZE];
		strcpy(targPName, "./");
		printf("%s\n", ((build_spec*)curr->element)->target);
		strcat(targPName, ((build_spec*)parent->element)->target);

		/*if(stat(targPName, buf1) != 0){
			List *tempComm1 = New_List();
			tempComm1 = ((build_spec*)parent->element)->commands;
			while(tempComm1->next != NULL){
				tempComm1 = tempComm1->next;
				execute_command(((char*)tempComm1->element));
			}
		}*/

		
		time_t targTime = buf1->st_mtime;
		
				
		time_t depTime = buf2->st_mtime;

		if(difftime(targTime, depTime) > 0){ //if targtime older than deptime
			List *tempComm2 = ((build_spec*)parent->element)->commands;
			while(tempComm2->next != NULL){
				tempComm2 = tempComm2->next;				
				execute_command(((char*)tempComm2->element));
				printf("executed diff time \n");
			}
		}
		curr = curr->next;
	}
}
