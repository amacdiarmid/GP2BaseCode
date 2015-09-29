#include "Common.h"
#include "Graphics.h"
#include "Vertex.h"

Vertex verts[] = {
	//front face
	//tri 1
	//top left
		{ -0.5f, 0.5f, 0.5f, //x,y,z
		1.0f, 0.0f, 0.0f, 1.0f }, //r,g,b,a
	//bottom left
		{ -0.5f, -0.5f, 0.5f, //x,y,z
		0.0f, 1.0f, 0.0f, 1.0f }, //r,g,b,a
	//bottom right
		{ 0.5f, -0.5f, 0.5f, //x,y,z
		0.0f, 0.0f, 1.0f, 1.0f }, //r,g,b,a
	//tri 2
	//top right
		{ 0.5f, 0.5f, 0.5f, //x,y,z
		0.0f, 1.0f, 0.0f, 1.0f }, //r,g,b,a
	//top left
		{ -0.5f, 0.5f, 0.5, //x,y,z
		1.0f, 0.0f, 0.0f, 1.0f }, //r,g,b,a
	//bottom right
		{ 0.5f, -0.5, 0.5f, //x,y,z
		0.0f, 0.0f, 1.0f, 1.0f }, //r,g,b,a
	//back face
	//tri 1
	//top left
		{ -0.5f, 0.5f, -0.5f, //x,y,z
		0.0f, 1.0f, 0.0f, 1.0f }, //r,g,b,a
	//bottom left
		{ -0.5f, -0.5f, -0.5f, //x,y,z
		0.0f, 0.0f, 1.0f, 1.0f }, //r,g,b,a
	//bottom right
		{0.5f, -0.5f, -0.5f, //x,y,z
		1.0f, 0.0f, 0.0f, 1.0f }, //r,g,b,a
	//tri 2
	//top right
		{ 0.5f, 0.5f, -0.5f, //x,y,z
		0.0f, 0.0f, 1.0f, 1.0f }, //r,g,b,a
	//top left
		{ -0.5f, 0.5f, -0.5f, //x,y,z
		0.0f, 1.0f, 0.0f, 1.0f }, //r,g,b,a
	//bottom right
		{ 0.5f, -0.5f, -0.5f, //x,y,z
		1.0f, 0.0f, 0.0f, 1.0f }, //r,g,b,a
	//top face
	//tri 1
	//front left
		{ -0.5f, 0.5f, 0.5f, //x,y,z
		1.0f, 0.0f, 0.0f, 1.0f }, //r,g,b,a
	//front right
		{ 0.5f, 0.5f, 0.5f, //x,y,z
		0.0f, 1.0f, 0.0f, 1.0f }, //r,g,b,a
	//back left
		{ -0.5f, 0.5f, -0.5f, //x,y,z
		0.0f, 1.0f, 0.0f, 1.0f }, //r,g,b,a
	//tri 2 
	//back right
		{ 0.5f, 0.5f, -0.5f, //x,y,z
		0.0f, 0.0f, 1.0f, 1.0f }, //r,g,b,a
	//back left
		{ -0.5f, 0.5f, -0.5f, //x,y,z
		0.0f, 1.0f, 0.0f, 1.0f }, //r,g,b,a
	//front right
		{ 0.5f, 0.5f, 0.5f, //x,y,z
		0.0f, 1.0f, 0.0f, 1.0f }, //r,g,b,a
	//bottom face 
	//tri 1
	//front left 
		{ -0.5f, -0.5f, 0.5f, //x,y,z
		0.0f, 1.0f, 0.0f, 1.0f }, //r,g,b,a
	//front right 
		{ 0.5f, -0.5f, 0.5f, //x,y,z
		0.0f, 0.0f, 1.0f, 1.0f }, //r,g,b,a
	//back left
		{ -0.5f, -0.5f, -0.5f, //x,y,z
		0.0f, 0.0f, 1.0f, 1.0f }, //r,g,b,a
	//tri 2
	//back right 
		{ 0.5f, -0.5f, -0.5f, //x,y,z
		1.0f, 0.0f, 0.0f, 1.0f }, //r,g,b,a
	//back left 
		{ -0.5f, -0.5f, -0.5f, //x,y,z
		0.0f, 0.0f, 1.0f, 1.0f }, //r,g,b,a
	//front right
		{ 0.5f, -0.5f, 0.5f, //x,y,z
		0.0f, 0.0f, 1.0f, 1.0f }, //r,g,b,a
	//right face
	//tri 1
	//front bottom 
		{ 0.5f, -0.5f, 0.5f, //x,y,z
		0.0f, 0.0f, 1.0f, 1.0f }, //r,g,b,a
	//front top
		{ 0.5f, 0.5f, 0.5f, //x,y,z
		0.0f, 1.0f, 0.0f, 1.0f }, //r,g,b,a
	//back bottom
		{ 0.5f, -0.5f, -0.5f, //x,y,z
		1.0f, 0.0f, 0.0f, 1.0f }, //r,g,b,a
	//tri 2 
	//back top
		{ 0.5f, 0.5f, -0.5f, //x,y,z
		0.0f, 0.0f, 1.0f, 1.0f }, //r,g,b,a
	//back bottom 
		{ 0.5f, -0.5f, -0.5f, //x,y,z
		1.0f, 0.0f, 0.0f, 1.0f }, //r,g,b,a
	//front top
		{ 0.5f, 0.5f, 0.5f, //x,y,z
		0.0f, 1.0f, 0.0f, 1.0f }, //r,g,b,a
	//left face
	//tri 1
	//front bottom
		{ -0.5f, -0.5f, 0.5f, //x,y,z
		0.0f, 1.0f, 0.0f, 1.0f }, //r,g,b,a
	//front top
		{ -0.5f, 0.5f, 0.5f, //x,y,z
		1.0f, 0.0f, 0.0f, 1.0f }, //r,g,b,a
	//back bottom
		{ -0.5f, -0.5f, -0.5f, //x,y,z
		0.0f, 0.0f, 1.0f, 1.0f }, //r,g,b,a
	//tri 2
	//back top
		{ -0.5f, 0.5f, -0.5f, //x,y,z
		0.0f, 1.0f, 0.0f, 1.0f }, //r,g,b,a
	//front top
		{ -0.5f, 0.5f, 0.5f, //x,y,z
		1.0f, 0.0f, 0.0f, 1.0f }, //r,g,b,a
	//back bottom
		{ -0.5f, -0.5f, -0.5f, //x,y,z
		0.0f, 0.0f, 1.0f, 1.0f }, //r,g,b,a

};

