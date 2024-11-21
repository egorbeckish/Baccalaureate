#include <GLFW/glfw3.h>
#include <GLFW/glut.h>
#include <GLFW/glaux.h>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <complex>
#define WIDTH 800
#define HEIGHT 640
#define RANGE 80
#define MAX 50
#define INDEX 0.01
#define RE_C 1.07
#define IM_C 0.0001



// Фрактал биоморф
//using namespace std;
//
////рисование точки с координатами (x, y) передаваемым в функцию цветом(RGB)
//void draw_dot(int x, int y, GLubyte *clr) {
//	glColor3ub(clr[0], clr[1], clr[2]); //цвет рисования
//	//на месте каждой вершины, указанной glVertex рисуется точка
//	glBegin(GL_POINTS);
//	glVertex2i(x, y);
//	glEnd();
//}
//
//void draw_biomorph() {
//	complex <double> z; //z будет возводиться в куб
//	//константа, на каждой итерации будет добавляться к z, возведенному в куб
//	const complex <double> constant(RE_C, IM_C);
//	double re_z, im_z; //модули действительной и мнимой частей z на текущей итерации
//	//clr_black-цвет фона, new_clr-цвет биоморфа(RGB)
//	GLubyte clr_black[] = { 0, 0, 0 }, new_clr[3];
//	//инициализация начала последовательности, генерируемой rand() текущим временем  в секундах
//	srand(time(0));
//	//определяем z для каждой точки окна
//	for (int x = -WIDTH / 2; x < WIDTH / 2; x++) {
//		for (int y = -HEIGHT / 2; y < HEIGHT / 2; y++) {
//			//преобразуем координаты текущей точки, re_z <= 4, im_z <= 3.2
//			z.real(x * INDEX);
//			z.imag(y * INDEX);
//			//модули действительной и мнимой частей z
//			re_z = fabs(z.real());
//			im_z = fabs(z.imag());
//			//возводим z в куб, пока модуль действительной, мнимой части или модуль самого z
//			//не превзойдут максимального числа из указанного диапазона(RANGE)
//			//MAX ограничивает число итераций для случая,
//			//если z убывает при каждом возведении в куб(т.е. никогда не достигнет MAX)
//			for (int i = 0; (re_z < RANGE || im_z < RANGE || abs(z) < RANGE) && i < MAX; i++) {
//				//возводим предыдущее значение z в куб добавляя константу
//				z = pow(z, 3) + constant;
//				re_z = fabs(z.real());
//				im_z = fabs(z.imag());
//			}
//			//закрашиваем z, попавшие в область, случайными значениями цвета
//			if (re_z < MAX || im_z < MAX * 50) {
//				new_clr[0] = rand() % 255;
//				new_clr[1] = rand() % 255;
//				new_clr[2] = rand() % 255;
//				draw_dot(x, y, new_clr);
//			}
//			else //точки, не попавшие в область, закрашиваем цветом фона
//				draw_dot(x, y, clr_black);
//		}
//	}
//	glFlush(); //отправляем весь вывод на экран
//}
//
//void init() {
//	glClearColor(0.0, 0.0, 0.0, 0.0); //цвет фона(RGBA, чёрный)
//	glPointSize(4.0); //точка размером 4x4 пикселя
//	glMatrixMode(GL_PROJECTION); //матрица проекций
//	glLoadIdentity(); //замена текущей матрицы на единичную
//	//установка системы координат
//	gluOrtho2D(-WIDTH / 2, WIDTH / 2, -HEIGHT / 2, HEIGHT / 2);
//}
//
//void display() {
//	glClear(GL_COLOR_BUFFER_BIT); //очистка текущего буфера цвета
//	glFlush();
//	draw_biomorph(); //рисование биоморфа
//}
//
//int main(int argc, char** argv) {
//	glutInit(&argc, argv); //инициализация OpenGL Utility Toolkit
//	//режим окна(одиночный буфер и RGB-палитра)
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//	//установка размеров окна(ширина и высота в пикселях)
//	glutInitWindowSize(WIDTH, HEIGHT);
//	//положение окна относительно левого верхнего угла экрана
//	glutInitWindowPosition(50, 50);
//	//создание окна c заголовком Biomorph
//	glutCreateWindow("Biomorph");
//	//инициализация функции, отвечающей за рисование в окне
//	glutDisplayFunc(display);
//	init(); // дополнительные параметры
//	glutMainLoop(); //вход в главный цикл
//	return 0;
//}















