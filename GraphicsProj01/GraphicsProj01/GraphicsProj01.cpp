#include "libs.h"
using namespace std;

Vertex vertices[] =
{
	//Positions						//color						//Texcoords
	glm::vec3(-0.5f, 0.5f, 0.f),	glm::vec3(1.f,0.f,0.f),		glm::vec2(0.f,1.f),
	glm::vec3(-0.5f, -0.5f, 0.f),	glm::vec3(0.f,1.f,0.f),		glm::vec2(0.f, 0.f),
	glm::vec3(0.5f, -0.5f, 0.f),	glm::vec3(0.f, 0.f, 1.f),	glm::vec2(1.f,0.f),

	//glm::vec3(-0.5f, 0.5f, 0.f),	glm::vec3(1.f,0.f,0.f),		glm::vec2(0.f,1.f),
	//glm::vec3(0.5f, -0.5f, 0.f),	glm::vec3(0.f,0.f,1.f),		glm::vec2(1.f, 0.f),
	glm::vec3(0.5f, 0.5f, 0.f),	    glm::vec3(1.f, 1.f, 0.f),	glm::vec2(1.f,1.f)
};
unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] =
{
	0,1,2, //Triangle 1
	0,2,3 //Triangle 2

};

unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

void updateInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void framebuffer_resize_callback(GLFWwindow* window, int fbw, int fbH)
{
	glViewport(0, 0, fbw, fbH);
}

bool loadShaders(GLuint& program)
{
	bool loadSuccess = true;
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
			src += temp + "\n";
		}
	}
	else
	{
		cout << "ERROR::LOADSHADERS::COULD_NOT_OPEN_VERTEX_FILE\n";
		loadSuccess = false;

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
		loadSuccess = false;

	}

	temp = "";
	src = "";

	//Fragment
	in_file.open("fragment_core.glsl");

	if (in_file.is_open())
	{
		while (getline(in_file, temp))
		{
			src += temp + "\n";
		}
	}
	else
	{
		cout << "ERROR::LOADSHADERS::COULD_NOT_OPEN_FRAGMENT_FILE\n";
		loadSuccess = false;
	}
	in_file.close();

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragSrc = src.c_str();
	glShaderSource(fragmentShader, 1, &fragSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::LOADSHADERS::COULD_NOT_COMPILE_FRAGMENT_SHADER\n";
		cout << infoLog << "\n";
		loadSuccess = false;

	}

	//Program
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		cout << "ERROR::LOADSHSDERS::COULD_NOT_LINK_PROGRAM\n";
		cout << infoLog << "\n";
		loadSuccess = false;

	}

	//End
	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return loadSuccess;

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

	//OPENGL OPTIONS
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); //we don't want to see the backside of the triangle
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //only the outlines
	//glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES); //Triangles

	//Shader init
	GLuint core_program;
	if (!loadShaders(core_program)) {
		glfwTerminate();
	}

	//Model
	
	//VAO, VBO, EBO
	//GEN VAO AND BIND
	GLuint VAO;
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//GEN VBO AND BIND AND SEND DATA
	//VBO = vertex buffer object: will send the data to graphics card
	//EBO = element buffer object : will send the index data

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//GEN EBO AND BIND SEND DATA
	GLuint	EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//SET vertex attributes and enables, input essembly : we tell here the GPU, how we are gonna use our data
	//positon
	GLuint attribLoc = glGetAttribLocation(core_program, "vertex_position");
	glVertexAttribPointer(attribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position)); //offset: how much memory is next attribute
	glEnableVertexAttribArray(attribLoc);
	//color
	attribLoc = glGetAttribLocation(core_program, "vertex_color");
	glVertexAttribPointer(attribLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color)); //offset: how much memory is next attribute
	glEnableVertexAttribArray(attribLoc);
	//texcoord
	attribLoc = glGetAttribLocation(core_program, "vertex_texcoord");
	glVertexAttribPointer(attribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord)); //offset: how much memory is next attribute
	glEnableVertexAttribArray(attribLoc);

	//Bind VAO 0
	glBindVertexArray(0);

	//Texture init
	int image_width = 0;
	int image_height = 0;
	unsigned char* image = SOIL_load_image("images/cat.png", &image_width, &image_height, NULL, SOIL_LOAD_RGBA);

	GLuint texture0;
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);

	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "ERROR::TEXTURE_LOADING_FAILED\n";
	}
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		//update input
		glfwPollEvents();
		//update

		updateInput(window);
		//draw
		
		
		//clear
		glClearColor(0.f, 0.f, 0.f, 1.f);//alpha is for opacity
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//Use a program
		glUseProgram(core_program);

		//Update unforms 
		glUniform1i(glGetUniformLocation(core_program, "texture0"), 0);

		//Activate texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);

		//Bind vertex array object
		glBindVertexArray(VAO);


		  //draw
		//glDrawArrays(GL_TRIANGLES, 0, nrOfVertices); //both works
		glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0); //if we use indices then we don't need 06 vertices


		//end draw

		glfwSwapBuffers(window);
		glFlush();

		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	//End of the program
	glfwDestroyWindow(window);
	glfwTerminate();

	//Delete program
	glDeleteProgram(core_program);

	//Delete VAO and Buffers

	return 0; 
}
