/*
    Bitmap implementation with stb_image
*/

#include <iostream>
#include <algorithm>
#include <cmath>
#include "bitmap.h"
#include "../core/utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../vendor/stb/stb_image.h"

/*
    Constructor
*/
Bitmap::Bitmap() : Result()
{
    // Nothing to initialize
}



/*
    Destructor
*/
Bitmap::~Bitmap()
{
    pixels.clear();
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
    delete this;
}



/*
    Load bitmap from file
*/
Bitmap* Bitmap::load
(
    std::string filename
)
{
    if( !fileExists( filename ) )
    {
        setResult( "file_not_exists", "File not exists: " + filename );
        return this;
    }

    int w, h, comp;
    unsigned char* data = stbi_load(filename.c_str(), &w, &h, &comp, 4);

    if( !data )
    {
        setResult
        (
            "decode_error",
            "Failed to decode image: " + std::string(stbi_failure_reason())
        );
        return this;
    }

    width = w;
    height = h;
    channels = 4;

    // Convert 8-bit to 16-bit (0-65535)
    size_t pixel_count = width * height * 4;
    pixels.resize(pixel_count);

    for( size_t i = 0; i < pixel_count; i++ )
    {
        // 8-bit -> 16-bit: multiply by 257 (0xFF -> 0xFFFF)
        pixels[i] = data[i] * 257;
    }

    stbi_image_free(data);
    setResult( "ok", "Loaded successfully" );
    return this;
}




/*
    Save bitmap to file (not implemented with stb_image)
*/
Bitmap* Bitmap::save
(
    std::string filename
)
{
    setResult( "not_implemented", "Save not implemented with stb_image" );
    return this;
}




/*
    Resize image using bilinear interpolation
*/
Bitmap* Bitmap::scale
(
    int newWidth,
    int newHeight
)
{
    if( pixels.empty() || width == 0 || height == 0 )
    {
        setResult( "no_data", "No image data to scale" );
        return this;
    }

    if( newWidth <= 0 || newHeight <= 0 )
    {
        setResult( "invalid_size", "Invalid target size" );
        return this;
    }

    std::vector<unsigned short> new_pixels(newWidth * newHeight * 4);

    float x_ratio = static_cast<float>(width) / newWidth;
    float y_ratio = static_cast<float>(height) / newHeight;

    for( int y = 0; y < newHeight; y++ )
    {
        for( int x = 0; x < newWidth; x++ )
        {
            float src_x = x * x_ratio;
            float src_y = y * y_ratio;

            int x1 = static_cast<int>(src_x);
            int y1 = static_cast<int>(src_y);
            int x2 = std::min(x1 + 1, width - 1);
            int y2 = std::min(y1 + 1, height - 1);

            float dx = src_x - x1;
            float dy = src_y - y1;

            int idx00 = (y1 * width + x1) * 4;
            int idx01 = (y1 * width + x2) * 4;
            int idx10 = (y2 * width + x1) * 4;
            int idx11 = (y2 * width + x2) * 4;
            int dst_idx = (y * newWidth + x) * 4;

            for( int c = 0; c < 4; c++ )
            {
                float top = pixels[idx00 + c] * (1 - dx) + pixels[idx01 + c] * dx;
                float bottom = pixels[idx10 + c] * (1 - dx) + pixels[idx11 + c] * dx;
                float value = top * (1 - dy) + bottom * dy;

                new_pixels[dst_idx + c] = static_cast<unsigned short>(value);
            }
        }
    }

    width = newWidth;
    height = newHeight;
    pixels = std::move(new_pixels);

    return this;
}




