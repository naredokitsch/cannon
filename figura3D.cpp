#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>

#define GEOM 0
#define TEXT 1
#define NORM 2

int width, height, nrChannels;

using namespace std;

class figura3D {

	map<string, vector< vector<float> > > geo;
	map<string, vector<vector<vector<int> > > > faces;

	public:
		figura3D(map<string, vector< vector<float> > > g, map<string, vector<vector<vector<int> > > > f) {
			geo = g;
			faces = f;
			unsigned int texture = 0;
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		void pointsCloud() {
			glColor3f(1.0f,0.0f,0.0f);
			glPointSize(2);  
			glBegin(GL_POINTS);
				for (vector<float> vertex : geo["vertex"]){
					glVertex3f(vertex[0], vertex[1], vertex[2]);
				}
			glEnd();
		}

		void mesh() {
			glColor3f(0.0f,1.0f,1.0f);
			for (vector<vector<int> > face : faces["quads"]) {
				glBegin(GL_LINE_LOOP);
					for (vector<int> vertex : face) {
						glVertex3f(geo["vertex"][vertex[0]][0], geo["vertex"][vertex[0]][1], geo["vertex"][vertex[0]][2]);
					}
				glEnd();
			}

			glColor3f(1.0f,0.0f,0.0f);
			for (vector<vector<int> > face : faces["trng"]) {
				glBegin(GL_LINE_LOOP);
					for (vector<int> vertex : face) {
						glVertex3f(geo["vertex"][vertex[0]][0], geo["vertex"][vertex[0]][1], geo["vertex"][vertex[0]][2]);
					}
				glEnd();
			}

			glColor3f(1.0f,1.0f,0.0f);
			for (vector<vector<int> > face : faces["poly"]) {
				glBegin(GL_LINE_LOOP);
					for (vector<int> vertex : face) {
						glNormal3f(geo["normals"][vertex[NORM]][0], geo["normals"][vertex[NORM]][1], geo["normals"][vertex[NORM]][2]);
						glVertex3f(geo["vertex"][vertex[GEOM]][0], geo["vertex"][vertex[GEOM]][1], geo["vertex"][vertex[GEOM]][2]);
					}
				glEnd();
			}
			glColor3f(1.0f,1.0f,1.0f);
		}

		void solid() {
			glColor3f(1.0f,1.0f,1.0f);
			for (vector<vector<int> > face : faces["quads"]) {
				glBegin(GL_QUADS);
					for (vector<int> vertex : face) {
						glNormal3f(geo["normals"][vertex[NORM]][0], geo["normals"][vertex[NORM]][1], geo["normals"][vertex[NORM]][2]);
						glVertex3f(geo["vertex"][vertex[GEOM]][0], geo["vertex"][vertex[GEOM]][1], geo["vertex"][vertex[GEOM]][2]);
					}
				glEnd();
			}

			glColor3f(1.0f,0.0f,0.0f);
			for (vector<vector<int> > face : faces["trng"]) {
				glBegin(GL_TRIANGLES);
					for (vector<int> vertex : face) {
						glNormal3f(geo["normals"][vertex[NORM]][0], geo["normals"][vertex[NORM]][1], geo["normals"][vertex[NORM]][2]);
						glVertex3f(geo["vertex"][vertex[GEOM]][0], geo["vertex"][vertex[GEOM]][1], geo["vertex"][vertex[GEOM]][2]);
					}
				glEnd();
			}

			glColor3f(1.0f,1.0f,0.0f);
			for (vector<vector<int> > face : faces["poly"]) {
				glBegin(GL_POLYGON);
					for (vector<int> vertex : face) {
						glNormal3f(geo["normals"][vertex[NORM]][0], geo["normals"][vertex[NORM]][1], geo["normals"][vertex[NORM]][2]);
						glVertex3f(geo["vertex"][vertex[GEOM]][0], geo["vertex"][vertex[GEOM]][1], geo["vertex"][vertex[GEOM]][2]);
					}
				glEnd();
			}
			glColor3f(1.0f,1.0f,1.0f);
		}

		void texturized(char* texturePath) {
			glEnable(GL_TEXTURE_2D);
			int i = 0;
			unsigned char* metal = stbi_load(texturePath, &width, &height, &nrChannels, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, metal);
			stbi_image_free(metal);

			for (vector<vector<int> > face : faces["quads"]) {
				glBegin(GL_QUADS);
					for (vector<int> vertex : face) {
						glTexCoord2f(geo["texts"][vertex[TEXT]][0], geo["texts"][vertex[TEXT]][1]);
						glNormal3f(geo["normals"][vertex[NORM]][0], geo["normals"][vertex[NORM]][1], geo["normals"][vertex[NORM]][2]);
						glVertex3f(geo["vertex"][vertex[GEOM]][0], geo["vertex"][vertex[GEOM]][1], geo["vertex"][vertex[GEOM]][2]);
					}
				glEnd();
			}

			for (vector<vector<int> > face : faces["trng"]) {
				glBegin(GL_TRIANGLES);
					for (vector<int> vertex : face) {
						glTexCoord2f(geo["texts"][vertex[TEXT]][0], geo["texts"][vertex[TEXT]][1]);
						glNormal3f(geo["normals"][vertex[NORM]][0], geo["normals"][vertex[NORM]][1], geo["normals"][vertex[NORM]][2]);
						glVertex3f(geo["vertex"][vertex[GEOM]][0], geo["vertex"][vertex[GEOM]][1], geo["vertex"][vertex[GEOM]][2]);
					}
				glEnd();
			}

			for (vector<vector<int> > face : faces["poly"]) {
				glBegin(GL_POLYGON);
					for (vector<int> vertex : face) {
						glTexCoord2f(geo["texts"][vertex[TEXT]][0], geo["texts"][vertex[TEXT]][1]);
						glNormal3f(geo["normals"][vertex[NORM]][0], geo["normals"][vertex[NORM]][1], geo["normals"][vertex[NORM]][2]);
						glVertex3f(geo["vertex"][vertex[GEOM]][0], geo["vertex"][vertex[GEOM]][1], geo["vertex"][vertex[GEOM]][2]);
					}
				glEnd();
			}

			glDisable(GL_TEXTURE_2D);	
		}
	};
