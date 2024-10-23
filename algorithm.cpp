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

        /*  SORT (N); **************************************************** */
        {
            int I = 1;
            double T1, T2;
            for (I = 1; I <= N && AA[I] <= 1e-10; ++I);
            if (I > N)
                return;
            T1 = Q[I] / AA[I];
            IR = I;
            for (I = I + 1; I <= N; ++I) {
                if (AA[I] > 1e-10) {
                    T2 = Q[I] / AA[I];
                    if (T1 > T2) {
                        IR = I;
                        T1 = T2;
                    }
                }
            }
        } /* SORT */

        /*  PIVOT (N); *********************************************** */
        {
            int I, J, L;
            for (I = 1; I <= N; ++I) {
                BB[IR][I] = BB[IR][I] / AA[IR];
            }
            Q[IR] = Q[IR] / AA[IR];
            for (I = 1; I <= N; ++I) {
                if (I == IR) continue;
                Q[I] = Q[I] - Q[IR] * AA[I];
                for (J = 1; J <= N; ++J) {
                    BB[I][J] = BB[I][J] - BB[IR][J] * AA[I];
                }
            }
            NL1 = MBASIS[IR];
            L = N + IR;
            NL2 = MBASIS[L];
            MBASIS[IR] = NE1;
            MBASIS[L] = NE2;
            L1 = L1 + 1;
        } /* PIVOT */

    } /* while */
   /*  PRINT(N); *************************************************** */
    {
        int I, III, J, K1, K2;
        for (III = 1; III <= N; ++III) {
            W[III] = 0.0;
            Z[III] = 0.0;
        }
        I = N + 1;
        for (J = 1; J <= N; ++J) {
            K1 = MBASIS[I];
            K2 = MBASIS[J];
            if (Q[J] < 0.0)
                Q[J] = 0.0;
            else if (K2 != 1)
                Z[K1] = Q[J];
            else
                W[K1] = Q[J];
            ++I;
        }
    } /* PRINT */
    free(MBASIS);
    return;
} /* LCP */
void BELL(double *DIST, int NORG, double D[], int *ARCB, int *LEVEL, int *PN, int *L)
{
    int *LF;
    int I, J, K, MLA, NNA, JK, II, JJ, LEV;
    double DD;

    void ErrorAlloc(char str[]);

    /* ****   FIRST SET DIST OF 0 ON SOURCE NODE NS */
    if (!(LF = (int *)calloc(TOTALNODES + 1, sizeof(int))))
        ErrorAlloc(" LF in BELL ");

    for (J = 1; J <= NNODES; ++J) {
        D[J] = MAXREALNUM;
        PN[J] = 0;
        LF[J] = 0;
        LEVEL[J] = -1;
    }

    D[NORG] = 0.0;
    L[1] = NORG;
    MLA = 1;
    /*  STEP 1 ******** */
    for (K = 1; K <= MLA; ++K) {
        I = L[K];
        /* STEP 2 ********** */
        if (NPT[I] == 0) {
            LF[I] = 0;
            continue;
        }
        if (I < NNODES) {
            for (JK = I + 1; JK <= NNODES && NPT[JK] == 0; ++JK);
            NNA = (JK > NNODES) ? (NARCS - NPT[I] + 1) : (NPT[JK] - NPT[I]);
        }
        else {
            NNA = NARCS - NPT[I] + 1;
        }
        for (J = 1; J <= NNA; ++J) {
            II = NPT[I] + J - 1;
            /*  STEP 3 ******* */
            DD = D[I] + DIST[II];
            JJ = ENNODE[idx(II)];
            if (DD < D[JJ]) {
                D[JJ] = DD;
                PN[JJ] = I;
                ARCB[JJ] = II;
                /* STEP 4 ****** */
                if (LF[JJ] != 1) {
                    ++MLA;
                    L[MLA] = JJ;
                    LF[JJ] = 1;
                }
            }
        } /* for */
        LF[I] = 0;

    } /* for */

    LEVEL[NORG] = 0;

    for (I = 1; I <= NNODES; ++I) {
        LEV = 0;
        J = I;
        while (PN[J] != 0) {
            J = PN[J];
            LEV = LEV + 1;
        }
        LEVEL[I] = LEV;
    }

    free(LF);

    if (MLA > MAXMLA)
        MAXMLA = MLA;

    return;
} /* BELL */
