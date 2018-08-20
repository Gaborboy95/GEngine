#include "window.h"
#include "maths.h"
#include "fileutils.h"
#include "shader.h"

#include "buffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"

#include "renderer2d.h"
#include "simple2drenderer.h"
#include "batchrenderer2d.h"

#include "static_sprite.h"
#include "sprite.h"

#define DEBUG false
#define GENGINE_VERSION "0.0.57_pre"
#define BATCH_RENDERER 1

int main()
{
	using namespace gengine;
	using namespace graphics;
	using namespace maths;

	Window window("GENGINE Prototype V.: " GENGINE_VERSION, 960, 540);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("basic.vert", "basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));
	shader.setUniform4f("colour", vec4(0.1f, 1.0f, 0.1f, 1.0f));

#if BATCH_RENDERER
	Sprite sprite(5 + 4, 5 + 3, 4, 4, maths::vec4(1, 0, 1, 1));
	Sprite sprite2(7 + 4, 1 + 3, 4, 4, maths::vec4(0.2, 0, 1, 1));
	BatchRenderer2D renderer;
#else
	StaticSprite sprite(5, 5, 4, 4, maths::vec4(1, 0, 1, 1), shader);
	StaticSprite sprite2(7, 1, 4, 4, maths::vec4(0.2, 0, 1, 1), shader);
	Simple2DRenderer renderer;
#endif

	while (!window.closed())
	{
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));
#if BATCH_RENDERER
		renderer.begin();
#endif
		renderer.submit(&sprite);
		renderer.submit(&sprite2);
#if BATCH_RENDERER
		renderer.end();
#endif
		renderer.flush();

		window.update();
	}

	return 0;
}