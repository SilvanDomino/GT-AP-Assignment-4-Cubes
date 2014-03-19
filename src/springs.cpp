#include "..\cyclone-physics-master\include\gl\glut.h"
#include "..\cyclone-physics-master\include\cyclone\cyclone.h"
#include "app.h"
#include "timing.h"
#include <iostream>
#include <stdio.h>
#include <cassert>
#include "../Cube.h"
#include "../LevelGraph.h"

using namespace cyclone;


class Springs : public RigidBodyApplication
{
	Cube cubes[3];
	CollisionPlane plane;
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
	

	Cube cube1;
	LevelGraph lvlGraph;
};

// Method definitions
Springs::Springs():RigidBodyApplication()
{
	for(int i = 0; i < 3; i ++){
		cubes[i] = Cube(Vector3(0,10,i*3 - 1), Quaternion(), Vector3(0.5,0.5,0.5), Vector3(0,0,0));
	}
	plane.direction = Vector3(0, 1, 0);
	plane.offset = 0;

	//cData.
}

Springs::~Springs()
{

}

void Springs::reset(){

}

void Springs::key(unsigned char key){
	RigidBodyApplication::key(key);
}
void Springs::mouse(int button, int state, int x, int y){
	RigidBodyApplication::mouse(button, state, x, y);
}
void Springs::mouseDrag(int x, int y){
	RigidBodyApplication::mouseDrag(x, y);
}
void Springs::display()
{
	RigidBodyApplication::display();
	for(int i = 0; i < 3; i ++){
		cubes[i].render();
	}
	lvlGraph.displayLevel();
}


void Springs::update()
{
    RigidBodyApplication::update();
	for(int i = 0; i < 3; i ++){
		cubes[i].update();
	}
	//creates the delta time the physics are working with. The higher the number the faster it goes.
	float duration = (float)TimingData::get().lastFrameDuration * 0.0005f;
	updateObjects(duration);
	generateContacts();

	//the resolver
	resolver.resolveContacts(cData.contactArray, cData.contactCount, duration);
}

//detects the collisions. Magic.
void Springs::generateContacts(){
	//RigidBodyApplication::generateContacts();

	cData.reset(maxContacts);
	for (int i = 0; i < 3; i ++ )
	{
		if ( !cData.hasMoreContacts( ) )
			return;
		CollisionDetector :: boxAndHalfSpace( cubes[i], plane, &cData );
	}
}
void Springs::updateObjects(real duration){
	//RigidBodyApplication.updateObjects(duration);
	for(int i = 0; i < 3; i ++){
		cubes[i].body ->integrate(duration);
		cubes[i].calculateInternals();
	}
	if(cubes[0].body->getPosition().y > -3){
		//std::cout << 0 << "  " << cubes[0].body->getPosition().y << std::endl;
	}

}

const char* Springs::getTitle()
{
    return "Lets make cubes!";
}


Application* getApplication()
{
    return new Springs();
}