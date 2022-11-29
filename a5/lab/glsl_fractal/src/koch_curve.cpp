///* Landscape */
//
//#include "glsl/Angel.h"
//#include <math.h>
//#include <time.h>
//
//using namespace std;
//
//const int NumTimesToSubdivide = 3;
//const int NumShapes = 4*4*4;  //
//const int NumVertices  = 9 * NumShapes;
//vec2 points[NumVertices];
//int Index = 0;
//
//const GLfloat f = sin(3.1415926/3)/3 ;
//
//void axiom( const vec2& a, const vec2& b)
//{
//    points[Index++] = a;
//    points[Index++] = b;
//}
//
//void generator( const vec2& a, const vec2& b, int count )
//{
//    if ( count > 0 ) {
//        vec2 v0 = ( a + b ) / 2.0;
//        vec2 vab = b - a;
//        vec2 v1 = a + vab / 3.0;
//        vec2 v2 =  a + vab * 2.0 / 3.0;
//        vec2 v3(v0.x -vab.y*f,  v0.y + vab.x*f);
//
//        generator( a, v1, count - 1 );
//        generator( v1, v3, count - 1 );
//        generator( v3, v2, count - 1 );
//        generator( v2, b, count - 1 );
//
//    }
//    else {
//        axiom( a, b );
//    }
//}
//
//
//void init() {
//    vec2 vertices[3] = {
//        vec2( 0, 1.38-0.5 ), vec2( 0.8, -0.5 ), vec2( -0.8, -0.5 )
//    };
//
//    generator( vertices[0], vertices[1], NumTimesToSubdivide );
//    generator( vertices[1], vertices[2], NumTimesToSubdivide );
//    generator( vertices[2], vertices[0], NumTimesToSubdivide );
//
//
////    vec2 vertices[3] = {
////        vec2( 0, -1 ), vec2( 0.0, 1 )
////    };
////
////    generator( vertices[0], vertices[1], NumTimesToSubdivide );
//
//
//
//    // Create and initialize a buffer object
//    GLuint buffer;
//    glGenBuffers( 1, &buffer );
//    glBindBuffer( GL_ARRAY_BUFFER, buffer );
//    glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );
//
//    // Load shaders and use the resulting shader program
//    GLuint program = InitShader( "vshader_iter.glsl", "fshader_iter.glsl" );
//    glUseProgram( program );
//
//    // Initialize the vertex position attribute from the vertex shader
//    GLuint loc = glGetAttribLocation( program, "vPosition" );
//    glEnableVertexAttribArray( loc );
//    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
//
//    glClearColor( 1.0, 1.0, 1.0, 1.0 );
//}
//
//void display( void )
//{
//    glClear( GL_COLOR_BUFFER_BIT );
//    glDrawArrays( GL_LINES, 0, NumVertices );
//    glFlush();
//}
//
//void keyboard( unsigned char key, int x, int y )
//{
//    switch ( key ) {
//    case 033:
//        exit( EXIT_SUCCESS );
//        break;
//    }
//}
//
//int main( int argc, char **argv )
//{
//    glutInit( &argc, argv );
//    glutInitDisplayMode( GLUT_RGBA );
//    glutInitWindowSize( 512, 512 );
//    glutCreateWindow( "Koch curve" );
//    glewInit();
//    init();
//    glutDisplayFunc( display );
//    glutKeyboardFunc( keyboard );
//    glutMainLoop();
//    return 0;
//}
