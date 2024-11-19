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

void CycleCost(int nCYCLE, const double *fa1, const double *ta1, const double *fa2, const double *ta2, CYCLEINFOSTRUCT CYCLEinfo[])
{
    CYCLEinfo[nCYCLE].Tcost = 0;
    CYCLEinfo[nCYCLE].User = 0;
    CYCLEinfo[nCYCLE].Ttoll = 0;

    for (int I = 0; I < NARCS; ++I)
    {
        //CYCLEinfo[nCYCLE].Tcost +=ta[I]*fa[I];
        CYCLEinfo[nCYCLE].Tcost += ((BGNODE[I] <= ZoneNumber || ENNODE[I] <= ZoneNumber) ? (ta1[I] - CCT) * fa1[I] : ta1[I] * fa1[I]);
        CYCLEinfo[nCYCLE].Tcost += ((BGNODE[I] <= ZoneNumber || ENNODE[I] <= ZoneNumber) ? (ta2[I] - CCT) * fa2[I] : ta2[I] * fa2[I]);
        CYCLEinfo[nCYCLE].Ttoll += (tau * fa1[I]) * tollRoad[I];

        double faa;
        double a0, a1, t, d;
    }

}/* CycleCost */

double PathOdError(PATHPOINTER PathStart, int npath, double fa[], double Tbell, double demand, bool classno)
{
    double PathErr, TP, hp, error;
    int p, size;
    PATHPOINTER tempPath;
    ARCPOINTER tempPntr;

    void ErrorAlloc(char str[]);

    error = 0;
    tempPath = PathStart;

    for (p = 0; p < npath; ++p)
    {
        size = tempPath->size;
        tempPntr = tempPath->ArcPntr;
        hp = tempPath->hp;
        TP = CALCTP(tempPntr, size, fa, classno);
        PathErr = (hp * fabs(TP - Tbell)) / (demand * TP);
        error += PathErr;
        tempPath = tempPath->next;
    }  /* for path */ 

    return (error);
}  /* PathOdError */

double RELGAP(PATHPOINTER PathStart, double fa[], double Tbell, double demand, bool classno)
{
    double PathGAP, CycleGAP, TP, hp;
    int size;
    PATHPOINTER tempPath;
    ARCPOINTER tempPntr;

    void ErrorAlloc(char str[]);

    CycleGAP = 0;
    tempPath = PathStart;
    while (tempPath != NULL)
    {
        size = tempPath->size;
        tempPntr = tempPath->ArcPntr;
        hp = tempPath->hp;
        TP = CALCTP(tempPntr, size, fa, classno);
        PathGAP = hp * (TP - 2 * CCT);
        CycleGAP += PathGAP;
        tempPath = tempPath->next;
    }  /* for path */ 

    return (CycleGAP);

}  /* RELGAP */