/*
    Zoom bitmap
*/
Bitmap* Bitmap::zoom
(
    double  zoomFactor,
    bool    keepSize
)
{
    if( pixels.empty() || width == 0 || height == 0 )
    {
        setResult( "no_data", "No image data to zoom" );
        return this;
    }
    
    if( zoomFactor < 0.0 ) zoomFactor = 0.0;
    
    int oldWidth = width;
    int oldHeight = height;
    int newWidth = static_cast<int>(width * zoomFactor);
    int newHeight = static_cast<int>(height * zoomFactor);
    
    if( newWidth <= 0 || newHeight <= 0 )
    {
        setResult( "invalid_zoom", "Zoom factor too small" );
        return this;
    }
    
    scale( newWidth, newHeight );
    
    if( keepSize )
    {
        if( zoomFactor >= 1.0 )
        {
            // Crop to original size
            crop(
                (width - oldWidth) / 2,
                (height - oldHeight) / 2,
                oldWidth,
                oldHeight
            );
        }
        else
        {
            // Create white canvas of original size
            std::vector<unsigned short> new_pixels(oldWidth * oldHeight * 4, 0xFFFF);
            
            int x_offset = (oldWidth - width) / 2;
            int y_offset = (oldHeight - height) / 2;
            
            // Paste scaled image onto white canvas
            for( int y = 0; y < height; y++ )
            {
                for( int x = 0; x < width; x++ )
                {
                    int dst_idx = ((y + y_offset) * oldWidth + (x + x_offset)) * 4;
                    int src_idx = (y * width + x) * 4;
                    
                    for( int c = 0; c < 4; c++ )
                    {
                        new_pixels[dst_idx + c] = pixels[src_idx + c];
                    }
                }
            }
            
            width = oldWidth;
            height = oldHeight;
            pixels = std::move(new_pixels);
        }
    }
    
    return this;
}




/*
    Shift bitmap
*/
Bitmap* Bitmap::shift
(
    double xShift,
    double yShift
)
{
    if( pixels.empty() || width == 0 || height == 0 )
    {
        setResult( "no_data", "No image data to shift" );
        return this;
    }

    std::vector<unsigned short> new_pixels(width * height * 4, 0xFFFF); // White background

    int x_offset = static_cast<int>(width * xShift);
    int y_offset = static_cast<int>(height * yShift);

    for( int y = 0; y < height; y++ )
    {
        for( int x = 0; x < width; x++ )
        {
            int src_x = x - x_offset;
            int src_y = y - y_offset;
            
            if( src_x >= 0 && src_x < width && src_y >= 0 && src_y < height )
            {
                int dst_idx = (y * width + x) * 4;
                int src_idx = (src_y * width + src_x) * 4;
                
                for( int c = 0; c < 4; c++ )
                {
                    new_pixels[dst_idx + c] = pixels[src_idx + c];
                }
            }
        }
    }
    
    pixels = std::move(new_pixels);
    return this;
}




/*
    Crop bitmap
*/
Bitmap* Bitmap::crop
(
    int left,
    int top,
    int cropWidth,
    int cropHeight
)
{
    if( pixels.empty() || width == 0 || height == 0 )
    {
        setResult( "no_data", "No image data to crop" );
        return this;
    }

    if
    (
        left < 0 || top < 0 ||
        left + cropWidth > width ||
        top + cropHeight > height ||
        cropWidth <= 0 || cropHeight <= 0
    )
    {
        setResult( "invalid_crop", "Invalid crop parameters" );
        return this;
    }

    std::vector<unsigned short> new_pixels(cropWidth * cropHeight * 4);
    for( int y = 0; y < cropHeight; y++ )
    {
        for( int x = 0; x < cropWidth; x++ )
        {
            int src_idx = ((top + y) * width + (left + x)) * 4;
            int dst_idx = (y * cropWidth + x) * 4;

            for( int c = 0; c < 4; c++ )
            {
                new_pixels[dst_idx + c] = pixels[src_idx + c];
            }
        }
    }

    width = cropWidth;
    height = cropHeight;
    pixels = std::move(new_pixels);

    return this;
}




