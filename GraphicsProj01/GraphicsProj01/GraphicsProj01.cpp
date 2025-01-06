#include "libs.h"
using namespace std;

void framebuffer_resize_callback(GLFWwindow* window, int fbw, int fbH)
{
	glViewport(0, 0, fbw, fbH);
}

int main()
{
	cout << "Start program\n";

	//INIT GLFW
	glfwInit();
	//Create window
	const int WINDOW_WIDTH = 649;
	const int WINDOW_HEIGHT = 480;
	int framebufferWidth = 0;
	int framebufferHeight = 0;

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //MacOS

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,"2D Games", NULL, NULL);

	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

	//glfwGetFramebufferSize(window, &framebufferHeight, &framebufferHeight);
	//glViewport(0, 0, framebufferWidth, framebufferHeight);
	glfwMakeContextCurrent(window); //important for glew

	//init glew (needs window and opengl context)

	glewExperimental = GL_TRUE;

	//Error
	if (glewInit() != GLEW_OK)
	{
		cout << "ERROR:MAIN.CPP::GLEW_INIT_FAILED\n";
		glfwTerminate();
	}
	
	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		//update input
		glfwPollEvents();
		//update

		//draw
		  //clear
		glClearColor(0.f, 0.f, 0.f, 1.f);//alpha is for opacity
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		  //draw

		//end draw

		glfwSwapBuffers(window);
		glFlush();
	}

	//End of the program
	glfwTerminate();

	return 0; 
}
