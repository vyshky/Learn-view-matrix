#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// ����:
// � ��� ���� ������ ��������� � �����
// � ������� glVertexAttribPointer �� ������ ���� ���������� ����������, � ���� ���� ����� index 1 � 0
// �����, ����� ���������� 6 float, �� ������ 3 ������������ � position, � ������ � color
// �������� ������������� ���� �������� � ��������� 3 ������
// 
// ������� ������ ��������
//  1.Vertex
//  2.Geometry
//  3.Fragment


//** ������ ���� ��������� : **
//
//1. * *��������� ������ : **
//*����������� ��� ������ ������� ������������.
//* �������� �� ���� �������� �������(�������, ����, ���������� ���������� � �.�.).
//* ��������� ����������� ���������� � �������� ���������� ������.
//2. * *������ ���������� : **
//*GPU �������� ������� � ���������(������������, �����, �����).
//* ����������, ����� ������� ����������� ������ ���������.
//3. * *������������ : **
//*GPU ����������� ��������� � �������(���������) �� ������.
//* ����������, ����� ������� ����������� ����������.
//* ���������� ��������� ��� ������� �������, ������� ����������� ����������.
//4. * *������������ ��������� : **
//*GPU ������������� ��������(����, ���������� ���������� � �.�.) ��� ������� ���������.
//* ���������� �������� ��������� ������ � ������������ �������� ��������� ��� ������� ���������.
//5. * *����������� ������ : **
//*����������� ��� ������� ���������.
//* �������� �� ���� ����������������� ��������(����, ���������� ���������� � �.�.).
//* ��������� ����������� ���������� � ���������� ������������� ���� ���������.
//6. * *������������ : **
//*GPU ��������� ������������ ����������(��������, ���� �������, ���� ������������).
//* ���������, ������ �� �������� ���� �������� ��� ���.
//7. * *���������� : **
//*GPU ��������� ���������� ����� ��������� � ������ ����(���� ����������).
//* ���������� ����� ��������� � ���� ��� �������� �������������� �����.
//8. * *������������ �������� : **
//*GPU ���������� ������������� ���� ��������� � ����� �����.
//* ����� ����� � ��� ������� ������, ��� �������� �����������, ������� ����� ���������� �� ������.
//
//** � ����� : **
//
//������ ���� ��������� �������� � ���� ��������� ������, ������� �� ���������� ������� � ���������� ������������� ��������.������ ���� ������ ������ ���� � �������� ������������ � ��������������� �������.

//
//1.������������ �����
//2.����������� ������
//3.������������(���� �������, ���� ������������ � �.�.)
//4.����������(���� ����������)
//5.������������ ��������(������ ����� ������� � ����� �����)



// ���������� ����
const GLuint WIDTH = 800, HEIGHT = 600;

// quadrate_coords - ��� ������ ��������� ������ �������� 
GLfloat quadrate_coords_first[] = {
	// ����������            // ����
	-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // ������ ������ ����
	0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,  // ������ ����� ����
	0.0f, 0.5f, 0.0f,     0.0f, 0.0f, 1.0f,  // ������� ����
};


// vertex shader
// shader_traingle - ��� ���������� ����������, ������� ���������� ��������� ������ � ������������, ��� ��������� ������ �������
const GLchar* shader_traingle = R"(
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
out vec3 ourColor;
void main()
{
   gl_Position = vec4(position, 1.0);
   ourColor = color;
}
)";


// fragmet shaders
// shader_color - ��� ���������� ����������, ������� ���������� ���� ������ � ������������, ��� ��������� ������ �������
const GLchar* shader_color = R"(
#version 330 core
in vec3 ourColor;  // �� ������������� �������� ���� ���������� � ���� OpenGL.
out vec4 color;
void main()
{
	color = vec4(ourColor,1.0f);
})";

int main() {
	glfwInit();
	// ��������� ������ OpenGL, ������� �� ����� ������������
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// ��������� ������ OpenGL, ������� �� ����� ������������
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// ��������� �������� ��� �������� ��������� ��������
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// ���������� ����������� ��������� ������� ����
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// ����� �� ��������� ��� �� ����� ESC
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mode) {
		// ����� ������������ �������� ESC, �� ������������� �������� WindowShouldClose � true, 
		// � ���������� ����� ����� ���������
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		});

	// ���������� �������� ������� ��� ���������� ������������ OpenGL
	glewExperimental = GL_TRUE;
	// glewInit - ��� �������, ������� �������������� GLEW
	glewInit();

	// ���������� ������� ������� ���������, ���� ��� ������, 
	// �� �� ����� ��� ������ �����, ����� ������ ������
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);



	//////////////////////////////������_������/////////////////////////////////////
	// �������� ������� � ����������
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &shader_traingle, NULL);
	glCompileShader(vertexShader);
	// �������� ������ ���������� �������
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ������1
	// �������� ������������ ������� orange
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &shader_color, NULL);
	glCompileShader(fragmentShader);

	// ������ �� �������, � ��� ������������� �������
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// �������� �� ������ ����������
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// �������� ��������, ��� ������ �� �����
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	///////////////////////////�����_�������//////////////////////////////////

	////////////////////////////������_������/////////////////////////////////////////
	// vbo(vertex buffer object) - ��� ����� ������, ������� ������ ���������� ������
	// vao(vertex array object) - ��� ������ ���������� �������, ������� ������ ��������� �� ����� ������
	// ebo(element buffer objects) - ��� ����� ��������, ������� ������ ������� ������, ����� ��� ��������� ���������
	GLuint VBO, VAO;

	// first quadrate
	// ������� ������ ���������� �������, ������� ������ ��������� �� ������ ������
	glGenVertexArrays(1, &VAO);
	// ��������� � ������ ����������, �� ���� �� �������� � ��������� OpenGL
	glGenBuffers(1, &VBO);
	// ��������� � ������ ����������, �� ���� �� �������� � ��������� OpenGL
	// glBindBuffer - ��� �������, ������� ����������� ����� ������ � �������� ��������� OpenGL
	glBindVertexArray(VAO);
	// ����������� ��������� �������� � VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadrate_coords_first), quadrate_coords_first, GL_STATIC_DRAW);

	// �����������. ��������� ������ VBO � ���������� ������� �� ������� triangle_coords
	// �����������, ��� OpenGL ������ ���������������� ������ ������ � ������� ����, ������� �������� � ������ (VBO)
	// 0 - index ��������� � ��������� Opengl. ������ � ���������� position � �������
	// 3 - ��� ���������� ���������, ������� �� �������� � ������
	// GL_FLOAT - ��� ��� ������, ������� �� �������� � ������
	// 3* sizeof(GLfloat) - ��� ������ ������, ������� �� �������� � ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	// ���������� ���������, ������� �� ��������� ���� ��� �������� 0
	glEnableVertexAttribArray(0);



	// ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	


	// ����������� ������ VBO
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	// ������� ������� VAO
	glBindVertexArray(0);
	////////////////////////////�����_������/////////////////////////////////////////

	// �������� � ������ ���������
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// ������� ����
	while (!glfwWindowShouldClose(window))
	{
		// ������������ �������
		glfwPollEvents();

		// ���������
		// ������� ����� �����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ���������� ��������� ���������
		glUseProgram(shaderProgram);

		// ������ �����������
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// ���� ����� ������ �� ��������� ����, ����� 2 ������, ������� �������������� ���� �� ������
		glfwSwapBuffers(window);
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}