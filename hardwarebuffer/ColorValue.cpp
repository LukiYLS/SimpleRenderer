#include "ColorValue.h"
#include <algorithm>
namespace SRE {

	float ColorValue::r() const
	{
		return _r;
	}

	float ColorValue::g() const
	{
		return _g;
	}

	float ColorValue::b() const
	{
		return _b;
	}

	float ColorValue::a() const
	{
		return _a;
	}
	unsigned int ColorValue::asRGBA(void) const
	{
		unsigned char val8;
		unsigned int val32 = 0;

		// Convert to 32bit pattern
		// (RGBA = 8888)

		// Red
		val8 = static_cast<unsigned char>(_r * 255);
		val32 = val8 << 24;

		// Green
		val8 = static_cast<unsigned char>(_g * 255);
		val32 += val8 << 16;

		// Blue
		val8 = static_cast<unsigned char>(_b * 255);
		val32 += val8 << 8;

		// Alpha
		val8 = static_cast<unsigned char>(_a * 255);
		val32 += val8;

		return val32;
	}

	unsigned int ColorValue::asARGB(void) const
	{
		unsigned char val8;
		unsigned int val32 = 0;

		// Convert to 32bit pattern
		// (ARGB = 8888)

		// Alpha
		val8 = static_cast<unsigned char>(_a * 255);
		val32 = val8 << 24;

		// Red
		val8 = static_cast<unsigned char>(_r * 255);
		val32 += val8 << 16;

		// Green
		val8 = static_cast<unsigned char>(_g * 255);
		val32 += val8 << 8;

		// Blue
		val8 = static_cast<unsigned char>(_b * 255);
		val32 += val8;


		return val32;
	}

	unsigned int ColorValue::asBGRA(void) const
	{
		unsigned char val8;
		unsigned int val32 = 0;

		// Convert to 32bit pattern
		// (ARGB = 8888)

		// Blue
		val8 = static_cast<unsigned char>(_b * 255);
		val32 = val8 << 24;

		// Green
		val8 = static_cast<unsigned char>(_g * 255);
		val32 += val8 << 16;

		// Red
		val8 = static_cast<unsigned char>(_r * 255);
		val32 += val8 << 8;

		// Alpha
		val8 = static_cast<unsigned char>(_a * 255);
		val32 += val8;
		return val32;
	}

	unsigned int ColorValue::asABGR(void) const
	{
		unsigned char val8;
		unsigned int val32 = 0;

		// Convert to 32bit pattern
		// (ABRG = 8888)

		// Alpha
		val8 = static_cast<unsigned char>(_a * 255);
		val32 = val8 << 24;

		// Blue
		val8 = static_cast<unsigned char>(_b * 255);
		val32 += val8 << 16;

		// Green
		val8 = static_cast<unsigned char>(_g * 255);
		val32 += val8 << 8;

		// Red
		val8 = static_cast<unsigned char>(_r * 255);
		val32 += val8;


		return val32;
	}

	void ColorValue::setRGBA(const unsigned int val)
	{

		unsigned int val32 = val;

		// Convert from 32bit pattern
		// (RGBA = 8888)

		// Red
		_r = ((val32 >> 24) & 0xFF) / 255.0f;

		// Green
		_g = ((val32 >> 16) & 0xFF) / 255.0f;

		// Blue
		_b = ((val32 >> 8) & 0xFF) / 255.0f;

		// Alpha
		_a = (val32 & 0xFF) / 255.0f;
	}

	void ColorValue::setARGB(const unsigned int val)
	{
		unsigned int val32 = val;

		// Convert from 32bit pattern
		// (ARGB = 8888)

		// Alpha
		_a = ((val32 >> 24) & 0xFF) / 255.0f;

		// Red
		_r = ((val32 >> 16) & 0xFF) / 255.0f;

		// Green
		_g = ((val32 >> 8) & 0xFF) / 255.0f;

		// Blue
		_b = (val32 & 0xFF) / 255.0f;
	}

	void ColorValue::setBGRA(const unsigned int val)
	{
		unsigned int val32 = val;

		// Convert from 32bit pattern
		// (ARGB = 8888)

		// Blue
		_b = ((val32 >> 24) & 0xFF) / 255.0f;

		// Green
		_g = ((val32 >> 16) & 0xFF) / 255.0f;

		// Red
		_r = ((val32 >> 8) & 0xFF) / 255.0f;

		// Alpha
		_a = (val32 & 0xFF) / 255.0f;
	}

