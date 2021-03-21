#include "header.h"

struct symbolItem* symbolTable[MAX_SYMBOLS];

/*
	Creating new symbol struct and adding to the symbols table
*/

void newSymbol(char *symbol, int val, char *data, char *type)
{
	int i = 0;
    struct symbolItem *newSymbol = (struct symbolItem*) malloc(sizeof(struct symbolItem));
	newSymbol-> symbol = strdup(symbol);
    newSymbol-> val = val;
    newSymbol-> data = strdup(data);
	newSymbol-> type = strdup(type);
    while(symbolTable[i] != NULL)
    {
      i++;
    }
    symbolTable[i] = newSymbol;
}

/*
	Getting the symbol struct by the symbol name
	Returning the struct by his symbol name that used as a key.
*/
struct symbolItem* getSymbol(char symbol[])
{
    int i = 0;
    while(symbolTable[i] != NULL) {
        if (strcmp(symbolTable[i] -> symbol, symbol) == 0)
            return symbolTable[i];
        ++i;
    }
    return NULL;
}

/*
	Getting the symbol struct by the type name
	Returning the struct by his symbol type that used as a key.
*/
struct symbolItem* getSymbolByType(char type[])
{
	int i = 0;
	while(symbolTable[i] != NULL) {
		if (strcmp(symbolTable[i] -> type, type) == 0)
			return symbolTable[i];
		++i;
	}
	return NULL;
}


/*
	Saving the entries symbols of the current assembly file to .ent file
*/
void saveEntries(char * fileName) {
	if(getSymbolByType(".entry") != NULL) {
		FILE *outf;
		int i = 0;
		char finalFileName[MAX_INPUT];
		finalFileName[0] = '\0';
		strncat(finalFileName, fileName, strlen(fileName) - 3);
		strncat(finalFileName, ".ent", 5);
		outf = fopen(finalFileName, "w");
		while(symbolTable[i] != NULL) {
			if(strcmp(symbolTable[i] -> type, ".entry") == 0) {
				fprintf(outf, "%s\t%07d\n", symbolTable[i] -> symbol, symbolTable[i] -> val);
			}
			++i;
		}
		fclose(outf);
	}
}

/*
	Saving the external symbols of the current assembly file to .ext file
*/
void saveExternals(char * fileName) {
	if(getSymbolByType("foroutput") != NULL) {
		FILE *outf;
		int i = 0;
		char finalFileName[MAX_INPUT];
		finalFileName[0] = '\0';
		strncat(finalFileName, fileName, strlen(fileName) - 3);
		strncat(finalFileName, ".ext", 5);
		outf = fopen(finalFileName, "w");
		while(symbolTable[i] != NULL) {
			if(strcmp(symbolTable[i] -> type, "foroutput") == 0) {
				fprintf(outf, "%s\t%07d\n", symbolTable[i] -> symbol, symbolTable[i] -> val);
			}
			++i;
		}
		fclose(outf);
	}
}

/*
	Setting the symbol type (external / entry)
*/
void setSymbolType(char * symbol, char * type)
{
	if(getSymbol(symbol) != NULL) {
		getSymbol(symbol)-> type = type;
	}
}

/*
	"Freeing" (Emptying) the symbol table for a assembly new file analysis.
*/
void freeSymbols() {
	int i = 0;
	while(symbolTable[i] != NULL) {
		symbolTable[i] = NULL;
		++i;
	}
}