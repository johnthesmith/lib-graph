#pragma once

/*
    Queue of double values
*/

class Queue1d
{
    private:
        /* Queue */
        map <double> queue;
        /* Maximum size of queue */
        unsigned int maxSize = 0;
    public:

        /*
            Push new value in to queue
        */
        Queue1d* push
        (
            int /* Value */
        );

        /*
            Setters and getters
        */

        /*
            Set maximum size of queue
        */
        Queue1d* setMaxSize( int );


        /**/
        int getMaxSize()
}
