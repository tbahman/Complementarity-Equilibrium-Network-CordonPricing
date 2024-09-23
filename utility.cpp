// IO_Demand_Utility_constant.cpp

#include "utility.h"

double *DEMAND, *DEMAND1, *DEMAND2;
double *ta1, *ta2, *fa1, *fa2, *urs1, *urs2;
double INITEPSILON = 0.001, FINLEPSILON = 0.00001, RGSTEP = 0.5;
int NARCS, NODB, NNODES, TOTALNODES, NODPRS;
int *BGNODE, *NPT, idx(int dst) { return dst; }
int LDIM;

void ErrorAlloc(const char *message)
{
    cout << "Memory allocation error: " << message << endl;
    exit(1);
}

// /**************************************** ErrorAlloc *********************************/

// void ErrorAlloc ( char str[])
// {
// 	printf("\n THERE IS NOT ENOUGH MEMORY TO ALLOCATE FOR %s\n", str );
	
// 	printf("%s%lu \n", "  MAX MEM FOR STRUCTS USED : ",PRGMEMinfo.MxStrcMem);
// 	printf("  MAX MEM FOR ARCS USED : %lu \n\n",PRGMEMinfo.MxArcMem);

// 	printf("%s%lu \n","  TOTAL USED MEMORY FOR STRUCTS AT FINAL SOL'N: ",PRGMEMinfo.StrcMemFnl);
// 	printf("%s%lu \n\n","  TOTAL USED MEMORY FOR ARCS AT FINAL SOL'N: ", PRGMEMinfo.ArcMemFnl);

// 	printf("%s%d \n", "  MAX NUMBER OF PATHS EVER USED : ",PRGMEMinfo.MxNPath);
// 	printf("%s%d \n\n", "  MAX NUMBER OF ARCS PER PATH EVER USED : ",PRGMEMinfo.MxNArc);
// 	printf("%s%d \n", "  MAX NUMBER OF PATHS AT FINAL SOL'N : ",PRGMEMinfo.MxNPathFnl);
// 	printf("%s%d \n\n", "  MAX NUMBER OF ARCS PER PATH AT FINAL SOL'N : ",PRGMEMinfo.MxNArcFnl);

// 	_getch();
// 	exit(1);
// } /* ErrorAlloc */

// /*************************************************************************************/
/*********************************** READDEMAND **************************************/
void READDEMAND(double DEMAND[])
{
	FILE *fp;
	int od;
	char
		str[80]="",
		demanddata[80]="DEMAND.DAT";

	printf("\n ENTER THE NAME OF DATA FILE FOR THE DEMAND. THE DEFULT IS");
	printf(" DEMAND.DAT \n");
	/*scanf("%c",str);*/
	
	/*if (str[0]!='\n')
	{
		scanf("%s",&str[1]);
		strcpy(demanddata,str);
		scanf("%c",&str[0]);
	}*/
	
	if ((fp=fopen(demanddata,"r"))==NULL) 
	{
		printf(" DATA FILE FOR DEMAND NOT FOUND ");
		exit(1);
	}

	/*(fp=fopen(demanddata,"r"));*/

	for (od=0; od<NODPRS && !feof(fp); ++od ) 
	{
		int org,dst;
		double dem;
		fscanf(fp," %d%d%lf ",&org,&dst,&dem);
		ORGNODE[od]=org;
		DSTNODE[od]=dst;               
		DEMAND[od]=dem;
		DSTNODE2[od]=dst;
		totaldemand+=dem;
	}
	
	if ( od<NODPRS || !feof(fp) ) 
	{
		printf("\n THERE MIGHT BE ERRORS IN READING NETWORK FILE \n");
		printf(" DO YOU WANT TO EXIT ?(Y) ");scanf("%c",str);
		if ((str[0]=='\n') || (*strupr(str)=='Y'))
			exit(1);
	}
	else
		printf("%s%s%s\n\n"," THE DEMAND FILE '",demanddata,"' WAS SUCCESSFULLY READ ");
	fclose(fp);
	return;

} /* READDEMAND */

/*************************************************************************************/
