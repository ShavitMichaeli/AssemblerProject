#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>


/*
	Denfines 
*/
#define MAX_INPUT 500
#define MAX_DATA_ENTRYS 50
#define MAX_SYMBOLS 50
#define BUFFER_SIZE 24
#define SIZE_OF_BINARY_STRING 7
#define MAX_BINARY_LETTERS 24
#define MAX_LINE_LENGTH 80

/* 
	Function decleration 
*/
void handleFiles(char *);
void firstLineAnalyze(char *);
void secondLineAnalyze(char *);
void newDataItem(char *, int, int, int);
struct dataItem* getData(char *);
void createData();
void newSymbol(char *, int, char *, char *);
struct symbolItem* getSymbol(char[]);
struct symbolItem* getSymbolByVal(int);
void setSymbolType(char *, char *);
char *intToBinary(int, int);
char *negToBinary(int numPrint,int num);
char* charToBinary(char);
char *binToHex(char *wordTable);
void newWord(int, char *, char *, char *, char *, char *, char *, char *);
void newDataWord(int, char *);
void printWords();
void editWord(int, char *);
int isData(char *buffer);
char *stringToHex(char *word);
char *splitBinary(char *word);
char *binToHex(char *data);
void saveWords(char *, int, int);
void saveExternals(char *);
void saveEntries(char *);
void freeWords();
void freeSymbols();
int isBlankLine(const char *);
char *strdup(const char *);

/*
	Defining the structs
*/
struct dataItem {
    char *functionName;
    int opcode;
    int funct;
	int maxOperands;
};

struct symbolItem {
    char * symbol;
    char * data;
    int val;
	char * type;
};

struct wordItem {
	int loc;
	char opcode[6];
	char src_address[2];
	char src_register[3];
	char dest_address[2];
	char dest_register[3];
	char funct[5];
	char are[3];
	char data[24];
};

enum boolean
{
    FALSE = 0,
    TRUE = 1
};