GLuint VBO;

void render()
{
	//set the clear colour background 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//make the new VBO active. repeat here as a sanity check(may have changed since initialisation)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//the 3 param is now filled out, the pipeline needs to know the size of each vertex
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), NULL);
	//the last param basically says that the colours start 3 floats into each element of the array
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), (void**)(3 * sizeof(float)));
	//establish array contains vertices and colours
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	//switch to model view
	glMatrixMode(GL_MODELVIEW);
	//reset using the identity matrix 
	glLoadIdentity();
	//calculate the view matrix to see 3D stuff
	gluLookAt(0.0, 0.0, 6.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
	//translate 
	glTranslatef(2.0f, 1.0f, 0.0f);
	//begin drawing triangle 
	glDrawArrays(GL_TRIANGLES, 0, sizeof(verts)/sizeof(Vertex));	
}

void update()
{

}

void initScene()
{
	//create buffer
	glGenBuffers(1, &VBO);
	//make the VBO active
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//copy vertex data to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
}

void cleanUp()
{
	glDeleteBuffers(1, &VBO);
}

int main(int argc, char * arg[])
{
	bool run = true;

	//init everything - SDL, if it is nonZero we have a problem
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR SDL_Init " << SDL_GetError() << std::endl;

		return -1;
	}

	//create a window 
	SDL_Window * window = SDL_CreateWindow("SDL", //window title
		SDL_WINDOWPOS_CENTERED, // x position centered
		SDL_WINDOWPOS_CENTERED, //y position centered
		640, //width in pixels 
		480, //height in pixels 
		SDL_WINDOW_OPENGL //flags
		);

	//create an openGL context associated with the window
	SDL_GLContext glcontext = SDL_GL_CreateContext(window);

	//initalisation
	//call our initOpenGL function
	initOpenGL();
	//call our initScene function with the vertex buffer object
	initScene();
	//set our viewport
	setViewport(640, 480);

	//value to hold the event generated by SDL
	SDL_Event event;
	//game loop
	while (run)
	{
		//while we still have events in the queue
		while (SDL_PollEvent(&event))
		{
			//get event type
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
			{
				//set our bool which controls the loop to false
				run = false;
			}
		}

		//update 
		update();
		//then draw
		render();

		//call swap so that our GL back buffer is displayed
		SDL_GL_SwapWindow(window);

	}

	//clean up in reverse order
	//clean out the buffers 
	cleanUp();
	//destroy openGL
	SDL_GL_DeleteContext(glcontext);
	//destroy window
	SDL_DestroyWindow(window);
	//destroy initalization 
	SDL_Quit;

    return 0;
}
