#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>


double M_PI = 3.1415926f;
void StrokeEllipse(float xCenter, float yCenter, float rx, float ry, float r, float g, float b, int pointCount = 360)
{
	const float step = float(2 * M_PI / pointCount);

	// Эллипс представлен в виде незамкнутой ломаной линии, соединяющей
	// pointCount точек на его границе с шагом 2*PI/pointCount
	//glBegin(GL_LINE_STRIP);
	glBegin(GL_TRIANGLE_FAN);
	for (float angle = 0; angle < float(2 * M_PI); angle += step)
	{
		const float dx = rx * cosf(angle);
		const float dy = ry * sinf(angle);
		glVertex2f(dx + xCenter, dy + yCenter);
		glColor3f(r, g, b);
	}
	glEnd();

}




int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glEnable(GL_POINT_SMOOTH);


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		// Выход из окна с помощью Esc
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		/* Render here */
		glClearColor(0.5f, 0.3f, 0.7f, 0.0f);	// фон
		glClear(GL_COLOR_BUFFER_BIT);

		//// рисование точек
		//glPointSize(15);
		//glBegin(GL_POINTS);
		//	glColor3f(0, 0, 0);
		//	glVertex2f(-0.5f, -0.5f);
		//	glVertex2f(0.1f, 0.5f);
		//	glVertex2f(0.8f, -0.5f);
		//glEnd();

		//// рисование пунктирной линии
		//glEnable(GL_LINE_STIPPLE);
		//glLineStipple(1.0f, 0x0fff);

		//// соединение всех линий
		//glLineWidth(5);
		//glBegin(GL_LINE_LOOP);
		//	glColor3f(1, 0, 0);
		//	glVertex2f(-0.5f, -0.5f);
		//	glColor3f(0, 0, 1);
		//	glVertex2f(0.1f, 0.5f);
		//	glColor3f(0, 1, 0);
		//	glVertex2f(0.8f, -0.5f);
		//glEnd();

		

		//glClearColor(0.5f, 0.3f, 0.7f, 0.0f);
		/*glClear(GL_COLOR_BUFFER_BIT);*/
		//glDisable(GL_LINE_STIPPLE);
		
		
		// пальцы (левая)
		glLoadIdentity();
		StrokeEllipse(-0.3f, 0.04f, 0.03f, 0.01f, 0.0f, 0.0f, 0.0f, 360);
		StrokeEllipse(-0.3f, 0.04f, 0.03f, 0.01f, 0.0f, 0.0f, 0.0f, 360);

		glRotatef(11, 0, 0, 1);
		StrokeEllipse(-0.3f, 0.07f, 0.03f, 0.01f, 0.0f, 0.0f, 0.0f, 360);

		glLoadIdentity();
		glRotatef(70, 0, 0, 1);
		StrokeEllipse(-0.11f, 0.265f, 0.03f, 0.01f, 0.0f, 0.0f, 0.0f, 360);

		glLoadIdentity();
		glRotatef(-80, 0, 0, 1);
		StrokeEllipse(-0.02f, -0.26f, 0.03f, 0.01f, 0.0f, 0.0f, 0.0f, 360);
		// ---------------------------------------------------------------

		// руки(левая)
		glLoadIdentity();
		glRotatef(45, 0, 0, 1);
		StrokeEllipse(-0.07f, 0.2f, 0.13f, 0.05f, 0.200f, 0.090f, 0.048f, 360);
		StrokeEllipse(-0.07f, 0.2f, 0.13f, 0.05f, 0.200f, 0.090f, 0.048f, 360);
		// ---------------------------------------------------------------

		// пальцы (правая)
		glLoadIdentity();
		StrokeEllipse(0.3f, 0.04f, 0.03f, 0.01f, 0.0f, 0.0f, 0.0f, 360);

		glRotatef(-11, 0, 0, 1);
		StrokeEllipse(0.3f, 0.07f, 0.03f, 0.01f, 0.0f, 0.0f, 0.0f, 360);

		glLoadIdentity();
		glRotatef(-70, 0, 0, 1);
		StrokeEllipse(0.12f, 0.27f, 0.03f, 0.01f, 0.0f, 0.0f, 0.0f, 360);

		glLoadIdentity();
		glRotatef(80, 0, 0, 1);
		StrokeEllipse(0.02f, -0.267f, 0.03f, 0.01f, 0.0f, 0.0f, 0.0f, 360);
		// ---------------------------------------------------------------



		// руки(правая)
		glLoadIdentity();
		glRotatef(-45, 0, 0, 1);
		StrokeEllipse(0.08f, 0.2f, 0.13f, 0.05f, 0.200f, 0.090f, 0.048f, 360);
		StrokeEllipse(0.08f, 0.2f, 0.13f, 0.05f, 0.200f, 0.090f, 0.048f, 360);
		// ---------------------------------------------------------------

		// ноги
		glLoadIdentity();
		StrokeEllipse(-0.10f, -0.40f, 0.05f, 0.17f, 0.200f, 0.090f, 0.048f, 360);
		StrokeEllipse(0.10f, -0.40f, 0.05f, 0.17f, 0.200f, 0.090f, 0.048f, 360);
		// ---------------------------------------------------------------

		// ступни
		StrokeEllipse(0.10f, -0.52f, 0.05f, 0.05f, 0.200f, 0.090f, 0.048f, 360);
		StrokeEllipse(-0.10f, -0.52f, 0.05f, 0.05f, 0.200f, 0.090f, 0.048f, 360);
		// ---------------------------------------------------------------

		// уши
		StrokeEllipse(0.2f, 0.55f, 0.17f, 0.24f, 0.200f, 0.090f, 0.048f, 360);
		StrokeEllipse(-0.2f, 0.55f, 0.17f, 0.24f, 0.200f, 0.090f, 0.048f, 360);
		// ---------------------------------------------------------------

		// уши(внутри)
		StrokeEllipse(-0.2f, 0.55f, 0.13f, 0.20f, 0.300f, 0.150f, 0.100f, 360);
		StrokeEllipse(-0.2f, 0.55f, 0.13f, 0.20f, 0.300f, 0.150f, 0.100f, 360);
		StrokeEllipse(0.2f, 0.55f, 0.13f, 0.20f, 0.300f, 0.150f, 0.100f, 360);
		// ---------------------------------------------------------------


		// тело
		StrokeEllipse(0.0f, 0.0f, 0.13f, 0.4f, 0.200f, 0.090f, 0.048f, 360);
		StrokeEllipse(0.0f, 0.0f, 0.13f, 0.4f, 0.200f, 0.090f, 0.048f, 360);
		StrokeEllipse(0.0f, 0.1f, 0.10f, 0.3f, 1.0f, 0.622f, 0.404f, 360);
		StrokeEllipse(0.0f, 0.1f, 0.10f, 0.3f, 1.0f, 0.622f, 0.404f, 360);
		// ---------------------------------------------------------------

		// голова
		StrokeEllipse(0.0f, 0.55f, 0.17f, 0.28f, 0.200f, 0.090f, 0.048f, 360);
		StrokeEllipse(0.0f, 0.55f, 0.17f, 0.28f, 0.200f, 0.090f, 0.048f, 360);
		// ---------------------------------------------------------------

		// лицо
		StrokeEllipse(0.00f, 0.55f, 0.14f, 0.24f, 1.0f, 0.622f, 0.404f, 360);
		StrokeEllipse(0.00f, 0.55f, 0.14f, 0.24f, 1.0f, 0.622f, 0.404f, 360);
		// ---------------------------------------------------------------
	

		// глаза
		StrokeEllipse(0.07f, 0.65f, 0.030f, 0.050f, 1.0f, 1.0f, 1.0f, 360);
		StrokeEllipse(0.07f, 0.65f, 0.030f, 0.050f, 1.0f, 1.0f, 1.0f, 360);
		StrokeEllipse(-0.07f, 0.65f, 0.030f, 0.050f, 1.0f, 1.0f, 1.0f, 360);
		// ---------------------------------------------------------------

		// зрачки
		glPointSize(20);
		glBegin(GL_POINTS);
		glColor3f(0, 0, 0);
		glVertex2f(-0.07f, 0.65f);
		glColor3f(0, 0, 0);
		glVertex2f(0.07f, 0.65f);
		glEnd();
		// ---------------------------------------------------------------
		
		// нос
		glBegin(GL_TRIANGLES);
		glColor3f(0, 0, 0);
		glVertex2f(0.00f, 0.56f);
		glColor3f(0, 0, 0);
		glVertex2f(0.03f, 0.51f);
		glColor3f(0, 0, 0);
		glVertex2f(-0.03f, 0.51f);
		glEnd();
		// ---------------------------------------------------------------


		// рот
		StrokeEllipse(0.0f, 0.42f, 0.050f, 0.060f, 1.0f, 0.0f, 0.0f, 360);
		StrokeEllipse(0.0f, 0.42f, 0.050f, 0.060f, 1.0f, 0.0f, 0.0f, 360);
		StrokeEllipse(0.0f, 0.44f, 0.050f, 0.060f, 1.0f, 0.622f, 0.404f, 360);
		StrokeEllipse(0.0f, 0.44f, 0.050f, 0.060f, 1.0f, 0.622f, 0.404f, 360);
		// ---------------------------------------------------------------



		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}