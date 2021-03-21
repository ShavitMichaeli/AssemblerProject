/* Assmbler - Maman 14 by Barel Azulai, ID: 206251951 and Shavit Michaeli, ID: 205782659 */

#include "header.h"

/*
	Defining some global vars for further use.
*/
static int IC, DC, ERROR, L;

/*
	This function handles the input from the files the transferring the input to analysis.
*/
void handleFiles(char *inputFileName) {
	if (strcmp("as" , inputFileName + strlen(inputFileName) - 2) == 0) { /* Checking if the files format it .as (for Assembly files use only) */
		FILE *inf;
		int k = 0, j = 0;
		char firstInput[MAX_INPUT], secondInput[MAX_INPUT];

		/* Be ready for a new file analysis.*/
		ERROR = FALSE;

		inf = fopen(inputFileName, "r");
		if (inf == NULL) {
			fprintf(stderr, "[ERROR]: Input file does not exist!\n");
			exit(1);
		}
		IC = 100, DC = 0;
		while (fgets(firstInput, MAX_INPUT, inf) != NULL) {
			k++;
			if(isBlankLine(firstInput) == 0)
			{
				firstLineAnalyze(firstInput);
			}
		}
		fclose(inf);
		--IC;
		printf("\n[ALERT]: First scan has done. IC = %i, DC = %i. Starting second scan...", IC, DC);

		IC = 100, L = 0;
		inf = fopen(inputFileName, "r");
		while(fgets(secondInput,MAX_INPUT,inf)!=NULL)
		{
			j++;
			if(isBlankLine(secondInput) == 0)
			{
				secondLineAnalyze(secondInput);
			}
		}
		printf("\n[ALERT]: Second scan has been finished.");

		if(ERROR == TRUE) /* If any error happened don't save the output files.*/
		{
			printf("\n[ERROR]: Your Assembly file contains errors. Fix them!!!\n");
		}else{
			saveWords(inputFileName, DC, L);
			saveExternals(inputFileName);
			saveEntries(inputFileName);
			printf("\n[ALERT]: Your Assembly file is correct, saving .ob, .ent and .ext files..");
			printf("\n[ALERT]: .ob, .ent and .ext Files has been saved.\n");
		}
		freeWords();
		freeSymbols();
		fclose(inf);
	}else{
		printf("[ERROR]: Accepting only .as files.\n");
	}
}