void INITIALVALUE(PATHPOINTER *& PATHstart, double *& DEMAND, double*& fa, double *& ta, double TP[], CYCLEINFOSTRUCT CYCLEinfo[], PRGPATHINFOSTRC *&PRGPTHinfo)
{
    int od, I;
    void ErrorAlloc(char str[]);

    if (!(NPT = (int *)calloc(NNODES, sizeof(int))))
        ErrorAlloc("NPT");
    if (!(BGNODE = (int *)calloc(NARCS, sizeof(int))))
        ErrorAlloc("BGNODE");
    if (!(ENNODE = (int *)calloc(NARCS, sizeof(int))))
        ErrorAlloc("ENNODE");
    if (!(A0 = (double *)calloc(NARCS, sizeof(double))))
        ErrorAlloc("A0");
    if (!(A1 = (double *)calloc(NARCS, sizeof(double))))
        ErrorAlloc("A1");
    if (!(DSTNODE = (int *)calloc(NODPRS + 10, sizeof(int))))
        ErrorAlloc("DSTNODE");
    if (!(DSTNODE2 = (int *)calloc(NODPRS + 10, sizeof(int))))
        ErrorAlloc("DSTNODE");
    if (!(ORGNODE = (int *)calloc(NODPRS + 10, sizeof(int))))
        ErrorAlloc("ORGNODE");
    if (!(DEMAND = (double *)calloc(NODPRS, sizeof(double))))
        ErrorAlloc("DEMAND");
    if (!(fa = (double *)calloc(NARCS, sizeof(double))))
        ErrorAlloc("fa");
    if (!(ta = (double *)calloc(NARCS, sizeof(double))))
        ErrorAlloc("ta");
    if (!(PRGPTHinfo = (PRGPATHINFOSTRC *)calloc(NARCS, sizeof(PRGPATHINFOSTRC))))
        ErrorAlloc("PRGPATHINFOSTRC");
    if (!(PATHstart = (PATHPOINTER *)calloc(NODPRS, sizeof(PATHPOINTER))))
        ErrorAlloc("PATHstart");

    for (od = 0; od < NODPRS; ++od)
    {
        DEMAND[od] = 0;
        PATHstart[od] = NULL;
    }

    for (I = 0; I < NARCS; ++I)
    {
        fa[I] = 0;
        ta[I] = 0;
    }

    for (I = 0; I < MXNPATH; ++I)
        TP[I] = 0;

    for (I = 0; I <= MAXNCYCLE; ++I)
    {
        CYCLEinfo[I].nNCP = 0;
        CYCLEinfo[I].nLCP = 0;
        CYCLEinfo[I].Eps = 0;
        CYCLEinfo[I].CYCLEtime = 0;
    }

    PRGPTHinfo->n_genPATH = 0;
    PRGPTHinfo->n_usePATH = 0;

    PRGMEMinfo.MxStrcMem = 0;
    PRGMEMinfo.MxArcMem = 0;
    PRGMEMinfo.StrcMemFnl = 0;
    PRGMEMinfo.ArcMemFnl = 0;
    PRGMEMinfo.MxNPath = 1;
    PRGMEMinfo.MxNArc = 1;
    PRGMEMinfo.MxNPathFnl = 1;
    PRGMEMinfo.MxNArcFnl = 1;

    return;
} /* INITIALVALUE */
void STARTPOINT(double *DEMAND, PATHPOINTER *PATHstart, double fa[], double *ta, PRGMEMINFOSTRC *PRGMEMinfo, PRGPATHINFOSTRC *PRGPTHinfo, bool classno)
{
    int od, org, PrvOrg, NODE, numofArcs;
    int *ARCB, *NODB, *LEVEL, *L;
    double *Tbell;
    PATHPOINTER path = NULL;
    ARCPOINTER ArcPntr, pntr;

    void UPDATEta(double fa[], double *ta, bool classno);
    void BELL(double *DIST, int NORG, double D[], int *ARCB, int *LEVEL, int *PN, int *L);
    void ErrorAlloc(char str[]);
    double CALCTP(ARCPOINTER ArcPntr, int size, double fa[], bool classno);

    if (!(ARCB = (int *)calloc(NNODES, sizeof(int))))
        ErrorAlloc("ARCB in STARTPOINT");
    if (!(NODB = (int *)calloc(NNODES, sizeof(int))))
        ErrorAlloc("NODB in STARTPOINT");
    if (!(LEVEL = (int *)calloc(NNODES, sizeof(int))))
        ErrorAlloc("LEVEL in STARTPOINT");
    if (!(Tbell = (double *)calloc(NNODES, sizeof(double))))
        ErrorAlloc("Tbell in STARTPOINT");
    if (!(L = (int *)calloc(LDIM, sizeof(int))))
        ErrorAlloc(" L in STARTPOINT ");

   UPDATEta(fa, ta, classno);
    for (org = 0, od = 0; od < NODPRS; ++org)
    {
        BELL(ta - 1, ORGNODE[od], Tbell - 1, ARCB - 1, LEVEL - 1, NODB - 1, L);
        PrvOrg = ORGNODE[od];
        for (; (PrvOrg == ORGNODE[od]) && (od < NODPRS); ++od)
        {
            NODE = DSTNODE[od];
            numofArcs = LEVEL[idx(NODE)];
            double demand = DEMAND[od];
            if (demand == 0)
                continue;
            if (!(path = (PATHPOINTER)malloc(sizeof(struct PATHSTRUCT))))
                ErrorAlloc("STRUCTURES IN STARTPOINT");
            if (!(ArcPntr = (ARCPOINTER)calloc(numofArcs, sizeof(int))))
                ErrorAlloc("ARCS IN STARTPOINT");

            pntr = ArcPntr + numofArcs - 1;
            for (int I = numofArcs - 1; I >= 0; --I)
            {
                *pntr = ARCB[idx(NODE)];
                fa[*pntr - 1] += demand;
                NODE = NODB[idx(NODE)];
                --pntr;
            }
            path->ArcPntr = ArcPntr;
            path->size = numofArcs;
            path->hp = demand;
            path->next = NULL;
            PATHstart[od] = path;

            PRGPTHinfo->n_genPATH += 1;
            PRGPTHinfo->n_usePATH += 1;

            PRGMEMinfo->ArcMemFnl += intSize * numofArcs;
            PRGMEMinfo->StrcMemFnl += structSize;
            if (numofArcs > PRGMEMinfo->MxNArc)
                PRGMEMinfo->MxNArc = numofArcs;
            if (PRGMEMinfo->ArcMemFnl > PRGMEMinfo->MxArcMem)
                PRGMEMinfo->MxArcMem = PRGMEMinfo->ArcMemFnl;
            if (PRGMEMinfo->StrcMemFnl > PRGMEMinfo->MxStrcMem)
                PRGMEMinfo->MxStrcMem = PRGMEMinfo->StrcMemFnl;

        } /* for od */

        UPDATEta(fa, ta, classno);

    } /* for org */
    
    UPDATEta(fa, ta, classno);

    free(ARCB);
    free(NODB);
    free(LEVEL);
    free(Tbell);

    return;
} /* STARTPOINT */

