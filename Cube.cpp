#include "Cube.h"
#include <iostream>

Cube::Cube(	
	Vector3 &position,
	Quaternion &orientation,
    Vector3 &extents,
    Vector3 &velocity,
	float size )
{
	body = new RigidBody();
	extents*= size;
	this->setState(position, orientation, extents, velocity);
	body->addForce( Vector3::GRAVITY);
	this->size = size;
}

Cube::Cube(){
	body = new RigidBody();
}
void Cube::update(){
	//std::cout << body->getPosition().y <<std::endl;
}
void Cube::render()
{
	// Get the OpenGL transformation
    GLfloat mat[16];
    body->getGLTransform(mat);

    if (isOverlapping) glColor3f(0.5f, 0.8f, 0.5f);
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
    halfSize = extents;

    cyclone::real mass = halfSize.x * halfSize.y * halfSize.z * 4.0f;
    body->setMass(mass);

    cyclone::Matrix3 tensor;
    tensor.setBlockInertiaTensor(halfSize, mass);
    body->setInertiaTensor(tensor);

    body->setLinearDamping(0.95f);
    body->setAngularDamping(0.8f);
    body->clearAccumulators();
	body->setAcceleration(Vector3::GRAVITY);
	body->setAwake(true);
	body->setCanSleep(false);
	offset = Matrix4();
    body->calculateDerivedData();
	calculateInternals();
}

Cube::~Cube(void)
{
}
