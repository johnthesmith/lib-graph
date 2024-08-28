#pragma once



#include <string>



using namespace std;



/*
    Three components integar point
*/
struct Point3i
{
    int x = 0;  /* x */
    int y = 0;  /* y */
    int z = 0;  /* z */



    /*
        Constructor
    */
    Point3i
    (
        int = 0,
        int = 0,
        int = 0
    );



    /*
        Return 3d position by linear index

          x 0 1 2 3 4
        y
        0   0 1 2 3 4
        1   5 6[7]8 9

        argument size[5,2,1], index[ 7 ]
        result [ 2,1,0 ]
    */
    static Point3i byIndex
    (
        /* Size of array */
        Point3i,
        /* Linear index */
        int
    );



    friend Point3i operator -
    (
        const Point3i&,  /* First operand */
        const Point3i&   /* Second operand */
    );



    friend Point3i operator -
    (
        const Point3i&,  /* First operand */
        const int        /* Second operand */
    );



    friend bool operator ==
    (
        const Point3i&,  /* First operand */
        const Point3i&   /* Second operand */
    );



    friend bool operator !=
    (
        const Point3i&,  /* First operand */
        const Point3i&   /* Second operand */
    );



    /*
        Convert Point3d to string
    */
    string toString
    (
        const string = "[%d,%d,%d]"
    ) const;



    /*
        Multiplication vector components
    */
    int mulComponents();

};



/*
    Point declarations
*/
static Point3i POINT_3I_0 = Point3i( 0, 0, 0 );
static Point3i POINT_3I_I = Point3i( 1, 1, 1 );
static Point3i POINT_3I_X = Point3i( 1, 0, 0 );
static Point3i POINT_3I_Y = Point3i( 0, 1, 0 );
static Point3i POINT_3I_Z = Point3i( 0, 0, 1 );
