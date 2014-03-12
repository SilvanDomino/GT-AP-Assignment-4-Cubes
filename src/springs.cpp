#include "..\cyclone-physics-master\include\gl\glut.h"
#include "..\cyclone-physics-master\include\cyclone\cyclone.h"
#include "app.h"
#include "timing.h"

#include <stdio.h>
#include <cassert>
#include "../Cube.h"

#define BASE_MASS 1
#define EXTRA_MASS 10
using namespace cyclone;
class Springs : public MassAggregateApplication
{
	cyclone::ParticleSpring *spring;

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

	Cube cube1;
};

// Method definitions
Springs::Springs()
:
MassAggregateApplication( 3 ), spring(0)
{
	cube1 = Cube();
}

Springs::~Springs()
{

}

void Springs::display()
{
    MassAggregateApplication::display();
	cube1.displayCube();
    

    glEnd();
}

void Springs::update()
{
    MassAggregateApplication::update();
}

const char* Springs::getTitle()
{
    return "AdvPhys Ass3: FranJanPoort_506031396";
}


Application* getApplication()
{
    return new Springs();
}