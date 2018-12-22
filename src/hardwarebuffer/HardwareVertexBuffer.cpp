#include "HardwareVertexBuffer.h"
#include "HardwareBufferManager.h"
#include<iostream>
#include <cstring>
namespace SRE {

	
	HardwareVertexBuffer::HardwareVertexBuffer(unsigned int vertexSize, unsigned int numVertices, HardwareBuffer::Usage usage, bool useShadowBuffer)
	: _numVertices(numVertices),
		_vertexSize(vertexSize),
		_usage(usage),
		_useShadowBuffer(useShadowBuffer),
		_lockSize(0),
		_lockStart(0),
		_isLocked(false)
	{
		//Ӱ�ӻ�������������Ϊ�����ڴ浱����һ�ݶ���ı������ݣ��������Զ�ȡ
		_sizeInBytes = numVertices * vertexSize;
		if (_useShadowBuffer)
		{
			_data = static_cast<unsigned char*>(malloc(_sizeInBytes));
		}
		else
		{
			glGenBuffersARB(1, &_verexBufferID);
			if (!_verexBufferID)
			{
				//������������ʾ��ʧ��
			}
		}
	}

	HardwareVertexBuffer::~HardwareVertexBuffer()
	{
		if (_useShadowBuffer)
		{
			if (_data)
				free(_data);
		}
		glDeleteBuffersARB(1, &_verexBufferID);		
	}
	void* HardwareVertexBuffer::lock(LockOptions options)
	{
		return lock(0, _sizeInBytes, options);
	}
	//why lock,what's mean, because we want read or write 
	void* HardwareVertexBuffer::lock(unsigned int offset, unsigned int length, LockOptions options)
	{
		//
		if (isLocked()){
			//printf("Cannot lock this buffer, it is already locked!");
			//
			return NULL;
		}

		void* ret = 0;

		if ((length + offset) > _sizeInBytes)
		{
			//����Խ��
			return ret;
		}
		else if (_useShadowBuffer)
		{
			if (options != HBL_READ_ONLY)
			{

			}
			ret = _data + offset;
			//
		}
		else
		{
			
			HardwareBufferManager* mgr = HardwareBufferManager::getSingletonPtr();
			//����С�ڴ棬�ȴ��ڴ��������ռ䣬�����ڴ���Ƭ
			if (mgr->getMapBufferThreshold() > length)
			{
				
				ret = mgr->allocate((unsigned int)length);
				if (ret)
				{
					//������Ϣ
					_lockFromPool = true;
					_scrachOffset = offset;
					_scrachSize = length;
					_scrachPtr = ret;
					//�������ֻ����buffer����Ҫ����GPU
					_scratchNeedUpload = (options != HBL_READ_ONLY);

					//��Ҫ�ض����ݣ���ȡ������������
					if (options != HBL_DISCARD)
						readData(offset, length, ret);
				}
			}
			if (!ret)//û������ɹ�����ֱ����GPU����
			{
				GLenum access = 0;
				glBindBufferARB(GL_ARRAY_BUFFER_ARB, _verexBufferID);
				if (options == HBL_DISCARD)
				{
					//����ԭ�����������
					glBufferDataARB(GL_ARRAY_BUFFER_ARB, _sizeInBytes, 0, HardwareBufferManager::getGLUsege(_usage));

				}
				//������ض�
				if (_usage & HBU_WRITE_ONLY)
					access = GL_WRITE_ONLY_ARB;
				else if (options == HBL_READ_ONLY)
					access = GL_READ_ONLY_ARB;
				else
					access = GL_READ_WRITE_ARB;

				void *buffer = glMapBufferARB(GL_ARRAY_BUFFER_ARB, access);
				if (buffer == 0)
				{
					//����
					return ret;
				}

				ret = static_cast<void*>(static_cast<unsigned char *>(buffer) + offset);
				//_locked_to_scratch = false;
			}
			
		}
		_isLocked = true;
		_lockStart = offset;
		_lockSize = length;
		return ret;
	}

	void HardwareVertexBuffer::unlock(void)
	{
		if (_isLocked == false)
		{
			//assert()
			return;
		}
		if (_useShadowBuffer && _isLocked)
		{
			_isLocked = false;
			return;
		}
		else
		{
			//����Ǵ��ڴ滺���������
			if (_lockFromPool)
			{
				if (_scratchNeedUpload)
					writeData(_scrachOffset, _scrachSize, _scrachPtr, _scrachOffset == 0 && _scrachSize == getSizeInBytes());
				//�ͷŻ���				
				HardwareBufferManager* hdbm = HardwareBufferManager::getSingletonPtr();
				hdbm->deallocate(_scrachPtr);
				//_locked_to_scratch = false;
			}
			else
			{
				glBindBufferARB(GL_ARRAY_BUFFER_ARB, _verexBufferID);
				glUnmapBufferARB(GL_ARRAY_BUFFER_ARB);//�ͷŻ�����������CPU�ռ�Ĺ�ϵ
			}
		}
		_isLocked = false;
		
	}

	void HardwareVertexBuffer::readData(unsigned int offset, unsigned int length, void* dest)
	{
		if (_useShadowBuffer)
		{
			memcpy(dest, _data + offset, length);
		}
		else
		{
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, _verexBufferID);
			glGetBufferSubDataARB(GL_ARRAY_BUFFER_ARB, offset, length, dest);
		}
	}
	void HardwareVertexBuffer::writeData(unsigned int offset, unsigned int length, const void* source, bool discardWholeBuffer)
	{
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, _verexBufferID);

		//ȫ���ύ
		if (offset == 0 && length == _sizeInBytes)
		{
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, _sizeInBytes, source, HardwareBufferManager::getGLUsege(_usage));
		}
		else //�����ύ
		{
			glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, offset, length, source);
		}
	}

	void HardwareVertexBuffer::upload(void)
	{
		if (_useShadowBuffer)
		{
			glGenBuffersARB(1, &_verexBufferID);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, _verexBufferID);
			writeData(_lockStart, _lockSize, _data, _lockStart == 0 && _lockSize == _sizeInBytes);
			free(_data);
			_data = 0;			
			_useShadowBuffer = false;			

		}
	}
}