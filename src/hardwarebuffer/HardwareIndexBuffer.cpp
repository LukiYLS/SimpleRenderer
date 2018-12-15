#include "HardwareIndexBuffer.h"
#include "HardwareBufferManager.h"
#include <GL/glew.h>
#include<iostream>
#include <cstring>
namespace SRE {
	HardwareIndexBuffer::HardwareIndexBuffer(IndexType index_type, unsigned int numIndexes, HardwareBuffer::Usage usage, bool useShadowBuffer)
		:_numIndexes(numIndexes),
		_indexType(index_type),
		_usage(usage),
		_useShadowBuffer(useShadowBuffer),
		_lockStart(0),
		_lockSize(0)
	{
		switch (index_type)
		{
		case IT_16BIT:
			_indexSize = sizeof(unsigned short);
			break;
		case IT_32BIT:
			_indexSize = sizeof(unsigned int);
			break;
		}
		_sizeInBytes = _numIndexes * _indexSize;
		if (_useShadowBuffer)
		{
			_data = static_cast<unsigned char*>(malloc(_sizeInBytes));
		}
		else
		{
			glGenBuffersARB(1, &_indexBufferID);
			if (!_indexBufferID)
			{
				//������������ʾ��ʧ��
			}
		}
	
	}
	HardwareIndexBuffer::~HardwareIndexBuffer()
	{
		if (_useShadowBuffer)
		{
			if (_data)
				free(_data);
		}
	
		{
			glDeleteBuffersARB(1, &_indexBufferID);
			
		}
	}
	/**
	* lock all
	**/
	void* HardwareIndexBuffer::lock(LockOptions options)
	{
		return this->lock(0, _sizeInBytes, options);
	}

	/**
	* lock part
	**/
	void* HardwareIndexBuffer::lock(unsigned int offset, unsigned int length, LockOptions options)
	{
		if (isLocked())
		{
			//�����ٴ�����,����
		}
		void *ret = 0;
		if ((length + offset) > _sizeInBytes)
		{
			//����Խ��
		}
		else if (_useShadowBuffer)
		{
			//if (options_ != HBL_READ_ONLY)
			//	_memory_need_update_to_video_card = true;
			ret = _data + offset;
		}
		else
		{
			HardwareBufferManager* hdbm = HardwareBufferManager::getSingletonPtr();
			if (hdbm->getMapBufferThreshold() > length)
			{
				ret = hdbm->allocate((unsigned int)length);
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
			if (!ret)
			{
				GLenum access = 0;
				glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, _indexBufferID);
				if (options == HBL_DISCARD)
				{
					//����ԭ�����������
					glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, _sizeInBytes, 0, HardwareBufferManager::getGLUsege(_usage));

				}
				//������ض�
				if (_usage & HBU_WRITE_ONLY)
					access = GL_WRITE_ONLY_ARB;
				else if (options == HBL_READ_ONLY)
					access = GL_READ_ONLY_ARB;
				else
					access = GL_READ_WRITE_ARB;

				void *buffer = glMapBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, access);
				if (buffer == 0)
				{
					//����
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


	void HardwareIndexBuffer::unlock(void)
	{
		if (_isLocked == false)
		{
			//assert()
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
				glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, _indexBufferID);
				glUnmapBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB);//�ͷŻ�����������CPU�ռ�Ĺ�ϵ
			}		
		}
		_isLocked = false;
	}

	void HardwareIndexBuffer::upload(void)
	{
		if (_useShadowBuffer)
		{
			glGenBuffersARB(1, &_indexBufferID);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, _indexBufferID);
			writeData(_lockStart, _lockSize, _data, _lockStart == 0 && _lockSize == _sizeInBytes);
			free(_data);
			_data = 0;
			_useShadowBuffer = false;

		}
	}

	/**
	* �ض�����
	**/
	void HardwareIndexBuffer::readData(unsigned int offset, unsigned int length, void* dest)
	{
		if (_useShadowBuffer)
		{
			memcpy(dest, _data + offset, length);
		}
		else
		{
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, _indexBufferID);
			glGetBufferSubDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, offset, length, dest);
		}
	}	
	/**
	* write
	**/
	void HardwareIndexBuffer::writeData(unsigned int offset, unsigned int length, const void* source, bool discardWholeBuffer)
	{
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, _indexBufferID);

		//ȫ���ύ
		if (offset == 0 && length == _sizeInBytes)
		{
			glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, _sizeInBytes, source, HardwareBufferManager::getGLUsege(_usage));
		}
		else //�����ύ
		{
			glBufferSubDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, offset, length, source);
		}
	}	

}