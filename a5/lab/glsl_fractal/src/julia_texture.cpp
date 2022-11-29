//// Display a Julia set
//// Uncomment the following line to use user-specified input values
//#include "glsl/Angel.h"
//
//using namespace std;
//
//typedef Angel::vec4 point4;
//typedef Angel::vec4 color4;
//
//// Use the C++ standard complex-number class.  It's a C++ template, so
////   we create a typedef of simplify our code.
//#include <complex>
//typedef std::complex<float>  Complex;
//
//inline float Random() { return float(rand())/RAND_MAX; }
//
//GLuint Projection;
//
//#define DIM 512
//
//
//int n = DIM;
//int m = DIM;
//
//GLfloat image[DIM][DIM][3];
//
////----------------------------------------------------------------------------
//
//void init( )
//{
//
//    const float scale = 1.5;
//
//    for ( int i = 0; i < DIM; i++ ) {
//        for ( int j = 0; j < DIM; j++ ) {
//
//            float x = scale * (float)(DIM/2 - i)/(DIM/2);
//            float y = scale * (float)(DIM/2 - j)/(DIM/2);
//
//			Complex c( -0.8, 0.156);
//			Complex p( x, y );
//
//			float  a = 1;
//
//		    for (int k=0; k<200; k++) {
//		        p = p * p + c;
//		        if ( abs(p)    > 1000) {
//		            a = 0;
//		            break;
//		        }
//		    }
//            image[j][i][0] = a;
//            image[j][i][1] = 0;
//            image[j][i][2] = 0;
//        }
//    }
//
//    glActiveTexture( GL_TEXTURE0 );
//    GLuint  texture;
//    glGenTextures( 1, &texture );
//    glBindTexture( GL_TEXTURE_2D, texture );
//    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, n, m, 0, GL_RGB, GL_FLOAT, image );
//
//    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
//    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
//    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
//    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
//
//    // Create and initialize a buffer object
//    GLuint buffer;
//    glGenBuffers( 1, &buffer );
//    glBindBuffer( GL_ARRAY_BUFFER, buffer );
//
//    point4 points[6] = {
//		point4( 0.0, 0.0, 0.0, 1.0 ),
//		point4( 0.0, 1.0, 0.0, 1.0 ),
//		point4( 1.0, 1.0, 0.0, 1.0 ),
//		point4( 1.0, 1.0, 0.0, 1.0 ),
//		point4( 1.0, 0.0, 0.0, 1.0 ),
//		point4( 0.0, 0.0, 0.0, 1.0 )
//    };
//
//    glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );
//
//    // Load shaders and use the resulting shader program
//    GLuint program = InitShader( "vshader_mandelbrot.glsl", "fshader_mandelbrot.glsl" );
//    glUseProgram( program );
//
//    // set up vertex arrays
//    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
//    glEnableVertexAttribArray( vPosition );
//    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
//
//    // Since our texture coordinates match our vertex positions, we
//    //   can reuse the position data for our texture coordinates.
//    GLuint vTexCoord = glGetAttribLocation( program, "vTexCoord" );
//    glEnableVertexAttribArray( vTexCoord );
//    glVertexAttribPointer( vTexCoord, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
//
//    Projection = glGetUniformLocation( program, "Projection" );
//
//    // Set our texture samples to the active texture unit
//    glUniform1i( glGetUniformLocation(program, "texture"), 0 );
//    glClearColor( 1.0, 1.0, 1.0, 1.0 );
//}
//
////----------------------------------------------------------------------------
//
//void reshape( int width, int height )
//{
//    glViewport(0, 0, width, height );
//    mat4 projection = Ortho( 0.0, 1.0, 0.0, 1.0, -1.0, 1.0 );
//    glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );
//}
//
////----------------------------------------------------------------------------
//
//void keyboard( unsigned char key, int x, int y )
//{
//    switch( key ) {
//	case 033: // Escape Key
//	case 'q': case 'Q':
//	    exit( EXIT_SUCCESS );
//	    break;
//    }
//}
//
////----------------------------------------------------------------------------
//
//void display()
//{
//    glClear( GL_COLOR_BUFFER_BIT );
//    glColor3f(1, 0, 0);
//    glDrawArrays( GL_TRIANGLES, 0, 6 );
//    glutSwapBuffers();
//}
//
////----------------------------------------------------------------------------
//
//int main( int argc, char *argv[] )
//{
//    glutInit( &argc, argv );
//    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
//    glutInitWindowSize(DIM, DIM );
//    glutCreateWindow( "Julia set" );
//    glewInit();
//    init();
//    glutDisplayFunc( display );
//    glutReshapeFunc( reshape );
//    glutKeyboardFunc( keyboard );
//    glutMainLoop();
//    return 0;
//}
