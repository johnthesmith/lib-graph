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
        int ax = 0,
        int ay = 0,
        int az = 0
    )
    : x(ax), y(ay), z(az)
    {}



    /*
        Return 3d position by linear index

          x 0 1 2 3 4
        y
        0   0 1 2 3 4
        1   5 6[7]8 9

        argument size[5,2,1], index[ 7 ]
        result [ 2,1,0 ]
    */
    inline static Point3i byIndex
    (
        /* Linear index */
        int aIndex,
        /* Size of array */
        Point3i aSize
    )
    {
        return Point3i
        (
            aIndex % aSize.x,
            ( aIndex / aSize.x ) % aSize.y,
            aIndex / ( aSize.x * aSize.y )
        );
    }



    /*
        Convert point in the 3d array in to linear index
    */
    inline int toIndex
    (
        /* Size of array */
        Point3i aSize
    )
    {
        return x + y * aSize.x + z * aSize.x * aSize.y;
    }



    inline friend Point3i operator +
    (
        /* First operand */
        const Point3i& a,
        /* Second operand */
        const Point3i& b
    )
    {
        return Point3i
        (
            a.x + b.x,
            a.y + b.y,
            a.z + b.z
        );
    }



    inline friend Point3i operator -
    (
        /* First operand */
        const Point3i& a,
        /* Second operand */
        const Point3i& b
    )
    {
        return Point3i
        (
            a.x - b.x,
            a.y - b.y,
            a.z - b.z
        );
    }



    inline friend Point3i operator -
    (
        /* First operand */
        const Point3i& a,
        /* Second operand */
        const int b
    )
    {
        return Point3i
        (
            a.x - b,
            a.y - b,
            a.z - b
        );
    }



    inline friend bool operator ==
    (
        /* First operand */
        const Point3i& a,
        /* Second operand */
        const Point3i& b
    )
    {
        return
        a.x == b.x &&
        a.y == b.y &&
        a.z == b.z;
    }



    inline friend Point3i operator *
    (
        /* First operand */
        const Point3i& a,
        /* Second operand */
        const int s
    )
    {
        return Point3i
        (
            a.x * s,
            a.y * s,
            a.z * s
        );
    }



    inline friend Point3i operator /
    (
        /* First operand */
        const Point3i& a,
        /* Second operand */
        const int s
    )
    {
        return Point3i
        (
            a.x / s,
            a.y / s,
            a.z / s
        );
    }



    /*
        Operator not equal for points
    */
    inline friend bool operator !=
    (
        /* First operand */
        const Point3i& a,
        /* Second operand */
        const Point3i& b
    )
    {
        return
        a.x != b.x ||
        a.y != b.y ||
        a.z != b.z;
    }



    /*
        Convert Point3i in to string
    */
    string toString
    (
        /* Masqu */
        const string = "[%d,%d,%d]"
    ) const;



    /*
        Pretty color convert Point3i in to string
    */
    string toString
    (
        /* Max size of */
        const Point3i aSize
    ) const;



    /*
        Multiplication vector components
    */
    inline int mulComponents()
    {
        return x * y * z;
    }

};



/*
    Point declarations
*/
static Point3i POINT_3I_0 = Point3i( 0, 0, 0 );
static Point3i POINT_3I_I = Point3i( 1, 1, 1 );
static Point3i POINT_3I_X = Point3i( 1, 0, 0 );
static Point3i POINT_3I_Y = Point3i( 0, 1, 0 );
static Point3i POINT_3I_Z = Point3i( 0, 0, 1 );
