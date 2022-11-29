

#ifndef BITMAP_H__
#define BITMAP_H__


#include <GL/glut.h>

#define GL_RGBA 				0x1908
#define GL_UNSIGNED_BYTE		0x1401

class Bitmap {
public:
    unsigned char *pixels;
    int x, y;

    Bitmap( int width, int height) {
        pixels = new unsigned char[width * height * 4];
        x = width;
        y = height;
    }

    ~Bitmap() {
        delete [] pixels;
    }

    unsigned char* get_ptr( void ) const   { return pixels; }

    void render( void ) {
        glClearColor( 0.0, 0.0, 0.0, 1.0 );
        glClear( GL_COLOR_BUFFER_BIT );
        glDrawPixels( x, y, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        glFlush();
    }

};

#endif
