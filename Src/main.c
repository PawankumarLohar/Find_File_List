#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ProjectConfig.h"


int main(int argc, char *argv[])
{
	
	FILE *FlPntr = NULL;
	FILE *WrtFlPntr = NULL;

	if(argv[INPT_FL_NME] != NULL && argv[OTPT_BTCH_FL_NME] != NULL)
	{
		FlPntr = fopen(argv[INPT_FL_NME], "r");
			if(FlPntr != NULL)
				WrtFlPntr = fopen(argv[OTPT_BTCH_FL_NME], "w");
	}
	else
	{
		printf("***Error --> Check Input & Output File Name Argument***\n");
	}
    
    FindParent(FlPntr , WrtFlPntr , argc, argv);
    return 0;
}


