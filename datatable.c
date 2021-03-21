#include "header.h"

struct dataItem* dataTable[MAX_DATA_ENTRYS];

/* 
	Entering new struct of data to the array of data structs
 */
void newDataItem(char *functionName, int opcode, int funct, int maxOperands) 
{
    int i = 0;
    struct dataItem *newItem = (struct dataItem*) malloc(sizeof(struct dataItem));
    newItem-> functionName = functionName;
    newItem-> opcode = opcode;
    newItem-> funct = funct;
	newItem-> maxOperands = maxOperands;
    while(dataTable[i] != NULL) {
      i++;
    }
    dataTable[i] = newItem;
}

/*
	Getting the requested data struct from the array.
	Returning the struct by his function name that used as a key.
*/
struct dataItem* getData(char key[]) 
{
    int i = 0;
    while(dataTable[i] != NULL) {
        if (strcmp(dataTable[i] -> functionName, key) == 0)
            return dataTable[i];
        ++i;
    }
    return NULL;
}

/*
	Creating the data items.
*/
void createData() 
{
    newDataItem("mov", 0, 0, 2);
    newDataItem("cmp", 1, 0, 2);
    newDataItem("add", 2, 1, 2);
    newDataItem("sub", 2, 2, 2);
    newDataItem("lea", 4, 0, 2);
    newDataItem("clr", 5, 1, 1);
    newDataItem("not", 5, 2, 1);
    newDataItem("inc", 5, 3, 1);
    newDataItem("dec", 5, 4, 1);
    newDataItem("jmp", 9, 1, 1);
    newDataItem("bne", 9, 2, 1);
    newDataItem("jsr", 9, 3, 1);
    newDataItem("red", 12, 0, 1);
    newDataItem("prn", 13, 0, 1);
    newDataItem("rts", 14, 0, 0);
    newDataItem("stop",15, 0, 0);
}
