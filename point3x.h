#pragma once

#include <iostream>
#include <string>
#include <cfloat>
#include <tgmath.h>

#include "point4.h"

#include "../core/math.h"


using namespace std;



struct Point4d;



template <typename v>
struct Point3
{
    v x = 0;
    v y = 0;
    v z = 0;



    /*
      Constructor
    */
    Point3() = default;



    /*
      Constructor
    */
    Point3
    (
        const Point3& a
    )
    {
        x = a.x;
        y = a.y;
        z = a.z;
    }



    /*
      Constructor
    */
    Point3
    (
        v ax,
        v ay,
        v az
    )
    {
        x = ax;
        y = ay;
        z = az;
    }



    /*
        Plus Operator r = a + b
    */
    friend Point3 operator+
    (
        /* First operand */
        const Point3& a,
        /* Second operand */
        const Point3& b
    )
    {
        return Point3
        (
            a.x + b.x,
            a.y + b.y,
            a.z + b.z
        );
    }



    /*
        Minus Operator r = a - b
    */
    friend Point3 operator-
    (
        /* First operand */
        const Point3& a,
        /* Second operand */
        const Point3& b
    )
    {
        return Point3
        (
            a.x - b.x,
            a.y - b.y,
            a.z - b.z
        );
    }



    /*
        Operator dot product r = a * b
    */
    friend v operator^
    (
        /* First operand */
        const Point3& a,
        /* Second operand */
        const Point3& b
    )
    {
        return
        a.x * b.x +
        a.y * b.y +
        a.z * b.z
        ;
    }



    friend Point3 operator/
    (
        /* First operand */
        const Point3& a,
        /* Second operand */
        const Point3& b
    )
    {
        return Point3
        (
            abs( a.x - b.x ) < EPSILON_D ? 0 : a.x / b.x,
            abs( a.y - b.y ) < EPSILON_D ? 0 : a.y / b.y,
            abs( a.z - b.z ) < EPSILON_D ? 0 : a.z / b.z
        );
    }



    /*
        Operator scale r = a * b
    */
    friend Point3 operator*
    (
        /* First operand */
        const Point3& a,
        /* Scalar operand */
        v b
    )
    {
        return Point3
        (
            a.x * b,
            a.y * b,
            a.z * b
        );
    }



