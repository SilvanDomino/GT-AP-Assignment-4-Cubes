#include "Cube.h"
#include <iostream>

//This creates the cube and several variables of it.
//The cube is extended from a BoxCollider. Personally I would've wanted to add a boxcollider and rigidbody to an seperate object myself
//I feel it gives a lot more controll, but I might be really influenced by the unity program design.
Cube::Cube(	
	Vector3 &position,
	Quaternion &orientation,
    Vector3 &extents,
    Vector3 &velocity,
	float size,
	float mass)
{
	color = Vector3(0.5f, 0.9f, 0.5f);
	body = new RigidBody();
	extents*= size;
	halfSize = extents;
	this->mass = mass;
    
	this->setState(position, orientation, extents, velocity);
	
	this->size = size;
	
}

Cube::Cube(){
	body = new RigidBody();
}
void Cube::update(){

}
void Cube::render()
{
	// Get the OpenGL transformation
    GLfloat mat[16];
    body->getGLTransform(mat);
    if (isOverlapping) glColor3f(color.x, color.y, color.z);
    else if (body->getAwake()) glColor3f(1.0f,0.7f,0.7f);
    else glColor3f(0.7f,0.7f,1.0f);

    glPushMatrix();
    glMultMatrixf(mat);
    glScalef(halfSize.x*2, halfSize.y*2, halfSize.z*2);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void Cube::setState(const cyclone::Vector3 &position,
				  const cyclone::Quaternion &orientation,
                  const cyclone::Vector3 &extents,
                  const cyclone::Vector3 &velocity)
{
	body->setPosition(position);
    body->setOrientation(orientation);
    body->setVelocity(velocity);
    body->setRotation(cyclone::Vector3(0,0,0));
    
	body->setMass(this->mass);

    cyclone::Matrix3 tensor;
	tensor.setBlockInertiaTensor(halfSize, body->getMass());
    body->setInertiaTensor(tensor);

    body->setLinearDamping(0.95f);
    body->setAngularDamping(0.8f);
    body->clearAccumulators();
	//body->setAcceleration(Vector3::GRAVITY);
	body->setAwake(true);
	body->setCanSleep(false);
	offset = Matrix4();
    body->calculateDerivedData();
	calculateInternals();
}

Cube::~Cube(void)
{
}
