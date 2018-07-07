#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace gengine {
	namespace maths {
		inline double toRadians(float degrees)
		{
			return degrees * (M_PI / 180.0f);
		}

	}
}