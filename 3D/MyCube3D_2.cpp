#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// разрешение окна
const GLuint WIDTH = 800, HEIGHT = 600;

// quadrate_coords - это массив координат вершин квадрата 
GLfloat quadrate_coords[] = {
	 0.5f,  0.5f, 0.0f,  // Верхний правый угол
	 0.5f, -0.5f, 0.0f,  // Нижний правый угол
	-0.5f, -0.5f, 0.0f,  // Нижний левый угол
	-0.5f,  0.5f, 0.0f   // Верхний левый угол
};

// Index строки, берет 3 точки из этой строки из quadrate_coords
GLuint indices[] = {
	2,1,0,
	3,2,0
	//0, 1, 3,   // Первый треугольник
	//1, 2, 3    // Второй треугольник	
};

// shader_traingle - это встроенная переменная, которая определяет положение вершин в пространстве, это результат работы шейдера
const GLchar* shader_traingle = R"(
#version 330 core
layout(location = 0) in vec3 position;
void main()
{
   gl_Position = vec4(position.x, position.y, position.z, 1.0);
}
)";

// shader_color - это встроенная переменная, которая определяет цвет вершин в пространстве, это результат работы шейдера
const GLchar* shader_color = R"(#version 330 core
out vec4 color;
void main()
{
	color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	//color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
})";

int main() {
	glfwInit();
	// Установка версии OpenGL, которую мы будем использовать
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// Установка версии OpenGL, которую мы будем использовать
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Установка профайла для которого создается контекст
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Выключение возможности изменения размера окна
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Выход из программы при на жатии ESC
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mode) {
		// Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
		// и приложение после этого закроется
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		});

	// Подключаем новейшие техники для управления функционалом OpenGL
	glewExperimental = GL_TRUE;
	// glewInit - это функция, которая инициализирует GLEW
	glewInit();

	// Определите размеры области просмотра, если они меньше, 
	// то по бокам или сверху снизу, будут черные полосы
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);



	//////////////////////////////НАЧАЛО_ШЕЙДЕР/////////////////////////////////////
	// Создание шейдера и компиляция
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &shader_traingle, NULL);
	glCompileShader(vertexShader);
	// Получаем статус компиляции шейдера
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Создание фрагментного шейдера
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &shader_color, NULL);
	glCompileShader(fragmentShader);
	// Ссылка на шейдеры, к ней привязываются шейдеры
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Проверка на ошибки компиляции
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// Удаление шейдеров, они больше не нужны
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	///////////////////////////КОНЕЦ_ШЕЙДЕРЫ//////////////////////////////////

	////////////////////////////НАЧАЛО_БУФЕРЫ/////////////////////////////////////////
	// vbo(vertex buffer object) - это буфер вершин, который хранит координаты вершин
	// vao(vertex array object) - это объект вершинного массива, который хранит указатели на буфер вершин
	// ebo(element buffer objects) - это буфер индексов, который хранит индексы вершин, нужен для рисования квадратов
	GLuint VBO, VAO, EBO;




	// Создает объект вершинного массива, который хранит указатели на буферы вершин
	glGenVertexArrays(1, &VAO);
	// Создается в памяти видеокарты, но пока не привязан к контексту OpenGL
	glGenBuffers(1, &VBO);
	// Создается в памяти видеокарты, но пока не привязан к контексту OpenGL
	glGenBuffers(1, &EBO);



	// glBindBuffer - это функция, которая привязывает буфер вершин к текущему контексту OpenGL
	glBindVertexArray(VAO);

	// Копирование координат квадрата в VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadrate_coords), quadrate_coords, GL_STATIC_DRAW);

	// Копирование вершин в EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	
	// Копирование. Заполняет буффер VBO в видеокарте данными из массива triangle_coords
	//настраивает, как OpenGL должен интерпретировать данные вершин в массиве байт, которые хранятся в буфере (VBO)
	// 0 - index аттрибута в контексте Opengl. Связан с аттрибутом position в шейдере
	// 3 - это количество координат, которые мы передаем в шейдер
	// GL_FLOAT - это тип данных, которые мы передаем в шейдер
	// 3* sizeof(GLfloat) - это размер данных, которые мы передаем в шейдер
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	// Активируем аттирибут, который мы настроили выше под индексом 0
	glEnableVertexAttribArray(0);
	// Отвыязываем буффер VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Отвязка массива VAO
	glBindVertexArray(0);
	////////////////////////////КОНЕЦ_БУФЕРЫ/////////////////////////////////////////
	
	// Рисовать в режиме полигонов
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Игровой цикл
	while (!glfwWindowShouldClose(window))
	{
		// Проверяет были ли вызваны какие либо события (вроде ввода с клавиатуры или перемещение мыши)
		glfwPollEvents();

		// Отчистить цветовой буфер
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Рисовать фигуру
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Меня буфер экрана на следующий кадр, всего 2 буфера, которые отрисовываются друг за другом
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}