#pragma once
#include "cyclone-physics-master\include\cyclone\cyclone.h"
#include "cyclone-physics-master\include\gl\glut.h"

using namespace cyclone;
class Cube : public cyclone::CollisionBox
{
public:
	bool isOverlapping;
	float size;
	float mass;
	Vector3 color;
	Cube();
	Cube(	Vector3 &position,
			Quaternion &orientation,
			Vector3 &extents,
			Vector3 &velocity,
			float size,
			float mass);
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

};