/*
    Rotate bitmap by arbitrary angle with bilinear interpolation
*/
Bitmap* Bitmap::rotate
(
    double circlePart,
    bool   cropToFit,
    Rgba   fillColor
)
{
    if( pixels.empty() || width == 0 || height == 0 )
    {
        setResult( "no_data", "No image data to rotate" );
        return this;
    }

    double angle = circlePart * 2.0 * M_PI; // Convert to radians
    double cos_a = cos(angle);
    double sin_a = sin(angle);

    // Конвертируем fillColor (0..1 double) в unsigned short (0..65535)
    unsigned short fillR = static_cast<unsigned short>(fillColor.red * 65535.0);
    unsigned short fillG = static_cast<unsigned short>(fillColor.green * 65535.0);
    unsigned short fillB = static_cast<unsigned short>(fillColor.blue * 65535.0);
    unsigned short fillA = static_cast<unsigned short>(fillColor.alpha * 65535.0);

    // Calculate new image bounds
    int corners[4][2] =
    {
        {0, 0},
        {width, 0},
        {0, height},
        {width, height}
    };

    // Project corners
    int min_x = width, max_x = 0, min_y = height, max_y = 0;

    for( int i = 0; i < 4; i++ )
    {
        int x = corners[i][0] - width/2;
        int y = corners[i][1] - height/2;

        int rot_x = static_cast<int>(x * cos_a - y * sin_a + width/2);
        int rot_y = static_cast<int>(x * sin_a + y * cos_a + height/2);

        min_x = std::min(min_x, rot_x);
        max_x = std::max(max_x, rot_x);
        min_y = std::min(min_y, rot_y);
        max_y = std::max(max_y, rot_y);
    }

    int newWidth = max_x - min_x + 1;
    int newHeight = max_y - min_y + 1;

    // If cropping to original size
    if( cropToFit )
    {
        newWidth = width;
        newHeight = height;
    }

    // Создаем новый буфер с указанным цветом фона
    std::vector<unsigned short> new_pixels(newWidth * newHeight * 4);

    // Заполняем указанным цветом
    for( size_t i = 0; i < new_pixels.size(); i += 4 )
    {
        new_pixels[i] = fillR;
        new_pixels[i+1] = fillG;
        new_pixels[i+2] = fillB;
        new_pixels[i+3] = fillA;
    }

    // Center offsets
    int center_x = width / 2;
    int center_y = height / 2;
    int new_center_x = newWidth / 2;
    int new_center_y = newHeight / 2;

    // Inverse rotation for bilinear sampling
    for( int y = 0; y < newHeight; y++ )
    {
        for( int x = 0; x < newWidth; x++ )
        {
            // Translate to center
            int tx = x - new_center_x;
            int ty = y - new_center_y;

            // Inverse rotate
            double src_x = tx * cos_a + ty * sin_a + center_x;
            double src_y = -tx * sin_a + ty * cos_a + center_y;

            if( src_x >= 0 && src_x < width - 1 && src_y >= 0 && src_y < height - 1 )
            {
                int x1 = static_cast<int>(src_x);
                int y1 = static_cast<int>(src_y);
                int x2 = x1 + 1;
                int y2 = y1 + 1;

                double dx = src_x - x1;
                double dy = src_y - y1;

                int idx00 = (y1 * width + x1) * 4;
                int idx01 = (y1 * width + x2) * 4;
                int idx10 = (y2 * width + x1) * 4;
                int idx11 = (y2 * width + x2) * 4;

                int dst_idx = (y * newWidth + x) * 4;

                for( int c = 0; c < 4; c++ )
                {
                    double top = pixels[idx00 + c] * (1 - dx) +
                                pixels[idx01 + c] * dx;
                    double bottom = pixels[idx10 + c] * (1 - dx) +
                                   pixels[idx11 + c] * dx;
                    double value = top * (1 - dy) + bottom * dy;

                    new_pixels[dst_idx + c] = static_cast<unsigned short>(value);
                }
            }
        }
    }

    width = newWidth;
    height = newHeight;
    pixels = std::move(new_pixels);

    return this;
}




/*
    Get width
*/
int Bitmap::getWidth()
{
    return width;
}



