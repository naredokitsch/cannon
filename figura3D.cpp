
#include <iostream>
#include "Main.h"
#include <vector>

using namespace std;

class figura3D {

	vector< vector<float> > coords;
	//float c[][3];  //Coordenadas de la nube de puntos del mueble
	// float* n;  //Vectores Normales
	// float* x;  //Vertices de Textura

	vector<vector<vector<int> > > quads;
	vector<vector<vector<int> > > trng;

	public:
		figura3D(vector<vector<float> > c) {
			coords = c;
		}

		figura3D(vector<vector<float> > c, vector<vector<vector<int> > > q, vector<vector<vector<int> > > t) {
			coords = c;
			quads = q;
			trng = t;
		}

		// figura3D(float* coordenadas, int* quadrilateral, int* triangles, float* normals) {
		// 	c = coordenadas;
		// 	q = quadrilateral;
		// 	t = triangles;
		// 	n = normals;
		// }

		// figura3D(float* coordenadas, int* quadrilateral, int* triangles, float* normals, float* v_textura) {
		// 	c = coordenadas;
		// 	q = quadrilateral;
		// 	t = triangles;
		// 	n = normals;
		// 	x = v_textura;
		// }

		void pointsCloud () {
			//c.push_back(vector<float> {0, 0, 0});
			glColor3f(1.0f,0.0f,0.0f);
			glPointSize(5);  
			glBegin(GL_POINTS);
				for (vector<float> vertice : coords){
					glVertex3f(vertice[0], vertice[1], vertice[2]);
				}
			glEnd();
		}

		void mesh () {
			glColor3f(0.0f,1.0f,0.0f);
			for (vector<vector<int> > face : quads) {
				glBegin(GL_LINE_LOOP);
					for (vector<int> point : face) {
						glVertex3f(coords[point[0] - 1][0], coords[point[0] - 1][1], coords[point[0] - 1][2]);
					}
				glEnd();
			}

			glColor3f(1.0f,0.0f,0.0f);
			for (vector<vector<int> > face : trng) {
				glBegin(GL_LINE_LOOP);
					for (vector<int> point : face) {
						glVertex3f(coords[point[0] - 1][0], coords[point[0] - 1][1], coords[point[0] - 1][2]);
					}
				glEnd();
			}
				// glVertex3f(coords[48][0], coords[48][1], coords[48][2]);
				// glVertex3f(coords[50][0], coords[50][1], coords[50][2]);
				// glVertex3f(coords[154][0], coords[154][1], coords[154][2]);
				// glVertex3f(coords[153][0], coords[153][1], coords[153][2]);
			
		// 	glColor3f(1,0,0);

		// 	if(t[0] > 0) {
		// 		for (i = 7 ; i <= t[0] ;  i+=9) {
		// 			glBegin(GL_LINE_LOOP);
		// 				glVertex3f(c[(t[i - 6] * 3) - 2] , c[(t[i - 6] * 3) - 1] , c[t[i - 6] * 3]);
		// 				glVertex3f(c[(t[i - 3] * 3) - 2] , c[(t[i - 3] * 3) - 1] , c[t[i - 3] * 3]);
		// 				glVertex3f(c[(t[i] * 3) - 2] , c[(t[i] * 3) - 1] , c[t[i] * 3]);
		// 			glEnd();
		// 		}
		// 	}
			
		// 	glColor3f(0,0,0);
		// }

		// void solid () {
		// 	int i = 0;
		// 	if(q[0] > 0) {
		// 		for (i = 10 ; i <= q[0] ;  i+=12) {
		// 			glBegin(GL_QUADS);
		// 				glNormal3f(n[(q[i - 7] * 3) - 2] , n[(q[i - 7] * 3) - 1] , n[q[i - 7] * 3]) ; glVertex3f(c[(q[i - 9] * 3) - 2] , c[(q[i - 9] * 3) - 1] , c[q[i - 9] * 3]);
		// 				glNormal3f(n[(q[i - 4] * 3) - 2] , n[(q[i - 4] * 3) - 1] , n[q[i - 4] * 3]) ; glVertex3f(c[(q[i - 6] * 3) - 2] , c[(q[i - 6] * 3) - 1] , c[q[i - 6] * 3]);
		// 				glNormal3f(n[(q[i - 1] * 3) - 2] , n[(q[i - 1] * 3) - 1] , n[q[i - 1] * 3]) ; glVertex3f(c[(q[i - 3] * 3) - 2] , c[(q[i - 3] * 3) - 1] , c[q[i - 3] * 3]);
		// 				glNormal3f(n[(q[i + 2] * 3) - 2] , n[(q[i + 2] * 3) - 1] , n[q[i + 2] * 3]) ; glVertex3f(c[(q[i] * 3) - 2] , c[(q[i] * 3) - 1] , c[q[i] * 3]);
		// 			glEnd();
		// 		}
		// 	}

		// 	if(t[0] > 0) {
		// 		for (i = 7 ; i <= t[0] ;  i+=9) {
		// 			glBegin(GL_TRIANGLES);
		// 				glNormal3f(n[(t[i - 4] * 3) - 2] , n[(t[i - 4] * 3) - 1] , n[t[i - 4] * 3]) ; glVertex3f(c[(t[i - 6] * 3) - 2] , c[(t[i - 6] * 3) - 1] , c[t[i - 6] * 3]);
		// 				glNormal3f(n[(t[i - 1] * 3) - 2] , n[(t[i - 1] * 3) - 1] , n[t[i - 1] * 3]) ; glVertex3f(c[(t[i - 3] * 3) - 2] , c[(t[i - 3] * 3) - 1] , c[t[i - 3] * 3]);
		// 				glNormal3f(n[(t[i + 2] * 3) - 2] , n[(t[i + 2] * 3) - 1] , n[t[i + 2] * 3]) ; glVertex3f(c[(t[i] * 3) - 2] , c[(t[i] * 3) - 1] , c[t[i] * 3]);
		// 			glEnd();
		// 		}
		// 	}
		// }


		// void texturized() {
		// 	int i = 0;
		// 	if(q[0] > 0) {
		// 			glBegin(GL_QUADS);
		// 			for (i = 1 ; i <= q[0] ;  i+=3) {
		// 				glTexCoord2f(x[(q[i + 1] * 2) - 1] , x[q[i + 1] * 2]) ; glNormal3f(n[(q[i + 2] * 3) - 2] , n[(q[i + 2] * 3) - 1] , n[q[i + 2] * 3]) ; glVertex3f(c[(q[i] * 3) - 2] , c[(q[i] * 3) - 1] , c[q[i] * 3]);
		// 			}
		// 			glEnd();
		// 	}

		// 	if(t[0] > 0) {
		// 			glBegin(GL_TRIANGLES);
		// 			for (i = 1 ; i <= t[0] ;  i+=3) {
		// 				glTexCoord2f(x[(t[i + 1] * 2) - 1] , x[t[i + 1] * 2]) ; glNormal3f(n[(t[i + 2] * 3) - 2] , n[(t[i + 2] * 3) - 1] , n[t[i + 2] * 3]) ; glVertex3f(c[(t[i] * 3) - 2] , c[(t[i] * 3) - 1] , c[t[i] * 3]);
		// 			}
		// 			glEnd();
				
		// 	}
		}

};