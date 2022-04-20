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
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

# define ESC 27

float transZ = -5.0f;
float transX = 0.0f;
float transY = 0.0f;
float angleX = 0.0f;
float angleY = 0.0f;
float angle = 0.0;
int screenW = 0.0;
int screenH = 0.0;

int width, height, nrChannels;

GLfloat positionalLightPosition[]= {0.0f, 3.0f, 0.0f, 1.0f};			// Light Position
GLfloat spotlightPosition[]= {0.0f, 0.0f, -5.0f, 1.0f};		// Light Position

void InitGL (void) {  // Inicializamos parametros
	glShadeModel(GL_SMOOTH);							// Habilitamos Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo
	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing

	//Configuracion luz
	glLightfv(GL_LIGHT0, GL_POSITION, positionalLightPosition);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotlightPosition);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// unsigned int texture = 0;
	// glBindTexture(GL_TEXTURE_2D, texture);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void display (void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limiamos pantalla y Depth Buffer
	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	figura3D barrel = figura3D(coord_barrel, quads_barrel, trng_barrel, poly_barrel, normals_barrel, text_barrel);
	figura3D box = figura3D(coord_box, quads_box, trng_box, poly_box, normals_box, text_box);
	figura3D wheels = figura3D(coord_wheels, quads_wheels, trng_wheels, poly_wheels, normals_wheels, text_wheels);

	//glEnable(GL_TEXTURE_2D);
	// int i = 0;
	// unsigned char* minecraftBlock = stbi_load("yellow.jpeg", &width, &height, &nrChannels, 0);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, minecraftBlock);
	// stbi_image_free(minecraftBlock);

	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0);
		//Poner Código Aquí.
		//glScalef(0.05, 0.05, 0.05);
		box.solid();
		wheels.solid();
		glTranslatef(0.5, 0.0, 0.0);
		glRotatef(30, 0.0, 0.0, 1.0);
		barrel.solid();
		
  	//glDisable(GL_TEXTURE_2D);				
	glutSwapBuffers();
  // Swap The Buffers
}

void reshape(int width, int height ) {  // Creamos funcion Reshape
  if (height==0) {										// Prevenir division entre cero
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 50.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	//glLoadIdentity();									
}

void keyboard(unsigned char key, int x, int y) {// Create Keyboard Function
	switch(key) {
		case 'w':
		case 'W':
			transZ +=0.2f;
			break;
		case 's':
		case 'S':
			transZ -=0.2f;
			break;
		case 'a':
		case 'A':
			transX +=0.2f;
			break;
		case 'd':
		case 'D':
			transX -=0.2f;
			break;
		case ESC:
			exit(0);
			break;        
		default:
			break;
  }
	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y) {// Funcion para manejo de teclas especiales (arrow keys)
  switch (a_keys) {
	case GLUT_KEY_PAGE_UP:
		transY += 1.0;
		break;
	case GLUT_KEY_PAGE_DOWN:
		transY -= 1.0;
		break;
    case GLUT_KEY_UP:
		angle +=2.0f;
		break;
    case GLUT_KEY_DOWN:
		angle -=2.0f;
		break;
	case GLUT_KEY_LEFT:
		angleY +=2.0f;
		break;
	case GLUT_KEY_RIGHT:
		angleY -=2.0f;
		break;
    default:
    	break;
  }
  glutPostRedisplay();
}


int main(int argc, char** argv) { // Main Function
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  screenW = glutGet(GLUT_SCREEN_WIDTH);
  screenH = glutGet(GLUT_SCREEN_HEIGHT);
  glutInitWindowSize  (screenH, screenH);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Practica 5 20191"); // Nombre de la Ventana
  printf("Resolution H: %i \n", screenW);
  printf("Resolution V: %i \n", screenH);
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutMainLoop        ( );          // 

  return 0;
}
