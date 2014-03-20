#include "../Wall.h"
#include <sstream>

using namespace cyclone;

// Method definitions
Springs::Springs():RigidBodyApplication()
{
	//This spawns the wall in a galaxy far far away, because they need to exist somewhere otherwise the display and update functions crash
	//ugliest way of a null object pattern implementation. See no evil hear no evil.
	for(int i = 0; i < 25; i ++){
		cubes[i] = Cube(
			Vector3(900,  0+ 2 * (i /5), 900), 
			Quaternion(), 
			Vector3(0.5,0.5,0.5), 
			Vector3(0,0,0),
			2,
			8);
	}
	gravity = false;

	//created a plane here. The direction is the direction of the normal. It confused me for several seconds though.
	plane.direction = Vector3(0, 1, 0);
	plane.offset = 0;

	//Unlike the wall, a single cube is used. The cube gets reset to the original position with the original mass
	//it's a design thing.
	shootCube = Cube(Vector3(5,9,0), Quaternion(), Vector3(0.5,0.5,0.5), Vector3(0,0,0),1, 10);
	shootCube.color = Vector3(0.8f, 0.5f, 0.3f);
	SpawnCube();

}

Springs::~Springs()
{

}
//I was gonna do stuff with this function, but I naaaah
void Springs::reset(){

}

//this method spawns the wall in the middle of the field.
//The mass is created here because the shot cube would have a different mass, and I felt this would be the most elegant way to do it
//The random is created every time in the for loop with a different seed so every time there will be a different value.
//if I didn't do that odds are I would've gotten the same random number several times in the loop.
void Springs::SpawnWall(){
	for(int i = 0; i < 25; i ++){
		Random rand = Random(i);
		float mass = 4 + rand.randomReal(1, 10);
		cubes[i] = Cube(
			Vector3(0,  1+ 2.02f * (i /5), 2.5f - 2.02f * (i %5)), 
			Quaternion(), 
			Vector3(0.5,0.5,0.5), 
			Vector3(0,0,0),2, mass);
	}
	
	gravity = false;
}

//A cube is spawned here. At the basic position, and with a mass.
//The mass is instantiated like this because otherwise it was getting confusing for me logistically. This was the easiest solution.
//The cubes from the wall all needed a fixed mass, while this one a variable mass that can increase or decrease
void Springs::SpawnCube(){
	shootCube.setState(Vector3(5,1,0), Quaternion(), Vector3(0.5,0.5,0.5), Vector3(0,0,0));
	shootCube.mass = 52;
	shootCube.body->setMass( shootCube.mass );
}

//this function handles the input.
void Springs::key(unsigned char key){
	RigidBodyApplication::key(key);
	if(key == 'n'){
		SpawnWall();
	}
	if(key == 'r'){
		SpawnCube();
	}
	if(key == 'w'){
		shootCube.mass += 0.5f;
		shootCube.body->setMass(shootCube.mass);
	}
	if(key == 's'){
		shootCube.mass -= 0.5f;
		shootCube.body->setMass(shootCube.mass);
	}
}
//this function handles the mouse input.
void Springs::mouse(int button, int state, int x, int y){
	RigidBodyApplication::mouse(button, state, x, y);
	
	if(button == 0){		//when mouse0 is clicked, it uses the mouse position to make a direction vector the cube is aimed at
		float xV = -0.5f + 2* x / (float)this->width;
		float yV = 0.8f - (y / (float)this->height *0.6f);
		shootCubeDir = Vector3(-1, yV, -xV);
	} if(button == 1 || button == 2){		
		//when another mouse button is clicked, it fires the cube in that direction.
		//I decided not to use a variable for it, because I liked how the mass impacted the acceleration and velocity of the shot cube
		shootCube.body->addForce(shootCubeDir * 20000);
	}
}
void Springs::mouseDrag(int x, int y){
	RigidBodyApplication::mouseDrag(x, y);
}
void Springs::display()
{
	RigidBodyApplication::display();
	//this draws the cubes
	for(int i = 0; i < 25; i ++){
		cubes[i].render();
	}
	shootCube.render();
	//this renders the lines of the level. It's not only used for debugging purposes, but also to gain an easier
	//understanding of the worldspace. It's easy to see what's the floor, and how high '1' or '2' is.
	lvlGraph.displayLevel();

	//this renders the directional line the shootcube uses.
	renderThrowCube();

	//the next part is what draws all the text
	// Create a variable to store the mass of the projectile as a float
	 float cubeMass = (float)shootCube.body->getMass();

	 // Convert the float we created above as a string value
	 std::ostringstream ss;
	 ss << cubeMass;

	 // Create strings to display on screen
	 std::string cubeMassString = "Mass of projectile: " + ss.str() + 
			 "\nAdd mass/Reduce mass: 'w'/'s'";

	 std::string controllsString = "Reset wall: 'n'" 
			 "\nReset projectile: 'r'" 
			 "\nClick with mouse to shoot." 
			 "\nAim by pointing mouse.";

	 /* 
	 * Display the mass of the projectile to the screen.
	 * c_str() is needed to store the string as a char*
	 */
	 glColor3f(0.0f, 0.0f, 0.0f);
	 renderText(470.0f, 50.0f, cubeMassString.c_str());
	 renderText(10.0f, 50.0f, controllsString.c_str());
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
	//every cube has an update function that gets called. Because I'm really used to having update functions in objects.
	//it doesn't do anything, but incase I needed to debug or trace anything, I really wanted to have it.
	for(int i = 0; i < 25; i ++){
		cubes[i].update();
	}
	shootCube.update();

	//creates the delta time the physics are working with. The higher the number the faster it goes.
	//this delta time is used in the physics calculations.
	float duration = (float)TimingData::get().lastFrameDuration * 0.0008f;
	
	updateObjects(duration);
	generateContacts();

	//the resolver
	resolver.resolveContacts(cData.contactArray, cData.contactCount, duration);
}

//detects the collisions. Magic.
void Springs::generateContacts(){
	//RigidBodyApplication::generateContacts();

	cData.reset(maxContacts);
	cData.friction = 1.1f;
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
		//what happens here is my physics hacking. my cubes don't have any gravity, until I hit them with a cube
		//then for all of them gravity is turned on.
		if(CollisionDetector :: boxAndBox( cubes[i], shootCube, &cData )){
			std::cout << "collision happened: G: " << gravity << std::endl;
			if(!gravity){
				std::cout << "not gravity happened" << std::endl;
				for (int i = 0; i < 25; i ++)
				{
					cubes[i].body->setAcceleration(Vector3::GRAVITY);
				}
				shootCube.body->setAcceleration(Vector3::GRAVITY);
				gravity = true;
			}
		}
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
	//if(theHorror){
	for(int i = 0; i < 25; i ++){
		cubes[i].body ->integrate(duration);
		cubes[i].calculateInternals();
	}
	//}
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