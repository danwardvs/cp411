# g++ -o SimpleView3.exe "src\\Camera.o" "src\\Cube.o" "src\\House.o" "src\\Light.o" "src\\Matrix.o" "src\\Menu.o" "src\\Point.o" "src\\Pyramid.o" "src\\Shape.o" "src\\SimpleView.o" "src\\Vector.o" "src\\World.o" "src\\curve\\Bezier.o" "src\\curve\\Curve.o" "src\\glsl\\InitShader.o" "src\\pixmap\\RGBpixmap.o" "src\\solar\\Solar.o" "src\\solar\\Sphere.o" "src\\surface\\RBM.o" "src\\surface\\Surface.o" -lfreeglut -lwinmm -lgdi32 -lglew32 -lglu32 -lopengl32 - 

g++ -o app.exe Camera.cpp Cube.cpp Ball.cpp Light.cpp Matrix.cpp Menu.cpp Point.cpp Shape.cpp SimpleView.cpp Vector.cpp World.cpp Paddle.cpp -lfreeglut -lwinmm -lgdi32 -lglew32 -lglu32 -lopengl32

PAUSE