// Дерево Пифагора

///* Обьявление функции, которая будет рисовать фрактал */
//void func(double x, double y, double angle, double len, int deph);
//
///* Функция, прорисовывающая изображение в окне */
//void display(void) {
//	/* Очистка экрана цветом по-умолчанию */
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	/* Задание цвета для рисования */
//	glColor3f(1.0f, 0.2f, 0.5f);
//
//	/* Начало рисования. Вершины 2n и 2n+1 будут обьединены в линию*/
//	glBegin(GL_LINES);
//
//	/* Вызов функции, рисующей фрактал. В функции передаются вершины в буфер */
//	func(50, 50, 1.1, 50, 12);
//	/* Функция, выгружающая буфер в сцену */
//	glEnd();
//
//	/*  Прорисовка текущего буфера */
//	glFlush();
//}
//
///* Функция, определённая выше */
//void func(double x, double y, double angle, double len, int deph) {
//	double angp = 0.5; //изменение угла
//	for (int i = -1; i < 5; i += 2) {
//		//если не достигнута глубина рекурсии - продолжить построение фрактала
//		if (deph > 0)
//			func(x + cos(angle + i * angp)*len / 2, y + sin(angle + i * angp)*len / 2, angle + i * angp, len / 2, deph - 1);
//		/* В буфер записываются вершины. Эти две вершины будут соединены в прямые между собой*/
//		glVertex2d(x, y);
//		glVertex2d(x + cos(angle + i * angp)*len / 2, y + sin(angle + i * angp)*len / 2);
//	}
//}
//
//void init(void) {
//	/* Установка цвета по-умолчанию */
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	/* Задаются параметры сцены. Матрица преобразований для проекции, координаты сдвигаются в 0 и границы экрана устанавливаются в заданные*/
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(0.0, 100.0, 0.0, 100.0, -100.0, 100.0);
//}
///* Позволяет закрыть программу нажатием клавиши "эскейп" */
//void processNormalKeys(unsigned char key, int x, int y) {
//	if (key == 27)
//		exit(0);
//}
//
//
//int main(int argc, char** argv) {
//	/* Инициализируются буферы для glut-a*/
//	glutInit(&argc, argv);
//	/* Задаются режимы смешивания цветов и количество буферов*/
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//	/* Задаётся размер окна 500 на 500*/
//	glutInitWindowSize(500, 500);
//	/* Окно сдвигается на 100 единиц по икс и по игрек */
//	glutInitWindowPosition(100, 100);
//	/* Создаётся окно с названием, размером и смещениями, которые были указаны */
//	glutCreateWindow("Fractal");
//	/* Вызывается функция инициализации, задания начальных параметров */
//	init();
//	/* Устанвливается фукция прорисовки, переданная как параметр */
//	glutDisplayFunc(display);
//	/* Задаётся функция, которая будет обрабатывать нажатия клавиш*/
//	glutKeyboardFunc(processNormalKeys);
//	/* Начинается выполнение прорисовки и обработка клавиш*/
//	glutMainLoop();
//	return 0;
//}










// Звезда Дюрера

