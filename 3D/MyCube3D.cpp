#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main() {
	glfwInit();
	//Мажорная 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//Минорная
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Установка профайла для которого создается контекст
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Выключение возможности изменения размера окна
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);


	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mode) {
		// Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
		// и приложение после этого закроется
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
	});

	// Игровой цикл
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.5f, 0.5f, 1.0f, 1.0f); // функция задает цвет отчистки RGBA
		glClear(GL_COLOR_BUFFER_BIT); // GL_COLOR_BUFFER_BIT - отчистить буфер, новым цветом
		// Проверяет были ли вызваны какие либо события (вроде ввода с клавиатуры или перемещение мыши)
		glfwPollEvents();
		// Меняем буфер местами, Opengl создает 2 буфера, отрисовывает на одном, меняет, отрисовывает на 2. Это нужно чтобы убрать мерцание экрана
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}