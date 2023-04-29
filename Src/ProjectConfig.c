#include "ProjectConfig.h"

#ifdef BATCH_REQUIRE
 const char *StrtCmmnds = "\nren *.C *.c \nren *.H *.h \nmkdir Src \nmkdir build \nmkdir Inc \nmkdir Setup \nmkdir Unused\\Src \nmkdir Unused\\Inc \nmkdir Unused\\Batch \nmkdir Unused\\Setup \n";
 const char *EndCmmnds = " \nmove *.h Inc \nmove *.c Unused\\Src \nmove *.s Unused\\Setup \nmove *.h Unused\\Inc \ndel *.d \ndel *.o \nmove *.scc Unused \n";
#endif

Prnt PrntLst[50];

void SaveChildsToFile(unsigned char Indx, FILE *FlPntr)
{

	unsigned char TempIndx;
	unsigned char OneDotOChild;
	unsigned char ChldNum;

	unsigned char MatchChldIndx[100];
	unsigned char NotMatchChldIndx[100];
	unsigned char MatchFlag = 0;
	unsigned short MatchChldNum = 0;
	char *Pntr = NULL;
	TempIndx = Indx;
	OneDotOChild = PrntLst[Indx].NumChld;
	unsigned char Indx_2;
	unsigned char Indx_3;
	
	while (OneDotOChild > 0)
	{
		// printf("PrntLst[%d]-->Child[%d]-->%s\n",Indx,OneDotOChild - 1,PrntLst[Indx].ChldLst[OneDotOChild - 1].ChldNm);
		while (TempIndx > 0)
		{
			if (strcmp(PrntLst[Indx].ChldLst[OneDotOChild - 1].ChldNm, PrntLst[TempIndx - 1].PrntNm) == 0)
			{
				MatchChldIndx[MatchChldNum] = OneDotOChild - 1;
				MatchChldNum += 1;
				// printf("PrntLst[%d].ChldLst[%d].ChldNm-->%s,PrntLst[%d].PrntNm-->%s\n",Indx,OneDotOChild-1,PrntLst[Indx].ChldLst[OneDotOChild-1].ChldNm,TempIndx - 1,PrntLst[TempIndx - 1].PrntNm);
				for (ChldNum = (PrntLst[TempIndx - 1].NumChld); ChldNum > 0; ChldNum--)
				{
					Pntr = strstr(PrntLst[TempIndx - 1].ChldLst[ChldNum - 1].ChldNm, ".o");
					if (Pntr != NULL && strcmp(PrntLst[TempIndx - 1].ChldLst[ChldNum - 1].ChldNm,"startup_stm32h750xx.o")!=0)
					{
						*(Pntr + 1) = 'c';
						#ifdef BATCH_REQUIRE
							fprintf(FlPntr, "move %s Src \n", PrntLst[TempIndx - 1].ChldLst[ChldNum - 1].ChldNm);
						#else
							fprintf(FlPntr, "%s\n", PrntLst[TempIndx - 1].ChldLst[ChldNum - 1].ChldNm);
						#endif
					}
					else if(strcmp(PrntLst[TempIndx - 1].ChldLst[ChldNum - 1].ChldNm,"startup_stm32h750xx.o")==0)
					{
						Pntr = strstr(PrntLst[TempIndx - 1].ChldLst[ChldNum - 1].ChldNm, ".o");
						if(Pntr != NULL)
						{
							*(Pntr + 1) = 's';
							#ifdef BATCH_REQUIRE
								fprintf(FlPntr, "move %s Setup \n", PrntLst[TempIndx - 1].ChldLst[ChldNum - 1].ChldNm);
							#else
								fprintf(FlPntr, "%s\n", PrntLst[TempIndx - 1].ChldLst[ChldNum - 1].ChldNm);
							#endif
						}
						
					}
					// printf("PrntLst[%d].ChldLst[%d].ChldNm -- > %s\n",TempIndx-1,ChldNum-1,PrntLst[TempIndx-1].ChldLst[ChldNum-1].ChldNm);
				}
			}
			TempIndx -= 1;
		}
		TempIndx = Indx;
		OneDotOChild -= 1;
	}
	//printf("Match Number = %d\n", MatchChldNum);
	for (Indx_2 = 0; Indx_2 < PrntLst[Indx].NumChld; Indx_2++)
	{
		for (Indx_3 = 0; Indx_3 < MatchChldNum; Indx_3++)
		{
			if (Indx_2 == MatchChldIndx[Indx_3])
			{
				MatchFlag = 1;
			}
		}
		if (MatchFlag != 1)
		{

			//printf("not match indx-->%d\n", Indx_2);
			Pntr = strstr(PrntLst[Indx].ChldLst[Indx_2].ChldNm, ".o");
			if (Pntr != NULL)
			{
				*(Pntr + 1) = 'c';
				#ifdef BATCH_REQUIRE
					fprintf(FlPntr, "move %s Src \n", PrntLst[Indx].ChldLst[Indx_2].ChldNm);
				#else
					fprintf(FlPntr, "%s\n", PrntLst[Indx].ChldLst[Indx_2].ChldNm);
				#endif
			}
		}
		else
		{
			MatchFlag = 0;
		}
	}
}

