#include "StringHelper.h"
#include <sstream>
using std::stringstream;
using namespace Math;
namespace SRE {

	string StringHelper::toString(float val, unsigned short precision /* = 6 */, unsigned short width /* = 0 */, char fill /* = ' ' */, std::ios::fmtflags flags /* = std::ios::fmtflags(0) */)
	{
		stringstream stream;
		stream.precision(precision);
		stream.width(width);
		stream.fill(fill);
		stream.setf(flags);
		stream << val;
		return stream.str();
	}
	string StringHelper::toString(double val, unsigned short precision /* = 6 */, unsigned short width /* = 0 */, char fill /* = ' ' */, std::ios::fmtflags flags /* = std::ios::fmtflags(0) */)
	{
		stringstream stream;
		stream.precision(precision);
		stream.width(width);
		stream.fill(fill);
		stream.setf(flags);
		stream << val;
		return stream.str();
	}

	string StringHelper::toString(unsigned int val, unsigned short width /* = 0 */, char fill /* = ' ' */, std::ios::fmtflags flags /* = std::ios::fmtflags(0) */)
	{
		stringstream stream;		
		stream.width(width);
		stream.fill(fill);
		stream.setf(flags);
		stream << val;
		return stream.str();
	}

	string StringHelper::toString(unsigned long val, unsigned short width /* = 0 */, char fill /* = ' ' */, std::ios::fmtflags flags /* = std::ios::fmtflags(0) */)
	{
		stringstream stream;
		stream.width(width);
		stream.fill(fill);
		stream.setf(flags);
		stream << val;
		return stream.str();
	}

	string StringHelper::toString(const Math::Vector2D& val)
	{
		stringstream stream;
		stream << val.x << " " << val.y;
		return stream.str();
	}
	string StringHelper::toString(const Math::Vector3D& val)
	{
		stringstream stream;
		stream << val.x << " " << val.y << " " << val.z;
		return stream.str();
	}
	string StringHelper::toString(const Math::Vector4D& val)
	{
		stringstream stream;
		stream << val.x << " " << val.y << " " << val.z << " " << val.w;
		return stream.str();
	}
}