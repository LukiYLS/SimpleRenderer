#include "PixelBox.h"
#include "PixelUtil.h"
namespace SRE {

	PixelBox::PixelBox(unsigned int width, unsigned int height, unsigned int depth, PixelFormat PixelFormat, void *data)
		:_left(0),
		_right(width),
		_top(0),
		_bottom(height),
		_front(0),
		_back(depth),
		_format(PixelFormat),
		_data(data)
	{
		setConsecutive();
	}

	void PixelBox::setConsecutive()
	{
		_rowPitch = getWidth();
		_slicePitch = getWidth() * getHeight();
	}
	size_t PixelBox::getConsecutive()const
	{
		return PixelUtil::getMemorySize(getWidth(), getHeight(), getDepth(), _format);
	}
	unsigned int PixelBox::getWidth() const
	{
		return (_right - _left);
	}

	unsigned int PixelBox::getHeight() const
	{
		return (_bottom - _top);
	}

	unsigned int PixelBox::getDepth() const
	{
		return (_back - _front);
	}

	bool PixelBox::isContains(PixelBox::ptr box) const
	{
		return (box->getLeft() >= getLeft() && box->getRight() <= getRight() && box->getTop() >= getTop() &&
			box->getBottom() <= getBottom() && box->getFront() >= getFront() && box->getBack() <= getBack());
	}

	void* PixelBox::getData() const
	{
		return _data;
	}

	void PixelBox::setData(void* data)
	{
		if (_data)
		{
			delete[]_data;
		}
		_data = data;
	}

	PixelFormat PixelBox::getPixelFormat() const
	{
		return _format;
	}

	//读取指定位置的像素
	ColorValue::ptr PixelBox::getColourAt(unsigned int x, unsigned int y, unsigned int z)
	{
		//要理解pixelbox的内存布局
		size_t pixel_size = PixelUtil::getNumElemBytes(_format);
		size_t pixel_offset = pixel_size * (z * _slicePitch+ y * _rowPitch + x);

		//像素转换
		return PixelUtil::unpackColor(_format, (unsigned char*)_data + pixel_offset);
	}


	//设置指定位置的像素
	void PixelBox::setColourAt(ColorValue::ptr color_value, unsigned int x, unsigned int y, unsigned int z)
	{
		size_t pixel_size = PixelUtil::getNumElemBytes(_format);
		size_t pixel_offset = pixel_size * (z * _slicePitch + y * _rowPitch + x);
		PixelUtil::packColor(color_value->r(), color_value->g(), color_value->b(), color_value->a(), _format, (unsigned char*)_data + pixel_offset);

	}

	//得到像素框的一个子集(得到的子集 内存不再是连续的）
	PixelBox::ptr PixelBox::getSubVolume(PixelBox::ptr box) const
	{
		if (isContains(box) == false)
		{
			//out of range
			return NULL;
		}
		const size_t elem_size = PixelUtil::getNumElemBytes(_format);

		PixelBox *PixelBox_ = new PixelBox(box->getWidth(), box->getHeight(), box->getDepth(),
			_format, ((unsigned char*)_data) + (box->getLeft() - _left) * elem_size +
			(box->getTop() - _top) * _rowPitch * elem_size +
			(box->getFront() - _front) * _slicePitch * elem_size);

		//funny
		PixelBox_->setRowPitch(_rowPitch);
		PixelBox_->setSlicePitch(_slicePitch);

		PixelBox::ptr retV(PixelBox_);
		return retV;
	}

	void PixelBox::allocateBuffer(size_t _size_in_bytes_)
	{
		if (_data)
			return;
		_data = new unsigned char[_size_in_bytes_];
	}
	void PixelBox::deallocBuffer()
	{
		delete[](unsigned char*)_data;
		_data = 0;
	}
}