/*
    Get height
*/
int Bitmap::getHeight()
{
    return height;
}



/*
    Set size (creates blank image)
*/
Bitmap* Bitmap::setSize
(
    int newWidth,
    int newHeight
)
{
    if( newWidth <= 0 || newHeight <= 0 )
    {
        setResult( "invalid_size", "Invalid dimensions" );
        return this;
    }

    width = newWidth;
    height = newHeight;
    pixels.assign(width * height * 4, 0xFFFF); // White, fully opaque

    return this;
}




/*
    Get pixel
*/
Bitmap* Bitmap::getRgba
(
    int x,
    int y,
    Rgba& rgba
)
{
    if( x >= 0 && x < width && y >= 0 && y < height && !pixels.empty() )
    {
        int idx = (y * width + x) * 4;
        rgba = Rgba(
            static_cast<double>(pixels[idx]) / 65535.0,
            static_cast<double>(pixels[idx + 1]) / 65535.0,
            static_cast<double>(pixels[idx + 2]) / 65535.0,
            static_cast<double>(pixels[idx + 3]) / 65535.0
        );
    }
    else
    {
        rgba = Rgba();
    }
    return this;
}




/*
    Draw rectangle
*/
Bitmap* Bitmap::rectangle
(
    int left,
    int top,
    int right,
    int bottom
)
{
    if( pixels.empty() ) return this;

    // Clamp coordinates
    left = std::max(0, std::min(left, width - 1));
    top = std::max(0, std::min(top, height - 1));
    right = std::max(0, std::min(right, width - 1));
    bottom = std::max(0, std::min(bottom, height - 1));

    // Draw white rectangle outline
    for( int x = left; x <= right; x++ )
    {
        // Top edge
        if( top >= 0 && top < height )
        {
            int idx_top = (top * width + x) * 4;
            pixels[idx_top] = 0xFFFF;
            pixels[idx_top + 1] = 0xFFFF;
            pixels[idx_top + 2] = 0xFFFF;
        }
        
        // Bottom edge
        if( bottom >= 0 && bottom < height )
        {
            int idx_bottom = (bottom * width + x) * 4;
            pixels[idx_bottom] = 0xFFFF;
            pixels[idx_bottom + 1] = 0xFFFF;
            pixels[idx_bottom + 2] = 0xFFFF;
        }
    }
    
    for( int y = top; y <= bottom; y++ )
    {
        // Left edge
        if( left >= 0 && left < width )
        {
            int idx_left = (y * width + left) * 4;
            pixels[idx_left] = 0xFFFF;
            pixels[idx_left + 1] = 0xFFFF;
            pixels[idx_left + 2] = 0xFFFF;
        }

        // Right edge
        if( right >= 0 && right < width )
        {
            int idx_right = (y * width + right) * 4;
            pixels[idx_right] = 0xFFFF;
            pixels[idx_right + 1] = 0xFFFF;
            pixels[idx_right + 2] = 0xFFFF;
        }
    }

    return this;
}




/*
    Draw text (not implemented)
*/
Bitmap* Bitmap::text
(
    std::string text,
    std::string font,
    int size,
    int x,
    int y
)
{
    setResult( "not_implemented", "Text rendering not implemented without freetype" );
    return this;
}




/*
    Clear bitmap (fill with black)
*/
Bitmap* Bitmap::erase()
{
    if( !pixels.empty() )
    {
        std::fill(pixels.begin(), pixels.end(), 0);
    }
    return this;
}




/*
    Return image buffer (for neural network)
*/
unsigned short* Bitmap::buildRGBA()
{
    if( pixels.empty() )
    {
        return nullptr;
    }
    return pixels.data();
}




/*
    Clear RGBA buffer (compatibility method)
*/
Bitmap* Bitmap::clearRGBA
(
    unsigned short* ptr
)
{
    // Nothing to do - vector manages its own memory
    // Kept for compatibility
    (void)ptr;
    return this;
}




