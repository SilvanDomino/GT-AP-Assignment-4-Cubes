#pragma once
#include "cyclone-physics-master\include\cyclone\cyclone.h"
#include "cyclone-physics-master\include\gl\glut.h"

using namespace cyclone;
class Cube : public cyclone::CollisionBox
{
public:
	bool isOverlapping;
	Cube();
	Cube(	Vector3 &position,
			Quaternion &orientation,
			Vector3 &extents,
			Vector3 &velocity);
	~Cube(void);
	
	// Draws the box 
	void render();
	//void displayCube();
	void update();
	// Sets the box to a specific location
	void setState(const cyclone::Vector3 &position,
				  const cyclone::Quaternion &orientation,
                  const cyclone::Vector3 &extents,
                  const cyclone::Vector3 &velocity);

	Vector3 vertices[8];
	cyclone::RigidBody rigidBody;
};

