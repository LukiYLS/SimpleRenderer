#pragma once
#include <GL/glew.h>
#include <memory>
namespace SRE {

	class FrameBuffer {

	public:
		enum BufferType {
			DepthBuffer,
			ColorBuffer,
			StencilBuffer
		};
		typedef std::shared_ptr<FrameBuffer> ptr;
		virtual void bindForWriting(bool isFullViewPort = true) = 0;
		virtual void bindForReading(unsigned int units) = 0;
		static GLenum getGLtype(BufferType type);
		static GLenum getGLAttach(BufferType);

	protected:
		unsigned int _width;
		unsigned int _height;
		unsigned int _fbo;
		unsigned int _texture;

	};

	class FrameBuffer2D : public FrameBuffer{
	public:

		FrameBuffer2D(unsigned int width, unsigned int height, FrameBuffer::BufferType type);
		void bindForWriting(bool isFullViewPort = true);
		void bindForReading(unsigned int units);
	protected:
		unsigned int _width;
		unsigned int _height;
		unsigned int _fbo;
		unsigned int _texture;
	};
	class FrameBufferCube : public FrameBuffer {

	public:

		FrameBufferCube(unsigned int width, unsigned int height, FrameBuffer::BufferType typ);
		void bindForWriting(bool isFullViewPort = true);
		void bindForReading(unsigned int units);
	protected:
		unsigned int _width;
		unsigned int _height;
		unsigned int _fbo;
		unsigned int _texture;

	};

	/*class FrameBuffer {
	public:
		typedef std::shared_ptr<FrameBuffer> ptr;
		FrameBuffer() = default;
		FrameBuffer(int width, int height);
		~FrameBuffer() = default;

	public:
		bool createFrameBufferWithTexture(int width, int height);
		void bindForReading(int units);		
		void bingForWriting(bool isFullViewPort = true);
		void saveShadowMap();
		void bindFrameBufferTexture(int units, bool isMipMap = true);
	private:
		int _width, _height;
		unsigned int _fbo;
		unsigned int _texture;

	};*/
}


