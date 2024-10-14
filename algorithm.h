// algorithm.h
#ifndef ALGORITHM_H
#define ALGORITHM_H

// Function declarations
void UPDATEta(double fa[], double *ta, bool classno);
void LCP(double AM[][ MAXNUMPATH+1 ], double Q[], int N, double Z[]);
void BELL(double *DIST, int NORG, double D[], int *ARCB, int *LEVEL, int *PN, int *L);
void CycleCost(int nCYCLE, const double *fa1, const double *ta1, const double *fa2, const double *ta2, CYCLEINFOSTRUCT CYCLEinfo[]);
double PathOdError(PATHPOINTER PathStart, int npath, double fa[], double Tbell, double demand, bool);
double RELGAP(PATHPOINTER PathStart, double fa[], double Tbell, double demand, bool);
void INITIALVALUE(PATHPOINTER *& PATHstart, double *& DEMAND, double*& fa, double *& ta, double TP[], CYCLEINFOSTRUCT CYCLEinfo[], PRGPATHINFOSTRC *&PRGPTHinfo);
void STARTPOINT(double *DEMAND, PATHPOINTER *PATHstart, double fa[], double *ta, PRGMEMINFOSTRC *PRGMEMinfo, PRGPATHINFOSTRC *PRGPTHinfo, bool classno);
int UPDATE_PATHS(PATHPOINTER *PATHstart, int od, double TP[], double fa[], double *Tmax, double *Tmin, double Tbell, int ARCB[], int NODB[], int numofArcs, PRGMEMINFOSTRC *PRGMEMinfo, PRGPATHINFOSTRC *PRGPTHinfo, double nRG, bool classno);
void LINEARIZE(int npath1, int npath2, double demand, PATHPOINTER PathStart1, PATHPOINTER PathStart2, double fa[], double TP[], double AM[][ MAXNUMPATH+1 ], double Q[], int od, double demandOne, double demandTwo);
void UPDATE_hpfaTPErr(int npath1, int npath2, double Z1[], double Z2[], PATHPOINTER PathStart1, PATHPOINTER PathStart2, double fa1[], double fa2[], double TP1[], double TP2[], double *Err1, double *Err2, double& Tmin1, double& Tmin2);
inline double CALCta(double *faFormal, int I, bool classno);
inline void DERIVtafb(double *faFormal, int I, double &rslt, bool whichclass);
double CALCTP(ARCPOINTER ArcPntr, int size, double fa[], bool classno);
double DERIVTP(double fa[], PATHPOINTER path1, PATHPOINTER path2, bool classOfFlow);
void binaryLogit(double DEMAND[], double urs1[], double urs2[], double DEMAND1[], double DEMAND2[]);
