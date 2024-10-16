// algorithm.cpp
#include "algorithm.h"

// Function definitions

void UPDATEta(double fa[], double *ta, bool classno)
{
    for (int I = 0; I < NARCS; ++I)
        ta[I] = CALCta(fa, I, classno);
}