/*
	This function doing the first "run" on the Assambly file.
	Basically this function is moving character by character and building words (in a buffer) for a further analysis.
*/
void firstLineAnalyze(char *asmLine)
{
	int i = 0, j = 0, k = 0, maxOperands = 0, isData = FALSE, isSymbol = FALSE, isFunction = FALSE, operands = 0, lineBreak = FALSE;
	char buffer[MAX_INPUT], symbol[MAX_INPUT], data[MAX_INPUT], databuff[MAX_INPUT];
	char opcode[MAX_INPUT], src_add[MAX_INPUT], src_reg[MAX_INPUT], dest_add[MAX_INPUT], dest_reg[MAX_INPUT], funct[MAX_INPUT], are[MAX_INPUT];
	char operandsname[2][10];
	if(strlen(asmLine) >= MAX_LINE_LENGTH) {
		printf("\n[ERROR]: Line is too long (80 characters): %s", asmLine);
    	ERROR = TRUE;
	}
	buffer[0] = '\0';
	for (; i <= strlen(asmLine); i++) {
		if (asmLine[i] >= '!' && asmLine[i] != ',') { /* Escape white spaces or ,*/
			if(asmLine[i] == ';') {
				lineBreak = TRUE;
				break;
			}
			if (asmLine[i] == ':') { /* found symbol, saving it for further use.*/
				strcpy(symbol, buffer);
				isSymbol = TRUE;
			}
			if (asmLine[i] >= 'A' || (asmLine[i] >= '-' && asmLine[i] <= '9') || asmLine[i] == ',' || asmLine[i] == '#' || asmLine[i] == '&') {
				strncat(buffer, &asmLine[i], 1);
			}
		} else {
			strcpy(are, "100");
			if (buffer[0] >= '!') {
				if (buffer[0] == '.') { /*found data of some kind (.data / .string), saving it for further use.*/
					strcpy(data, buffer);
					isData = TRUE;
				}
				if (isSymbol == TRUE && strcmp(symbol, buffer) != 0) { /*adding the symbol that we found to the symbol tabel and dropping errors if needs*/
					if(getSymbol(symbol) != NULL) {
						printf("\n[ERROR]: In line : %s[ERROR]: Symbol: %s already exist in the symbol table!", asmLine, symbol);
						ERROR = TRUE;
					}
					if(symbol[0] == 'r' && (symbol[1] > '0' || symbol[1] < '7')) {
						printf("\n[ERROR]: In line : %s[ERROR]: Symbol: %s cannot called as a register!", asmLine, symbol);
						ERROR = TRUE;
					}
					if(getData(symbol) != NULL) {
						printf("\n[ERROR]: In line : %s[ERROR]: Symbol: %s cannot called as a function!", asmLine, symbol);
						ERROR = TRUE;
					}
					if (buffer[0] == '.') {
						newSymbol(symbol, IC, ".data", "");
					} else {
						newSymbol(symbol, IC, ".code", "");
					}
					isSymbol = FALSE;
				}
				if (isData == TRUE && buffer[0] != '.') { /* handling the data kind that we found earlier (Counting the IC, creating a new symbol if needs) */
					if (strcmp(data, ".string") == 0) {
						DC += strlen(buffer) + 1;
						for(; j < strlen(buffer) + 1; ++j)
            			{
              				newDataWord(IC, charToBinary(buffer[j]));
							IC++;
						}
					}
					if (strcmp(data, ".data") == 0) {
						if (buffer[0] == '-') {
							newDataWord(IC, negToBinary(24, atoi(buffer + 1)));
            				IC++;
							DC++;
						} else {
							newDataWord(IC, intToBinary(24, atoi(buffer)));
              				IC++;
							DC++;
						}
					}
					if (strcmp(data, ".entry") == 0) {
						setSymbolType(buffer, ".entry");
					}
					if (strcmp(data, ".extern") == 0) {
						newSymbol(buffer, 0, "", ".extern");
					}
				}
				if (isFunction == TRUE && operands >= 0) { /* we found function, in this case we are counting the operands and analyzing them. */
					operands++;
					if(operands > maxOperands) {
						printf("\n[ERROR]: Too many operands in line: %s", asmLine);
            			ERROR = TRUE;
					}
					if(operands == 1) {
						if(buffer[0] == 'r' && (buffer[1] >= '0' || buffer[1] <= '7')) {
							strcpy(src_reg, intToBinary(3, buffer[1]));
							strcpy(src_add, "11");
						} else if(buffer[0] == '&') {
							strcpy(src_add, "10");
							strcpy(dest_add, "10");
						} else if(buffer[0] == '#') {
							strcpy(src_add, "00");
						} else {
							strcpy(src_add, "01");
						}
					}else if(operands == 2) {
						if(buffer[0] == 'r' && (buffer[1] >= '0' || buffer[1] <= '7')) {
							strcpy(dest_reg, intToBinary(3, buffer[1]));
							strcpy(dest_add, "11");
						} else if(buffer[0] == '#') {
							strcpy(dest_add, "00");
						} else {
							strcpy(dest_add, "01");
						}
					}
					if(buffer[0] == 'r' && ((buffer[1] < '0' || buffer[1] > '7') || buffer[2] >= '0')) {
						printf("\n[ERROR]: The register %s is not legal. in line %s", buffer, asmLine);
            			ERROR = TRUE;
					}
					if(operands > 0) {
						strcpy(operandsname[operands - 1], buffer);
					}
				}
				if (isSymbol == FALSE && isData == FALSE && buffer[0] != '#' && !(buffer[0] == 'r' && (buffer[1] >= '0' || buffer[1] <= '7')) && operands == 0) { /* we found function*/
					if (getData(buffer) != NULL) {
						isFunction = TRUE;
						operands = 0;
						maxOperands = getData(buffer)->maxOperands;
						strcpy(opcode, intToBinary(6, getData(buffer)->opcode));
						strcpy(funct, intToBinary(5, getData(buffer)->funct));
						strcpy(src_reg, "000");
						strcpy(dest_reg, "000");
						strcpy(dest_add, "00");
						strcpy(src_add, "00");
					} else {
						printf("\n[ERROR]: %s Function does not exist", buffer);
            			ERROR = TRUE;
					}
				}
			}
			strcpy(buffer, "\0");
			strcpy(databuff, "\0");
		}
	}
	if(isFunction == TRUE) { /* if we found function we are handling the operands and creating the word for the "memory image"*/
		if(operands == 0) {
			newWord(IC, opcode, "00", "000", "00", "000", funct, are);
		}else{
			if(operands == 1)
			{
				newWord(IC, opcode, "00", "000", src_add, src_reg, funct, are);
			}else{
				newWord(IC, opcode, src_add, src_reg, dest_add, dest_reg, funct, are);
			}
			for(; k < operands; k++) {
				if (operandsname[k][0] == '#') {
					IC++;
					if (operandsname[k][1] == '-') {
						strcat(databuff, negToBinary(21, atoi(operandsname[k] + 2)));
						strcat(databuff, "100");
					} else {
						strcat(databuff, intToBinary(21, atoi(operandsname[k] + 1)));
						strcat(databuff, "100");
					}
					newDataWord(IC, databuff);
				} else if(operandsname[k][0] != '#' && !(operandsname[k][0] == 'r' && (operandsname[k][0] >= '0' || operandsname[k][0] <= '7'))) {
					IC++;
					newDataWord(IC, "000000000000000000000010");
				}
			}
		}
	}
	if(isData == FALSE && lineBreak == FALSE) {
		IC++;
	}
}

