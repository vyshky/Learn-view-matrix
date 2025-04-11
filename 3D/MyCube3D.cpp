#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main() {
	glfwInit();
	//�������� 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//��������
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//��������� �������� ��� �������� ��������� ��������
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//���������� ����������� ��������� ������� ����
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
		// ����� ������������ �������� ESC, �� ������������� �������� WindowShouldClose � true, 
		// � ���������� ����� ����� ���������
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
	});

	// ������� ����
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.5f, 0.5f, 1.0f, 1.0f); // ������� ������ ���� �������� RGBA
		glClear(GL_COLOR_BUFFER_BIT); // GL_COLOR_BUFFER_BIT - ��������� �����, ����� ������
		// ��������� ���� �� ������� ����� ���� ������� (����� ����� � ���������� ��� ����������� ����)
		glfwPollEvents();
		// ������ ����� �������, Opengl ������� 2 ������, ������������ �� �����, ������, ������������ �� 2. ��� ����� ����� ������ �������� ������
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}