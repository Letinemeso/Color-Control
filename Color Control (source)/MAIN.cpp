#include <glew.h>
#include <glfw3.h>

#include <gtx\transform.hpp>

#include <iostream>
#include <thread>
#include <chrono>

#include "Tetrahedron.cpp"
#include "Slider.cpp"

bool buttonPressed(GLFWwindow* wind, int mouseButtonPressed) {
	if (glfwGetMouseButton(wind, GLFW_MOUSE_BUTTON_1) && !mouseButtonPressed) {
		return true;
	}
	else {
		return false;
	}
}
bool buttonReleased(GLFWwindow* wind, int mouseButtonPressed) {
	if (!glfwGetMouseButton(wind, GLFW_MOUSE_BUTTON_1) && mouseButtonPressed) {
		return true;
	}
	else {
		return false;
	}
}

int main() {
	std::cout << "Welcome to color-changing program!\nYou can use slider to increase / decrease color of triangle\n";

	glfwInit();

	GLFWwindow* wind = glfwCreateWindow(500, 500, "airstream", 0, 0);
	glfwMakeContextCurrent(wind);

	glfwSetWindowSizeLimits(wind, 500, 500, 500, 500);

	glewInit();

	const char* vs =
		"#version 330 core\n"
		"layout (location = 0) in vec3 posInp;\n"
		"layout (location = 1) in vec3 colorInp;\n"
		"out vec3 colorOutp;\n"
		"uniform mat4x4 orthographicMatrix;\n"
		"void main(){\n"
		"colorOutp = colorInp;\n"
		"gl_Position = orthographicMatrix * vec4(posInp, 1.0f);\n"
		"}";

	const char* fs =
		"#version 330 core\n"
		"in vec3 colorOutp;\n"
		"out vec4 resultColor;\n"
		"void main(){\n"
		"resultColor = vec4(colorOutp, 1.0f);\n"
		"}";

	unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vs, 0);
	glCompileShader(vShader);

	unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fs, 0);
	glCompileShader(fShader);

	unsigned int prog = glCreateProgram();
	glAttachShader(prog, vShader);
	glAttachShader(prog, fShader);
	glLinkProgram(prog);

	glUseProgram(prog);

	glm::mat4x4 ortho = glm::ortho(0.0f, 500.0f, 0.0f, 500.0f, 0.0f, -5.0f);
	unsigned int orthographicMatrixLocation = glGetUniformLocation(prog, "orthographicMatrix");
	glUniformMatrix4fv(orthographicMatrixLocation, 1, GL_FALSE, &ortho[0][0]);

	Figure triangle(
		180.0f, 250.0f, 0.0f, 170.0f,

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f
	);

	Slider slider(
		430.0f, 250.0f, 0.0f, 50.0f, 350.0f,

		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.2f,
		0.0f, 0.0f, 0.2f,

		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f
	);

	int mouseButtonPressed = 0;
	double mousePosX = 0, mousePosY = 0;

	while (glfwWindowShouldClose(wind) == 0) {
		glClear(GL_COLOR_BUFFER_BIT);

		if (glfwGetMouseButton(wind, GLFW_MOUSE_BUTTON_1)) {
			glfwGetCursorPos(wind, &mousePosX, &mousePosY);
			mousePosY = 500 - mousePosY;

			if (buttonPressed(wind, mouseButtonPressed)) {
				slider.buttonPressedAtASliderChecker(mousePosX, mousePosY);
			}

			slider.moveIt(float(mousePosX), float(mousePosY));
		}

		if (buttonReleased(wind, mouseButtonPressed)) {
			slider.buttonReleased();
		}

		triangle.colorChange(slider.returnColorBrightness());

		triangle.drawIt();

		slider.drawIt();

		std::this_thread::sleep_for(std::chrono::milliseconds(1000/300));

		mouseButtonPressed = glfwGetMouseButton(wind, GLFW_MOUSE_BUTTON_1);

		glfwPollEvents();
		glfwSwapBuffers(wind);
	}

	return 0;
}