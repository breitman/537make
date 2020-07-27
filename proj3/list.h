#ifndef list
#define list

#include "text_parsing.h"

typedef struct List{
	void * element;
	struct List *next;
}List;

List* add(List * root, void * element);

int get_size(List * root);
List * New_List();

#endif
