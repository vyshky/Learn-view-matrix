//#include <iostream>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//
//// ���������� ����
//const GLuint WIDTH = 800, HEIGHT = 600;
//
//// triangle_coords - ��� ������ ��������� ������ ������������ 
//GLfloat triangle_coords[] = {
//	-0.5f,  -0.5f, 0.0f, // left
//	 0.5f,  -0.5f, 0.0f, // right
//	 0.0f,   0.5f, 0.0f, // top
//};
//
//// shader_traingle - ��� ���������� ����������, ������� ���������� ��������� ������ � ������������, ��� ��������� ������ �������
//const GLchar* shader_traingle = R"(
//#version 330 core
//layout(location = 0) in vec3 position;
//void main()
//{
//   gl_Position = vec4(position.x, position.y, position.z, 1.0);
//}
//)";
//
//// shader_color - ��� ���������� ����������, ������� ���������� ���� ������ � ������������, ��� ��������� ������ �������
//const GLchar* shader_color = R"(#version 330 core
//out vec4 color;
//void main()
//{
//	color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
//	//color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
//})";
//
//int main1() {
//	glfwInit();
//	// ��������� ������ OpenGL, ������� �� ����� ������������
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	// ��������� ������ OpenGL, ������� �� ����� ������������
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	// ��������� �������� ��� �������� ��������� ��������
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	// ���������� ����������� ��������� ������� ����
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
//	glfwMakeContextCurrent(window);
//
//	// ����� �� ��������� ��� �� ����� ESC
//	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mode) {
//		// ����� ������������ �������� ESC, �� ������������� �������� WindowShouldClose � true, 
//		// � ���������� ����� ����� ���������
//		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//			glfwSetWindowShouldClose(window, GL_TRUE);
//		});
//
//	// ���������� �������� ������� ��� ���������� ������������ OpenGL
//	glewExperimental = GL_TRUE;
//	// glewInit - ��� �������, ������� �������������� GLEW
//	glewInit();
//
//	// ���������� ������� ������� ���������, ���� ��� ������, 
//	// �� �� ����� ��� ������ �����, ����� ������ ������
//	int width, height;
//	glfwGetFramebufferSize(window, &width, &height);
//	glViewport(0, 0, width, height);
//
//
//
//	//////////////////////////////������_������/////////////////////////////////////
//	// �������� ������� � ����������
//	GLuint vertexShader;
//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &shader_traingle, NULL);
//	glCompileShader(vertexShader);
//	// �������� ������ ���������� �������
//	GLint success;
//	GLchar infoLog[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//	// �������� ������������ �������
//	GLuint fragmentShader;
//	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &shader_color, NULL);
//	glCompileShader(fragmentShader);
//	// ������ �� �������, � ��� ������������� �������
//	GLuint shaderProgram;
//	shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//
//	// �������� �� ������ ����������
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//	if (!success) {
//		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//	}
//	// �������� ��������, ��� ������ �� �����
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//	///////////////////////////�����_�������//////////////////////////////////
//
//	////////////////////////////������_������/////////////////////////////////////////
//	// vbo - ��� ����� ������, ������� ������ ���������� ������
//	// vao - ��� ������ ���������� �������, ������� ������ ��������� �� ����� ������
//	GLuint VBO, VAO;
//
//	// ������� ������ ���������� �������, ������� ������ ��������� �� ������ ������
//	glGenVertexArrays(1, &VAO);
//	// ����������� VAO � ���������� �������, �� ���� � ������� �� ��������� OpenGL
//	glBindVertexArray(VAO);
//
//	// ��������� � ������ ����������, �� ���� �� �������� � ��������� OpenGL
//	glGenBuffers(1, &VBO);
//	// glBindBuffer - ��� �������, ������� ����������� ����� ������ � �������� ��������� OpenGL
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	
//	// ��������� ������ VBO � ���������� ������� �� ������� triangle_coords
//	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_coords), triangle_coords, GL_STATIC_DRAW);
//	//�����������, ��� OpenGL ������ ���������������� ������ ������ � ������� ����, ������� �������� � ������ (VBO)
//	// 0 - index ��������� � ��������� Opengl. ������ � ���������� position � �������
//	// 3 - ��� ���������� ���������, ������� �� �������� � ������
//	// GL_FLOAT - ��� ��� ������, ������� �� �������� � ������
//	// 3* sizeof(GLfloat) - ��� ������ ������, ������� �� �������� � ������
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
//	// ���������� ���������, ������� �� ��������� ���� ��� �������� 0
//	glEnableVertexAttribArray(0);
//	// ����������� ������ VBO
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	// ������� ������� VAO
//	glBindVertexArray(0);
//	////////////////////////////�����_������/////////////////////////////////////////
//	// ������� ����
//	while (!glfwWindowShouldClose(window))
//	{
//		// ��������� ���� �� ������� ����� ���� ������� (����� ����� � ���������� ��� ����������� ����)
//		glfwPollEvents();
//
//		// ��������� �������� �����
//		//glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
//		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//        // �������� ������
//		glUseProgram(shaderProgram);
//		glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//		glBindVertexArray(0);
//
//		// ���� ����� ������ �� ��������� ����, ����� 2 ������, ������� �������������� ���� �� ������
//		glfwSwapBuffers(window);
//	}
//
//	glfwTerminate();
//	return 0;
//}