#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFSIZE 1024

#include "list.h"

List* add(List * root, void * element){

	List * newNode = New_List();
	
	newNode->element = element;
	if(root == NULL){
		root = newNode;
		//free(newNode);
		return root;
	}
	if(root->next == NULL){
		root->next = newNode;
		root->next->next = NULL;
	}
	else{

		List * curr;
		curr = root;
		
		while(curr->next != NULL){
			curr = curr->next;
		}
		curr->next = newNode;
		curr->next->next = NULL;
		
	}
	//free(newNode->element);
	//free(newNode);
	return root;
}

List * New_List(){
	List * newList = NULL;
	return newList;
}

int get_size(List * root){
	int count = 0; 
	List * curr = root;
	if(curr == NULL){
		return count;
	}
	while(curr != NULL){
		count ++;
		curr = curr->next;
	}
	return count;
}
