#include "window.h"
#include "maths.h"
#include "fileutils.h"
#include "shader.h"

#include "buffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"

#include "renderer2d.h"
#include "simple2drenderer.h"


#define DEBUG false

int main()
{
	using namespace gengine;
	using namespace graphics;
	using namespace maths;

	Window window("GENGINE Prototype V.:0.0.5_pre", 960, 540);

	GLfloat vertices[] = {
		0, 0, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0,
	};

	GLushort indices[] =
	{
		0,1,2,
		2,3,0
	};

	GLfloat colorsA[] = {
		1, 0, 0, 1,
		0, 1, 0, 1,
		0, 0, 1, 1,
		1, 0, 1, 1,
	};

	GLfloat colorsB[] = {
		0.2f, 0.3f, 0.8f, 1,
		0.2f, 0.3f, 0.8f, 1,
		0.2f, 0.3f, 0.8f, 1,
		0.2f, 0.3f, 0.8f, 1,
	};

	VertexArray sprite1, sprite2;
	IndexBuffer ibo(indices, 6);

	sprite1.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	sprite1.addBuffer(new Buffer(colorsA, 4 * 4, 4), 1);

	sprite2.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	sprite2.addBuffer(new Buffer(colorsB, 4 * 4, 3), 1);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("basic.vert", "basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));

	Renderable2D sprite(maths::vec3(5,5,0), maths::vec2(4, 4), maths::vec4(1, 0, 1, 1), shader);
	
	Simple2DRenderer renderer;
	
	while (!window.closed())
	{
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
			shader.setUniform4f("colour", vec4(0.1f, 1.0f, 0.1f, 1.0f));
		else
			shader.setUniform4f("colour", vec4(0.2, 0.3f, 0.8f, 1.0f));

		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));
		
		renderer.submit(&sprite);
		renderer.flush();

		window.update();
	}

	return 0;
}