    /*
        Operator cross r = a x b
    */
    friend Point3 operator%
    (
        /* First operand */
        const Point3& a,
        /* Second operand */
        const Point3& b
    )
    {
        return Point3
        (
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }



    /*
        Operator equal for points
    */
    friend bool operator==
    (
        /* First operand */
        const Point3& a,
        /* Second operand */
        const Point3& b
    )
    {
        return
        abs( a.x - b.x ) <= EPSILON_D &&
        abs( a.y - b.y ) <= EPSILON_D &&
        abs( a.z - b.z ) <= EPSILON_D;
    }



    /*
        Operator equal for points
    */
    friend bool operator!=
    (
        /* First operand */
        const Point3& a,
        /* Second operand */
        const Point3& b
    )
    {
        return
        abs( a.x - b.x ) > EPSILON_D ||
        abs( a.y - b.y ) > EPSILON_D ||
        abs( a.z - b.z ) > EPSILON_D;
    }



    /*
        Return vector
    */
    Point3& get();
    {
        return *this;
    }



    /*
        Set vector coordinates
    */
    Point3& set
    (
        v ax = 0.0,
        v ay = 0.0,
        v az = 0.0
    )
    {
        x = ax;
        y = ay;
        z = az;
        return *this;
    }



    /*
        Set point3 from point3
    */
    Point3& set
    (
        const Point3& a
    )
    {
        x = a.x;
        y = a.y;
        z = a.z;
        return *this;
    }



    /*
        Set point3 from point4
    */
    Point3& set
    (
        Point4d& a
    )
    {
        x = a.x;
        y = a.y;
        z = a.z;
        return *this;
    }



    /*
        Set X component
    */
    Point3& setX
    (
        v a = 0
    )
    {
        x = a;
        return *this;
    }




    /*
        Set Y component
    */
    Point3& setY
    (
        v a = 0
    )
    {
        y = a;
        return *this;
    }



    /*
        Set Z component
    */
    Point3& setZ
    (
        v a = 0
    )
    {
        z = a;
        return *this;
    }



    /*
        Conver to Point4d object
    */
    Point4d toPoint4d
    (
        const v w = 0
    )
    {
        return Point4d( x, y, z, w );
    }



    /*
        Negative vector
    */
    Point3& negative()
    {
        x = -x;
        y = -y;
        z = -z;
        return *this;
    }



    /*
        Add Point3 to Point3
    */
    Point3& add
    (
        const Point3& a
    )
    {
        x += a.x;
        y += a.y;
        z += a.z;
        return *this;
    }




    /*
        Add components to Point3
    */
    Point3& add
    (
        v ax = 0, /* x */
        v ay = 0, /* y */
        v az = 0  /* z */
    )
    {
        x += ax;
        y += ay;
        z += az;
        return *this;
    }



    /*
        Sub
    */
    Point3& sub
    (
        const Point3& a
    )
    {
        x -= a.x;
        y -= a.y;
        z -= a.z;
        return *this;
    }



    /*
        Sub current vector from argument
        and put result to this
    */
    Point3& subFrom
    (
        Point3& a
    )
    {
        x = a.x - x;
        y = a.y - y;
        z = a.z - z;
        return *this;
    }



    /*
        Scale
    */
    Point3& scale
    (
        /* Scalar */
        v a
    )
    {
        x *= a;
        y *= a;
        z *= a;
        return *this;
    }



    /*
        Magnitude
    */
    v magn()
    {
        return sqrt
        (
            x * x +
            y * y +
            z * z
        );
    }




    /*
        Normalize
    */
    Point3& norm()
    {
        auto m = magn();
        if( m > EPSILON_D )
        {
            scale( 1 / m );
        }
        else
        {
            set();
        }
        return *this;
    }



    /*
        Rotate current point around vector

        Point
        o
        |  o Result
        |a/
        |/
        O---------> aBase
    */
    Point3& rotate
    (
        const Point3 aBase,
        /* Angle at radians */
        const v aAngleRad
    )
    {
        auto sn = sinf( aAngleRad );
        auto cs = cosf( aAngleRad );

        auto dz = aBase * ( *this ^ aBase );
        auto dx = *this - dz;
        auto dy = dx % aBase;

        set( dx.scale( cs ) + dy.scale( sn ) + dz );
        return *this;
    }



    /*
        Distance between this Point3
    */
    v dist
    (
        const Point3& a
    ) const
    {
        auto dx = a.x - x;
        auto dy = a.y - y;
        auto dz = a.z - z;
        return sqrt( dx * dx + dy * dy + dz * dz );
    }




    /*
        Distance between this Point3 in XY surface
    */
    v distXY
    (
        const Point3& a
    )
    {
        auto dx = a.x - x;
        auto dy = a.y - y;
        return sqrt( dx * dx + dy * dy );
    }




    /*
        Cross vproduct
    */
    Point3& cross
    (
        const Point3& a
    )
    {
        auto dx = y * a.z - z * a.y;
        auto dy = z * a.x - x * a.z;
        auto dz = x * a.y - y * a.x;

        x = dx;
        y = dy;
        z = dz;

        return *this;
    }




    /*
        Dot product
    */
    v dot
    (
        Point3& a
    )
    {
        return
        x * a.x +
        y * a.y +
        z * a.z;
    }



    /*
        Compare vectors
    */
    v cmp
    (
        const Point3& a
    )
    {
        return
        abs( x - a.x ) < EPSILON_D &&
        abs( y - a.y ) < EPSILON_D &&
        abs( z - a.z ) < EPSILON_D
        ;
    }



    /*
        Set min point to this
    */
    Point3& min
    (
        const Point3& a
    )
    {
        x = std::min( x, a.x );
        y = std::min( y, a.y );
        z = std::min( z, a.z );
        return *this;
    }



    /*
        Set max point to this
    */
    Point3& max
    (
        const Point3& a
    )
    {
        x = std::max( x, a.x );
        y = std::max( y, a.y );
        z = std::max( z, a.z );
        return *this;
    }




    /*
        Linear interpolate from this for 0 to argument for 1
    */
    Point3& itpLin
    (
        const Point3& a,
        const v t
    )
    {
        x += ( a.x - x ) * t;
        y += ( a.y - y ) * t;
        z += ( a.z - z ) * t;
        return *this;
    }



    /*
        Convert Point3 to string
    */
    string toString() const;
    {
        return
        "[" + to_string( x ) + "]" +
        "[" + to_string( y ) + "]" +
        "[" + to_string( z ) + "]"
        ;
    }



    /*
        Test this point at rect
    */
    bool testRectXY
    (
        /* Top left */
        Point3& aTopLeft,
        /* Bottom right */
        Point3 aBottomRight
    )
    {
        return
        x >= std::min( aTopLeft.x, aBottomRight.x ) &&
        x <= std::max( aBottomRight.x, aTopLeft.x ) &&
        y >= std::min( aTopLeft.y, aBottomRight.y ) &&
        y <= std::max( aBottomRight.y, aTopLeft.y );
    }

};



/*
    Define static constatns
*/
static auto POINT_3D_0 = Point3( 0.0, 0.0, 0.0 );
static auto POINT_3I_0 = Point3( 0, 0, 0 );

static auto POINT_3D_I = Point3( 1.0, 1.0, 1.0 );
static auto POINT_3I_I = Point3( 1, 1, 1 );

static Point3 POINT_3D_X        = Point3( 1.0, 0.0, 0.0 );
static Point3 POINT_3D_RIGHT    = Point3( 1.0, 0.0, 0.0 );
static Point3 POINT_3D_LEFT     = Point3( -1.0, 0.0, 0.0 );

static Point3 POINT_3D_Y        = Point3( 0.0, 1.0, 0.0 );
static Point3 POINT_3D_TOP      = Point3( 0.0, 1.0, 0.0 );
static Point3 POINT_3D_BOTTOM   = Point3( 0.0, -1.0, 0.0 );

static Point3 POINT_3D_Z        = Point3( 0.0, 0.0, 1.0 );
static Point3 POINT_3D_FRONT    = Point3( 0.0, 0.0, 1.0 );
static Point3 POINT_3D_BACK     = Point3( 0.0, 0.0, -1.0 );

static Point3 POINT_3D_NZ       = Point3( 0.0, 0.0, -1.0 );

static Point3 POINT_3D_X_05     = Point3( 0.5, 0.0, 0.0 );
static Point3 POINT_3D_Y_05     = Point3( 0.0, 0.5, 0.0 );
static Point3 POINT_3D_Z_05     = Point3( 0.0, 0.0, 0.5 );

static Point3 POINT_3D_MIN_INF  = Point3( DBL_MIN, DBL_MIN, DBL_MIN );
static Point3 POINT_3D_MAX_INF  = Point3( DBL_MAX, DBL_MAX, DBL_MAX );
