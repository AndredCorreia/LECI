#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "linked-list.h"

/*******************************************************/

SllNode* sllDestroy(SllNode* list)
{
    return list;
}

/*******************************************************/

void sllPrint(SllNode *list, FILE *fout)
{
	SllNode *current= list;
	
	while (current!=NULL){
		fprintf(fout, "Nmec: %u | Name: %s\n", current->reg.nmec, current->reg.name);
        	current = current->next;
    }

}

/*******************************************************/

SllNode* sllInsert(SllNode* list, uint32_t nmec, const char *name)
{
    assert(name != NULL && name[0] != '\0');
    assert(!sllExists(list, nmec));
    
    struct SllNode *newNode =(struct SllNode*)malloc(sizeof(struct SllNode));
    
    
    newNode->reg.nmec = nmec;
    newNode->reg.name = strdup(name);
    newNode->next = NULL;
    
    //meter no inicio da lista
    if (list == NULL || list->reg.nmec > nmec){
    	newNode->next= list;
    	return newNode;
    }
    
    //meter no meio da lista
    struct SllNode *current = list;
    

    while (current->next != NULL && current->next->reg.nmec < nmec) {
        current = current->next;
    }

    // Inserir o novo nó entre 'current' e 'current->next'
    newNode->next = current->next;
    current->next = newNode;

    return list;
}

/*******************************************************/

bool sllExists(SllNode* list, uint32_t nmec)
{
    return false;
}

/*******************************************************/

SllNode* sllRemove(SllNode* list, uint32_t nmec)
{
    assert(list != NULL);
    assert(sllExists(list, nmec));

    return list;
}

/*******************************************************/

const char *sllGetName(SllNode* list, uint32_t nmec)
{
    assert(list != NULL);
    assert(sllExists(list, nmec));

    return NULL;
}

/*******************************************************/

SllNode* sllLoad(SllNode *list, FILE *fin, bool *ok)
{
    assert(fin != NULL);

    if (ok != NULL)
       *ok = false; // load failure

    return NULL;
}

/*******************************************************/

