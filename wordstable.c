#include "header.h"

struct wordItem* wordsTable[MAX_SYMBOLS];

/*
	Creating new word struct and adding to the words table (The "memory image" - we called it words table.)
	This type of word is handling all the data that the assembler analyzing. 
*/
void newWord(int loc, char *opcode, char *src_add, char *src_reg, char *dest_add, char *dest_reg, char *funct, char *are)
{
	int i = 0;

	struct wordItem *newWord = (struct wordItem*) malloc(sizeof(struct wordItem));

	newWord-> loc = loc;
	strcpy(newWord-> opcode, opcode);
	strcpy(newWord-> src_address, src_add);
	strcpy(newWord-> src_register, src_reg);
	strcpy(newWord-> dest_address, dest_add);
	strcpy(newWord-> dest_register, dest_reg);
	strcpy(newWord-> funct, funct);
	strcpy(newWord-> are, are);

    while(wordsTable[i] != NULL) 
    {
      i++;
    }
    wordsTable[i] = newWord;
}

/*
	Creating new word struct and adding to the words table (The "memory image" - we called it words table.)
	Same as the previous function just creating word that handels data like character or integer value.
*/
void newDataWord(int loc, char *data)
{
	int i = 0;
	struct wordItem *newWord = (struct wordItem*) malloc(sizeof(struct wordItem));
	newWord-> loc = loc;
	strcpy(newWord-> data, data);
    while(wordsTable[i] != NULL) 
    {
      i++;
    }
    wordsTable[i] = newWord;
}

/*
	Getting the word by the word location (IC) and returning the struct of the requsted word
*/
struct wordItem* getWord(int loc) 
{
    int i = 0;
    while(wordsTable[i] != NULL) {
        if (wordsTable[i] -> loc == loc)
            return wordsTable[i];
        ++i;
    }
    return NULL;
}

/*
	This function editing the content of word
	Getting the location of the word (IC) and the requsted data to change to.
*/
void editWord(int loc, char *data)
{
	if(getWord(loc) != NULL) {
		strcpy(getWord(loc)-> data, data);
	}
}

/*
	Saving the the words table (the "memory image") to .ob file
*/
void saveWords(char * fileName, int DC, int L) {
	FILE *outf;
	int i = 0;
	char finalFileName[MAX_INPUT];
	finalFileName[0] = '\0';
	strncat(finalFileName, fileName, strlen(fileName) - 3);
	strncat(finalFileName, ".ob", 4);
	outf = fopen(finalFileName, "w");
	fprintf(outf, "\t%i\t%i\n", L, DC);
    while(wordsTable[i] != NULL) {
		if(strcmp(wordsTable[i]->data, "") == 0) {
			fprintf(outf, "%07d\t%s\n", wordsTable[i]-> loc, binToHex(wordsTable[i]-> opcode));
		}else{
			fprintf(outf, "%07d\t%s\n", wordsTable[i]-> loc,  binToHex(wordsTable[i]-> data));
		}   
        ++i;
    }	
	fclose(outf);
}

/*
	"Freeing" (Emptying) the words table (the "memory image") for a assembly new file analysis.
*/
void freeWords() {
	int i = 0;
	while(wordsTable[i] != NULL) {
			wordsTable[i] = NULL;
		++i;
	}
}