#pragma once

/* TODO next 2 lines must be removed */
#include <GL/gl.h>
#include <GL/glu.h>


#include <GLES3/gl31.h>
#include <GLFW/glfw3.h>
#include <GL/glext.h>


#include "../core/log.h"
#include "../core/result.h"

#include "bitmap.h"

class Texture: public Result
{
    private:
        Log*            log = NULL;
        unsigned int    openglId    = 0;
    public:


        /*
            Constructor
        */
        Texture
        (
            Log*
        );



        /*
            Destructor
        */
        ~Texture();



        /*
            Create and return texture
        */
        static Texture* create
        (
            Log*
        );



        /*
            Destroy texture
        */
        void destroy();



        /*
            Build from bitmap
        */
        Texture* buildFromBitmap
        (
            Bitmap*
        );


        /*
            Free texture
        */
        Texture* free();


        Texture* use();
};