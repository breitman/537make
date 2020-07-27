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


void execute_command(char *command){
	char** argv; //= (char**)malloc(sizeof(char*)*BUFSIZE);
	
	argv = split(command, " "); //split command into array for execution
	pid_t child_pid;
	child_pid = fork();
	int child_status;
	if(child_pid == 0){ //execute command for child process;
		if(execvp(*argv, argv) < 0){	/*print error and exit if there is return value of exec func*/
			printf("Error: exec failed->unknown command\n");
			exit(0);
		}
	}
	else{
		while(wait(&child_status) != child_pid) //for parent, wait for process completion
			;
	}
}
