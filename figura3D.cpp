#include <iostream>
#include <vector>
#define GEOM 0
#define TEXT 1
#define NORM 2

using namespace std;

class figura3D {

	vector< vector<float> > coords;
	vector< vector<float> > norms;
	vector< vector<float> > text;
	vector<vector<vector<int> > > quads;
	vector<vector<vector<int> > > trng;
	vector<vector<vector<int> > > poly;

	public:
		figura3D(vector<vector<float> > c,
				vector<vector<vector<int> > > q,
				vector<vector<vector<int> > > t,
				vector<vector<vector<int> > > p,
				vector<vector<float> > n,
				vector<vector<float> > x) {
			coords = c;
			quads = q;
			trng = t;
			poly = p;
			norms = n;
			text = x;
		}

		void pointsCloud() {
			glColor3f(1.0f,0.0f,0.0f);
			glPointSize(5);  
			glBegin(GL_POINTS);
				for (vector<float> vertice : coords){
					glVertex3f(vertice[0], vertice[1], vertice[2]);
				}
			glEnd();
		}

		void mesh() {
			glColor3f(0.0f,1.0f,1.0f);
			for (vector<vector<int> > face : quads) {
				glBegin(GL_LINE_LOOP);
					for (vector<int> vertex : face) {
						glVertex3f(coords[vertex[0] - 1][0], coords[vertex[0] - 1][1], coords[vertex[0] - 1][2]);
					}
				glEnd();
			}

			glColor3f(1.0f,0.0f,0.0f);
			for (vector<vector<int> > face : trng) {
				glBegin(GL_LINE_LOOP);
					for (vector<int> vertex : face) {
						glVertex3f(coords[vertex[0] - 1][0], coords[vertex[0] - 1][1], coords[vertex[0] - 1][2]);
					}
				glEnd();
			}

			glColor3f(1.0f,1.0f,0.0f);
			for (vector<vector<int> > face : poly) {
				glBegin(GL_LINE_LOOP);
					for (vector<int> vertex : face) {
						glNormal3f(norms[vertex[NORM] - 1][0], norms[vertex[NORM] - 1][1], norms[vertex[NORM] - 1][2]);
						glVertex3f(coords[vertex[GEOM] - 1][0], coords[vertex[GEOM] - 1][1], coords[vertex[GEOM] - 1][2]);
					}
				glEnd();
			}
		}

		void solid() {
			glColor3f(1.0f,1.0f,1.0f);
			for (vector<vector<int> > face : quads) {
				glBegin(GL_QUADS);
					for (vector<int> vertex : face) {
						glNormal3f(norms[vertex[NORM] - 1][0], norms[vertex[NORM] - 1][1], norms[vertex[NORM] - 1][2]);
						glVertex3f(coords[vertex[GEOM] - 1][0], coords[vertex[GEOM] - 1][1], coords[vertex[GEOM] - 1][2]);
					}
				glEnd();
			}

			glColor3f(1.0f,0.0f,0.0f);
			for (vector<vector<int> > face : trng) {
				glBegin(GL_TRIANGLES);
					for (vector<int> vertex : face) {
						glNormal3f(norms[vertex[NORM] - 1][0], norms[vertex[NORM] - 1][1], norms[vertex[NORM] - 1][2]);
						glVertex3f(coords[vertex[GEOM] - 1][0], coords[vertex[GEOM] - 1][1], coords[vertex[GEOM] - 1][2]);
					}
				glEnd();
			}

			glColor3f(1.0f,1.0f,0.0f);
			for (vector<vector<int> > face : poly) {
				glBegin(GL_POLYGON);
					for (vector<int> vertex : face) {
						glNormal3f(norms[vertex[NORM] - 1][0], norms[vertex[NORM] - 1][1], norms[vertex[NORM] - 1][2]);
						glVertex3f(coords[vertex[GEOM] - 1][0], coords[vertex[GEOM] - 1][1], coords[vertex[GEOM] - 1][2]);
					}
				glEnd();
			}
		}

		void texturized() {
			for (vector<vector<int> > face : quads) {
				glBegin(GL_QUADS);
					for (vector<int> vertex : face) {
						glTexCoord2f(text[vertex[TEXT] - 1][0], text[vertex[TEXT] - 1][1]);
						glNormal3f(norms[vertex[NORM] - 1][0], norms[vertex[NORM] - 1][1], norms[vertex[NORM] - 1][2]);
						glVertex3f(coords[vertex[GEOM] - 1][0], coords[vertex[GEOM] - 1][1], coords[vertex[GEOM] - 1][2]);
					}
				glEnd();
			}

			for (vector<vector<int> > face : trng) {
				glBegin(GL_TRIANGLES);
					for (vector<int> vertex : face) {
						glTexCoord2f(text[vertex[TEXT] - 1][0], text[vertex[TEXT] - 1][1]);
						glNormal3f(norms[vertex[NORM] - 1][0], norms[vertex[NORM] - 1][1], norms[vertex[NORM] - 1][2]);
						glVertex3f(coords[vertex[GEOM] - 1][0], coords[vertex[GEOM] - 1][1], coords[vertex[GEOM] - 1][2]);
					}
				glEnd();
			}

			for (vector<vector<int> > face : poly) {
				glBegin(GL_POLYGON);
					for (vector<int> vertex : face) {
						glTexCoord2f(text[vertex[TEXT] - 1][0], text[vertex[TEXT] - 1][1]);
						glNormal3f(norms[vertex[NORM] - 1][0], norms[vertex[NORM] - 1][1], norms[vertex[NORM] - 1][2]);
						glVertex3f(coords[vertex[GEOM] - 1][0], coords[vertex[GEOM] - 1][1], coords[vertex[GEOM] - 1][2]);
					}
				glEnd();
			}
		}
	};
