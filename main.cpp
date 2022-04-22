//*************************************************//
//*************************************************//
//******************** Alumno: ********************//
//************** NOÉ MARTÍNEZ NAREDO **************//
//*************************************************//
//*************************************************//
#include "Main.h"
#include "figura3D.cpp"
#include "barrel.cpp"
#include "box.cpp"
#include "wheels.cpp"
#include "ball.cpp"
#include <math.h>

#define ESC 27
#define FOCUS 1
#define OFFSET 2.5
#define INITIAL_CANNON_BALL_X_POSITION 0.5
#define MAX_CANNON_BALL_X_POSITION 12.6
#define PARABOLA_FACTOR 27

float scenarioZ_Translation = -10.0f,
	  scenarioX_Translation = -6.0f,
	  scenarioY_Translation = -5.0f;
float scenarioX_Rotation = 0.0f;
float scenarioY_Rotation = 0.0f;
float scenarioZ_Rotation = 0.0f;
float cannonRotation = 0.0f;
int screenW = 0.0;
int screenH = 0.0;

float cannonBallPositionX = INITIAL_CANNON_BALL_X_POSITION,
	cannonBallPositionY = -((pow(cannonBallPositionX - 5, 2))/PARABOLA_FACTOR * FOCUS) + OFFSET,
	cannonBallPositionZ = 0.0;
int startAnimation = 0;

GLfloat positionalLightPosition[]= {0.0f, 3.0f, 0.0f, 1.0f};
GLfloat spotlightPosition[]= {0.0f, 0.0f, -5.0f, 1.0f};

void makeGrass();

void InitGL (void) {
	glShadeModel(GL_SMOOTH);
	glClearColor(135.0/255.0f, 206.0/255.0f, 235.0/255.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);

	//Configuracion luz
	glLightfv(GL_LIGHT0, GL_POSITION, positionalLightPosition);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotlightPosition);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	glDepthFunc(GL_LEQUAL);
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	unsigned int texture = 0;
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void display (void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	figura3D barrel = figura3D(geo_barrel, faces_barrel);
	figura3D box = figura3D(geo_box, faces_box);
	figura3D wheels = figura3D(geo_wheels, faces_wheels);
	figura3D ball = figura3D(geo_ball, faces_ball);

	glRotatef(scenarioY_Rotation, 0.0, 1.0, 0.0);
	glRotatef(scenarioX_Rotation, 1.0, 0.0, 0.0);
	glRotatef(scenarioZ_Rotation, 0.0, 0.0, 1.0);
	glTranslatef(scenarioX_Translation, scenarioY_Translation, scenarioZ_Translation);
	
		makeGrass();
		glRotatef(cannonRotation, 0.0, 1.0, 0.0);
		box.texturized("wood.jpeg");
		wheels.texturized("metal.jpeg");
		glTranslatef(0.5, 0.0, 0.0);
		glPushMatrix();
			glRotatef(30, 0.0, 0.0, 1.0);
			barrel.texturized("metal.jpeg");
		glPopMatrix();
		glTranslatef(cannonBallPositionX, cannonBallPositionY, cannonBallPositionZ);
		glPushMatrix();
			glScalef(0.004, 0.004, 0.004);
			ball.texturized("metal.jpeg");
		glPopMatrix();		
	glutSwapBuffers();
  // Swap The Buffers
}

void makeGrass() {
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	unsigned char* grassData = stbi_load("grass.jpeg", &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, grassData);
	stbi_image_free(grassData);
	glPushMatrix();
		for (int i = (-60); i <= 60; i++) {
			glPushMatrix();
				glTranslatef(i, 0.0, 0.0);
				glPushMatrix();
					glTranslatef(0.0, 0.0, 15);
					for (int k = 15; k >= (-100); k--) {
						glTranslatef(0.0, 0.0, -1.0);
						glBegin(GL_QUADS);
							glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.0, 0.5);
							glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, 0.0, 0.5);
							glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, 0.0, -0.5);
							glTexCoord2f(0.0, 1.0); glVertex3f(0.5, 0.0, -0.5);
						glEnd();
					}
				glPopMatrix();
			glPopMatrix();
		}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

void cannonBallParabola() {
	if (startAnimation && cannonBallPositionX < MAX_CANNON_BALL_X_POSITION) {
		cannonBallPositionX += 0.2;
		cannonBallPositionY = -((pow(cannonBallPositionX - 5, 2))/PARABOLA_FACTOR * FOCUS) + OFFSET;
	}

	glutPostRedisplay();
}

void reshape(int width, int height ) {
  if (height==0) {
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 50.0);
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();									
}

void keyboard(unsigned char key, int x, int y) {
	switch(key) {
		case 'w':
		case 'W':
			scenarioZ_Translation +=0.2f;
			break;
		case 's':
		case 'S':
			scenarioZ_Translation -=0.2f;
			break;
		case 'a':
		case 'A':
			scenarioX_Translation +=0.2f;
			break;
		case 'd':
		case 'D':
			scenarioX_Translation -=0.2f;
			break;
		case '2':
			startAnimation = 1;
			cannonBallPositionX = INITIAL_CANNON_BALL_X_POSITION;
			break;

		case '1':
			cannonRotation += 5;
			break;
		case '3':
			cannonRotation -= 5;
			break;
		case ESC:
			exit(0);
			break;        
		default:
			break;
  }
	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y) {
  switch (a_keys) {
	case GLUT_KEY_PAGE_UP:
		scenarioY_Translation -= 0.5;
		break;
	case GLUT_KEY_PAGE_DOWN:
		scenarioY_Translation += 0.5;
		break;
    case GLUT_KEY_UP:
		scenarioZ_Rotation +=2.0f;
		break;
    case GLUT_KEY_DOWN:
		scenarioZ_Rotation -=2.0f;
		break;
	case GLUT_KEY_LEFT:
		scenarioY_Rotation +=2.0f;
		break;
	case GLUT_KEY_RIGHT:
		scenarioY_Rotation -=2.0f;
		break;
    default:
    	break;
  }
  glutPostRedisplay();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  screenW = glutGet(GLUT_SCREEN_WIDTH);
  screenH = glutGet(GLUT_SCREEN_HEIGHT);
  glutInitWindowSize(screenH, screenH);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Proyecto Extraordinario");
  printf("Resolution H: %i \n", screenW);
  printf("Resolution V: %i \n", screenH);
  InitGL();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(arrow_keys);
  glutIdleFunc(cannonBallParabola);
  glutMainLoop();

  return 0;
}
