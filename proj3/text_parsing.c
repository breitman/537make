#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>

#include "text_parsing.h"
#include "list.h"

#define BUFSIZE 1024

FILE* checkDirectory(){ 
	FILE* file;
	struct dirent* myFile;
	DIR* dir;
	char* path; // = (char*)malloc(sizeof(char)*100);
	path = "./"; //IS THIS THE PATH
	dir = opendir(path);
	
	while((myFile = readdir(dir))){ //iterate through each file in directory
		if( (strcmp(myFile->d_name, "Makefile")==0)){
			file = fopen("./Makefile", "r");
			closedir(dir);
			return file;
		}
		if(strcmp(myFile->d_name, "makefile")==0){ //get the file we want
			file = fopen("./makefile", "r");
			closedir(dir);
			return file;
		}
	}
	closedir(dir);

	fprintf(stderr, "Error : Failed to open makerfile from Proc Directory\n"); 
	exit(1);
}

List* target_dependencies(){
	FILE* file;
	file = checkDirectory();
	char *target = (char*)malloc(sizeof(char)*BUFSIZE);
	char *depName = (char*)malloc(sizeof(char)*BUFSIZE);
	
	char *someComm = (char*)malloc(sizeof(char)); //command for some target

	List *structList = NULL;


	int lineNum = 1;
	char * line = (char*)malloc(sizeof(char)*BUFSIZE);
	int lPos = 0;

	char c = fgetc(file);
	
	int i = 0;
	int x = 0;

	build_spec *tnd = (build_spec*)malloc(sizeof(build_spec)*BUFSIZE); //target and dependencies (and commands)
	tnd->commands = NULL;
	tnd->target = NULL;

	tnd->dependencies = NULL;

	tnd->children = NULL;
	int pos = 0;

	
	while(c != EOF){

		do{
			if(c != ' '){
				target[i++] = c;
			}
			c = fgetc(file);
			

		} while(c != ':' && (tnd->target) == NULL);
		
		if(c == ':' && (tnd->target) == NULL){
			target[i] = '\0';
			//printf("target is: %s\n", target);
			tnd->target = target;
			target = (char*)calloc(strlen(target), sizeof(char));
			i = 0;
		}
		
		while(tnd->target != NULL ){
			if(c == ':'){
				c = fgetc(file);
				while(c == ' '){
					c = fgetc(file);
				}
			}
			while(c == '\t'){ //if its tab, we know we are at command step
				c = fgetc(file);
				if(c == '\t'){
					while(c != '\n'){
						line[lPos++] = c;
						c = fgetc(file);
					}
					line[lPos] = '\0';
					fprintf(stderr, "Line %d: Invalid Line: %s\n",lineNum, line);
					exit(0);
				}
				pos = 0;
				while(c != '\n'){
					if(c == EOF){
						if(pos + 1> BUFSIZE){
							fprintf(stderr, "Error: Command exceeds buffer size\n");
							exit(0);
						}
						tnd->commands = add(tnd->commands, (char *)someComm);
						structList = add(structList, (build_spec*)tnd); 
						return structList;
					}
					someComm[pos++] = c;
					c = fgetc(file);
				}
				someComm[pos] = '\0';
				if(pos > BUFSIZE){
					fprintf(stderr, "Error: Command exceeds buffer size\n");
					exit(0);
				}
				
				tnd->commands = add(tnd->commands, (char *)someComm);

				someComm = (char*)calloc(strlen(someComm), sizeof(char)*BUFSIZE);
			}
			while(c != '\n'){
			        if(c == ' '){
					c = fgetc(file);
					while(c == ' '){
						c = fgetc(file);
					}
				        depName[x] = '\0';
				        tnd->dependencies = add(tnd->dependencies, (char*)depName);
				        depName = (char*)calloc(strlen(depName), sizeof(char)*BUFSIZE);
					x = 0;
			        }
			        else{
				        depName[x++] = c;
				        c = fgetc(file);
					if(c == '\n'){
						lineNum ++;
						depName[x] = '\0';
				        	tnd->dependencies = add(tnd->dependencies, (char*)depName);
				        	depName = (char*)calloc(strlen(depName), sizeof(char)*BUFSIZE);
						x = 0;
					}
			        }
			}
			if(c == '\n'){
				while(c == '\n'){
					lineNum++;
					c = fgetc(file);
				}
				if(c != '\t'){
					structList =add(structList, (build_spec*)tnd);
					tnd = (build_spec*)calloc(sizeof(build_spec)*BUFSIZE, sizeof(build_spec));
					tnd->dependencies = NULL;
					tnd->commands = NULL;
					tnd->children = NULL;
					tnd->target = NULL;
				}
			}
		}
		//lineNum++;
		
		if(c == ' '){
			continue;
		}
		if(c == '#'){
			while(c != '\n'){
				c = fgetc(file);
			}
			c = fgetc(file);
			lineNum++;
		}
	}
	free(depName);
	free(someComm);
	free(tnd);
	free(target);
	free(line);

	return structList;
}


char** split(char string[], char* delim){
	char** arr = (char**)malloc(sizeof(char*)*BUFSIZE);  
	char* spl; // = (char*)malloc(sizeof(char)*BUFSIZE);
	spl = strtok(string, delim);
	int x = 0;

	while(spl){ //iterate through string
		arr[x] = spl;
		spl = strtok(NULL, delim); //basically a next word
		x++;
	}
	arr[x] = NULL;
	free(spl);
	return arr;
}


