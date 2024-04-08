/*
    Bitmap
*/

#include <iostream>
#include "bitmap.h"
#include "../core/utils.h"


/* Global flag for image magic initialization in Bitmap constructor */
static bool imageMagicInit = false;



/*
    Constructor
*/
Bitmap::Bitmap()
{
    if( !imageMagicInit )
    {
        Magick::InitializeMagick( nullptr );
        imageMagicInit = true;
    }

    image = new Magick::Image();
}



/*
    Destructor
*/
Bitmap::~Bitmap()
{
    delete image;
}



/*
    Creator
*/
Bitmap* Bitmap::create()
{
    return new Bitmap();
}



/*
    Destroy the bitmap
*/
void Bitmap::destroy()
{
    delete( this );
}



/*
    Load bitmap from file
*/
Bitmap* Bitmap::load
(
    string a /* File name */
)
{
    if( fileExists( a ) )
    {
        try
        {
            image -> read( a );
            updateSize();
        }
        catch( Magick::Exception &e )
        {
            setResult
            (
                "file_read_error",
                "File read error " + (string) e.what()
            );
        }
    }
    else
    {
        setResult( "file_not_exists", "File not exists" + a );
    }
    return this;
}




/*
    Load bitmap from file
*/
Bitmap* Bitmap::save
(
    string a /* File name */
)
{
    try
    {
        image -> write( a );
    }
    catch( Magick::Exception &e )
    {
        setResult
        (
            "file_write_error",
            "File write error " + ( string ) e.what()
        );
    }
    return this;
}




/*
    Resize image
*/
Bitmap* Bitmap::scale
(
    int aWidth,
    int aHeight
)
{
    image -> sample( Magick::Geometry( aWidth, aHeight ));
    updateSize();
    return this;
}




/*
    Resize bitmap
*/
Bitmap* Bitmap::zoom
(
    double  aZoom,      /* Zoom */
    bool    aKeepSize   /* Keep size */
)
{
    auto oldWidth = width;
    auto oldHeight = height;

    if( aZoom < 0.0 ) aZoom = 0;

    scale( width * aZoom, height * aZoom );
    if( aKeepSize )
    {
        if( aZoom >= 1.0 )
        {
            crop
            (
                ( width - oldWidth ) / 2,
                ( height - oldHeight ) / 2,
                oldWidth,
                oldHeight
            );
        }
        else
        {
            auto newImage = new Magick::Image
            (
                Magick::Geometry( oldWidth, oldHeight ),
                Magick::Color( "white" )
            );

            int x = ( oldWidth - width ) / 2;
            int y = ( oldHeight - height ) / 2;

            newImage -> composite( *image, x, y, Magick::OverCompositeOp );

            delete image;
            image = newImage;
            updateSize();
        }
    }
    else
    {
        updateSize();
    }
    return this;
}



/*
    Resize bitmap
*/
Bitmap* Bitmap::shift
(
    double aX,
    double aY
)
{
    auto newImage = new Magick::Image
    (
        Magick::Geometry( width, height ),
        Magick::Color( "white" )
    );

    newImage -> composite
    (
        *image,
        width * aX,
        height * aY,
        Magick::OverCompositeOp
    );

    delete image;
    image = newImage;

    return this;
}




/*
    Crop bitmap
*/
Bitmap* Bitmap::crop
(
    int aLeft,      /* left */
    int aTop,       /* top */
    int aWidth,     /* width */
    int aHeight    /* height */
)
{
    image -> crop( Magick::Geometry( aWidth, aHeight, aLeft, aTop ));
    updateSize();
    return this;
}




/*
    Rotate bitmap
*/
Bitmap* Bitmap::rotate
(
    double aCircle, /* Part of circle */
    bool    aCrop
)
{
    image -> rotate( aCircle * 360.0 );
    if( aCrop )
    {
        crop
        (
            ( image -> columns() - width ) / 2,
            ( image -> rows() - height ) / 2,
            width,
            height
        );
    }
    else
    {
        updateSize();
    }
    return this;
}



/*
    Resize bitmap
*/
Bitmap* Bitmap::setSize
(
    int aWidth,
    int aHeight
)
{
    image -> size( to_string( aWidth ) + "x" + to_string( aHeight ));
    updateSize();
    return this;
}



/*
    Get width of bitmap
*/
int Bitmap::getWidth()
{
    return width;
}



/*
    Get height of bitmap
*/
int Bitmap::getHeight()
{
    return height;
}



/*
    Get pixel
*/
Bitmap* Bitmap::getRgba
(
    int x,
    int y,
    Rgba& a
)
{
    if( x >= 0 && x < width && y >= 0 && y < height )
    {
        auto p = image -> getPixels( x, y, 1, 1 );
        a = Rgba
        (
            (double) p -> red / (double) 0xFFFF,
            (double) p -> green / (double) 0xFFFF,
            (double) p -> blue / (double) 0xFFFF,
            1.0
        );
    }
    else
    {
        a = Rgba();
    }
    return this;
}



Bitmap* Bitmap::updateSize()
{
    width = image -> columns();
    height = image -> rows();
    return this;
}



Bitmap* Bitmap::rectangle
(
    int l,
    int t,
    int r,
    int b
)
{
    image -> strokeColor( Magick::Color( "white" ) );
    image -> fillColor( Magick::Color( "none" ) );
    image -> draw( Magick::DrawableRectangle( l, t, r, b ));
    return this;
}


/*
    Draw text on bitamp
*/
Bitmap* Bitmap::text
(
    string aText,
    string aFont,
    int size,
    int x,
    int y
)
{
    image -> fontPointsize( size );
    image -> font( aFont );
    image -> fillColor( Magick::Color( "white" ) );
    image -> draw( Magick::DrawableText( x, y,  aText ));
    return this;
}



/*
    Return image buffer
*/
unsigned short* Bitmap::buildRGBA()
{
    int w = getWidth();
    int h = getHeight();
    unsigned short* ptr = new unsigned short[ 4 * w * h ];
    image -> write( 0, 0, w, h, "RGBA", Magick::ShortPixel, ptr );
    return ptr;
}



Bitmap* Bitmap::clearRGBA
(
    unsigned short* a
)
{
    if( a != NULL )
    {
        delete [] a;
    }
    return this;
}



Bitmap* Bitmap::erase()
{
    if( image != NULL )
    {
        image -> backgroundColor( Magick::Color( "black" ) );
        image -> erase();
    }
    return this;
}
