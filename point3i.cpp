#include <sstream>

#include "point3i.h"
#include "../core/console.h"
#include "../core/utils.h"


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
    int size = std::snprintf( nullptr, 0, format, x, y, z) + 1;
    std::string result(size, '\0');
    std::snprintf(&result[0], size, format, x, y, z);
    /* Remove null-terminator */
    result.pop_back();
    return result;
}



/*
    Convert Point3d to string
*/
string Point3i::toString
(
    const Point3i aSize
) const
{
    /* Vector masque build */
    std::stringstream s;

    s
    << INK_GREY
    << "["
    << ( x < 0 ? INK_RED : ( x > 0 ? INK_GREEN : INK_CYAN ))
    << "%"
    << length( aSize.x )
    << "d"
    << INK_GREY
    << ","
    << ( y < 0 ? INK_RED : ( y > 0 ? INK_GREEN : INK_CYAN ))
    << "%"
    << length( aSize.y )
    << "d"
    << INK_GREY
    << ","
    << ( z < 0 ? INK_RED : ( z > 0 ? INK_GREEN : INK_CYAN ))
    << "%"
    << length( aSize.z )
    << "d"
    << INK_GREY
    << "]"
    << INK_DEFAULT;

    return toString( s.str() );
}
