#include "Main.h"
#include "ball.cpp"
#include "canhao.cpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <math.h>

#include <vector>

#include "figura3D.cpp"
#define E 2.71828

using namespace std;


float pos_camX = 0, pos_camY = 0, pos_camZ = -5;

int eye_camX = 0, eye_camY = 0.0, eye_camZ = 0;

void InitGL(GLvoid);
void reshape(int width, int height);
void display(void);
void cannon(void);
void keyboard(unsigned char key, int x, int y);
void arrow_keys(int a_keys, int x, int y);

float t = -1.85,
	ballRotX = 0.0, ballRotY = 0.0,
	rotation = 0.0,
	posX = 0.0, posY = 0.0, posZ = 0.0,
	startAnimation = 0;
int width, height, nrChannels;

int main(int argc, char** argv) {
	glutInit(&argc, argv);                          // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);   // Display Mode (Clores RGB y alpha | Buffer Sencillo )
	glutInitWindowSize(1500, 1000);                 // Tama�o de la Ventana
	glutInitWindowPosition(0, 0);                   //Posicion de la Ventana
	glutCreateWindow("Proyecto Extraordinario");    // Nombre de la Ventana
	InitGL();                                       // Parametros iniciales de la aplicacion
	glutDisplayFunc(display);                       //Indicamos a Glut funcion de dibujo
	glutReshapeFunc(reshape);                       //Indicamos a Glut funcion en caso de cambio de tamano
	glutKeyboardFunc(keyboard);                     //Indicamos a Glut funcion de manejo de teclado
	glutSpecialFunc(arrow_keys);                    //Otras
	glutMainLoop();//}
	return 0;
}
void InitGL(GLvoid) {    // Inicializamos parametros
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);			// Negro de fondo
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
}
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limiamos pantalla y Depth Buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	// Reinicializamos la actual matriz Modelview

	glTranslatef(pos_camX, pos_camY, pos_camZ);
		glRotatef(eye_camX, 1.0, 0.0, 0.0);
		glRotatef(eye_camY, 0.0, 1.0, 0.0);
		glRotatef(eye_camZ, 0.0, 0.0, 1.0);


	// glTranslatef(0.0, -7.0, -20.0);
	// glTranslatef(posX, posY, posZ);
	// glRotatef(rotation, 0.0, 1.0, 0.0);
	cannon();
	glFlush();
}

void cannon() {
	glEnable(GL_TEXTURE_2D);
	int i = 0;
	unsigned char* ballData = stbi_load("texturas/ballTexture.jpg", &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, ballData);
	stbi_image_free(ballData);
	figura3D balon = figura3D(coord_ball, quads_ball, trng_ball);
	figura3D cannon = figura3D(coord_canhao, quads_canhao, trng_canhao);

	glPushMatrix();
		glTranslatef(0.000000 , -3.590332 , 0.347820);
		glPushMatrix();
			cannon.mesh();	
		glPopMatrix();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void reshape(int width, int height) { // Creamos funcion Reshape
	if (height == 0)									// Prevenir division entre cero
		height = 1;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();
	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 170.0); //Tipo de vista
	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}
void keyboard ( unsigned char key, int x, int y )  {// Create Keyboard Function

	switch ( key ) {
		case 's':   //Movimientos de camara
		case 'S':
			pos_camZ += 3.0f;
			//eye_camZ -= 0.5f;
			break;

		case 'w':
		case 'W':
			pos_camZ -= 3.0f;
			//eye_camZ += 0.5f;
			break;

		case 'd':
		case 'D':
			pos_camX += 0.5f;
			//eye_camX -= 0.5f;
			break;
		case 'a':
		case 'A':
			pos_camX -= 0.5f;
			//eye_camX += 0.5f;
			break;

		case 'l':
		case 'L':
		pos_camY -= 0.5f;
		//eye_camY -= 0.5f;
		break;

    	case 'o':
		case 'O':
		pos_camY += 0.5f;
		break;

		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }
	glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  {// Funcion para manejo de teclas especiales (arrow keys)

  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		pos_camY -= 0.5f;
		//eye_camY += 0.5f;
		break;

	case GLUT_KEY_PAGE_DOWN:
		pos_camY += 0.5f;
		//eye_camY -= 0.5f;
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		eye_camX = (eye_camX-15) % 360;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		eye_camX = (eye_camX+15) % 360;
		break;

	case GLUT_KEY_LEFT:
		eye_camY = (eye_camY-15) % 360;
		break;

	case GLUT_KEY_RIGHT:
		eye_camY = (eye_camY+15) % 360;
		break;
    default:
      break;
  }
  glutPostRedisplay();
}
