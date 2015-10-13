#include "Texture.h"

GLuint loadTextureFromFile(const string& filename)
{
	SDL_Surface *imageSurface = IMG_Load(filename.c_str());
	if (!imageSurface)
	{
		cout << "can't load image" << filename << " " << IMG_GetError();
		return 0;
	}
	GLuint textureID = convertSDLSurfaceToTexture(imageSurface);
	SDL_FreeSurface(imageSurface);

	return textureID;
}

GLuint convertSDLSurfaceToTexture(SDL_Surface* surface)
{
	GLuint textureID = 0;
	GLint nOfColours = surface->format->BytesPerPixel;

	GLenum textureFormat = GL_RGB;
	GLenum internalFormat = GL_RGB8;

	if (nOfColours == 4) //contains an alpha channel
	{
		if (surface->format->Rmask == 0x000000ff)
		{
			textureFormat = GL_RGBA;
			internalFormat = GL_RGB8;
		}
		else
		{
			textureFormat = GL_BGRA;
			internalFormat = GL_RGBA8;
		}
	}
	else if (nOfColours == 3)
	{
		if (surface->format->Rmask == 0x00000ff)
		{
			textureFormat = GL_RGB;
			internalFormat = GL_RGB8;
		}
		else
		{
			textureFormat = GL_BGR;
			internalFormat = GL_RGB8;
		}
	}
	else
	{
		cout << "warning: the image is not true colour..this will probable break" << endl;
		return 0;
	}

	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, surface->w, surface->h, 0, textureFormat, GL_UNSIGNED_BYTE, surface->pixels);

	return textureID;
}