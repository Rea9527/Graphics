

#include "shaderProgram.h"

#include <fstream>
#include <sstream>


namespace GLSLShaderInfo {
	struct shader_file_extension {
		const char* ext;
		GLSLShader::ShaderType type;
	};

	struct shader_file_extension extensions[] = {
		{".vs", GLSLShader::VERTEX},
		{".tcs", GLSLShader::TESS_CONTROL},
		{".tes", GLSLShader::TESS_EVALUATION},
		{".gs", GLSLShader::GEOMETRY},
		{".fs", GLSLShader::FRAGMENT},
		{".cs", GLSLShader::COMPUTE}
	};
}


ShaderProgram::ShaderProgram() : handle(0), linked(false) {}

ShaderProgram::~ShaderProgram() {
	// todo
}

// get the shader type and then compile shader using filename and type
void ShaderProgram::compileShader(const char* filename) {
	int ext_num = sizeof(GLSLShaderInfo::extensions) / sizeof(GLSLShaderInfo::shader_file_extension);

	string ext = this->getExtension(filename);
	// default shader type: vertex
	GLSLShader::ShaderType type = GLSLShader::VERTEX;
	bool match_found = false;

	for (int i = 0; i < ext_num; i++) {

		if (ext == GLSLShaderInfo::extensions->ext) {
			type = GLSLShaderInfo::extensions->type;
			match_found = true;
			break;
		}
	}

	if (!match_found) {
		string err = "Filename format error or type " + ext + " not exists.";
		throw ShaderProgramException("Compiling shader error: " + err);
	}

	this->compileShader(filename, type);

}

// Get shader code by filename and shader type, then compile shader using filename and type.
void ShaderProgram::compileShader(const char* filename, GLSLShader::ShaderType type) {

	if (!fileExists(filename)) {
		string err = string("File: ") + filename + " not exists.";
		throw ShaderProgramException(err);
	}

	if (this->handle <= 0) {
		this->handle = glCreateProgram();
		if (handle == 0) {
			throw ShaderProgramException("Unable to create shader program.");
		}
	}

	ifstream shader_file(filename, ios::in);
	if (!shader_file) {
		string err = string("Unable to open file ") + filename;
		throw ShaderProgramException(err);
	}

	stringstream ss;
	ss << shader_file.rdbuf();
	shader_file.close();

	this->compileShader(ss.str(), type, filename);
}

// Compile shader using shader code
void ShaderProgram::compileShader(const string &code, GLSLShader::ShaderType type, const char* filename) {

	if (this->handle <= 0) {
		this->handle = glCreateProgram();
		if (handle == 0) {
			throw ShaderProgramException("Unable to create shader program.");
		}
	}

	GLuint shader_handle = glCreateShader(type);
	const GLchar* c_code = code.c_str();
	glShaderSource(shader_handle, 1, &c_code, NULL);

	glCompileShader(shader_handle);
	// Get shader create error
	int result;
	glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		// compile failed
		int length = 0;
		string log_string;
		glGetShaderiv(shader_handle, GL_INFO_LOG_LENGTH, &length);
		if (length > 0) {
			char* c_log = new char[length];
			int written = 0;
			glGetShaderInfoLog(shader_handle, length, &written, c_log);
			log_string = c_log;
			delete[] c_log;
		}

		string err;
		if (filename) {
			err = string(filename) + " : shader compilation failed.\n";
		}
		else {
			err = "Shader compilation failed.\n";
		}
		err += log_string;
		throw ShaderProgramException(err);
	}
	else {
		glAttachShader(this->handle, shader_handle);
	}
}

void ShaderProgram::link() {
	if (this->linked) return;

	if (this->handle <= 0) throw ShaderProgramException("Program has not been created.");

	glLinkProgram(this->handle);

	int status = 0;
	glGetShaderiv(this->handle, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {

	}
}