int UPDATE_PATHS(PATHPOINTER *PATHstart, int od, double TP[], double fa[], double *Tmax, double *Tmin, double Tbell, int ARCB[], int NODB[], int numofArcs, PRGMEMINFOSTRC *PRGMEMinfo, PRGPATHINFOSTRC *PRGPTHinfo, double nRG, bool classno)
{
    double tempTP;
    int I, npath, size, NODE;
    PATHPOINTER temppath, newpath, oldpath;
    ARCPOINTER ArcPntr, temppntr;

    void ErrorAlloc(char str[]);

    temppath = PATHstart[od];
    while (temppath != NULL && temppath->hp < FLOWACCU)
    {
        size = temppath->size;
        PRGMEMinfo->ArcMemFnl -= intSize * size;
        PRGMEMinfo->StrcMemFnl -= structSize;
        free(temppath->ArcPntr);
        PATHstart[od] = temppath->next;
        free(temppath);
        --PRGPTHinfo->n_usePATH;
        temppath = PATHstart[od];
    } /* while */
   
    *Tmax = 0;
    *Tmin = MAXREALNUM;
    npath = 0;
    oldpath = temppath;
    newpath = oldpath;
    while (newpath)
    {
        if (newpath->hp < FLOWACCU) {
            size = newpath->size;
            PRGMEMinfo->ArcMemFnl -= intSize * size;
            PRGMEMinfo->StrcMemFnl -= structSize;
            oldpath->next = newpath->next;
            --PRGPTHinfo->n_usePATH;
            free(newpath->ArcPntr);
            free(newpath);
        } /* if */
        else {
            ++npath;
            oldpath = newpath;
            TP[npath - 1] = (tempTP = CALCTP(newpath->ArcPntr, newpath->size, fa, classno));
            if (*Tmax < tempTP)
            {
                *Tmax = tempTP;
            }
            if (*Tmin > tempTP)
            {
                *Tmin = tempTP;
            }

        } /* else */
        newpath = oldpath->next;
    } /* while */

    if (((*Tmin - Tbell) / (Tbell - 2 * CCT)) > (nRG))
    {
        if (!(newpath = (PATHPOINTER)malloc(sizeof(struct PATHSTRUCT))))
            ErrorAlloc("STRUCTURES IN UPDATE_PATH");
        if (!(ArcPntr = (ARCPOINTER)calloc(numofArcs, sizeof(int))))
            ErrorAlloc("ARCS IN UPDATE_PATH");
        tempTP = 0;
        NODE = DSTNODE[od];
        temppntr = ArcPntr + numofArcs - 1;
        for (int I = numofArcs - 1; I >= 0; --I, --temppntr)
        {
            *temppntr = ARCB[idx(NODE)];
            tempTP += CALCta(fa, *temppntr - 1, classno);
            NODE = NODB[idx(NODE)];
        } /* for I */

        if (((*Tmin - tempTP) / (tempTP - 2 * CCT)) > (nRG))
        {
            ++npath;
            oldpath->ArcPntr = ArcPntr;
            oldpath->size = numofArcs;
            oldpath->hp = 0;
            oldpath->next = NULL;
            ++PRGPTHinfo->n_usePATH;
            ++PRGPTHinfo->n_genPATH;
            PRGMEMinfo->ArcMemFnl += intSize * numofArcs;
            PRGMEMinfo->StrcMemFnl += structSize;
            if (numofArcs > PRGMEMinfo->MxNArc)
                PRGMEMinfo->MxNArc = numofArcs;
            if (PRGMEMinfo->ArcMemFnl > PRGMEMinfo->MxArcMem)
                PRGMEMinfo->MxArcMem = PRGMEMinfo->ArcMemFnl;
            if (PRGMEMinfo->StrcMemFnl > PRGMEMinfo->MxStrcMem)
                PRGMEMinfo->MxStrcMem = PRGMEMinfo->StrcMemFnl;
            if (npath > PRGMEMinfo->MxNPath)
                PRGMEMinfo->MxNPath = npath;

            if (oldpath)
                oldpath->next = newpath;
            else
                PATHstart[od] = newpath;

            TP[npath - 1] = tempTP;
            *Tmin = tempTP;
        } /* if */
        else
        {
            free(ArcPntr);
            free(oldpath);
        } /* else */

    } /* if */

    return (npath);
} /* UPDATE_PATHS */

void LINEARIZE(int npath1, int npath2, double demand, PATHPOINTER PathStart1, PATHPOINTER PathStart2, double fa[], double TP[], double AM[][ MAXNUMPATH+1 ], double Q[], int od, double demandOne, double demandTwo)
{
    int p1, p2, matrixLinker, npath;
    double temp, DRV, derDem11, derDem12, derDem21, derDem22;
    PATHPOINTER path1, path2;
    ARCPOINTER ArcPntr1, ArcPntr2;

    double DERIVTP(double fa[], PATHPOINTER path1, PATHPOINTER path2, bool classOfFlow);

    if (classNo == 1)
    {
        path1 = PathStart1;
        npath = npath1;
        matrixLinker = 0;
    }
    else
    {
        path1 = PathStart2;
        npath = npath2;
        matrixLinker = npath1;
    }
