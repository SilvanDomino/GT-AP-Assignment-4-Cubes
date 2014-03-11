#include "..\cyclone-physics-master\include\gl\glut.h"
#include "..\cyclone-physics-master\include\cyclone\cyclone.h"
#include "app.h"
#include "timing.h"

#include <stdio.h>
#include <cassert>

#define BASE_MASS 1
#define EXTRA_MASS 10
using namespace cyclone;
class Springs : public MassAggregateApplication
{
	cyclone::ParticleSpring *spring;

    /**
     * Updates particle masses to take into account the mass
     * that's crossing the bridge.
     */
    void updateAdditionalMass();

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
};

// Method definitions
Springs::Springs()
:
MassAggregateApplication( 3 ), spring(0)
{
	particleArray[0].setPosition(	0,	6,		0);
	particleArray[0].setDamping(0.9f);
	particleArray[1].setPosition(	0,	4,		0);
	particleArray[1].setDamping(0.9f);
	particleArray[2].setPosition(	0,	2,		0);
	particleArray[2].setDamping(0.3f);
	particleArray[1].setAcceleration(Vector3::GRAVITY);
	for ( int i = 0; i < 3; ++i )
	{
		world.getParticles( )[i] = &particleArray[i];
	}

	spring = new cyclone :: ParticleSpring( &particleArray[0], 3.0f, 6.0f );
	
	//cyclone::ParticleSpring(&particleArray[1], 0.5f, 1.0f);
	world.getForceRegistry( ).add( &particleArray[1], spring );
	world.getForceRegistry( ).add( &particleArray[1], new ParticleDrag(0.8f, 0.04f) );
    updateAdditionalMass();
}

Springs::~Springs()
{

}

void Springs::updateAdditionalMass()
{
	particleArray[0].setMass(1.0f);  
	particleArray[1].setMass(1.2f);
}

void Springs::display()
{
    MassAggregateApplication::display();

    glBegin(GL_LINES);
    glColor3f(0,0,1);
	
    for (unsigned i = 0; i < 1; i++)
    {
		const cyclone::Vector3 &p0 = particleArray[i].getPosition();
        const cyclone::Vector3 &p1 = particleArray[i+1].getPosition();
        glVertex3f(p0.x, p0.y, p0.z);
        glVertex3f(p1.x, p1.y, p1.z);
    }

    glEnd();
}

void Springs::update()
{
    MassAggregateApplication::update();

    updateAdditionalMass();
}

const char* Springs::getTitle()
{
    return "AdvPhys Ass3: FranJanPoort_506031396";
}


Application* getApplication()
{
    return new Springs();
}