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
//	-0.5f, -0.5f, 0.0f,  // Left 
//	0.5f, -0.5f, 0.0f,  // Right
//	0.0f, 0.5f, 0.0f,  // Top 
//};
//
//
//// vertex shader
//// shader_traingle - ��� ���������� ����������, ������� ���������� ��������� ������ � ������������, ��� ��������� ������ �������
//const GLchar* shader_traingle = R"(
//#version 330 core
//layout(location = 0) in vec3 position;
//out vec4 vertexColor;
//void main()
//{
//   gl_Position = vec4(position.x, position.y, position.z, 1.0);
//   //vertexColor = gl_Position;
//   vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);
//}
//)";
//
//
//// fragmet shaders
//// shader_color - ��� ���������� ����������, ������� ���������� ���� ������ � ������������, ��� ��������� ������ �������
//const GLchar* shader_color_first = R"(
//#version 330 core
////in vec4 vertexColor; 
//uniform vec4 ourColor;  // �� ������������� �������� ���� ���������� � ���� OpenGL.
//out vec4 color;
//void main()
//{
//	color = ourColor;
//	//color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
//	//color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
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
//	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
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
//	// ������1
//	// �������� ������������ ������� orange
//	GLuint fragmentShader_orange = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader_orange, 1, &shader_color_first, NULL);
//	glCompileShader(fragmentShader_orange);
//	// ������ �� �������, � ��� ������������� �������
//	GLuint shaderProgram_orange = glCreateProgram();
//	glAttachShader(shaderProgram_orange, vertexShader);
//	glAttachShader(shaderProgram_orange, fragmentShader_orange);
//	glLinkProgram(shaderProgram_orange);
//
//	// �������� �� ������ ����������
//	glGetProgramiv(shaderProgram_orange, GL_LINK_STATUS, &success);
//	if (!success) {
//		glGetProgramInfoLog(shaderProgram_orange, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//	}
//
//	// �������� ��������, ��� ������ �� �����
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader_orange);
//	///////////////////////////�����_�������//////////////////////////////////
//
//	////////////////////////////������_������/////////////////////////////////////////
//	// vbo(vertex buffer object) - ��� ����� ������, ������� ������ ���������� ������
//	// vao(vertex array object) - ��� ������ ���������� �������, ������� ������ ��������� �� ����� ������
//	// ebo(element buffer objects) - ��� ����� ��������, ������� ������ ������� ������, ����� ��� ��������� ���������
//	GLuint VBO, VAO;
//
//	// first quadrate
//	// ������� ������ ���������� �������, ������� ������ ��������� �� ������ ������
//	glGenVertexArrays(1, &VAO);
//	// ��������� � ������ ����������, �� ���� �� �������� � ��������� OpenGL
//	glGenBuffers(1, &VBO);
//	// ��������� � ������ ����������, �� ���� �� �������� � ��������� OpenGL
//	// glBindBuffer - ��� �������, ������� ����������� ����� ������ � �������� ��������� OpenGL
//	glBindVertexArray(VAO);
//	// ����������� ��������� �������� � VBO
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(quadrate_coords_first), quadrate_coords_first, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
//	// ���������� ���������, ������� �� ��������� ���� ��� �������� 0
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
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
//		// ������������ �������
//		glfwPollEvents();
//
//		// ���������
//		// ������� ����� �����
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// ���������� ��������� ���������
//		glUseProgram(shaderProgram_orange);
//
//		// ��������� ���� �����
//		GLfloat timeValue = glfwGetTime();
//		GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
//		GLfloat redValue = (sin(timeValue * 2) / 2) + 0.5;
//		GLfloat blueValue = (sin(timeValue * 3) / 2) + 0.5;
//		GLint vertexColorLocation = glGetUniformLocation(shaderProgram_orange, "ourColor");
//		glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);
//		
//		// ������ �����������
//		glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//		glBindVertexArray(0);
//
//		// ���� ����� ������ �� ��������� ����, ����� 2 ������, ������� �������������� ���� �� ������
//		glfwSwapBuffers(window);
//	}
//	// Properly de-allocate all resources once they've outlived their purpose
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glfwTerminate();
//	return 0;
//}