	void ColorValue::setABGR(const unsigned int val)
	{
		unsigned int val32 = val;

		// Convert from 32bit pattern
		// (ABGR = 8888)

		// Alpha
		_a = ((val32 >> 24) & 0xFF) / 255.0f;

		// Blue
		_b = ((val32 >> 16) & 0xFF) / 255.0f;

		// Green
		_g = ((val32 >> 8) & 0xFF) / 255.0f;

		// Red
		_r = (val32 & 0xFF) / 255.0f;
	}

	void ColorValue::saturate(void)
	{
		if (_r < 0)
			_r = 0;
		else if (_r > 1)
			_r = 1;

		if (_g < 0)
			_g = 0;
		else if (_g > 1)
			_g = 1;

		if (_b < 0)
			_b = 0;
		else if (_b > 1)
			_b = 1;

		if (_a < 0)
			_a = 0;
		else if (_a > 1)
			_a = 1;
	}

	ColorValue::ptr ColorValue::saturateCopy(void) const
	{
		ColorValue *ret = new ColorValue();
		ret = const_cast<ColorValue*>(this);
		ret->saturate();
		return ColorValue::ptr(ret);
	}

	void ColorValue::setHSB(double hue, double saturation, double brightness)
	{
		// wrap hue
		if (hue > 1.0f)
		{
			hue -= (int)hue;
		}
		else if (hue < 0.0f)
		{
			hue += (int)hue + 1;
		}
		// clamp saturation / brightness
		saturation = std::min(saturation, (double)1.0);
		saturation = std::max(saturation, (double)0.0);
		brightness = std::min(brightness, (double)1.0);
		brightness = std::max(brightness, (double)0.0);

		if (brightness == 0.0f)
		{
			// early exit, this has to be black
			_r = _g = _b = 0.0f;
			return;
		}

		if (saturation == 0.0f)
		{
			// early exit, this has to be grey

			_r = _g = _b = brightness;
			return;
		}


		double hueDomain = hue * 6.0f;
		if (hueDomain >= 6.0f)
		{
			// wrap around, and allow mathematical errors
			hueDomain = 0.0f;
		}
		unsigned short domain = (unsigned short)hueDomain;
		double f1 = brightness * (1 - saturation);
		double f2 = brightness * (1 - saturation * (hueDomain - domain));
		double f3 = brightness * (1 - saturation * (1 - (hueDomain - domain)));

		switch (domain)
		{
		case 0:
			// red domain; green ascends
			_r = brightness;
			_g = f3;
			_b = f1;
			break;
		case 1:
			// yellow domain; red descends
			_r = f2;
			_g = brightness;
			_b = f1;
			break;
		case 2:
			// green domain; blue ascends
			_r = f1;
			_g = brightness;
			_b = f3;
			break;
		case 3:
			// cyan domain; green descends
			_r = f1;
			_g = f2;
			_b = brightness;
			break;
		case 4:
			// blue domain; red ascends
			_r = f3;
			_g = f1;
			_b = brightness;
			break;
		case 5:
			// magenta domain; blue descends
			_r = brightness;
			_g = f1;
			_b = f2;
			break;
		}
	}

	void ColorValue::getHSB(double* hue, double* saturation, double* brightness) const
	{

		double vMin = std::min(_r, std::min(_g, _b));
		double vMax = std::max(_r, std::max(_g, _b));
		double delta = vMax - vMin;

		*brightness = vMax;

		/*if (Math::MathHelper::RealEqual(delta, 0.0f, 1e-6))
		{
			// grey
			*hue = 0;
			*saturation = 0;
		}
		else
		{
			// a colour
			*saturation = delta / vMax;

			double deltaR = (((vMax - _r) / 6.0f) + (delta / 2.0f)) / delta;
			double deltaG = (((vMax - _g) / 6.0f) + (delta / 2.0f)) / delta;
			double deltaB = (((vMax - _b) / 6.0f) + (delta / 2.0f)) / delta;

			if (Math::MathHelper::RealEqual(_r, vMax))
				*hue = deltaB - deltaG;
			else if (Math::MathHelper::RealEqual(_g, vMax))
				*hue = 0.3333333f + deltaR - deltaB;
			else if (Math::MathHelper::RealEqual(_b, vMax))
				*hue = 0.6666667f + deltaG - deltaR;

			if (*hue < 0.0f)
				*hue += 1.0f;
			if (*hue > 1.0f)
				*hue -= 1.0f;
		}*/
	}
}