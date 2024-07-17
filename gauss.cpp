#include "gauss.h"

#include <cmath>
#include <iostream>

#include "../core/math.h"

/*
    Create kernel gaussian buffer
*/
void GaussD1::buildKernel
(
    /* Pointer of kernel buffer */
    double* aKernel,
    /* Count of kernel items */
    const unsigned int aCount,
    /* Smoth factor (sigma) */
    double aSigma
)
{
    double sum = 0.0;
    unsigned int halfSize = aCount / 2;

    double k = (aSigma * sqrt( 2 * PI));
    double sigma2 = aSigma * aSigma;

    /* Fill kernel */
    for( unsigned int i = 0; i < aCount; i++ )
    {
        auto x = ( double )i - halfSize;
        aKernel[ i ] = exp( -0.5 * ( x * x ) / sigma2 ) / k;
        sum += aKernel[ i ];
    }

    /* Kernel normolize */
    for( unsigned int i = 0; i < aCount; i++ )
    {
        aKernel[ i ] /= sum;
    }
}


/*
    Internel smoth
*/
void GaussD1::smoth
(
    /* Source buffer */
    double*         aSource,
    /* Destination buffer */
    double*         aDestination,
    /* Count of items */
    const unsigned int    aCountBuffer,
    /* Kernel buffer */
    double* aKernel,
    /* Kernel size */
    const unsigned int aCountKernel,
    /* Smoth factor (sigma) */
    double aSigma
)
{
    unsigned int halfKernelSize = aCountKernel / 2;
    for( unsigned int i = 0; i < aCountBuffer; i++ )
    {
        double sum = 0.0;
        for( unsigned int j = 0; j < aCountKernel; j++)
        {
            int idx = i + j - halfKernelSize;
            if( idx >= 0 && idx < aCountBuffer )
            {
                sum += aSource[ idx ] * aKernel[ j ];
            }
        }
        aDestination[ i ] = sum;
    }
}



/*
    The users method for smothing Source buffer
*/
void GaussD1::smoth
(
    /* Source buffer */
    double*             aSource,
    /* Destination buffer */
    double*             aDestination,
    /* Count of items */
    const unsigned int  aCount,
    /* Count of Kernel */
    const unsigned int  aCountKernel,
    /* Smoth factor (sigma) */
    unsigned int        aSmoth
)
{
    double kernel[ aCountKernel ];
    buildKernel( kernel, aCountKernel, aSmoth );
    smoth( aSource, aDestination, aCount, kernel, aCountKernel, aSmoth );
}

