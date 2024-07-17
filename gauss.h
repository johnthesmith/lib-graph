#pragma once


class GaussD1
{
    private:

    /*
        Create kernel gaussian buffer
    */
    static void buildKernel
    (
        /* Pointer of kernel buffer */
        double*,
        /* Count of kernel items */
        const unsigned int,
        /* Smoth factor (sigma) */
        double
    );



    /*
        Internel smoth
    */
    static void smoth
    (
        /* Source buffer */
        double*,
        /* Destination buffer */
        double*,
        /* Count of items */
        const unsigned int,
        /* Kernel buffer */
        double*,
        /* Kernel size */
        const unsigned int,
        /* Smoth factor (sigma) */
        double
    );

    public:

    /*
        The users method for smothing Source buffer
    */
    static void smoth
    (
        /* Source buffer */
        double*,
        /* Destination buffer */
        double*,
        /* Count of items */
        const unsigned int,
        /* Kernel size */
        const unsigned int,
        /* Smoth factor (sigma) */
        unsigned int
    );
};
