#pragma once

#include <functional>   /* for lyambda */

#include "rect2d.h"
#include "scene.h"
#include "rgba.h"
#include "../core/chart_data.h"

class Chart2d
{
    private:

        Rect2d& rect = RECT_2D_0;   /* Chart rect */

        double  xMin = -1.0;        /* Begin x axis */
        double  xMax = 1.0;
        double  yMin = -1.0;
        double  yMax = 1.0;

        Rgba backColor = Rgba( 0.4, 0.7, 1.0, 0.7 );
        Rgba lineColor = Rgba( 0.1, 0.2, 0.4, 0.7 );
        double lineWeight = 1.0;

        Scene*  scene;

    public:

        Chart2d
        (
            Scene*
        );



        static Chart2d* create
        (
            Scene*
        );



        void destroy();



        /* Draw method */
        Chart2d* drawBack();


        /* Draw method */
        Chart2d* draw
        (
            function <double ( double, double )>,    /* Lambda calculate function */
            double
        );



        /* Draw method */
        Chart2d* draw
        (
            function <double ( double )>    /* Lambda calculate function */
        );




        /*
            Draw chart
        */
        Chart2d* drawChartData
        (
            ChartData*
        );




        Chart2d* drawX  /* Draw X value */
        (
            double,
            bool = false,   /* Label */
            int = 0         /* Label shoft */
        );



        Chart2d* drawY  /* Draw Y value */
        (
            double
        );



        Chart2d* setCenterSize
        (
            const Point2d&,
            const Point2d&
        );



        Point2d chartToScreen
        (
            const Point2d& a
        );



        Chart2d* setBackColor
        (
            Rgba&
        );



        Chart2d* setLineColor
        (
            Rgba&
        );



        Chart2d* setXMin
        (
            double
        );



        Chart2d* setXMax
        (
            double
        );



        Chart2d* setYMin
        (
            double
        );



        Chart2d* setYMax
        (
            double
        );



        Chart2d* setLineWeight
        (
            double
        );
};
