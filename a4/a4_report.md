# A4 Report

Author: ???

Date: ???

Check [readme.txt](readme.txt) for course work statement and self-evaluation.

## Q1 Culling, Lighting, Shading (short_answer)

### Q1.1 Concepts of culling

What is the difference between culling and clipping?
clipping is handling polygons at the edge of the viewport and culling is handling faces that are out of view

What is the difference between object precision and image precision hidden surface removal algorithms? Give an example of each method.

Object precision is analyzing the object to determine what faces are visible, and what to draw
Image precision traces a line from each pixel to determine what is visible first, and draws that

### Q1.2 Culling computing

Given:

    eye position at E(3, 2, 2), and
    reference (look at) point at R(0, 0, 0).

    1. Compute to determine if triangle P1(1,0,0)P2(0,1,0)P3(0, 0, 1) is a back face.
    2. Compute the depth of the above triangle.

x0 1
y0 0
z0 0
x1 0
y1 1
z1 0
x2 0
y2 0
z2 1

1. N dot P(eye)\*P(ref) = [(y1-y0)(z2-z1) - (y2-y1)(z1-z0)](xref-xeye)+[(z1-z0)(x2-x1)-(z2-z1)(x1-x0)](yref-yeye)+[(x1-x0)(y2-y1)-(x2-x1)(y1-y0)](zref-zeye)
   [(1 - 0)(1-0) - (0-1)(0-0)](0-3) + [(0-0)(0-0)-(1-0)(0-1)](0-2) + [(0-1)(0-1)-(0-0)(1-0)](0-2)
   [1-0](-3) + [0+1](-2) + [1-0](-2)
   -3 + -2 -2
   -7

-7<0 so P is a front face

2.  dg = [(xref-xeye)(x-xeye)+(yref-yeye)(y-yeye)+(zref-zeye)(z-zeye)]/sqrt( (xref-xeye)^2 + (yref-yeye)^2 + (zref-zeye)^2)
    dg = [(0-3)(x-3) + (0-2)(y-2) + (0-2)(z-2)] / sqrt( (0-3)^2 + (0-2)^2 + (0-2)^2)
    dg = [-3(x-3) - 2(y-2) - 2(z-2)] / sqrt(17)

d1 = [-3(1-3) - 2(0-2) - 2(0-2)] / sqrt(17)
d1 = 14/sqrt(17)

d2 = [-3(0-3) - 2(1-2) - 2(0-2)] / sqrt(17)
d2 = 15/sqrt(17)

d3 = [-3(0-3) - 2(0-2) - 2(1-2)] / sqrt(17)
d3 = 15/sqrt(17)

d = (d1 + d2 + d3)/3
d = (44/sqrt(17))/3
d = 44/(3\*sqrt(17))

depth is 3.557

### Q1.3 Concepts of lighting and shading

What does a light source model determine? Give the names of three light source models.

Light source model determines the direction and behaviour of the "beams" of light. Point, directional, ambient

What does a reflection model determine? Give the names of three reflection models.

The reflection model determines how light bounces off object's surface, their reflectiveness. Diffuse, specular, ambient

What does a shading model determine? Give the names of three shading models.

The shading model determines how the colour of a pixel is calculated based on the reflection model. Constant, Gouraud, Phong

### Q1.4 Lighting computing

## Q2 OpenGL culling, lighting, shading (lab practice)

### Q2.1 Hidden surface removal

Complete? (Yes/No)

If Yes, insert a screen shot image to show the completion.

![image caption](images/demo.png){width=90%}

If No, Add a short description to describe the issues encountered.

### Q2.2 Lighting and Shading

Complete? (Yes/No)

If Yes, insert a screen shot image to show the completion.

![image caption](images/demo.png){width=90%}

If No, Add a short description to describe the issues encountered.

### Q2.3 Animation

Complete? (Yes/No)

If Yes, insert a screen shot image to show the completion.

![image caption](images/demo.png){width=90%}

If No, Add a short description to describe the issues encountered.

## Q3 SimpleView2 - culling, lighting, shading (programming)

### Q3.1 Culling

Complete? (Yes/No)

If Yes, insert a screen shot image to show the completion.

[image caption](images/demo.png){width=90%}

If No, add a short description to describe the issues encountered.

### Q3.2 Lighting

Complete? (Yes/No)

If Yes, insert a screen shot image to show the completion.

[image caption](images/demo.png){width=90%}

If No, add a short description to describe the issues encountered.

### Q3.3 Shading

Complete? (Yes/No)

If Yes, insert a screen shot image to show the completion.

[image caption](images/demo.png){width=90%}

If No, add a short description to describe the issues encountered.

### Q3.4 Animations

Complete? (Yes/No)

If Yes, insert a screen shot image to show the completion.

[image caption](images/demo.png){width=90%}

If No, add a short description to describe the issues encountered.

**References**

1. CP411 a4
2. Add your references if you used any.
