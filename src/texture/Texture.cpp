#include "Texture.h"
#include <FreeImage.h>
#include "hardwarebuffer/HardwareTextureBuffer.h"
#include "hardwarebuffer/PixelUtil.h"
#include <iostream>
namespace SRE {


	Texture::Texture(const std::string name, TextureType type)
		:_name(name),
		_width(0),
		_height(0),
		_depth(0),
		_isAlpha(false),
		_textureType(type),
		_resourceCreated(false),
		_autoGenerateMipMap(true)
	{

	}
	//Texture::Texture(GLenum textureTarget, const std::string& fileName)
	//{
	//	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//	FIBITMAP *dib(0);
	//	unsigned int width(0), height(0);
	//	GLuint gl_texID;

	//	fif = FreeImage_GetFileType(fileName.c_str(), 0);

	//	if (fif == FIF_UNKNOWN)
	//		fif = FreeImage_GetFIFFromFilename(fileName.c_str());

	//	if (fif == FIF_UNKNOWN)
	//		return;


	//	if (FreeImage_FIFSupportsReading(fif))
	//		dib = FreeImage_Load(fif, fileName.c_str());

	//	if (!dib)
	//		return;
	//	dib = FreeImage_ConvertTo24Bits(dib);

	//	BYTE *pixels = (BYTE*)FreeImage_GetBits(dib);

	//	width = FreeImage_GetWidth(dib);
	//	height = FreeImage_GetHeight(dib);

	//	if ((pixels == 0) || (width == 0) || (height == 0))
	//		return;

	//	glGenTextures(1, &_textureID);
	//	glBindTexture(textureTarget, _textureID);

	//	glTexParameteri(textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//	glTexParameteri(textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//	glTexParameteri(textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//	glTexParameteri(textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//	glTexImage2D(textureTarget, 0, GL_RGBA, width, height,
	//		0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	//	glBindTexture(textureTarget, 0);
	//	//_textureTarget = textureTarget;
	//}
	Texture::~Texture()
	{
		freeInternalResources();
	}

	size_t Texture::calculateSize()const
	{
		return getNumFaces() * PixelUtil::getMemorySize(_width, _height, _depth, _pixelFormat);
	}
	bool Texture::hasAlpha(void) const
	{
		return PixelUtil::hasAlpha(_pixelFormat);
	}
	void Texture::loadImages(std::vector<Image::ptr> images)
	{
		for (auto image : images)
			loadImage(image);
	}
	void Texture::loadImage(Image::ptr image)
	{
		if (!image)
			return;

		_width = image->width();
		_height = image->height();
		_depth = image->depth();

		_pixelFormat = image->pixelFormat();
		size_t maxMips = PixelUtil::getMaxMipmaps(_width, _height, _depth, _pixelFormat);
		if (_numMipMaps > maxMips)
			_numMipMaps = maxMips;
		if (_autoGenerateMipMap) _numMipMaps = 1;
		unsigned int numMipMaps = _numMipMaps;
		size_t width = _width;
		size_t height = _height;
		size_t depth = _depth;
		for (unsigned short mip = 0; mip < numMipMaps; mip++)
		{
			if (mip == 0)
			{
				_image_list.push_back(image);
				
			}
			else
			{
				_image_list.push_back(Image::rescale(image, width, height));
			}				
			if (width > 1)
				width = width / 2;
			if (height > 1)
				height = height / 2;
			if (depth > 1)
				depth = depth / 2;
		}	
		createInternalResources();

		
	}
	void Texture::upLoad()
	{
		std::cout << "start upload texture: width = " << _width << ",height = " << _height << ",depth = " << _depth << std::endl;
		GLenum target = getTextureTarget();
		_surface_list.clear();

		unsigned int numMipMaps = _numMipMaps;

		for (GLuint face = 0; face < getNumFaces(); face++)
		{
			for (unsigned short mip = 0; mip < numMipMaps; mip++)
			{
				HardwareTextureBuffer::ptr buffer = std::make_shared<HardwareTextureBuffer>(target, _textureID, face, mip, _usage, !_autoGenerateMipMap);
				_surface_list.push_back(buffer);
			}
		}

		size_t faces;
		bool multiImage; // Load from multiple images?
		if (_image_list.size() > 1)
		{
			faces = _image_list.size();
			multiImage = true;
		}
		else
		{
			faces = 1;//_image_list[0]->getNumFaces();
			multiImage = false;
		}
		for (size_t mip = 0; mip < numMipMaps; ++mip)
		{
			for (size_t i = 0; i < faces; ++i)
			{
				std::cout << "upload texture: faces = " << i << std::endl;

				Image::ptr image = _image_list[i];
				PixelBox::ptr box = std::make_shared<PixelBox>(image->width(), image->height(), image->depth(), image->pixelFormat(), image->data());
				HardwareTextureBuffer::ptr buffer = getBuffer(i, mip);
				if(buffer == nullptr)
					std::cout << "null buffer ptr";
				getBuffer(i, mip)->blitFromMemory(box);
			}
		}
		std::cout << "end upload texture" << std::endl;


	}
	/**
	 * 先从显卡中申请内存，upload的时候直接获取属性
	 */
	void Texture::createInternalResources()
	{
		if (_resourceCreated)return;
		GLenum target = getTextureTarget();
		glGenTextures(1, &_textureID);
		glBindTexture(target, _textureID);

		glTexParameteri(target, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, _numMipMaps);
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		unsigned width = _width;
		unsigned height = _height;
		unsigned depth = _depth;
		GLenum format = PixelUtil::getClosestGLInternalFormat(_pixelFormat);
		bool isCompressed = PixelUtil::isCompressed(_pixelFormat);//目前这个判断是有问题的
		if (false)
		{
		}
		else
		{
			for (unsigned short mip = 0; mip < 1; mip++)
			{
				switch (_textureType)
				{
				case TEX_TYPE_1D:
					glTexImage1D(GL_TEXTURE_1D, mip, format,
						width, 0,
						GL_RGBA, GL_UNSIGNED_BYTE, 0);

					break;
				case TEX_TYPE_2D:
					glTexImage2D(GL_TEXTURE_2D, mip, format,
						width, height, 0,
						GL_RGBA, GL_UNSIGNED_BYTE, 0);
					break;
				case TEX_TYPE_2D_ARRAY:
				case TEX_TYPE_3D:
					glTexImage3D(target, mip, format,
						width, height, depth, 0,
						GL_RGBA, GL_UNSIGNED_BYTE, 0);
					break;
				case TEX_TYPE_CUBE_MAP:
					for (int face = 0; face<6; face++) {
						glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, mip, format,
							width, height, 0,
							GL_RGBA, GL_UNSIGNED_BYTE, 0);
					}
					break;
				case TEX_TYPE_2D_RECT:
					break;
				};
				if (_autoGenerateMipMap)break;
				if (width>1)
					width = width / 2;
				if (height>1)
					height = height / 2;
				if (depth>1 && _textureType != TEX_TYPE_2D_ARRAY)
					depth = depth / 2;
			}
		}

