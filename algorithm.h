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
