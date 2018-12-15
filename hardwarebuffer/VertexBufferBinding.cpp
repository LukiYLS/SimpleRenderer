#include "VertexBufferBinding.h"


namespace SRE {



	void VertexBufferBinding::setBinding(unsigned short index, const HardwareVertexBuffer::ptr buffer)
	{
		_bindingMap[index] = buffer;
	}
	void VertexBufferBinding::unsetBinding(unsigned short index)
	{
		VertexBufferBindingMap::iterator iter = _bindingMap.find(index);
		if (iter == _bindingMap.end())
		{
			//没找到
		}
		_bindingMap.erase(iter);
	}
	void VertexBufferBinding::unsetAllBindings(void)
	{
		_bindingMap.clear();
		_highIndex = 0;
	}
	const VertexBufferBindingMap& VertexBufferBinding::getBindings(void) const
	{
		return _bindingMap;
	}
	const HardwareVertexBuffer::ptr& VertexBufferBinding::getBuffer(unsigned short index) const
	{
		VertexBufferBindingMap::const_iterator iter = _bindingMap.find(index);
		if (iter == _bindingMap.end())
		{
			//没找到
		}
		return iter->second;

	}
	bool VertexBufferBinding::isBufferBound(unsigned short index) const
	{
		return _bindingMap.find(index) != _bindingMap.end();
	}
	unsigned int VertexBufferBinding::getBufferCount(void) const
	{
		return _bindingMap.size();
	}
	unsigned short VertexBufferBinding::getNextIndex(void) const
	{
		return _highIndex++;
	}
	unsigned short VertexBufferBinding::getLastBoundIndex(void) const
	{
		return _bindingMap.empty() ? 0 : _bindingMap.rbegin()->first + 1;
	}
}