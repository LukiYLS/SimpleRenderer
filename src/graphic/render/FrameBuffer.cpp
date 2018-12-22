#include "FrameBuffer.h"
namespace SRE {

	GLenum FrameBuffer::getGLtype(BufferType type)
	{
		switch (type) {
		case DepthBuffer:
			return GL_DEPTH_COMPONENT;
			break;
		case ColorBuffer:
			return GL_RGB;
			break;
		case StencilBuffer:
			return GL_STENCIL_COMPONENTS;
			break;
		default:
			break;
		}
	}
	GLenum FrameBuffer::getGLAttach(BufferType type)
	{
		switch (type) {
		case DepthBuffer:
			return GL_DEPTH_ATTACHMENT;
			break;
		case ColorBuffer:
			return GL_COLOR_ATTACHMENT0;
			break;
		case StencilBuffer:
			return GL_STENCIL_ATTACHMENT;
			break;
		default:
			break;
		}
	}
	FrameBuffer2D::FrameBuffer2D(unsigned int width, unsigned int height, FrameBuffer::BufferType type)
		:_width(width),
		_height(height)
	{
		glGenFramebuffers(1, &_fbo);
		glGenTextures(1, &_texture);
		glBindTexture(GL_TEXTURE_2D, _texture);

		GLenum gltype = FrameBuffer::getGLtype(type);
		glTexImage2D(GL_TEXTURE_2D, 0, gltype, width, height, 0, gltype, GL_FLOAT, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
		glFramebufferTexture2D(GL_FRAMEBUFFER, FrameBuffer::getGLAttach(type), GL_TEXTURE_2D, _texture, 0);

		_width = width;
		_height = height;
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void FrameBuffer2D::bindForWriting(bool isFullViewPort)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
		if (isFullViewPort)glViewport(0, 0, _width, _height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void FrameBuffer2D::bindForReading(unsigned int units)
	{
		glActiveTexture(GL_TEXTURE0 + units);
		glBindTexture(GL_TEXTURE_2D, _texture);
	}

	FrameBufferCube::FrameBufferCube(unsigned int width, unsigned int height, FrameBuffer::BufferType type)
		:_width(width),
		_height(height)
	{
		glGenFramebuffers(1, &_fbo); 
		glGenTextures(1, &_texture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _texture);
		GLenum gltype = FrameBuffer::getGLtype(type);
		for (unsigned int i = 0; i < 6; ++i)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);		
		

		float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BORDER_COLOR, borderColor);
		glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _texture, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
	void FrameBufferCube::bindForWriting(bool isFullViewPort)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
		if (isFullViewPort)glViewport(0, 0, _width, _height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void FrameBufferCube::bindForReading(unsigned int units)
	{
		glActiveTexture(GL_TEXTURE0 + units);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _texture);
	}

	
}