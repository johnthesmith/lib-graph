#include "point3i.h"



Point3i::Point3i
(
    int aX,
    int aY,
    int aZ
)
{
    x = aX;
    y = aY;
    z = aZ;
}



/*
    Return 3d position by linear index

      x 0 1 2 3 4
    y
    0   0 1 2 3 4
    1   5 6[7]8 9

    argument size[5,2,1], index[ 7 ]
    result [ 2,1,0 ]
*/
Point3i Point3i::byIndex
(
    Point3i aSize,
    int aIndex
)
{
    return Point3i
    (
        aIndex % aSize.x,
        aIndex / aSize.x,
        aIndex / ( aSize.x * aSize.y )
    );
}



/*
    Minus Operator r = a - b
*/
Point3i operator -
(
    const Point3i& a, /* First operand */
    const int b       /* Second operand */
)
{
    return Point3i
    (
        a.x - b,
        a.y - b,
        a.z - b
    );
}



/*
    Minus Operator r = a - b
*/
Point3i operator -
(
    const Point3i& a,    /* First operand */
    const Point3i& b     /* Second operand */
)
{
    return Point3i
    (
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    );
}



/*
    Operator equal for points
*/
bool operator ==
(
    const Point3i& a,    /* First operand */
    const Point3i& b     /* Second operand */
)
{
    return
    a.x == b.x &&
    a.y == b.y &&
    a.z == b.z;
}



/*
    Operator not equal for points
*/
bool operator !=
(
    const Point3i& a,    /* First operand */
    const Point3i& b     /* Second operand */
)
{
    return
    a.x != b.x ||
    a.y != b.y ||
    a.z != b.z;
}



/*
    Multiplication vector components
*/
int Point3i::mulComponents()
{
    return x * y * z;
}



/*
    Convert Point3d to string
*/
string Point3i::toString
(
    const string aFormat
) const
{
    const char* format = aFormat.c_str();
    /* Let buffer size */
    int size = std::snprintf(nullptr, 0, format, x, y, z) + 1;
    std::string result(size, '\0');
    std::snprintf(&result[0], size, format, x, y, z);
    /* Remove null-terminator */
    result.pop_back();
    return result;
}
