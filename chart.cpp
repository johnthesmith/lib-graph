#include <iostream>

#include "chart.h"
#include "../core/rnd.h"



Chart2d::Chart2d
(
    Scene* aScene
)
{
    scene = aScene;
}



Chart2d* Chart2d::create
(
    Scene* aScene
)
{
    return new Chart2d( aScene );
}



void Chart2d::destroy()
{
    delete this;
}


/*
    y
    ^
    |
    |
    |   p2-------------p3
    |    |             |
    |    |      *      |
    |    |      center |
    |   p1-------------p4
    |
    *-----------------------------> x
*/

Chart2d* Chart2d::drawBack()
{
    Point2d p1 = rect.center - rect.size;
    Point2d p2 = Point2d( p1.x, rect.center.y + rect.size.y );
    Point2d p3 = rect.center + rect.size;
    Point2d p4 = Point2d( p3.x, p1.y);

    scene -> begin( QUAD ) -> color( backColor );
    scene -> vertex( p1 ) -> vertex( p2 ) -> vertex( p3 ) -> vertex( p4 );
    scene -> end();

    scene -> setLineWidth( 1 );
    scene -> begin( LOOP ) -> color( lineColor );
    scene -> vertex( p1 ) -> vertex( p2 ) -> vertex( p3 ) -> vertex( p4 );
    scene -> end();

    return this;
}



Chart2d* Chart2d::draw
(
    function <double ( double, double )> aCalc,
    double a1
)
{
    double step = ( xMax - xMin ) / ( rect.size.x * 2 );

    scene -> setLineWidth( lineWeight );

    scene -> begin( LINES  ) -> color( lineColor );;
    double x = xMin;
    while( x < xMax )
    {
        double y = aCalc( x, a1 );
        Point2d p = chartToScreen( Point2d( x, y ));
        scene -> vertex( p );
        x = x + step;
    }
    scene -> end();


    return this;
}



Chart2d* Chart2d::draw
(
    function <double ( double )> aCalc
)
{
    double step = ( xMax - xMin ) / ( rect.size.x * 2 );

    scene -> setLineWidth( lineWeight );

    scene -> begin( LINES  ) -> color( lineColor );;
    double x = xMin;
    while( x < xMax )
    {
        double y = aCalc( x );
        Point2d p = chartToScreen( Point2d( x, y ));
        scene -> vertex( p );
        x = x + step;
    }
    scene -> end();

    return this;
}



/*
    Draw chart
*/
Chart2d* Chart2d::drawChartData
(
    ChartData* aChartData
)
{
    return this;
}



Chart2d* Chart2d::drawX
(
    double  x,
    bool    aLabel,
    int     aShift
)
{
    scene -> setLineWidth( lineWeight );

    Point2d p1 = chartToScreen( Point2d( x, yMin ));
    Point2d p2 = chartToScreen( Point2d( x, yMax ));

    scene
    -> begin( LINE  )
    -> color( lineColor )
    -> vertex( p1 )
    -> vertex( p2 )
    -> end();

    if( aLabel )
    {
        scene
        -> setTextHorisontalAlign( ALIGN_LEFT )
        -> setTextPosition( Point3d( p2.x, p2.y, 0 ))
        -> textCR( aShift )
        -> text( to_string( x ));
    }

    return this;
}



Chart2d* Chart2d::drawY
(
    double y
)
{
    scene -> setLineWidth( lineWeight );

    Point2d p1 = chartToScreen( Point2d( xMin, y ));
    Point2d p2 = chartToScreen( Point2d( xMax, y ));

    scene
    -> begin( LINE  )
    -> color( lineColor )
    -> vertex( p1 )
    -> vertex( p2 )
    -> end();

    return this;
}



Chart2d* Chart2d::setCenterSize
(
    const Point2d& aCenter,
    const Point2d& aSize
)
{
    rect.setCenterSize( aCenter, aSize );
    return this;
}



Point2d Chart2d::chartToScreen
(
    const Point2d& a
)
{
    double chartWidth   = xMax - xMin;
    double screenWidth  = rect.size.x * 2;
    double chartHeight  = yMax - yMin;
    double screenHeight = rect.size.y * 2;

    double nx = a.x < xMin ? xMin : ( a.x > xMax ? xMax : a.x );
    double ny = a.y < yMin ? yMin : ( a.y > yMax ? yMax : a.y );

    nx = ( nx - xMin ) / chartWidth;
    ny = ( ny - yMin ) / chartHeight;

    auto result = Point2d
    (
        nx * screenWidth + rect.center.x - rect.size.x,
        ny * screenHeight + rect.center.y - rect.size.y
    );

    return result;
}



Chart2d* Chart2d::setBackColor
(
    Rgba& a
)
{
    backColor = a;
    return this;
}



Chart2d* Chart2d::setLineColor
(
    Rgba& a
)
{
    lineColor = a;
    return this;
}



Chart2d* Chart2d::setXMin
(
    double a
)
{
    xMin = a;
    return this;
}



Chart2d* Chart2d::setXMax
(
    double a
)
{
    xMax = a;
    return this;
}



Chart2d* Chart2d::setYMin
(
    double a
)
{
    yMin = a;
    return this;
}



Chart2d* Chart2d::setYMax
(
    double a
)
{
    yMax = a;
    return this;
}



Chart2d* Chart2d::setLineWeight
(
    double a
)
{
    lineWeight = a;
    return this;
}
