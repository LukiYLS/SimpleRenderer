#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

namespace SRE {


	Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		std::ifstream gShaderFile;
		
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			
			vShaderFile.close();
			fShaderFile.close();
			
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
			
			if (geometryPath != nullptr)
			{
				gShaderFile.open(geometryPath);
				std::stringstream gShaderStream;
				gShaderStream << gShaderFile.rdbuf();
				gShaderFile.close();
				geometryCode = gShaderStream.str();
			}
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char * fShaderCode = fragmentCode.c_str();

		unsigned int vertex, fragment;
		
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
		
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");
		
		unsigned int geometry;
		if (geometryPath != nullptr)
		{
			const char * gShaderCode = geometryCode.c_str();
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry, 1, &gShaderCode, NULL);
			glCompileShader(geometry);
			checkCompileErrors(geometry, "GEOMETRY");
		}
		
		_shaderID = glCreateProgram();
		glAttachShader(_shaderID, vertex);
		glAttachShader(_shaderID, fragment);
		if (geometryPath != nullptr)
			glAttachShader(_shaderID, geometry);
		glLinkProgram(_shaderID);
		checkCompileErrors(_shaderID, "PROGRAM");
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		if (geometryPath != nullptr)
			glDeleteShader(geometry);
	}


	void Shader::load(const char* vertexStr, const char* fragmentStr, const char* geometryStr)
	{
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexStr, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentStr, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		unsigned int geometry;
		if (geometryStr != nullptr)
		{			
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry, 1, &geometryStr, NULL);
			glCompileShader(geometry);
			checkCompileErrors(geometry, "GEOMETRY");
		}

		_shaderID = glCreateProgram();
		glAttachShader(_shaderID, vertex);
		glAttachShader(_shaderID, fragment);
		if (geometryStr != nullptr)
			glAttachShader(_shaderID, geometry);
		glLinkProgram(_shaderID);
		checkCompileErrors(_shaderID, "PROGRAM");
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		if (geometryStr != nullptr)
			glDeleteShader(geometry);
	}
	void Shader::use()
	{
		glUseProgram(_shaderID);
	}
	void Shader::unUse()
	{
		glUseProgram(0);
	}
	void Shader::setBool(const char* name, bool value)const
	{
		glUniform1i(glGetUniformLocation(_shaderID, name), (int)value);
	}
	void Shader::setInt(const char* name, int value)const
	{
		glUniform1i(glGetUniformLocation(_shaderID, name), value);
	}
	void Shader::setFloat(const char* name, float value)const
	{
		glUniform1f(glGetUniformLocation(_shaderID, name), value);
	}
	void Shader::setVec2(const char* name, const Vector2D& value)const
	{
		glUniform2f(glGetUniformLocation(_shaderID, name), value.x, value.y);
	}
	void Shader::setVec3(const char* name, const Vector3D& value)const
	{		
		glUniform3f(glGetUniformLocation(_shaderID, name), value.x,value.y,value.z);
	}
	void Shader::setVec4(const char* name, const Vector4D& value)const
	{
		glUniform4f(glGetUniformLocation(_shaderID, name), value.x, value.y, value.z, value.w);
	}	
	void Shader::setMat3(const char* name, const Matrix3D& value)const
	{
		GLfloat matrix_gl[9];
		for (unsigned int i = 0; i < 3; i++)	
			for (unsigned int j = 0; j < 3; j++)
			{				
				matrix_gl[i * 3 + j] = value[i][j];
			}			
		glUniformMatrix3fv(glGetUniformLocation(_shaderID, name), 1, GL_FALSE, matrix_gl);
	}
	void Shader::addUniform(Uniform uniform)
	{
		
	}
	void Shader::getUnifrom(unsigned int index)
	{

	}
	void Shader::getUniform(const char* name)
	{

	}
	void Shader::uplaod()
	{
		for (auto uniform : _uniforms)
		{
			/*const char* name = uniform.getName();
			AnyValue value = uniform.getValue();
			ValueType type = uniform.getType();*/
			uploadUniform(uniform);
		}
	}
	void Shader::setMat4(const char* name, const Matrix4D& value)const
	{		
		GLfloat matrix_gl[16];
		for (unsigned int i = 0; i < 16; i++)
		{
			matrix_gl[i] = value[i];
		}
		glUniformMatrix4fv(glGetUniformLocation(_shaderID, name), 1, GL_FALSE, matrix_gl);//����glsl���Զ�ת�ã�GL_TRUE����ת��
	}	

	void Shader::uploadUniform(Uniform uniform)
	{
		const char* name = uniform.getName();
	
		ValueType type = uniform.getType();

		switch (type)
		{
		case FLOAT:
		{
			float value1 = uniform.getValue();
			setFloat(name, value1);
			break;
		}
		case FLOAT_VEC2:
		case DOUBLE_VEC2:
		{
			Vector2D value2 = uniform.getValue();
			setVec2(name, value2);
			break;
		}
		case FLOAT_VEC3:
		case DOUBLE_VEC3:
		{
			Vector3D value3 = uniform.getValue();
			setVec3(name, value3);
			break;
		}
		case FLOAT_VEC4:
		case DOUBLE_VEC4:
		{
			Vector4D value4 = uniform.getValue();
			setVec4(name, value4);
			break;
		}
		
		case FLOAT_MAT3:
		case DOUBLE_MAT3:
		{
			Matrix3D matrix3 = uniform.getValue();
			setMat3(name, matrix3);
			break;
		}
		case FLOAT_MAT4:
		case DOUBLE_MAT4:
		{
			Matrix4D matrix4 = uniform.getValue();
			setMat4(name, matrix4);
			break;
		}
		default:
			break;
		}
	}
	void Shader::checkCompileErrors(GLuint shader, const char* type)
	{
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
}