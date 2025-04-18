#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// ГАЙД:
// У нас есть массив координат и цвета
// с помощью glVertexAttribPointer мы задаем куда записывать координаты, а куда цвет через index 1 и 0
// Далее, когда вызывается 6 float, то первые 3 записываются в position, а другие в color
// Вершинам присваивается цвет заданный в последних 3 байтах
// 
// Порядок вызова шейдеров
//  1.Vertex
//  2.Geometry
//  3.Fragment


//** Полный цикл отрисовки : **
//
//1. * *Вершинный шейдер : **
//*Выполняется для каждой вершины треугольника.
//* Получает на вход атрибуты вершины(позиция, цвет, текстурные координаты и т.д.).
//* Выполняет необходимые вычисления и передает результаты дальше.
//2. * *Сборка примитивов : **
//*GPU собирает вершины в примитивы(треугольники, линии, точки).
//* Определяет, какие вершины принадлежат одному примитиву.
//3. * *Растеризация : **
//*GPU преобразует примитивы в пиксели(фрагменты) на экране.
//* Определяет, какие пиксели покрываются примитивом.
//* Генерирует фрагменты для каждого пикселя, который покрывается примитивом.
//4. * *Интерполяция атрибутов : **
//*GPU интерполирует атрибуты(цвет, текстурные координаты и т.д.) для каждого фрагмента.
//* Использует значения атрибутов вершин и рассчитывает значения атрибутов для каждого фрагмента.
//5. * *Фрагментный шейдер : **
//*Выполняется для каждого фрагмента.
//* Получает на вход интерполированные атрибуты(цвет, текстурные координаты и т.д.).
//* Выполняет необходимые вычисления и определяет окончательный цвет фрагмента.
//6. * *Тестирование : **
//*GPU выполняет тестирование фрагментов(например, тест глубины, тест прозрачности).
//* Проверяет, должен ли фрагмент быть закрашен или нет.
//7. * *Смешивание : **
//*GPU выполняет смешивание цвета фрагмента с цветом фона(если необходимо).
//* Объединяет цвета фрагмента и фона для создания окончательного цвета.
//8. * *Закрашивание пикселей : **
//*GPU записывает окончательный цвет фрагмента в буфер кадра.
//* Буфер кадра — это область памяти, где хранится изображение, которое будет отображено на экране.
//
//** В целом : **
//
//Полный цикл отрисовки включает в себя несколько этапов, начиная от вершинного шейдера и заканчивая закрашиванием пикселей.Каждый этап играет важную роль в создании реалистичной и привлекательной графики.

//
//1.Интерполяция цвета
//2.Фрагментный шейдер
//3.Тестирование(тест глубины, тест прозрачности и т.д.)
//4.Смешивание(если необходимо)
//5.Закрашивание пикселей(запись цвета пикселя в буфер кадра)



// разрешение окна
const GLuint WIDTH = 800, HEIGHT = 600;

// quadrate_coords - это массив координат вершин квадрата 
GLfloat quadrate_coords_first[] = {
	// КООРДИНАТЫ            // ЦВЕТ
	-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // Нижний правый угол
	0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,  // Нижний левый угол
	0.0f, 0.5f, 0.0f,     0.0f, 0.0f, 1.0f,  // Верхний угол
};


// vertex shader
// shader_traingle - это встроенная переменная, которая определяет положение вершин в пространстве, это результат работы шейдера
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
// shader_color - это встроенная переменная, которая определяет цвет вершин в пространстве, это результат работы шейдера
const GLchar* shader_color = R"(
#version 330 core
in vec3 ourColor;  // Мы устанавливаем значение этой переменной в коде OpenGL.
out vec4 color;
void main()
{
	color = vec4(ourColor,1.0f);
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
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
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

	// Шейдер1
	// Создание фрагментного шейдера orange
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &shader_color, NULL);
	glCompileShader(fragmentShader);

	// Ссылка на шейдеры, к ней привязываются шейдеры
	GLuint shaderProgram = glCreateProgram();
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
	GLuint VBO, VAO;

	// first quadrate
	// Создает объект вершинного массива, который хранит указатели на буферы вершин
	glGenVertexArrays(1, &VAO);
	// Создается в памяти видеокарты, но пока не привязан к контексту OpenGL
	glGenBuffers(1, &VBO);
	// Создается в памяти видеокарты, но пока не привязан к контексту OpenGL
	// glBindBuffer - это функция, которая привязывает буфер вершин к текущему контексту OpenGL
	glBindVertexArray(VAO);
	// Копирование координат квадрата в VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadrate_coords_first), quadrate_coords_first, GL_STATIC_DRAW);

	// Копирование. Заполняет буффер VBO в видеокарте данными из массива triangle_coords
	// настраивает, как OpenGL должен интерпретировать данные вершин в массиве байт, которые хранятся в буфере (VBO)
	// 0 - index аттрибута в контексте Opengl. Связан с аттрибутом position в шейдере
	// 3 - это количество координат, которые мы передаем в шейдер
	// GL_FLOAT - это тип данных, которые мы передаем в шейдер
	// 3* sizeof(GLfloat) - это размер данных, которые мы передаем в шейдер
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	// Активируем аттирибут, который мы настроили выше под индексом 0
	glEnableVertexAttribArray(0);



	// ЦВЕТ
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	


	// Отвыязываем буффер VBO
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Отвязка массива VAO
	glBindVertexArray(0);
	////////////////////////////КОНЕЦ_БУФЕРЫ/////////////////////////////////////////

	// Рисовать в режиме полигонов
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Игровой цикл
	while (!glfwWindowShouldClose(window))
	{
		// Обрабатываем события
		glfwPollEvents();

		// Отрисовка
		// Очищаем буфер цвета
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Активируем шейдерную программу
		glUseProgram(shaderProgram);

		// рисуем треугольник
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// Меня буфер экрана на следующий кадр, всего 2 буфера, которые отрисовываются друг за другом
		glfwSwapBuffers(window);
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}