// /* Обьявление функции, которая будет рисовать фрактал */
//void func(double x, double y, double radius, double angle, int deep);
//
///* Функция, прорисовывающая изображение в окне */
//void display(void) {
//
//	/* Очистка экрана цветом по-умолчанию */
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	/* Задание цвета для рисования */
//	glColor3f(1.0f, 0.2f, 0.5f);
//
//	/* Начало рисования. Вершины 2n и 2n+1 будут обьединены в линию*/
//	glBegin(GL_LINES);
//
//	/* Вызов функции, рисующей фрактал. В функции передаются вершины в буфер */
//	func(55, 50, 20, 0, 7);
//
//	/* Функция, выгружающая буфер в сцену */
//	glEnd();
//
//	/*  Прорисовка текущего буфера */
//	glFlush();
//}
//
///* Функция, определённая выше */
//void func(double x, double y, double radius, double angle, int deep) {
//
//	/* Для уменьшения кода в строках вводятся эти переменные
//	  pi5 равна Пи, делённой на 5
//	  h равна расстоянию от центра большего пятиугольника к центрам меньших
//	*/
//	double pi5 = 3.141596 / 5;
//	double h = 2 * radius*cos(pi5);
//
//	for (int i = 0; i < 5; i++) {
//		/*
//		  Вычисление некоторых параметров для рисования их на экране
//		  ang2 Поворот относительно центрального пятиугольника на 360/5 градусов
//		  x2 центр меньшего пятиугольника
//		  y2 центр меньшего пятиугольника
//		  ang3 уголь, на который нужно повернуть вершину изначально
//		  rad расстояние до каждого из углов меньшего пятиугольника от его центра
//		*/
//		double ang2 = angle + pi5 * i * 2,
//			x2 = x - h * cos(ang2),
//			y2 = y - h * sin(ang2),
//			radd2 = radius / (2 * cos(pi5) + 1),
//			ang3 = angle + 3.141596 + (2 * i + 1)*pi5;
//		for (int j = 0; j < 4; j++) {
//			/* В буфер записываются вершины. Эти две вершины будут соединены в прямые между собой*/
//			glVertex2f(x + radd2 * cos(ang3 + j * pi5 * 2), y + radd2 * sin(ang3 + j * pi5 * 2));
//			glVertex2f(x + radd2 * cos(ang3 + (j + 1)*pi5 * 2), y + radd2 * sin(ang3 + (j + 1)*pi5 * 2));
//		}
//		/* Условие выхода из рекурсии. Из максимальной глубины рекурсии не строятся меньшие пятиугольники*/
//		if (deep > 0)func(x2, y2, radius / (2 * cos(pi5) + 1), angle + 3.141596 + (2 * i + 1)*pi5, deep - 1);
//	}
//}
//
//void init(void) {
//	/* Установка цвета по-умолчанию */
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	/* Задаются параметры сцены. Матрица преобразований для проекции, координаты сдвигаются в 0 и границы экрана устанавливаются в заданные*/
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(0.0, 100.0, 0.0, 100.0, -100.0, 100.0);
//}
///* Позволяет закрыть программу нажатием клавиши "эскейп" */
//void processNormalKeys(unsigned char key, int x, int y) {
//	if (key == 27)
//		exit(0);
//}
//
//
//int main(int argc, char** argv) {
//	/* Инициализируются буферы для glut-a*/
//	glutInit(&argc, argv);
//	/* Задаются режимы смешивания цветов и количество буферов*/
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//	/* Задаётся размер окна 500 на 500*/
//	glutInitWindowSize(500, 500);
//	/* Окно сдвигается на 100 единиц по икс и по игрек */
//	glutInitWindowPosition(100, 100);
//	/* Создаётся окно с названием, размером и смещениями, которые были указаны */
//	glutCreateWindow("Fractal");
//	/* Вызывается функция инициализации, задания начальных параметров */
//	init();
//	/* Устанвливается фукция прорисовки, переданная как параметр */
//	glutDisplayFunc(display);
//	/* Задаётся функция, которая будет обрабатывать нажатия клавиш*/
//	glutKeyboardFunc(processNormalKeys);
//	/* Начинается выполнение прорисовки и обработка клавиш*/
//	glutMainLoop();
//	return 0;
//}














// Построение множества Мандельброта

