#include "../Wall.h"


#define NUM_CUBES = 25;

using namespace cyclone;

// Method definitions
Springs::Springs():RigidBodyApplication()
{
	for(int i = 0; i < 25; i ++){
		cubes[i] = Cube(
			Vector3(0,  4+ 2 * (i /5), 2.5f - 2 * (i %5)), 
			Quaternion(), 
			Vector3(0.5,0.5,0.5), 
			Vector3(0,0,0),2);
	}
	plane.direction = Vector3(0, 1, 0);
	plane.offset = 0;

	shootCube = Cube(Vector3(5,1,0), Quaternion(), Vector3(0.5,0.5,0.5), Vector3(0,0,0),1);
	shootCube.body->setMass(10);
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
	
	if(button == 0){
		shootCube.body->addForce(shootCubeDir * 50000);
		std::cout << "button: " << button << std::endl;
	}
	//std::cout<< x << this->width std::endl;
}
void Springs::mouseDrag(int x, int y){
	RigidBodyApplication::mouseDrag(x, y);
	float xV = 0.5f - x / (float)this->width;
	float yV = 1 - (y / (float)this->height *0.7f);
	std::cout << xV << std::endl;
	shootCubeDir = Vector3(-1, yV, -xV);
}
void Springs::display()
{
	RigidBodyApplication::display();
	for(int i = 0; i < 25; i ++){
		cubes[i].render();
	}
	shootCube.render();
	lvlGraph.displayLevel();
	renderThrowCube();
}

void Springs::renderThrowCube(){
	glBegin(GL_LINES);
	Vector3 start = shootCube.body->getPosition();
	Vector3 end = start+(shootCubeDir*20);
	glVertex3f(start.x, start.y, start.z);
	glVertex3f(end.x, end.y, end.z);
	glEnd();
}

void Springs::update()
{
    RigidBodyApplication::update();
	for(int i = 0; i < 25; i ++){
		cubes[i].update();
	}
	shootCube.update();

	//creates the delta time the physics are working with. The higher the number the faster it goes.
	float duration = (float)TimingData::get().lastFrameDuration * 0.0004f;
	updateObjects(duration);
	generateContacts();

	//the resolver
	resolver.resolveContacts(cData.contactArray, cData.contactCount, duration);
}

//detects the collisions. Magic.
void Springs::generateContacts(){
	//RigidBodyApplication::generateContacts();

	cData.reset(maxContacts);
	cData.friction = 0.9f;
    cData.restitution = 0.6f;
    cData.tolerance = 0.9f;
	CollisionDetector :: boxAndHalfSpace( shootCube, plane, &cData );
	//std::cout << shootCube.body->getPosition().y <<std::endl;
	//check all the cubes
	for (int i = 0; i < 25; i ++)
	{
		if (!cData.hasMoreContacts( ))
			return;
		//checks all the cubes for collisions with the bottomplane
		CollisionDetector :: boxAndHalfSpace( cubes[i], plane, &cData );
		CollisionDetector :: boxAndBox( cubes[i], shootCube, &cData );	
		//checks for all the cubexcube collisions
		for (int j = i+1; j < 25; j ++)
		{
			if ( !cData.hasMoreContacts( ) ) return;
			CollisionDetector :: boxAndBox( cubes[i], cubes[j], &cData );	
			if(IntersectionTests::boxAndBox(cubes[i], cubes[j])){
				cubes[i].isOverlapping = cubes[j].isOverlapping = true;
			}
		}
	}
}
void Springs::updateObjects(real duration){
	//RigidBodyApplication.updateObjects(duration);
	for(int i = 0; i < 25; i ++){
		cubes[i].body ->integrate(duration);
		cubes[i].calculateInternals();
	}
	shootCube.body ->integrate(duration);
	shootCube.calculateInternals();

}

const char* Springs::getTitle()
{
    return "Lets make cubes!";
}


Application* getApplication()
{
    return new Springs();
}