/*
    Get pixel vector reference
*/
const std::vector<unsigned short>& Bitmap::getPixels() const
{
    return pixels;
}



Bitmap* Bitmap::updateSize()
{
    // Not needed anymore - size tracked in width/height
    return this;
}


//
//
///*
//    Bitmap
//*/
//
//#include <iostream>
//#include "bitmap.h"
//#include "../core/utils.h"
//
//
///* Global flag for image magic initialization in Bitmap constructor */
//static bool imageMagicInit = false;
//
//
//
///*
//    Constructor
//*/
//Bitmap::Bitmap()
//{
//    if( !imageMagicInit )
//    {
//        Magick::InitializeMagick( nullptr );
//        imageMagicInit = true;
//    }
//
//    image = new Magick::Image();
//}
//
//
//
///*
//    Destructor
//*/
//Bitmap::~Bitmap()
//{
//    delete image;
//}
//
//
//
///*
//    Creator
//*/
//Bitmap* Bitmap::create()
//{
//    return new Bitmap();
//}
//
//
//
///*
//    Destroy the bitmap
//*/
//void Bitmap::destroy()
//{
//    delete( this );
//}
//
//
//
///*
//    Load bitmap from file
//*/
//Bitmap* Bitmap::load
//(
//    string a /* File name */
//)
//{
//    if( fileExists( a ) )
//    {
//        try
//        {
//            image -> read( a );
//            updateSize();
//        }
//        catch( Magick::Exception &e )
//        {
//            setResult
//            (
//                "file_read_error",
//                "File read error " + (string) e.what()
//            );
//        }
//    }
//    else
//    {
//        setResult( "file_not_exists", "File not exists" + a );
//    }
//    return this;
//}
//
//
//
//
///*
//    Load bitmap from file
//*/
//Bitmap* Bitmap::save
//(
//    string a /* File name */
//)
//{
//    try
//    {
//        image -> write( a );
//    }
//    catch( Magick::Exception &e )
//    {
//        setResult
//        (
//            "file_write_error",
//            "File write error " + ( string ) e.what()
//        );
//    }
//    return this;
//}
//
//
//
//
///*
//    Resize image
//*/
//Bitmap* Bitmap::scale
//(
//    int aWidth,
//    int aHeight
//)
//{
//    image -> sample( Magick::Geometry( aWidth, aHeight ));
//    updateSize();
//    return this;
//}
//
//
//
//
///*
//    Resize bitmap
//*/
//Bitmap* Bitmap::zoom
//(
//    double  aZoom,      /* Zoom */
//    bool    aKeepSize   /* Keep size */
//)
//{
//    auto oldWidth = width;
//    auto oldHeight = height;
//
//    if( aZoom < 0.0 ) aZoom = 0;
//
//    scale( width * aZoom, height * aZoom );
//    if( aKeepSize )
//    {
//        if( aZoom >= 1.0 )
//        {
//            crop
//            (
//                ( width - oldWidth ) / 2,
//                ( height - oldHeight ) / 2,
//                oldWidth,
//                oldHeight
//            );
//        }
//        else
//        {
//            auto newImage = new Magick::Image
//            (
//                Magick::Geometry( oldWidth, oldHeight ),
//                Magick::Color( "white" )
//            );
//
//            int x = ( oldWidth - width ) / 2;
//            int y = ( oldHeight - height ) / 2;
//
//            newImage -> composite( *image, x, y, Magick::OverCompositeOp );
//
//            delete image;
//            image = newImage;
//            updateSize();
//        }
//    }
//    else
//    {
//        updateSize();
//    }
//    return this;
//}
//
//
//
///*
//    Resize bitmap
//*/
//Bitmap* Bitmap::shift
//(
//    double aX,
//    double aY
//)
//{
//    auto newImage = new Magick::Image
//    (
//        Magick::Geometry( width, height ),
//        Magick::Color( "white" )
//    );
//
//    newImage -> composite
//    (
//        *image,
//        width * aX,
//        height * aY,
//        Magick::OverCompositeOp
//    );
//
//    delete image;
//    image = newImage;
//
//    return this;
//}
//
//
//
//
///*
//    Crop bitmap
//*/
//Bitmap* Bitmap::crop
//(
//    int aLeft,      /* left */
//    int aTop,       /* top */
//    int aWidth,     /* width */
//    int aHeight    /* height */
//)
//{
//    image -> crop( Magick::Geometry( aWidth, aHeight, aLeft, aTop ));
//    updateSize();
//    return this;
//}
//
//
//
//
///*
//    Rotate bitmap
//*/
//Bitmap* Bitmap::rotate
//(
//    double aCircle, /* Part of circle */
//    bool    aCrop
//)
//{
//    image -> rotate( aCircle * 360.0 );
//    if( aCrop )
//    {
//        crop
//        (
//            ( image -> columns() - width ) / 2,
//            ( image -> rows() - height ) / 2,
//            width,
//            height
//        );
//    }
//    else
//    {
//        updateSize();
//    }
//    return this;
//}
//
//
//
///*
//    Resize bitmap
//*/
//Bitmap* Bitmap::setSize
//(
//    int aWidth,
//    int aHeight
//)
//{
//    image -> size( to_string( aWidth ) + "x" + to_string( aHeight ));
//    updateSize();
//    return this;
//}
//
//
//
///*
//    Get width of bitmap
//*/
//int Bitmap::getWidth()
//{
//    return width;
//}
//
//
//
///*
//    Get height of bitmap
//*/
//int Bitmap::getHeight()
//{
//    return height;
//}
//
//
//
///*
//    Get pixel
//*/
//Bitmap* Bitmap::getRgba
//(
//    int x,
//    int y,
//    Rgba& a
//)
//{
//    if( x >= 0 && x < width && y >= 0 && y < height )
//    {
//        auto p = image -> getPixels( x, y, 1, 1 );
//        a = Rgba
//        (
//            (double) p -> red / (double) 0xFFFF,
//            (double) p -> green / (double) 0xFFFF,
//            (double) p -> blue / (double) 0xFFFF,
//            1.0
//        );
//    }
//    else
//    {
//        a = Rgba();
//    }
//    return this;
//}
//
//
//
//Bitmap* Bitmap::updateSize()
//{
//    width = image -> columns();
//    height = image -> rows();
//    return this;
//}
//
//
//
//Bitmap* Bitmap::rectangle
//(
//    int l,
//    int t,
//    int r,
//    int b
//)
//{
//    image -> strokeColor( Magick::Color( "white" ) );
//    image -> fillColor( Magick::Color( "none" ) );
//    image -> draw( Magick::DrawableRectangle( l, t, r, b ));
//    return this;
//}
//
//
///*
//    Draw text on bitamp
//*/
//Bitmap* Bitmap::text
//(
//    string aText,
//    string aFont,
//    int size,
//    int x,
//    int y
//)
//{
//    image -> fontPointsize( size );
//    image -> font( aFont );
//    image -> fillColor( Magick::Color( "white" ) );
//    image -> draw( Magick::DrawableText( x, y,  aText ));
//    return this;
//}
//
//
//
///*
//    Return image buffer
//*/
//unsigned short* Bitmap::buildRGBA()
//{
//    int w = getWidth();
//    int h = getHeight();
//    unsigned short* ptr = new unsigned short[ 4 * w * h ];
//    image -> write( 0, 0, w, h, "RGBA", Magick::ShortPixel, ptr );
//    return ptr;
//}
//
//
//
//Bitmap* Bitmap::clearRGBA
//(
//    unsigned short* a
//)
//{
//    if( a != NULL )
//    {
//        delete [] a;
//    }
//    return this;
//}
//
//
//
//Bitmap* Bitmap::erase()
//{
//    if( image != NULL )
//    {
//        image -> backgroundColor( Magick::Color( "black" ) );
//        image -> erase();
//    }
//    return this;
//}
