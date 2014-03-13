#include "..\cyclone-physics-master\include\gl\glut.h"
#include "..\cyclone-physics-master\include\cyclone\cyclone.h"
#include "app.h"
#include "timing.h"

#include <stdio.h>
#include <cassert>
#include "../Cube.h"
#include "../LevelGraph.h"

using namespace cyclone;
class Springs : public RigidBodyApplication
{

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
	cube1 = Cube();
}

Springs::~Springs()
{

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
	cube1.displayCube();
	lvlGraph.displayLevel();

    
}

void Springs::update()
{
    RigidBodyApplication::update();
}

const char* Springs::getTitle()
{
    return "Lets make cubes!";
}


Application* getApplication()
{
    return new Springs();
}