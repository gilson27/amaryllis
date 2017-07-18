#ifndef SHADER_H
#define SHADER_H

#include <glad\glad.h>
#include <glm\glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader {
public:
	unsigned int ID;

	/**
	Constucter to generate shader
	*/
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr) {
		/**
		Retreive vertex/fragment source code from filePath
		*/
		string vertexCode;
		string fragmentCode;
		string geometryCode;

		ifstream vShaderFile;
		ifstream fShaderFile;
		ifstream gShaderFile;

		/**
		Ensure ifstream can throw exceptions
		*/
		vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		gShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		try {
			/**
			Open files
			*/
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			stringstream vShaderStream, fShaderStream;

			/**
			Read File's buffer content into streams
			*/
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			/**
			Close File handles
			*/
			vShaderFile.close();
			fShaderFile.close();

			/**
			Convert stream to string
			*/
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

			/**
			If geometry shader is present load geometry shader also
			*/
			if (geometryPath != nullptr) {
				gShaderFile.open(geometryPath);
				stringstream gShaderStream;
				gShaderStream << gShaderFile.rdbuf();
				gShaderFile.close();
				geometryCode = gShaderStream.str();
			}
		}
		catch (ifstream::failure e) {
			cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		/**
		Compile shaders
		*/
		unsigned int vertex, fragment;

		/**
		Vertex Shader
		*/
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileError(vertex, "VERTEX");

		/**
		Fragment Shader
		*/
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileError(fragment, "FRAGMENT");

		unsigned int geometry;
		/**
		If geometry shader is given compile geometry shader
		*/
		if (geometryPath != nullptr) {
			const char* gShaderCode = geometryCode.c_str();
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry, 1, &gShaderCode, NULL);
			glCompileShader(geometry);
			checkCompileError(geometry, "GEOMETRY");
		}

		/**
		* Shader Program
		*/
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		if (geometryPath != nullptr) {
			glAttachShader(ID, geometry);
		}
		glLinkProgram(ID);
		checkCompileError(ID, "PROGRAM");

		/**
		Delete the shaders as they are linked to the program now and are no longer required
		*/
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		if (geometryPath != nullptr) {
			glDeleteShader(geometry);
		}
	}

	/**
	Activate the shader
	*/
	void use() {
		glUseProgram(ID);
	}

	/**
	Utiltity Functions
	*/
	void setBool(const string &name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void setInt(const std::string &name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setFloat(const std::string &name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setVec2(const std::string &name, const glm::vec2 &value) const {
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec2(const std::string &name, float x, float y) const {
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}

	void setVec3(const std::string &name, const glm::vec3 &value) const {
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec3(const std::string &name, float x, float y, float z) const {
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}

	void setVec4(const std::string &name, const glm::vec4 &value) const {
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec4(const std::string &name, float x, float y, float z, float w) {
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}

	void setMat2(const std::string &name, const glm::mat2 &mat) const {
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void setMat3(const std::string &name, const glm::mat3 &mat) const {
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void setMat4(const std::string &name, const glm::mat4 &mat) const {
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

private:
	void checkCompileError(GLuint shader, std::string shaderType) {
		GLint success;
		GLchar infoLog[1024];
		if (shaderType != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			cout << "ERROR::SHADER::" << shaderType << "::COMPILE status is: " << infoLog << endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 512, NULL, infoLog);
			cout << "ERROR::SHADER::" << shaderType << "::LINKING status is: " << infoLog << endl;
		}
	}
}
};

#endif