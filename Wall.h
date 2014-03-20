#include "cyclone-physics-master\include\gl\glut.h"
#include "cyclone-physics-master\include\cyclone\cyclone.h"
#include "src\app.h"
#include "src\timing.h"
#include <iostream>
#include <stdio.h>
#include <cassert>
#include "Cube.h"
#include "LevelGraph.h"

class Springs : public RigidBodyApplication
{
	Cube cubes[25];
	CollisionPlane plane;
	Cube shootCube;
	Vector3 shootCubeDir;
	bool hasHit;
	/** Processes the contact generation code. */
    virtual void generateContacts();

    /** Processes the objects in the simulation forward in time. */
    virtual void updateObjects(cyclone::real duration);

    /** Resets the position of all the bones. */
    virtual void reset();
public:
    /** Creates a new demo object. */
    Springs();
    virtual ~Springs();
    /** Returns the window title for the demo. */
    virtual const char* getTitle();
    /** Display the particles. */
    virtual void display();
    /** Update the particle positions. */
    virtual void update();
	 /** Handle a mouse click. */
    virtual void mouse(int button, int state, int x, int y);
    /** Handle a mouse drag */
    virtual void mouseDrag(int x, int y);
    /** Handles a key press. */
    virtual void key(unsigned char key);
	
	void renderThrowCube();
	

	Cube cube1;
	LevelGraph lvlGraph;
};