#include "Cube.h"
#include <iostream>

Cube::Cube(void)
{
	rigidBody = RigidBody();
	setVertices(vertices);
}

void Cube::displayCube(){
	glBegin(GL_LINES);
    glColor3f(1,0,0);
	//draws the top and bottom squares
	for(int j = 0; j < 2; j++){
		for(int i = 0; i < 4; i++){
			Vector3* a = &vertices[i + j*4];
			Vector3* b;
			i != 3 ? b = &vertices[i+1+ j*4] : b = &vertices[j*4] ;
			glVertex3f(a->x, a->y, a->z);
			glVertex3f(b->x, b->y, b->z);
		}
	}
	//draws the lines between the squares
	for(int i = 0; i < 4; i++){
			Vector3* a = &vertices[i];
			Vector3* b= &vertices[i+4];
			glVertex3f(a->x, a->y, a->z);
			glVertex3f(b->x, b->y, b->z);
		}

	glEnd();
}

void Cube::setVertices(Vector3* vertexArray){
	vertexArray[0] = Vector3(-0.5, -0.5, -0.5);
	vertexArray[1] = Vector3(0.5, -0.5, -0.5);
	vertexArray[2] = Vector3(0.5, -0.5, 0.5);
	vertexArray[3] = Vector3(-0.5, -0.5, 0.5);

	vertexArray[4] = Vector3(-0.5, 0.5, -0.5);
	vertexArray[5] = Vector3(0.5, 0.5, -0.5);
	vertexArray[6] = Vector3(0.5, 0.5, 0.5);
	vertexArray[7] = Vector3(-0.5, 0.5, 0.5);
}
Cube::~Cube(void)
{
}
