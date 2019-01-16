#include <Windows.h>
#include <iostream>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "inputManager.h"
#include "cubeLink.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;

vec3 color;

void drawCube(mat4 toDraw) {

	MVP = P * toDraw;
	shader.Bind();

	color = vec3(1.0f, 1.0f, 1.0f);
	shader.Update(MVP, toDraw, color);
}

int main(int argc, char** argv)
{



	glfwSetKeyCallback(display.m_window, key_callback);
	glfwSetMouseButtonCallback(display.m_window, mouseButtonCallback);
	glfwSetCursorPosCallback(display.m_window, cursorPositionCallback);
	glfwSetScrollCallback(display.m_window, scrollCallback);
	if (glfwGetMouseButton(display.m_window, GLFW_MOUSE_BUTTON_LEFT)) {

	}
	initCubes();
	
	while (!glfwWindowShouldClose(display.m_window))
	{

		Sleep(3);
		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		drawCube(cubes[blockChainNum+1]->getMat());  // for general axises
		buildGenAxises();

		drawCube(targetCube);
		mesh.Draw();

		mat4 matrix;

		for (int i = 0; i <blockChainNum; i++) {


			matrix = cubes[i]->getMat() * cubes[0]->scaleMat;

			MVP = P * matrix;

			shader.Bind();
			shader.Update(MVP, matrix, color);

			buildAxises();

			mesh.Draw();
		}


		display.SwapBuffers();

		glfwPollEvents();
		if (solver) {
			IKsolver();
			numOfAction = (numOfAction + 1) % (blockChainNum);
			Sleep(3);
		}
	}

	return 0;
}





