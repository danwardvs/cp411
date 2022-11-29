// /* sierpinski gasket with vertex arrays */

// #include "glsl/Angel.h"

// const int NumTimesToSubdivide = 5;
// const int NumTetrahedrons = 4 * 4 * 4 * 4 * 4;
// const int NumTriangles = 4 * NumTetrahedrons;
// const int NumVertices = 3 * NumTriangles;

// vec3 points[NumVertices];
// vec3 colors[NumVertices];
// int Index = 0;

// GLfloat xeye = 1.0, yeye = 2.0, zeye = 3.0;  //  Viewing-coordinate origin.
// GLfloat xref = 0.0, yref = 0.0, zref = 0.0;  //  Look-at point.
// GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0, theta; //  View up vector.
// GLfloat vangle = 40.0, dnear = 1.0,
//         dfar = 10.0; // Set positions for near and far clipping planes

// //----------------------------------------------------------------------------

// void triangle(const vec3 &a, const vec3 &b, const vec3 &c) {
//   points[Index++] = a;
//   points[Index++] = b;
//   points[Index++] = c;
// }

// //----------------------------------------------------------------------------

// void axiom(const vec3 &a, const vec3 &b, const vec3 &c, const vec3 &d) {
//   triangle(a, b, c);
//   triangle(a, c, d);
//   triangle(a, d, b);
//   triangle(b, d, c);
// }

// //----------------------------------------------------------------------------

// void generator(const vec3 &a, const vec3 &b, const vec3 &c, const vec3 &d,
//                int count) {
//   if (count > 0) {
//     vec3 v0 = (a + b) / 2.0;
//     vec3 v1 = (a + c) / 2.0;
//     vec3 v2 = (a + d) / 2.0;
//     vec3 v3 = (b + c) / 2.0;
//     vec3 v4 = (c + d) / 2.0;
//     vec3 v5 = (b + d) / 2.0;
//     generator(a, v0, v1, v2, count - 1);
//     generator(v0, b, v3, v5, count - 1);
//     generator(v1, v3, c, v4, count - 1);
//     generator(v2, v4, v5, d, count - 1);
//   } else {
//     axiom(a, b, c, d); // draw tetrahedron at end of recursion
//   }
// }

// //----------------------------------------------------------------------------

// void init() {
//   vec3 vertices[4] = {vec3(0.0, 0.0, -1.0), vec3(0.0, 0.942809, 0.333333),
//                       vec3(-0.816497, -0.471405, 0.333333),
//                       vec3(0.816497, -0.471405, 0.333333)};

//   // Subdivide the original tetrahedron
//   generator(vertices[0], vertices[1], vertices[2], vertices[3],
//             NumTimesToSubdivide);

//   GLuint buffer;
//   glGenBuffers(1, &buffer);
//   glBindBuffer(GL_ARRAY_BUFFER, buffer);

//   // First, we create an empty buffer of the size we need by passing
//   //   a NULL pointer for the data values
//   glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), points,
//                GL_STATIC_DRAW);

//   glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
//   glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);

//   // Load shaders and use the resulting shader program
//   GLuint program = InitShader("vshader_3d.glsl", "fshader_3d.glsl");
//   glUseProgram(program);

//   // Initialize the vertex position attribute from the vertex shader
//   GLuint vPosition = glGetAttribLocation(program, "vPosition");
//   glEnableVertexAttribArray(vPosition);
//   glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0,
//   BUFFER_OFFSET(0));

//   GLuint vColor = glGetAttribLocation(program, "vColor");
//   glEnableVertexAttribArray(vColor);
//   glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0,
//                         BUFFER_OFFSET(sizeof(points)));

//   glEnable(GL_DEPTH_TEST);
//   glClearColor(0.0, 0.0, 0.0, 1.0); /* white background */
// }

// //----------------------------------------------------------------------------

// void display() {
//   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//   glMatrixMode(GL_PROJECTION);
//   glLoadIdentity();
//   gluPerspective(vangle, 1.0, dnear, dfar);

//   GLfloat xtemp = xeye * cos(theta) - yeye * sin(theta);
//   GLfloat ytemp = xeye * sin(theta) + yeye * cos(theta);
//   xeye = xtemp;
//   yeye = ytemp;

//   glMatrixMode(GL_MODELVIEW);
//   glLoadIdentity();
//   gluLookAt(xeye, yeye, zeye, xref, yref, zref, Vx, Vy, Vz);

//   glDrawArrays(GL_TRIANGLES, 0, NumVertices);
//   glFlush();
// }

// //----------------------------------------------------------------------------

// void keyboard(unsigned char key, int x, int y) {
//   switch (key) {
//   case 033: // Escape Key
//   case 'q':
//   case 'Q':
//     exit(EXIT_SUCCESS);
//     break;
//   case 'r':
//     theta = 0.02;
//     break;
//   case 'l':
//     theta = -0.02;
//     break;
//   default:
//     break;
//   }
//   glutPostRedisplay();
// }

// //----------------------------------------------------------------------------

// int main(int argc, char **argv) {
//   glutInit(&argc, argv);
//   glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
//   glutInitWindowSize(512, 512);
//   glutCreateWindow("Sirerpinski Gasket 3D");
//   glewInit();
//   init();
//   glutDisplayFunc(display);
//   glutKeyboardFunc(keyboard);
//   glutMainLoop();
//   return 0;
// }
