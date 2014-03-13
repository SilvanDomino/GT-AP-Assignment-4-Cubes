#pragma once
#include "cyclone-physics-master\include\cyclone\cyclone.h"
#include "cyclone-physics-master\include\gl\glut.h"

using namespace cyclone;
class Cube
{
public:
	Cube(void);
	~Cube(void);
	void displayCube();
	Vector3 vertices[8];
	RigidBody rigidBody;
private:
	void setVertices(Vector3* vertexArray);
};

