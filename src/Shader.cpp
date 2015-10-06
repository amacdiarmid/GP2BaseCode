#include "Shader.h"

//load it from mem buff
GLuint loadShaderFromMemory(const char *pMem, SHADER_TYPE shaderType)
{
	GLuint program = glCreateShader(shaderType);
	glShaderSource(program, 1, &pMem, NULL);
	glCompileShader(program);
	return program;
}

GLuint loadShaderFromFile(const std::string& filename, SHADER_TYPE shaderType)
{
	string fileContents;
	ifstream file;
	file.open(filename.c_str(), std::ios::in);
	if (!file)
	{
		cout << "File could not be loaded" << endl;
		return 0;
	}

	//calculate file size
	if (file.good())
	{
		file.seekg(0, std::ios::end);
		unsigned long len = file.tellg();
		file.seekg(std::ios::beg);
		if (len == 0)
		{
			std::cout << "file has no contents" << std::endl;
			return 0;
		}
		fileContents.resize(len);
		file.read(&fileContents[0], len);
		file.close();
		GLuint program = loadShaderFromMemory(fileContents.c_str(), shaderType);
		return program;
	}

	return 0;
}

bool checkForCompilerErrors(GLuint shaderProgram)
{
	GLint ifCompiled = 0;
	glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &ifCompiled);
	if (ifCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

		//the maxLength included the null character
		string infoLog;
		infoLog.resize(maxLength);
		glGetShaderInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);

		cout << "shader not compiled" << infoLog << endl;

		//we dont need the shader anymore 
		glDeleteShader(shaderProgram);
		return true;
	}
	return false;
}