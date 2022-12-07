/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-03
 */
#include "Menu.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "level/Generation.hpp"

extern GLint csType;
extern Shape* selectObj;
extern GLint xbegin;
extern World myWorld;
extern Generation myGeneration;
extern Camera myCamera;
extern CullMode cullMode;
extern RenderMode renderMode;
extern int paused;


void menu() {
	GLint Cull_Menu = glutCreateMenu(cullMenu);
	glutAddMenuEntry("No culling", 1);
	glutAddMenuEntry("OpenGL back-face & depth buffer", 3);

	GLint Shading_Menu = glutCreateMenu(shadeMenu);
	glutAddMenuEntry("No shading", 1);
	glutAddMenuEntry("My constant shading", 2);
	glutAddMenuEntry("OpenGL flat shading", 3);
	glutAddMenuEntry("OpenGL smooth shading", 4);
	glutAddMenuEntry("Texture", 5);

	GLint Level_Menu = glutCreateMenu(levelMenu);
	glutAddMenuEntry("Level 1", 1);
	glutAddMenuEntry("Level 2", 2);
	glutAddMenuEntry("Level 3", 3);
	glutAddMenuEntry("Level 4", 4);
	glutAddMenuEntry("Level 5", 5);

	glutCreateMenu(mainMenu);
	glutAddMenuEntry("Reset", 1);
	glutAddMenuEntry("Pause/Unpause", 3);
	glutAddSubMenu("Level Select", Level_Menu);
	glutAddSubMenu("Culling", Cull_Menu);
	glutAddSubMenu("Shading", Shading_Menu);
	glutAddMenuEntry("Quit", 2);
}

void mainMenu(GLint option) {
	switch (option){
		case 1: //reset
			//reset the world
			myWorld.reset();
			
			//generate selected level
			myGeneration.blockGenerator(myGeneration.currentLevel, myGeneration.currentDifficulty, false);
			break;
		case 2: //quit
			exit(0);
			break;
		case 3: //pause
			if(paused)
				paused=0;
			else
		 		paused=1;
			break;
	}
	glutPostRedisplay();
}

void cullMenu(GLint option) {
	switch (option){
	  case 1:
		cullMode = NONE;
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		break;
	  case 3:
		cullMode = GLCULL;
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		break;
	}
	glutPostRedisplay();
}

void shadeMenu(GLint option) {
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable( GL_NORMALIZE);
	glDisable(GL_COLOR_MATERIAL);
	
	switch (option) {
		case 1:
			renderMode = WIRE;
			break;
		case 2:
			renderMode = CONSTANT;
			break;
		case 3:
			renderMode = FLAT;
			break;
		case 4:
			renderMode = SMOOTH;
			break;
		case 5:
			renderMode = TEXTURE;
			break;
	}
	glutPostRedisplay();
}

void levelMenu(GLint option) {
	//reset the world
	myWorld.reset();
	
	//generate selected level
	myGeneration.blockGenerator(option, option, true);
	glutPostRedisplay();
}
