#include "param_point.h"



using namespace std;



Point3i ParamPoint::point3i
(
    ParamList* a
)
{
    auto result = POINT_3I_0;

    if( a != NULL )
    {
        result = Point3i
        (
            a -> getInt( 0 ),
            a -> getInt( 1 ),
            a -> getInt( 2 )
        );
    }

    return result;
}
