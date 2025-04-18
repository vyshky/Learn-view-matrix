//#include <iostream>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//
//// ���������� ����
//const GLuint WIDTH = 800, HEIGHT = 600;
//
//// quadrate_coords - ��� ������ ��������� ������ �������� 
//GLfloat quadrate_coords_first[] = {
//	// First triangle
//	-0.9f, -0.5f, 0.0f,  // Left 
//	-0.0f, -0.5f, 0.0f,  // Right
//	-0.45f, 0.5f, 0.0f,  // Top 
//};
//
//// quadrate_coords - ��� ������ ��������� ������ �������� 
//GLfloat quadrate_coords_second[] = {
//		 0.0f, -0.5f, 0.0f,  // Left
//		 0.9f, -0.5f, 0.0f,  // Right
//		 0.45f, 0.5f, 0.0f   // Top 
//};
//
//// Index ������, ����� 3 ����� �� ���� ������ �� quadrate_coords
////GLuint indices[] = {
////	2,1,0,
////	3,2,0
////	//0, 1, 3,   // ������ �����������
////	//1, 2, 3    // ������ �����������	
////};
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
//	//color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
//	color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
//})";
//
//int main() {
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
//
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
//	// vbo(vertex buffer object) - ��� ����� ������, ������� ������ ���������� ������
//	// vao(vertex array object) - ��� ������ ���������� �������, ������� ������ ��������� �� ����� ������
//	// ebo(element buffer objects) - ��� ����� ��������, ������� ������ ������� ������, ����� ��� ��������� ���������
//	GLuint VBO[2], VAO[2];
//
//	// first quadrate
//
//	// ������� ������ ���������� �������, ������� ������ ��������� �� ������ ������
//	glGenVertexArrays(1, &VAO[0]);
//	// ��������� � ������ ����������, �� ���� �� �������� � ��������� OpenGL
//	glGenBuffers(1, &VBO[0]);
//	// ��������� � ������ ����������, �� ���� �� �������� � ��������� OpenGL
//	// glBindBuffer - ��� �������, ������� ����������� ����� ������ � �������� ��������� OpenGL
//	glBindVertexArray(VAO[0]);
//	// ����������� ��������� �������� � VBO
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(quadrate_coords_first), quadrate_coords_first, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
//	// ���������� ���������, ������� �� ��������� ���� ��� �������� 0
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//
//	// Second quadrate
//	//Generate
//	glGenVertexArrays(1, &VAO[1]);
//	glGenBuffers(1, &VBO[1]);
//	//bind
//	glBindVertexArray(VAO[1]);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
//	//copy
//	glBufferData(GL_ARRAY_BUFFER, sizeof(quadrate_coords_second), quadrate_coords_second, GL_STATIC_DRAW);
//
//
//	// �����������. ��������� ������ VBO � ���������� ������� �� ������� triangle_coords
//	// �����������, ��� OpenGL ������ ���������������� ������ ������ � ������� ����, ������� �������� � ������ (VBO)
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
//
//	// �������� � ������ ���������
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//	// ������� ����
//	while (!glfwWindowShouldClose(window))
//	{
//		// ��������� ���� �� ������� ����� ���� ������� (����� ����� � ���������� ��� ����������� ����)
//		glfwPollEvents();
//
//		// ��������� �������� �����
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// ������������� ������, ������� �� ������� ����
//		glUseProgram(shaderProgram);
//
//		// �������� ������ 1
//		glBindVertexArray(VAO[0]);
//		// 6 ��� ���������� �������� �� indices
//		// GL_UNSIGNED_INT - ��� ��� ������ �������� �� indices
//		// 0 - ��� �������� � ������ ��������, �� ���� � ������
//		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//		// ������ �������� - ��� ��� ���������, ������� �� ����� ����������
//		// ������ �������� ��� ������ ������� �� ��������� � ������� �� �������� ��������
//		// ������ �������� ��� ���������� ������, ������� �� ����� ����������, �� ���� 3, ������ 1 �����������
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//		glBindVertexArray(0);
//
//		// �������� ������ 2
//		glBindVertexArray(VAO[1]);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//
//		// ������� VAO
//		glBindVertexArray(0);
//
//		// ���� ����� ������ �� ��������� ����, ����� 2 ������, ������� �������������� ���� �� ������
//		glfwSwapBuffers(window);
//	}
//	// Properly de-allocate all resources once they've outlived their purpose
//	glDeleteVertexArrays(2, VAO);
//	glDeleteBuffers(2, VBO);
//	glfwTerminate();
//	return 0;
//}