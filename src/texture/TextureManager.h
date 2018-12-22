//**********************************************
//��freeimage��ֲ����
//**********************************************

#pragma once
#include <GL/glew.h>
#include "FreeImage.h"
#include <map>
#include <vector>
#include "Texture.h"
namespace SRE {
	class TextureManager
	{
	public:
		static TextureManager* Inst();
		virtual ~TextureManager();
	
		Texture::ptr loadTexture(std::string tex_name, const char* file_name, TextureType type = TEX_TYPE_2D);
		Texture::ptr loadCubeMap(const char* tex_name, std::vector<std::string> files);
		Texture::ptr getTexture(const std::string& tex_name);
		//bool loadTexture(const char* filename, const std::string texName, GLenum image_format = GL_RGB, GLint internal_format = GL_RGB, GLint level = 0, GLint border = 0);
		//bool loadCubeMap(std::vector<const char*> flies);
		bool unloadTexture(std::string texName);		

		bool bindTexture(const std::string texName, int units);		

		

		void unloadAllTextures();

		void addTexture(const std::string texName, GLuint textureID);

	protected:
		TextureManager();
		TextureManager(const TextureManager& tm);
		TextureManager& operator=(const TextureManager& tm);

		static TextureManager* m_inst;
		std::map<std::string, GLuint> m_texID;
		typedef std::map<std::string, Texture::ptr> TextureMap;
		TextureMap _textures;
		unsigned int m_cubeMap;
	};

}

