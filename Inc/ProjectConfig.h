#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

#include<stdio.h>
#include<string.h>

#define MAX_FLE_DT 50
#define DSH_O_FND 1
#define PRVS_DSH_O_FND_STT 2

#define INPT_FL_NME 1
#define OTPT_BTCH_FL_NME 2

#define MAX_CHLD_NM_LENGTH	100
#define MAX_PRNT_NM_LENGHT 	50
#define MAX_CHLD			100

void SaveChildsToFile(unsigned char Indx, FILE *FlPntr);
void PrintStartCommands(FILE *FilePntr);
void PrintEndCommands(FILE *FilePntr);
void FindParent(FILE *FlPntr , FILE *WrtFlPntr,int argc, char *argv[]);

typedef struct
{
	char ChldNm[MAX_CHLD_NM_LENGTH];
} Chld;

typedef struct
{
	char PrntNm[MAX_PRNT_NM_LENGHT];
	Chld ChldLst[MAX_CHLD];
	unsigned short NumChld;
} Prnt;


#endif