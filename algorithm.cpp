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
   /* INITIA (N); ***************************************** */
    {
        int I = 1, J = 2, L;
        double T1;
        for (J = 2; J <= N; ++J) {
            if (Q[I] > Q[J]) {
                I = J;
            }
        }
        IR = I;
        T1 = -Q[IR];
        if (T1 <= 0.0)
            return;
        for (I = 1; I <= N; ++I) {
            Q[I] = Q[I] + T1;
        }
        Q[IR] = T1;
        for (J = 1; J <= N; ++J) {
            BB[J][IR] = -1.0;
            W[J] = Q[J];
            Z[J] = 0.0;
            MBASIS[J] = 1;
            L = N + J;
            MBASIS[L] = J;
        }
        NL1 = 1;
        L = N + IR;
        NL2 = IR;
        MBASIS[IR] = 3;
        MBASIS[L] = 0;
        W[IR] = 0.0;
        L1 = 1;
    } /* INITIA */
   while (NL1 == 1 || NL1 == 2) {

        /* NEWBAS (N); ************************************************** */
        {
            int I, J;
            double T1;
            switch (NL1) {
            case 1:
                NE1 = 2;
                NE2 = NL2;
                for (I = 1; I <= N; ++I) {
                    T1 = 0.0;
                    for (J = 1; J <= N; ++J) {
                        T1 = T1 - BB[I][J] * AM[J - 1][NE2 - 1]; /* AM CHANGED!! */
                    }
                    AA[I] = T1;
                }
                break;
            case 2:
                NE1 = 1;
                NE2 = NL2;
                for (I = 1; I <= N; ++I) {
                    AA[I] = BB[I][NE2];
                }
            } /* switch */
        }  /* NEWBAS */