//double x, y;
//
//class Complex //класс комплексных чисел, необходимый для расчетов
//{
//private:
//	double r, i;
//public:
//	Complex(double r, double i)
//	{
//		this->r = r; this->i = i;
//	}
//	Complex operator+(const Complex &c)
//	{
//		return Complex(r + c.r, i + c.i);
//	}
//	Complex operator*(const Complex &c)
//	{
//		return Complex(r * c.r - i * c.i, 2 * r * c.i);
//	}
//	double abs() { return r * r + i * i; }
//};
//
//void reshape(int w, int h)
//{
//	glViewport(0, 0, w, h);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(0, w, 0, h);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//}
//
//void display()
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glBegin(GL_POINTS);
//	for (int y = 0; y < 800; y++) //построение множества
//		for (int x = 0; x < 1200; x++)
//		{
//			Complex z(0, 0);
//			int i = 0;
//			while (i < 500 && z.abs() < 16) {
//				z = z * z + Complex((x - 600) / 180.0, (y - 400) / 180.0);
//				i++;
//			}
//			double r = 0.1 + i * 0.03 * 0.2; //расчет 
//			double g = 0.2 + i * 0.03 * 0.3; //значений
//			double b = 0.3 + i * 0.03 * 0.1; //для раскраски множества
//			glColor3d(r, g, b);
//			glVertex2d(x, y);
//		}
//	glEnd();
//
//	glutSwapBuffers();
//}
//
//int main(int argc, char *argv[])
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//	glutInitWindowSize(1200, 800);
//
//	glutCreateWindow("Mandelbrot");
//
//	glutDisplayFunc(display);
//	glutReshapeFunc(reshape);
//
//	glutMainLoop();
//}











// T-Квадрат


//void drowT(int x, int y, int l, int it)
//{
//	int X1 = x - l / 2; //координаты вершин
//	int X2 = x + l / 2;
//	int Y1 = y - l / 2;
//	int Y2 = y + l / 2;
//	glColor3f(0.7 / it, 0.7 / it, 0.7);
//	glVertex2i(X1, Y1);
//	glVertex2i(X1, Y2);
//	glVertex2i(X2, Y2);
//	glVertex2i(X2, Y1);
//	if (it != 0) {
//		drowT(X1, Y1, l / 2, it - 1); //вызов рекурсии для каждой из вершин
//		drowT(X1, Y2, l / 2, it - 1); //квадрата
//		drowT(X2, Y2, l / 2, it - 1);
//		drowT(X2, Y1, l / 2, it - 1);
//	}
//}
//
//void reshape(int w, int h)
//{
//	glClearColor(1.0, 1.0, 1.0, 0.0);
//	glViewport(0, 0, w, h);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(0, w, 0, h);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//}
//
//void display()
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glBegin(GL_QUADS);
//	drowT(400, 400, 400, 10); //вызов функции вырисовки
//	glEnd();
//
//	glutSwapBuffers();
//}
//
//int main(int argc, char *argv[])
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//	glutInitWindowSize(800, 800);
//
//	glutCreateWindow("Levy");
//
//	glutDisplayFunc(display);
//	glutReshapeFunc(reshape);
//
//	glutMainLoop();
//}














// Кривая Леви

void drowLevy(int x1, int y1, int x2, int y2, int i)
{
	if (i == 0) {
		glColor3f(x1 * 0.01, x2 * 0.002, i * 0.03);
		glVertex2i(x1, y1); //координаты вырисовываемого 
		glVertex2i(x2, y2); //отрезка
	}
	else {
		int x3 = (x1 + x2) / 2 - (y2 - y1) / 2; //координаты
		int y3 = (y1 + y2) / 2 + (x2 - x1) / 2; //точки излома
		drowLevy(x1, y1, x3, y3, i - 1);
		drowLevy(x3, y3, x2, y2, i - 1);
	}
}

void reshape(int w, int h)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINES);
	drowLevy(300, 400, 500, 400, 15); //вызов функции вырисовки
	glEnd();

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800);

	glutCreateWindow("Levy");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
}