/*

	This function works exactly like that first run function
	But this function only counts the IC again and counting the instructions (L) doing the final editing and adjustment for the "memory image"
	(Editing the distance between '&' char and symbols, handling the external symbols)

*/
void secondLineAnalyze(char *asmLine) {
  
	int i = 0, k = 0, difference = 0, isData = FALSE, operands = FALSE, isFunction = FALSE, lineBreak = FALSE;
	char buffer[MAX_INPUT], databuff[MAX_INPUT], data[MAX_INPUT], operandsname[2][10];
	for (; i <= strlen(asmLine); i++) {
		if (asmLine[i] >= '!' || asmLine[i] == ',') {
			if (asmLine[i] >= 'A' || (asmLine[i] >= '-' && asmLine[i] <= ':') || asmLine[i] == '#' || asmLine[i] == '&') {
				strncat(buffer, &asmLine[i], 1);
			}
			if(asmLine[i] == ';') {
				lineBreak = TRUE;
				break;
			}
		} else {
			if (buffer[0] >= '!') {
				if (buffer[0] == '.') {
					strcpy(databuff, buffer);
					isData = TRUE;
				}
				if (isData == TRUE && buffer[0] != '.') {
					if (strcmp(databuff, ".string") == 0) {
						IC = IC + strlen(buffer);
					}
					if (strcmp(databuff, ".data") == 0) {
              			IC++;
					}
					if (strcmp(databuff, ".entry") == 0) {
						setSymbolType(buffer, ".entry");
					}
				}
				if (isFunction == TRUE && operands >= 0) {
					operands++;
					if(operands > 0) {
						strcpy(operandsname[operands - 1], buffer);
					}
				}
				if (isData == FALSE && buffer[0] != '#' && !(buffer[0] == 'r' && strlen(buffer) == 2) && operands == 0) {
					if (getData(buffer) != NULL) {
						isFunction = TRUE;
						operands = 0;
						L++;
					}
				}
				if((buffer[0] != '#' && !(buffer[0] == 'r' && (buffer[1] >= '0' || buffer[1] <= '7')) && getSymbol(buffer) != NULL) || buffer[0] == '&') {
					if(ERROR == FALSE) {
						if(buffer[0] == '&') {
							if(strcmp(getSymbol(buffer + 1) -> type, ".extern") == 0) {
								printf("\n[ERROR]: Function cannot jump to external symbol - %s", buffer + 1);
							}
							difference = getSymbol(buffer + 1) -> val - (IC);
							if(difference > 0) {
								strcat(data, intToBinary(21, difference));
							}else{
								strcat(data, negToBinary(21, abs(difference)));
							}
							strcat(data, "100");
						}else if((strcmp(getSymbol(buffer) -> type, ".extern") == 0) ) {
							strcat(data, intToBinary(21, difference));
							strcat(data, "001");
							if(strcmp(databuff, ".extern") != 0) {
								newSymbol(buffer, IC + 1, "", "foroutput");
							}
						}else{
							strcat(data, intToBinary(21, getSymbol(buffer) -> val));
							strcat(data, "010");
						}
						editWord(IC + 1, data);
					}
				}
			}
			strcpy(buffer, "\0");
			strcpy(data, "\0");
   		}
		if(isFunction == TRUE) {
			if(operands > 0) {
				for(; k < operands; k++) {
					if (operandsname[k][0] == '#') {
						IC++;
						L++;
					} else if(operandsname[k][0] != '#' && !(operandsname[k][0] == 'r' && (operandsname[k][0] >= '0' || operandsname[k][0] <= '7'))) {
						IC++;
						L++;
					}
				}
			}
		}
	}
	if(isData == FALSE && lineBreak == FALSE) {
		IC++;
	}
	strcpy(databuff, "\0");
}
