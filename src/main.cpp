#include "Common.h"
#include "Graphics.h"

struct Position
{
	float x, y, z;
};

Position trianglePosRight = { 1.0f, 0.0f, -5.0f };
Position trianglePosLeft = { -1.0f, 0.0f, -5.0f };

void render()
{
	//set the clear colour background 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//switch to model view
	glMatrixMode(GL_MODELVIEW);
	
	//right triangle 
	//reset using the identity matrix 
	glLoadIdentity();
	//translate to world pos
	glTranslatef(trianglePosRight.x, trianglePosRight.y, trianglePosRight.z);
	//begin drawing triangle 
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f); //colour the vertices
	glVertex3f(-1.0f, 1.0f, 0.0f); //top point
	glVertex3f(-1.0f, -1.0f, 0.0f); //bottom left
	glVertex3f(1.0f, -1.0f, 0.0f); //bottom right 
	glEnd();

	//left triangle 
	//reset using the identity matrix 
	glLoadIdentity();
	//translate to world pos
	glTranslatef(trianglePosLeft.x, trianglePosLeft.y, trianglePosLeft.z);
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 1.0f); //colour the vertices
	glVertex3f(1.0f, 1.0f, 0.0f); //top point
	glVertex3f(-1.0f, -1.0f, 0.0f); //bottom left
	glVertex3f(1.0f, -1.0f, 0.0f); //bottom right 
	glEnd();
}

void update()
{

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
			if (event.type == SDL_GetKeyFromScancode(SDL_SCANCODE_W));
			{
				trianglePosRight.y += 0.1f;
				trianglePosLeft.y += 0.1f;
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
	//destroy openGL
	SDL_GL_DeleteContext(glcontext);
	//destroy window
	SDL_DestroyWindow(window);
	//destroy initalization 
	SDL_Quit;

    return 0;
}
