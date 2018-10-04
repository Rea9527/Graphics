

#include "shaderProgram.h"


ShaderProgram::ShaderProgram() { }

ShaderProgram::ShaderProgram(string vertexFilepath, string fragFilepath) {
	ifstream vertexFile, fragFile;
	vertexFile.open(vertexFilepath.c_str(), ios::in);
	fragFile.open(fragFilepath.c_str(), ios::in);
	stringstream vertexSS, fragSS;
	vertexSS << vertexFile.rdbuf();
	fragSS << fragFile.rdbuf();
	vertexFile.close();
	fragFile.close();

	// get file code
	const GLchar *vertexCode, *fragCode;
	vertexCode = vertexSS.str().c_str();
	fragCode = fragSS.str().c_str();

	// create shader program
	// create vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	if (!vertexShader) {
		fprintf(stderr, "Error when creating vertex shader.\n");
		exit(EXIT_FAILURE);
	}
	glShaderSource(vertexShader, 1, &vertexCode, NULL);
	glCompileShader(vertexShader);
	GLint success;
	GLchar errInfo[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, errInfo);
		fprintf(stderr, "Vertex shader: %s\n", errInfo);
	}
	
	// create fragment shader
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (!fragShader) {
		fprintf(stderr, "Error when creating fragment shader.\n");
		exit(EXIT_FAILURE);
	}
	glShaderSource(fragShader, 1, &vertexCode, NULL);
	glCompileShader(fragShader);
	GLint success;
	GLchar errInfo[512];
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragShader, 512, NULL, errInfo);
		fprintf(stderr, "Fragment shader: %s\n", errInfo);
	}

	// create program
	GLuint programHandle = glCreateProgram();

	
}