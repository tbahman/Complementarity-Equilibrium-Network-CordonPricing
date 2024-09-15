#ifndef UTILITY_H
#define UTILITY_H
// IO_Demand_Utility_constant

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

// Struct Definitions
typedef struct {
    unsigned long int MxStrcMem;
    unsigned long int MxArcMem;
    unsigned long int StrcMemFnl;
    unsigned long int ArcMemFnl;
    int MxNPath;
    int MxNArc;
    int MxNPathFnl;
    int MxNArcFnl;
} PRGMEMINFOSTRC;

struct PATHSTRUCT {
    int *ArcPntr;
    int size;
    double hp;
    struct PATHSTRUCT *next;
};
typedef struct PATHSTRUCT *PATHPOINTER;

typedef struct {
    unsigned long int StrcMemCyc;
    unsigned long int ArcMemCyc;
    double Tcost;
    double MaxErr;
    double CycGAP;
    double User;
    int nNCP;
    int nLCP;
    double Eps;
    double CYCLEtime;
    double maxFCH;
    double minFCH;
    double maxPFCH;
    double infoAEC;
    double infonRG;
    double ARG;
    double ERRORD;
    double Ttoll;
    double aveTravelTime;
} CYCLEINFOSTRUCT;

typedef struct {
    int nCYCLE;
    int nNCP;
    int nLCP;
    int maxnLCPod;
    int nPATH;
    double PRGtime;
} PRGITRINFOSTRC;

typedef struct {
    int n_usePATH;
    int n_genPATH;
} PRGPATHINFOSTRC;

// Global Variables and Constants
extern double *DEMAND, *DEMAND1, *DEMAND2;
extern double *ta1, *ta2, *fa1, *fa2, *urs1, *urs2;
extern double INITEPSILON, FINLEPSILON, RGSTEP, *tfa;
extern int NARCS, NODB, NNODES, TOTALNODES, NODPRS;
extern int *BGNODE, *NPT, idx(int dst);
extern int LDIM;
