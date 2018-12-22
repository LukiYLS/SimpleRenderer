#pragma once
#include "Light.h"

namespace SRE {

	class HemisphereLight : public Light{

	public:

		virtual HemisphereLight* asHemisphereLight() { return this; }

	};
}