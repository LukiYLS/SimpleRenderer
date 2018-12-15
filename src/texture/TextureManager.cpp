
#include "TextureManager.h"
#include <algorithm>
#include <iostream>
namespace SRE {
	TextureManager* TextureManager::m_inst(0);

	TextureManager* TextureManager::Inst()
	{
		if (!m_inst)
			m_inst = new TextureManager();

		return m_inst;
	}

	TextureManager::TextureManager()
	{
		FreeImage_Initialise();
	}



	TextureManager::~TextureManager()
	{
		FreeImage_DeInitialise();
		unloadAllTextures();
		m_inst = 0;
	}
	Texture::ptr TextureManager::loadTexture(std::string tex_name,const char* file_name, TextureType type)
	{
		if (_textures.find(tex_name) != _textures.end())
			return _textures[tex_name];
		Texture::ptr texture = std::make_shared<Texture>(tex_name, type);
		Image::ptr image = std::make_shared<Image>();
		image->load(file_name);
		texture->loadImage(image);
		texture->upLoad();
		_textures[tex_name] = texture;
		return texture;
	}
	Texture::ptr TextureManager::loadCubeMap(const char* tex_name, std::vector<std::string> files)
	{
		//Texture* texture = new Texture(tex_name, TEX_TYPE_CUBE_MAP);
		std::vector<Image::ptr> images;
		for (auto file : files)
		{
			Image::ptr image = std::make_shared<Image>();
			image->load(file);
			images.push_back(image);
		}

		Texture::ptr texture = std::make_shared<Texture>(tex_name, TEX_TYPE_CUBE_MAP);
		texture->loadImages(images);
		texture->upLoad();
		_textures[tex_name] = texture;
		return texture;
		
	}
	Texture::ptr TextureManager::getTexture(const std::string& tex_name)
	{
		if (_textures.find(tex_name) != _textures.end())
		{
			return _textures[tex_name];
		}
		return NULL;
	}
	/*bool TextureManager::loadTexture(const char* fileName, const std::string texName, GLenum image_format, GLint internal_format, GLint level, GLint border)
	{

		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *dib(0);
		unsigned int width(0), height(0);
		GLuint gl_texID;

		fif = FreeImage_GetFileType(fileName, 0);

		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(fileName);

		if (fif == FIF_UNKNOWN)
			return false;


		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, fileName);

		if (!dib)
			return false;		
		dib = FreeImage_ConvertTo32Bits(dib);
		width = FreeImage_GetWidth(dib);
		height = FreeImage_GetHeight(dib);
		BYTE *pixels = (BYTE*)FreeImage_GetBits(dib);
		if ((pixels == 0) || (width == 0) || (height == 0))
			return false;

		
		int bit_count_ = FreeImage_GetLine(dib)*height;
		int bytespp = FreeImage_GetLine(dib) / FreeImage_GetWidth(dib);
		for (long index = 0; index < bit_count_; index += bytespp)
		{
			unsigned char temp_color_ = pixels[index];
			pixels[index] = pixels[index + 2];
			pixels[index + 2] = temp_color_;
		}	

		if (m_texID.find(texName) != m_texID.end())
			glDeleteTextures(1, &(m_texID[texName]));

		glGenTextures(1, &gl_texID);
		m_texID[texName] = gl_texID;

		glBindTexture(GL_TEXTURE_2D, gl_texID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, width, height,
			border, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		return true;
	}
	bool TextureManager::loadCubeMap(std::vector<const char*> files)
	{
		Texture::ptr cube = std::shared_ptr<Texture>(TEX_TYPE_CUBE_MAP);
		Texture* cube = new Texture("tt",TEX_TYPE_CUBE_MAP);
		glGenTextures(1, &m_cubeMap);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeMap);
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *dib(0);
		unsigned int width(0), height(0);
		for (int i = 0; i < files.size(); i++)
		{
			const char* filename = files[i];
			fif = FreeImage_GetFileType(filename, 0);
			if (fif == FIF_UNKNOWN)
				fif = FreeImage_GetFIFFromFilename(filename);
			if (fif == FIF_UNKNOWN)
				return false;

			if (FreeImage_FIFSupportsReading(fif))
				dib = FreeImage_Load(fif, filename);
			if (!dib)
				return false;
			dib = FreeImage_ConvertTo24Bits(dib);
			BYTE *pixels = (BYTE*)FreeImage_GetBits(dib);
			width = FreeImage_GetWidth(dib);
			height = FreeImage_GetHeight(dib);
			if ((pixels == 0) || (width == 0) || (height == 0))
				return false;
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels
			);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}*/

	bool TextureManager::unloadTexture(const std::string texName)
	{
		bool result(true);
		if (m_texID.find(texName) != m_texID.end())
		{
			glDeleteTextures(1, &(m_texID[texName]));
			m_texID.erase(texName);
		}
		else
		{
			result = false;
		}

		return result;
	}

	bool TextureManager::bindTexture(const std::string texName,int units)
	{
		bool result(true);

		if (m_texID.find(texName) != m_texID.end())
		{
			glActiveTexture(GL_TEXTURE0 + units);
			glBindTexture(GL_TEXTURE_2D, m_texID[texName]);			
		}
		else
			result = false;

		return result;
	}	

	void TextureManager::addTexture(const std::string texName, GLuint textureID)
	{
		if (m_texID.find(texName) != m_texID.end())
			glDeleteTextures(1, &(m_texID[texName]));
		m_texID[texName] = textureID;
	}

	void TextureManager::unloadAllTextures()
	{
		std::map<std::string, GLuint>::iterator it = m_texID.begin();
		while (it != m_texID.end())
			unloadTexture(it->first);

		m_texID.clear();
	}
}
