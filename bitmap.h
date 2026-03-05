#pragma once

/*
    The Bitmap class for image operations using stb_image
*/

#include "../core/result.h"
#include "rgba.h"
#include <vector>
#include <string>

class Bitmap : public Result
{
    private:

        int                     width   = 0;
        int                     height  = 0;
        int                     channels = 4;   // RGBA
        std::vector<unsigned short> pixels;     // 16-bit per channel

        Bitmap* updateSize();

    public:

        /*
            Constructor
        */
        Bitmap();



        /*
            Destructor
        */
        ~Bitmap();


        /*
            Creator
        */
        static Bitmap* create();



        /*
            Destroy the bitmap
        */
        void destroy();



        /*
            Load bitmap from file (any format via stb_image)
        */
        Bitmap* load
        (
            std::string  /* File name */
        );




        /*
            Save bitmap to file (not implemented with stb_image)
        */
        Bitmap* save
        (
            std::string  /* File name */
        );



        /*
            Resize bitmap
        */
        Bitmap* scale
        (
            int, /* Width */
            int /* Height */
        );



        /*
            Resize bitmap
        */
        Bitmap* zoom
        (
            double,         /* Zoom */
            bool = false    /* Keep size */
        );



        /*
            Crop bitmap
        */
        Bitmap* crop
        (
            int,    /* left */
            int,    /* top */
            int,    /* width */
            int     /* height */
        );



        /*
            Shift bitmap
        */
        Bitmap* shift
        (
            double, /* x shift */
            double  /* y shift */
        );



        /*
            Rotate bitmap
        */
        Bitmap* rotate
        (
            double circlePart,
            bool   cropToFit,
            Rgba   fillColor
        );



        /*
            Get width of bitmap
        */
        int getWidth();



        /*
            Get height of bitmap
        */
        int getHeight();




        /*
            Set size of bitmap (creates blank image)
        */
        Bitmap* setSize
        (
            int,
            int
        );




        /*
            Get pixel
        */
        Bitmap* getRgba
        (
            int,
            int,
            Rgba&
        );



        /*
            Draw rectangle
        */
        Bitmap* rectangle
        (
            int,
            int,
            int,
            int
        );


        /*
            Draw text on bitmap
        */
        Bitmap* text
        (
            std::string,
            std::string,
            int,    /* Size */
            int,
            int
        );



        /*
            Clear bitmap (fill with black)
        */
        Bitmap* erase();



        /*
            Return image buffer for neural network
        */
        unsigned short* buildRGBA();


        /*
            Get raw pixel vector reference
        */
        const std::vector<unsigned short>& getPixels() const;

        /*
            Clear RGBA buffer (compatibility method)
        */
        Bitmap* clearRGBA
        (
            unsigned short*
        );

};








//#pragma once
//
///*
//    The Bitmap muzle on ImageMagic
//    http://www.graphicsmagick.org/Magick++/Image.html
//*/
//
//#include <Magick++.h>
//#include "../core/result.h"
//#include "rgba.h"
//#include "../../vendor/fpng/src/fpng.h"
//
//using namespace std;
//
//
//
//class Bitmap : public Result
//{
//    private:
//
//        int             width   = 0;
//        int             height  = 0;
//
//        Magick::Image*  image   = NULL;
//
//        Bitmap* updateSize();
//
//    public:
//
//        /*
//            Constructor
//        */
//        Bitmap();
//
//
//
//        /*
//            Destructor
//        */
//        ~Bitmap();
//
//
//        /*
//            Creator
//        */
//        static Bitmap* create();
//
//
//
//        /*
//            Destroy the bitmap
//        */
//        void destroy();
//
//
//
//        /*
//            Load bitmap from file
//        */
//        Bitmap* load
//        (
//            string  /* File name */
//        );
//
//
//
//
//        /*
//            Load bitmap from file
//        */
//        Bitmap* save
//        (
//            string  /* File name */
//        );
//
//
//
//        /*
//            Resize bitmap
//        */
//        Bitmap* scale
//        (
//            int, /* Width */
//            int /* Height */
//        );
//
//
//
//        /*
//            Resize bitmap
//        */
//        Bitmap* zoom
//        (
//            double,         /* Zoom */
//            bool = false    /* Keep size */
//        );
//
//
//
//        /*
//            Crop bitmap
//        */
//        Bitmap* crop
//        (
//            int,    /* left */
//            int,    /* top */
//            int,    /* width */
//            int     /* height */
//        );
//
//
//
//        /*
//            Resize bitmap
//        */
//        Bitmap* shift
//        (
//            double, /* x shift */
//            double  /* y shift */
//        );
//
//
//
//        /*
//            Rotate bitmap
//        */
//        Bitmap* rotate
//        (
//            double,         /* Part of circle */
//            bool = false    /* Crop */
//        );
//
//
//
//        /*
//            Get width of bitmap
//        */
//        int getWidth();
//
//
//
//        /*
//            Get height of bitmap
//        */
//        int getHeight();
//
//
//
//
//        /*
//            Set width of bitmap
//        */
//        Bitmap* setSize
//        (
//            int,
//            int
//        );
//
//
//
//
//        /*
//            Get pixel
//        */
//        Bitmap* getRgba
//        (
//            int,
//            int,
//            Rgba&
//        );
//
//
//
//        /*
//            Rectangle
//        */
//        Bitmap* rectangle
//        (
//            int,
//            int,
//            int,
//            int
//        );
//
//
//        /*
//            Draw text on bitamp
//        */
//        Bitmap* text
//        (
//            string,
//            string,
//            int,    /* Size */
//            int,
//            int
//        );
//
//
//
//        /*
//            Clear bitmap
//        */
//        Bitmap* erase();
//
//
//
//        /*
//            Return image buffer
//        */
//        unsigned short* buildRGBA();
//        Bitmap* clearRGBA
//        (
//            unsigned short*
//        );
//
//};
