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
