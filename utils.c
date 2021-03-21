#include "header.h"

/*
	Converts Integers To Binary
*/
char *intToBinary(int numPrint, int num) {
  char *bin = (char*) malloc(numPrint + 1 * sizeof(char));
  int i = 0;
  for(i = numPrint-1; i >= 0; i--){
    if(num > 0){
      bin[i] = num % 2 == 0 ? '0' : '1';
      num/=2;
    }
    else bin[i] = '0';    
  }
  bin[numPrint + 1]='\0';
  return bin;
}

/*
	Converts Negative Integers To Binary using the "Complements Two" method.
*/
char *negToBinary(int numPrint, int num){
    char * bin = intToBinary(numPrint,num);
    int complementDone = 0;
    int i = 0;
    for(i = 0; i < numPrint; i ++)
        bin[i] = bin[i] == '1' ? '0' : '1';
    for(i = numPrint; i >= 0 && !complementDone; i--){
        if(bin[i] == '0') {
            bin[i] = '1';
            complementDone = !complementDone;
        }
        else if(bin[i]) {
            bin[i] = '0';
        }
    } 
    return bin;
}

/*
	Converts Charecters To Binary
*/
char * charToBinary(char ch) {
  int i=0;
  int j=0;
  char *bin = malloc(25); 

  for(i=0;i<16;++i)
    bin[i]='0';

  for(j = 7; j >= 0; --j){
    if(ch & (1 << j)) 
      strcat(bin,"1");
       else
      strcat(bin,"0");
    }
    bin[25]='\0';
  return bin;
}

/*
	Checks if the line is Blank (\n \t etc..)
*/
int isBlankLine(const char *str) {
    while (*str) {
        if (!isspace(*str++)) {
            return 0;
        }
    }
    return 1;
}


/*
	Converts Binary Charecters to Hexadecimal
*/
char *binToHex(char *data)
{
  int i=0;
  int j=0;
  int t=0;
  char *hex = malloc(7); 
  char *zero = "0";
  char *one="1";
  char *two="2";
  char *three="3";
  char *four="4";
  char *five="5";
  char *six="6";
  char *seven="7";
  char *eight="8";
  char *nine="9";
  char *A="a";
  char *B="b";
  char *C="c";
  char *D="d";
  char *E="e";
  char *F="f";
  char *binZero={"0000\0"};
  char *binOne={"0001\0"};
  char *binTwo={"0010\0"};
  char *binThree={"0011\0"};
  char *binFour={"0100\0"};
  char *binFive={"0101\0"};
  char *binSix={"0110\0"};
  char *binSeven={"0111\0"};
  char *binEight={"1000\0"};
  char *binNine={"1001\0"};
  char *binA={"1010\0"};
  char *binB={"1011\0"};
  char *binC={"1100\0"};
  char *binD={"1101\0"};
  char *binE={"1110\0"};
  char *binF={"1111\0"};
  char *buff= malloc(5);
  buff[0]='\0';
  buff[1]='\0';
  buff[2]='\0';
  buff[3]='\0';
  buff[4]='\0';
  buff[5]='\0';
  hex[0]='\0';
  hex[1]='\0';
  hex[2]='\0';
  hex[3]='\0';
  hex[4]='\0';
  hex[5]='\0';
  hex[6]='\0';

  for(i=0;i<29;i++){
    if(j<4)
    {
      buff[j]=data[i];
      j++;
    }
    if(j==4){
    {
        if(strcmp(buff,binZero)==0)
        {
          hex[t]=*zero;
        }
        if(strcmp(buff,binOne)==0)
        {
          hex[t]=*one;
        }
        if(strcmp(buff,binTwo)==0)
        {
          hex[t]=*two;
        }
        if(strcmp(buff,binThree)==0)
        {
          hex[t]=*three;
        }
        if(strcmp(buff,binFour)==0)
        {
          hex[t]=*four;
        }
        if(strcmp(buff,binFive)==0)
        {
          hex[t]=*five;
        }
        if(strcmp(buff,binSix)==0)
        {
          hex[t]=*six;
        }
        if(strcmp(buff,binSeven)==0)
        {
          hex[t]=*seven;
        }
        if(strcmp(buff,binEight)==0)
        {
          hex[t]=*eight;
        }
        if(strcmp(buff,binNine)==0)
        {
          hex[t]=*nine;
        }
        if(strcmp(buff,binA)==0)
        {
          hex[t]=*A;
        }
        if(strcmp(buff,binB)==0)
        {
          hex[t]=*B;
        }
        if(strcmp(buff,binC)==0)
        {
          hex[t]=*C;
        }
        if(strcmp(buff,binD)==0)
        {
          hex[t]=*D;
        }
        if(strcmp(buff,binE)==0)
        {
          hex[t]=*E;
        }
        if(strcmp(buff,binF)==0)
        {
          hex[t]=*F;
        }
        j=0;
        t++;
      }
    }
  }
  return hex;
}

/*
	Split the full Binary Charecters to Hexadecimal
*/
char *splitBinary(char *word)
{
  char *split = malloc(29);
  int i,j;
  for(i=0,j=0;i<=31;i++)
  {
    if(i<4){/**/
      split[i]=word[j];
      ++j;
    }
    if(i==4){
      split[i]=' ';
    }
    if(i>4&&i<9)
    {
      ++j;
      split[i]=word[j-1];
    }
    if(i==9)
    {
      split[i]=' ';
    }
    if(i>9&&i<14){
      ++j;
      split[i]=word[j-1];
    }
    if(i==14)
    {
      split[14]=' ';
    }
    if(i>14&&i<19)
    {
      ++j;
      split[i]=word[j-1];
    }
    if(i==19)
    {
      split[i]=' ';
    }
    if(i>19&&i<24){
      ++j;
      split[i]=word[j-1];
    }
    if(i==24)
    {
      split[i]=' ';
    }
    if(i>24)
    {
      ++j;
      split[i]=word[j-1];
    }
    if(i==29)
    {
      split[i]='\0';
      j++;
    }
  }
  return split;
}


char *strdup(const char *str)
{
    int n = strlen(str) + 1;
    char *dup = malloc(n);
    if(dup)
    {
        strcpy(dup, str);
    }
    return dup;
}