		_resourceCreated = true;
	}
	void Texture::freeInternalResources()
	{
		_surface_list.clear();
		glDeleteTextures(1, &_textureID);
	}
	HardwareTextureBuffer::ptr Texture::getBuffer(size_t face, size_t mipmap)
	{
		if (face > getNumFaces())
		{
			return NULL;
		}
		if (mipmap > _numMipMaps)
		{
			return NULL;
		}
		unsigned short numMipMaps = _numMipMaps;
		if (_autoGenerateMipMap)numMipMaps = 0;
		unsigned long idx = face*(numMipMaps + 1) + mipmap;
		return idx < _surface_list.size() ? _surface_list[idx] : NULL;
		
	}
	void Texture::bindTextureUnit(unsigned int unit)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(getTextureTarget(), _textureID);
	}
	//void Texture::setFiltering(int magnification, int minification)
	//{
	//	glBindSampler(0, _sampler);
	//	
	//	if (magnification == TEXTURE_FILTER_MAG_NEAREST)
	//		glSamplerParameteri(_sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//	else if (magnification == TEXTURE_FILTER_MAG_BILINEAR)
	//		glSamplerParameteri(_sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//	
	//	if (minification == TEXTURE_FILTER_MIN_NEAREST)
	//		glSamplerParameteri(_sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//	else if (minification == TEXTURE_FILTER_MIN_BILINEAR)
	//		glSamplerParameteri(_sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//	else if (minification == TEXTURE_FILTER_MIN_NEAREST_MIPMAP)
	//		glSamplerParameteri(_sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	//	else if (minification == TEXTURE_FILTER_MIN_BILINEAR_MIPMAP)
	//		glSamplerParameteri(_sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	//	else if (minification == TEXTURE_FILTER_MIN_TRILINEAR)
	//		glSamplerParameteri(_sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//}

	//void Texture::bindTexture(int unit)
	//{
	//	glActiveTexture(GL_TEXTURE0 + unit);
	//	//glBindTexture(_textureTarget, _textureID);		
	//	glBindSampler(unit, _sampler);
	//}
	GLenum Texture::getTextureTarget()const
	{
		switch (_textureType)
		{
		case TEX_TYPE_1D:
			return GL_TEXTURE_1D;
		case TEX_TYPE_2D:
			return GL_TEXTURE_2D;
		case TEX_TYPE_3D:
			return GL_TEXTURE_3D;
		case TEX_TYPE_CUBE_MAP:
			return GL_TEXTURE_CUBE_MAP;
		case TEX_TYPE_2D_ARRAY:
			return GL_TEXTURE_2D_ARRAY_EXT;
		default:
			return 0;
		};
	}

}