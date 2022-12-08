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

void levelMenu(GLint option) {
	//reset the world
	myWorld.reset();
	
	//generate selected level
	myGeneration.blockGenerator(option, option, true);
	glutPostRedisplay();
}
