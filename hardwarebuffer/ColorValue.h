#pragma once

#include <memory>
namespace SRE {

	class ColorValue {
	public:
		typedef std::shared_ptr<ColorValue> ptr;
	public:
		ColorValue(float r, float g, float b, float a)
		{
			_r = r;
			_g = g;
			_b = b;
			_a = a;
		}
		ColorValue()
		{
			_r = 0.0;
			_g = 0.0;
			_b = 0.0;
			_a = 0.0;
		}
	public:
		float r() const;		

		float g() const;

		float b() const;

		float a() const;

		/** Retrieves colour as RGBA.
		*/
		unsigned int asRGBA(void) const;

		/** Retrieves colour as ARGB.
		*/
		unsigned int asARGB(void) const;

		/** Retrieves colour as BGRA.
		*/
		unsigned int asBGRA(void) const;

		/** Retrieves colours as ABGR */
		unsigned int asABGR(void) const;

		/** Sets colour as RGBA.
		*/
		void setRGBA(const unsigned int val);

		/** Sets colour as ARGB.
		*/
		void setARGB(const unsigned int val);

		/** Sets colour as BGRA.
		*/
		void setBGRA(const unsigned int val);

		/** Sets colour as ABGR.
		*/
		void setABGR(const unsigned int val);

		/** Clamps colour value to the range [0, 1].
		*/
		void saturate(void);

		/** As saturate, except that this colour value is unaffected and
		the saturated colour value is returned as a copy. */
		ColorValue::ptr saturateCopy(void) const;

		/** Set a colour value from Hue, Saturation and Brightness.
		@param hue Hue value, scaled to the [0,1] range as opposed to the 0-360
		@param saturation Saturation level, [0,1]
		@param brightness Brightness level, [0,1]
		*/
		void setHSB(double hue, double saturation, double brightness);

		/** Convert the current colour to Hue, Saturation and Brightness values.
		@param hue Output hue value, scaled to the [0,1] range as opposed to the 0-360
		@param saturation Output saturation level, [0,1]
		@param brightness Output brightness level, [0,1]
		*/
		void getHSB(double* hue, double* saturation, double* brightness) const;

	protected:
		float _r, _g, _b, _a;
	};
}