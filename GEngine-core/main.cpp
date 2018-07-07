#include "window.h"
#include "maths.h"
#include "fileutils.h"
#include "shader.h"

#include "buffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"

#define DEBUG false

int main()
{
	using namespace gengine;
	using namespace graphics;
	using namespace maths;

	Window window("GENGINE Prototype V.:0.0.5_pre", 960, 540);
	//glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

#if DEBUG
	GLfloat vertices[] = {
		0, 0, 0,
		8, 0, 0,
		0, 3, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
#else
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
		1, 0, 1, 1,
		1, 0, 1, 1,
		1, 0, 1, 1,
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
#endif
	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("basic.vert", "basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);

	shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));

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
#if DEBUG		
		glDrawArrays(GL_TRIANGLES, 0, 6 );
#else
		sprite1.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4,3,0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		sprite1.unbind();

		sprite2.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", mat4::translation(vec3(0, 0, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		sprite2.unbind();
#endif
		window.update();
	}

	return 0;
}