void FindParent(FILE *FlPntr , FILE *WrtFlPntr,int argc, char *argv[])
{
	char FlDt[MAX_FLE_DT];
	unsigned char NmOfLd = 0;
	unsigned char DshOFnd = 0;
	unsigned char PrntIndx = 0;
	unsigned char ChldIndx = 0;

	#ifdef BATCH_REQUIRE
		if(FlPntr != NULL)
			PrintStartCommands(WrtFlPntr);
	#endif

    if(FlPntr != NULL && WrtFlPntr != NULL)
    {
            while (!feof(FlPntr))
            {
                fscanf(FlPntr, "%s", FlDt);
                DshOFnd = (DshOFnd == DSH_O_FND) ? PRVS_DSH_O_FND_STT : DshOFnd;
                DshOFnd = (strcmp(FlDt, "-o") == 0) ? DSH_O_FND : DshOFnd;
                if (strcmp("ld", FlDt) != 0 && strcmp("-r", FlDt) != 0 && DshOFnd != DSH_O_FND)
                {
                    if (DshOFnd == PRVS_DSH_O_FND_STT)
                    {
                        DshOFnd = 0;
                        ChldIndx = 0;
                        sprintf((PrntLst[PrntIndx].PrntNm), "%s", FlDt);
                        //fprintf(WrtFlPntr,"Parent[%d]-->%s\n",PrntIndx,FlDt);
                        if (strcmp(PrntLst[PrntIndx].PrntNm, "ONE.o") == 0 || strcmp(PrntLst[PrntIndx].PrntNm, "four.o") == 0 ||  strcmp(PrntLst[PrntIndx].PrntNm, "three.o") == 0)
                        {
                            SaveChildsToFile(PrntIndx, WrtFlPntr);
                            break;
                        }
                        PrntIndx += 1;
                    }
                    else
                    {
                        sprintf((PrntLst[PrntIndx].ChldLst[ChldIndx].ChldNm), "%s", FlDt);
                        PrntLst[PrntIndx].NumChld += 1;
                        //fprintf(WrtFlPntr,"Prnt[%d]->Child[%d]=%s\n",PrntIndx,ChldIndx,FlDt);
                        ChldIndx += 1;
                    }
                }
                // printf("Number of Parent = %d\n",PrntIndx);
            }
            #ifdef BATCH_REQUIRE
                if(FlPntr != NULL)
                    PrintEndCommands(WrtFlPntr);
            #endif

            printf("Done.......!\n");
    }
        else if( argv[INPT_FL_NME] != NULL && argv[OTPT_BTCH_FL_NME] != NULL )
        {
            printf("***Error --> Input File Unable To Open***\n");
        }
}

#ifdef BATCH_REQUIRE
void PrintStartCommands(FILE *FilePntr)
{
	fprintf(FilePntr,"%s\n",StrtCmmnds);
}
#endif

#ifdef BATCH_REQUIRE
void PrintEndCommands(FILE *FilePntr)
{
	fprintf(FilePntr,"%s\n",EndCmmnds);
}
#endif