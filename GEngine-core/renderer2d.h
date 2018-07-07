#pragma once

#include <GL/glew.h>
#include "maths.h"
#include "renderable2d.h"

namespace gengine { namespace graphics {

	class Renderer2D
	{
	public:
		virtual void submit(Renderable2D& renderable) = 0;
		virtual void flush() = 0;
	};

} }