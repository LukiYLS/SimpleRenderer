#pragma once
#include <GL/glew.h>
#include <memory>
#include <string>
#include <vector>
#include "Image.h"
#include "hardwarebuffer/PixelBox.h"
#include "hardwarebuffer/HardwareTextureBuffer.h"

namespace SRE {
	enum TextureType
	{	
		TEX_TYPE_1D = 1,	
		TEX_TYPE_2D = 2,	
		TEX_TYPE_3D = 3,	
		TEX_TYPE_CUBE_MAP = 4,	
		TEX_TYPE_2D_ARRAY = 5,	
		TEX_TYPE_2D_RECT = 6
	};
	enum TextureFiltering
	{
		TEXTURE_FILTER_MAG_NEAREST = 0,
		TEXTURE_FILTER_MAG_BILINEAR,
		TEXTURE_FILTER_MIN_NEAREST, 
		TEXTURE_FILTER_MIN_BILINEAR, 
		TEXTURE_FILTER_MIN_NEAREST_MIPMAP, 
		TEXTURE_FILTER_MIN_BILINEAR_MIPMAP,
		TEXTURE_FILTER_MIN_TRILINEAR, 
	};
	class Texture 
		{
	public:
		typedef std::shared_ptr<Texture> ptr;
		typedef std::vector<HardwareTextureBuffer::ptr> TextureBufferVector;
	public:
		Texture(const std::string name,TextureType type = TEX_TYPE_2D);
		//Texture(GLenum textureTarget, const std::string& fileName);
		~Texture();
	public:		
		
		virtual bool gtNumMipmaps(void) const { return _numMipMaps; }		
		virtual void setNumMipmaps(bool num) { _numMipMaps = num; }		
		void setTextureType(TextureType type) { _textureType = type; }
		TextureType getTextureType(void) const { return _textureType; }
		HardwareBuffer::Usage getUsage()const { return _usage; }
		void setUsage(HardwareBuffer::Usage usage) { _usage = usage; }
		unsigned int getWidth()const { return _width; }
		void setWidth(unsigned int width) { _width = width; }
		unsigned int getHeight()const { return _height; }
		void setHeight(unsigned int height) { _height = height; }		
		unsigned int getDepth()const { return _depth; }
		void setDepth(unsigned int depth) { _depth = depth; }
			
		PixelFormat getFromat()const { return _pixelFormat; }

		void bindTextureUnit(unsigned int unit);

		GLenum getTextureTarget()const;
		size_t getNumFaces()const { return _textureType == TEX_TYPE_CUBE_MAP ? 6 : 1; }
		size_t calculateSize()const;
		bool hasAlpha(void) const;
		
		void loadImage(Image::ptr image);
		void loadImages(std::vector<Image::ptr> images);
		void upLoad();
		HardwareTextureBuffer::ptr getBuffer(size_t face, size_t mipmap);
	protected:
		
		void createInternalResources();
		void freeInternalResources();
		

		std::string _name;
		unsigned int _numMipMaps;
		PixelFormat _pixelFormat;
		TextureBufferVector _surface_list;
		std::vector<Image::ptr> _image_list;
		unsigned int  _width,_height, _depth;
		HardwareBuffer::Usage _usage;
		GLuint _textureID; // Texture name
		GLuint _sampler; // Sampler name
		bool _isAlpha;
		bool _autoGenerateMipMap;
		TextureType _textureType;
		bool _resourceCreated;
	};
}


