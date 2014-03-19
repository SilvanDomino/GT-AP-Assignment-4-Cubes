#include "LevelGraph.h"


LevelGraph::LevelGraph(void)
{
}


LevelGraph::~LevelGraph(void)
{
}

void LevelGraph::displayLevel(){
	glBegin(GL_LINES);
	
    glColor3f(0.8f,0.8f,0.9f);
    glVertex3f(-20,0,0);
    glVertex3f(20,0,0);
    glVertex3f(0,0,-20);
    glVertex3f(0,0,20);
	glEnd();
	
	float numCircles = 10;
	float size = 2;
	glColor3f(0.8, 0.8, 1);
    for (unsigned i = 1; i < 10; i++)
    {
        glBegin(GL_LINE_LOOP);
        for (unsigned j = 0; j < 32; j++)
        {
            float theta = 3.1415926f * j / 16.0f;
            glVertex3f(i*cosf(theta)*size, 0.0f, i*sinf(theta)*size);
        }
        glEnd();
    }

	glBegin(GL_LINES);
	glColor3f(0.7f,0.7f,0.8f);
    glVertex3f(0,0,0);
    glVertex3f(0,20,0);
	
	for(int i = 0; i < 10; i++){
		glVertex3f(0, i,-0.5f);
		glVertex3f(0, i,0.5f);
		glVertex3f(-0.5f, i,0);
		glVertex3f(0.5f, i,0);
	}
	glEnd();
}
