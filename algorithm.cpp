// algorithm.cpp
#include "algorithm.h"

// Function definitions

void UPDATEta(double fa[], double *ta, bool classno)
{
    for (int I = 0; I < NARCS; ++I)
        ta[I] = CALCta(fa, I, classno);
}

void LCP(double AM[][ MAXNUMPATH+1 ], double Q[], int N, double Z[])
{
    int IR, L1, NL1, NL2, NE1, NE2;
    int *MBASIS;

    double BB[MAXNUMPATH+2][MAXNUMPATH+2], AA[MAXNUMPATH+2], W[MAXNUMPATH+2];

    if (!(MBASIS = (int *)calloc(MBASISNUM, sizeof(int))))
        ErrorAlloc(" MBASIS in LCP ");

    /*  MATRIX (N); ***************************************** */
    {
        int I, J;
        for (J = 1; J <= N; ++J) {
            for (I = 1; I <= N; ++I) {
                if (I == J)
                    BB[I][J] = 1;
                else
                    BB[I][J] = 0.0;
            }
        }
    } /* MATRIX */

