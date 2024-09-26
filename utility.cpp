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
/*************************************** SAVEOUTPUT **********************************/
void SAVEOUTPUT(double  *ta1, double fa1[], PATHPOINTER  *PATHstart, double  *DEMAND, double  *ta2, double fa2[],
				clock_t starttime, clock_t endtime, const PRGPATHINFOSTRC *PRGPTHinfo1, const PRGPATHINFOSTRC *PRGPTHinfo2,
				double _ARG, double _ERROR_D, double urs1[], double urs2[],double DEMAND1[], double DEMAND2[],
				PATHPOINTER  *PATHstart01, PATHPOINTER  *PATHstart02,  const PRGITRINFOSTRC *PRGITRinfo)
{
	FILE
		*fp;
	char
		str[80]="", output[80]="OutputTAKMILI.DAT";
	int
		I;
	

	//double CALCTP ( ARCPOINTER ArcPntr, int size, double fa[], bool );

	/*printf("\n\n DO YOU WANT TO SAVE OUTPUT (press ENTER or Y for Yes)? ");
	scanf("%c",str);*/
	
	/*if (str[0]!='\n') 
	{
		scanf("%c",&str[1]);
		if (*strupr(str)!='Y')
			return;
	}*/
	/*printf("\n ENTER THE NAME OF THE FILE FOR THE OUTPUTS. THE DEFULT IS");
	printf(" OurputTAKMILI.DAT \n");
	scanf("%c",str);
	if (str[0]!='\n') 
	{
		scanf("%s",&str[1]);
		strcpy(output,str);
		scanf("%c",&str[0]);
	}
	if ((fp=fopen(output,"w"))==NULL) 
	{
		printf(" UNABLE TO OPEN THE FILE FOR OUTPUT ");
		return;
	}*/

	(fp=fopen(output,"w"));
	for (I=0; I<NARCS; ++I)
		if ((BGNODE[I]<=ZoneNumber)||(ENNODE[I]<=ZoneNumber))
			ta1[I] -= CCT;

	for (I=0; I<NARCS; ++I)
		if ((BGNODE[I]<=ZoneNumber)||(ENNODE[I]<=ZoneNumber))
			ta2[I] -= CCT;

	fprintf(fp,"%s\n"," THE TIME AND FLOW ASSOCIATED WITH THE ARCS ARE AS FOLLOWS : ");
	fprintf(fp,"\n %7s %7s %15s %15s %15s %15s","BGNODE","ENNODE","TIME1","FLOW1","TIME2","FLOW2");
	for ( I=0; I<NARCS; ++I ) 
		fprintf(fp,"\n %7d %7d %15.3f %15.3f %15.3f %15.3f",BGNODE[I],ENNODE[I],ta1[I],fa1[I],ta2[I],fa2[I]);
	fprintf(fp, "\n %10s %16.4f %10s %16.4f \n", "_ARG: ", _ARG, ", _ERROR_D:", _ERROR_D);
	double duration;	
	//duration=( endtime-starttime)/(double)CLOCKS_PER_SEC;	
	fprintf(fp,"\n\n  execution time : %f  \n",PRGITRinfo->PRGtime);	
	fprintf(fp,"%s%d \n", "  THE TOTAL NUMBER OF PATH (class 1) EVER GENERATED IS : ",PRGPTHinfo1->n_genPATH);
	fprintf(fp,"%s%d \n\n", "  THE TOTAL NUMBER OF PATH (class 1) EVER USED IS : ",PRGPTHinfo1->n_usePATH);
	fprintf(fp,"%s%d \n", "  THE TOTAL NUMBER OF PATH (class 2) EVER GENERATED IS : ",PRGPTHinfo2->n_genPATH);
	fprintf(fp,"%s%d \n\n", "  THE TOTAL NUMBER OF PATH (class 2) EVER USED IS : ",PRGPTHinfo2->n_usePATH);
	fprintf(fp, "\n %9s %16s %16s %16s %16s \n", "OD", "urs1", "urs2", "DEMAND1", "DEMAND2");
	for ( int i=0; i<NODPRS; i++)
		fprintf(fp, "\n %9d %16.3f %16.3f %16.3f %16.3f  ", i, urs1[i], urs2[i], DEMAND1[i], DEMAND2[i]);
	/////////////////////////////////////////////
	fprintf(fp,"\n\n%s%f \n", "  THE INITIAL EPSILON IS : ", INITEPSILON);
	fprintf(fp,"%s%4.10f \n\n", "  THE FINAL EPSILON IS : ", FINLEPSILON);
	
	fprintf(fp,"%s%d \n\n", "  THE NUMBER OF CYCLES IS : ", PRGITRinfo->nCYCLE);
	
	fprintf(fp,"%s%d \n", "  THE TOTAL NUMBER OF NCP SOLVED IS : ",PRGITRinfo->nNCP);
	fprintf(fp,"%s%d \n", "  THE TOTAL NUMBER OF LINEARIZATIONS IS : ",PRGITRinfo->nLCP);
	fprintf(fp,"%s%d \n\n","  MAX NUM OF LCP PER OD: ",PRGITRinfo->maxnLCPod);
	/////////////////////////////////////////////
	fprintf(fp,"\n\n%s", "Path(s):");
	fprintf(fp,"\n%7s %7s %5s %15s %15s \n","ORGNODE", "DSTNODE","CLASS","PATHFLOW","TIME(+ toll)");
	double tp1[ MAXNUMPATH ],  tp2[ MAXNUMPATH ];
	for( int tc=0; tc<TOTALODPRS; tc++)
	{
		PATHPOINTER pathtest=PATHstart01[tc];
		int i=0;
		int* ptr;

		while(pathtest)
		{	
			ptr=pathtest->ArcPntr;
			tp1[i]=CALCTP(pathtest -> ArcPntr, pathtest -> size, tfa, 1);
			fprintf(fp,"\n%7d %7d %5s %15.4f %15.4f %7s\n",ORGNODE[tc],DSTNODE[tc], "auto",pathtest ->hp,tp1[i], "arcs:");
			for(int c=0; c< pathtest->size; c++)
				fprintf(fp,"%d%s",ptr[c],",");
			pathtest=pathtest->next;
			i++;
		}
		pathtest=PATHstart02[tc];
		i=0;
		while(pathtest)
		{	
			ptr=pathtest->ArcPntr;
			tp2[i]=CALCTP(pathtest -> ArcPntr, pathtest -> size, tfa, 0);
			fprintf(fp,"\n%7d %7d %5s %15.4f %15.4f %7s\n",ORGNODE[tc],DSTNODE[tc], "taxi",pathtest ->hp,tp2[i],"arcs:");
			for(int c=0; c< pathtest->size; c++)
				fprintf(fp,"%d%s",ptr[c],",");
			pathtest=pathtest->next;
			i++;
		}
		
	}
	fclose(fp);
	return;
} /* SAVEOUTPUT */

/*************************************************************************************/
