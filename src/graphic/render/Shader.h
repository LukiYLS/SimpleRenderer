#pragma once

#include <GL/glew.h>
#include <vector>
#include <memory>
#include "Uniform.h"
#include "math/Vector3D.h"
#include "math/Vector4D.h"
#include "math/Matrix3D.h"
#include "math/Matrix4D.h"
using namespace Math;
namespace SRE {
	class Shader {
	public:
		typedef std::shared_ptr<Shader> ptr;
		Shader() = default;
		Shader(uint32_t shaderID):_shaderID(shaderID){}
		Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
		
		Shader(const Shader& shader) {}
		~Shader() {}
	public:
		void load(const char* vertexStr, const char* fragmentStr, const char* geometryStr = nullptr);
		void use();
		void unUse();
		void setBool(const char* name, bool value)const;
		void setInt(const char* name, int value)const;
		void setFloat(const char* name, float value)const;
		void setVec2(const char* name, const Vector2D& value)const;
		void setVec3(const char* name, const Vector3D& value)const;
		void setVec4(const char* name, const Vector4D& value)const;
		//void setMat2(const char* name, const Matrix2D& value)const;
		void setMat3(const char* name, const Matrix3D& value)const;
		void setMat4(const char* name, const Matrix4D& value)const;		

		void addUniform(Uniform uniform);
		void getUnifrom(unsigned int index);
		void getUniform(const char* name);
		void uplaod();
		
	private:
		void checkCompileErrors(GLuint shader, const char* type);
		void uploadUniform(Uniform uniform);
	public:
		unsigned int _shaderID;	
		std::vector<Uniform> _uniforms;
	};
}

