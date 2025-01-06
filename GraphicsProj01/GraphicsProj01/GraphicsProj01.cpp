#include "libs.h"
using namespace std;

void framebuffer_resize_callback(GLFWwindow* window, int fbw, int fbH)
{
	glViewport(0, 0, fbw, fbH);
}

bool loadShaders(GLuint& program)
{
	char infoLog[512];
	GLint success;

	string temp = "";
	string src = "";

	ifstream in_file;

	//Vertex

	in_file.open("vertex_core.glsl");

	if (in_file.is_open())
	{
		while (getline(in_file, temp))
		{
			src += temp = "\n";
		}
	}
	else
	{
		cout << "ERROR::LOADSHADERS::COULD_NOT_OPEN_VERTEX_FILE\n";
	}
	in_file.close();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertSrc = src.c_str();
	glShaderSource(vertexShader, 1, &vertSrc, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::LOADSHADERS::COULD_NOT_COMPILE_VERTEX_SHADER\n";
		cout << infoLog << "\n";
	}

	temp = "";
	src = "";

	//Fragment

	//Program


	//End
	glDeleteShader(vertexShader);

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
	//Shader init
	GLuint core_program;
	loadShaders(core_program);

	//Model
	
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
