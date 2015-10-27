#include "Common.h"
#include "Graphics.h"
#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "FileSystem.h"
#include "FBXLoader.h"

GLuint VBO;
GLuint EBO;
GLuint VAO;
GLuint shaderProgram = 0;
GLuint textureMap;
GLuint fontTexture;

MeshData *currentMesh;

//matrices
mat4 viewMatrix;
mat4 projMatrix;
mat4 worldMatrix;
mat4 MVPMatrix;

//move object
vec3 movementVec = vec3(0.0f, 0.0f, 0.0f);
//move camera 
vec3 worldPoint = vec3(0.0f, 0.0f, 10.0f);
vec3 lookAtPoint = vec3(0.0f, 0.0f, 0.0f);


void render()
{
	//set the clear colour background 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//blend alpha channel
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(shaderProgram);
	
	//get the uniform loaction for the MVP
	GLint MVPLocation = glGetUniformLocation(shaderProgram, "MVP");
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, value_ptr(MVPMatrix));
	
	//get the uniform for the movementVec
	GLint moveVecLocation = glGetUniformLocation(shaderProgram, "movementVec");
	glUniform3fv(moveVecLocation, 1, value_ptr(movementVec));
	
	//get the uniform for the texture coords
	GLint texture0Location = glGetUniformLocation(shaderProgram, "texture0");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureMap);
	glUniform1i(texture0Location, 0);

	glBindVertexArray(VAO);
	//begin drawing triangle 
	glDrawElements(GL_TRIANGLES, currentMesh->getNumIndices(), GL_UNSIGNED_INT, 0);
}

void update()
{
	projMatrix = perspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);
	viewMatrix = lookAt(worldPoint, lookAtPoint, vec3(0.0f, 1.0f, 0.0f));
	worldMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));
	MVPMatrix = projMatrix*viewMatrix*worldMatrix;
}

void initScene()
{
	
	//load texture & bind
	string texturePath = ASSET_PATH + TEXTURE_PATH + "/Tank1.png";
	textureMap = loadTextureFromFile(texturePath);

	glBindTexture(GL_TEXTURE_2D, textureMap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	/*
	//load font and bind 
	string fontPath = ASSET_PATH + FONT_PATH + "/OratorStd.otf";
	fontTexture = loadTextureFromFont(fontPath, 18, "Hello World");

	glBindTexture(GL_TEXTURE_2D, fontTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	*/

	//load model
	currentMesh = new MeshData();
	string modelPath = ASSET_PATH + MODEL_PATH + "/Tank.fbx";
	loadFBXFromFile(modelPath, currentMesh);
	printf("%d %d\n", currentMesh->vertices.size(), currentMesh->indices.size());

	//gen vertex array object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//create vertex buffer object
	glGenBuffers(1, &VBO);
	//make the VBO active
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//copy vertex data to VBO
	glBufferData(GL_ARRAY_BUFFER, currentMesh->getNumVerts()*sizeof(Vertex), currentMesh->vertices.data(), GL_STATIC_DRAW);

	//create element buffer object 
	glGenBuffers(1, &EBO);
	//make the EBO active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//copy the index date to the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, currentMesh->getNumIndices()*sizeof(int), currentMesh->indices.data(), GL_STATIC_DRAW);

	//tell the shader that 0 is the position element 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
	//send the colour to the shader
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)sizeof(vec3));
	//send the text coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec4)));

	GLuint vertexShaderProgram = 0;
	string vsPath = ASSET_PATH + SHADER_PATH + "/textureVS.glsl";
	vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);
	checkForCompilerErrors(vertexShaderProgram);

	GLuint fragmentShaderProgram = 0;
	string fsPath = ASSET_PATH + SHADER_PATH + "/textureFS.glsl";
	fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);
	checkForCompilerErrors(fragmentShaderProgram);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderProgram);
	glAttachShader(shaderProgram, fragmentShaderProgram);

	//link attributes 
	glBindAttribLocation(shaderProgram, 0, "vertexPosition");
	glBindAttribLocation(shaderProgram, 1, "vertexColour");
	glBindAttribLocation(shaderProgram, 2, "vertexTexCoords");

	glLinkProgram(shaderProgram);
	checkForLinkErrors(shaderProgram);
	//now we can delete the VS and FS programs 
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);

}

void cleanUp()
{
	glDeleteTextures(1, &textureMap);
	glDeleteTextures(1, &fontTexture);
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

int main(int argc, char * arg[])
{
	ChangeWorkingDirectory();
	//controls the game loop 
	bool run = true;

	//init everything - SDL, if it is nonZero we have a problem
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR SDL_Init " << SDL_GetError() << std::endl;

		return -1;
	}

	//init SDL image
	int imageInitFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	int returnInitFlags = IMG_Init(imageInitFlags);
	if (((returnInitFlags) & (imageInitFlags)) != imageInitFlags)
	{
		cout << "Error SDL_Image Init " << IMG_GetError() << endl;
	}

	//init SDL font
	if (TTF_Init() == -1)
	{
		cout << "ERROR TTF_Init: " << TTF_GetError();
	}

	//ask for version 4.2 of openGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
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
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					movementVec.y += 0.5;
					cout << "up arrow " << endl;
					break;
				case SDLK_DOWN:
					movementVec.y += -0.5f;
					cout << "down arrow " << endl;
					break;
				case SDLK_RIGHT:
					movementVec.x += 0.5f;
					cout << "right arrow " << endl;
					break;
				case SDLK_LEFT:
					movementVec.x += -0.5f;
					cout << "left arrow " << endl;
					break;
				case SDLK_w:
					worldPoint.z += -1.0f;
					lookAtPoint.z += -1.0f;
					cout << "w key " << endl;
					break;
				case SDLK_s:
					worldPoint.z += 1.0f;
					lookAtPoint.z += 1.0f;
					cout << "s key " << endl;
					break;
				case SDLK_a:
					worldPoint.x += -1.0f;
					lookAtPoint.x += -1.0f;
					cout << "a key " << endl;
					break;
				case SDLK_d:
					worldPoint.x += 1.0f;
					lookAtPoint.x += 1.0f;
					cout << "d key " << endl;
					break;
				default:
					break;
				}
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
	//destroy image Lib
	IMG_Quit();
	//destroy SDL font lib
	TTF_Quit();
	//destroy initalization 
	SDL_Quit();

    return 0;
}
