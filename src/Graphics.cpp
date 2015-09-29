#include "Graphics.h"
#include "Common.h"

//function to initalise OpenGL
void initOpenGL()
{
	//smopth shading
	glShadeModel(GL_SMOOTH);

	//clear the background to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//clear the depth buffer to 1.0
	glClearDepth(1.0f);

	//enable depth testing
	glEnable(GL_DEPTH_TEST);

	//the depth test to use
	glDepthFunc(GL_LEQUAL);

	//turn on best perspective correction
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/*Problem: glewInit failed, something is SERIOUSLY wrong*/
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
	}
}

//function to set/reset viewport
void setViewport(int width, int height)
{
	//screen ratio
	GLfloat ratio;

	//make sure the height is always above 1
	if (height == 0)
	{
		height = 1;
	}

	//calculate screen ratio
	ratio = (GLfloat)width / (GLfloat)height;

	//set up viewport
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	//change the projection matrix mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//calculate perspective matrix, using GLU library functions 
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	//switch to modelView
	glMatrixMode(GL_MODELVIEW);

	//reset using the identity matrix 
	glLoadIdentity();
}
