#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
using namespace std;

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Deu pau monstro n. %f: %s", error, description);
}

// void window_close_callback(GLFWwindow* window)
// {
// 	printf("called the callback!\n");
//     // if (!time_to_close)
//     //     glfwSetWindowShouldClose(window, GL_FALSE);
// }

// void render(GLint shaderProgram)
// {
// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 	glUseProgram(shaderProgram);

// 	glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
// 	glClear (GL_COLOR_BUFFER_BIT);

// 	glBegin (GL_TRIANGLES);
// 	{
// 		glColor3f (0.6, 0.3, 0.3);
// 		glVertex2f (0, .5);
// 		glVertex2f (-.5, -.5);
// 		glVertex2f (.5, -.5);
// 	}
// 	glEnd ();
// }

std::string get_shader_content(const char *filename) {
	string shaderStr;
	ifstream fileStream (filename, ios::in);
	if (fileStream.is_open()) {
		fileStream.seekg(0, ios::end);
		shaderStr.resize(fileStream.tellg());
		fileStream.seekg(0, ios::beg);
		fileStream.read(&shaderStr[0], shaderStr.size());
		fileStream.close();
	}

	return shaderStr;
}

string checkShaderStatus(GLint shader, GLenum status) {
	GLint retStatus = 0;
	string retStr;
	glGetShaderiv(shader, status, &retStatus);
	if (retStatus == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

		printf("Erro no shader:\n%s", &errorLog[0]);
		printf("Terminou pau de shader\n");
		// Provide the infolog in whatever manor you deem best.
		retStr = string (&errorLog[0]);
	}

	return retStr;

	// std::string str(ethernetCharArray);
}
string checkProgramStatus(GLint program, GLenum status) {
	GLint retStatus = 0;
	string retStr;
	glGetProgramiv(program, status, &retStatus);
	if (retStatus == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &errorLog[0]);

		printf("Erro no program:\n%s", &errorLog[0]);
		printf("Terminou pau de program\n");
		// Provide the infolog in whatever manor you deem best.
		retStr = string (&errorLog[0]);
	}

	return retStr;

	// std::string str(ethernetCharArray);
}


GLint createShaderProgram() {
	string vsString = get_shader_content("simple.vs");
	string fsString = get_shader_content("simple.fs");
	const char* vs = vsString.c_str();
	const char* fs = fsString.c_str();

	const char* separator = string(20, '*').c_str();
	// printf("%s\n%s\n", string(20, '*').c_str());
	printf("%s\nvertex shader:\n%s\n%s\n%s\nfragment shader:\n%s\n%s\n%s\n", separator, separator, vs, separator, separator, fs, separator);




	// printf("fragment shader:\n%s", fs);

	string shaderStatus;
	//Create vertex shader
	GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vs, NULL);
	glCompileShader(vertexShader);


	shaderStatus = checkShaderStatus(vertexShader, GL_COMPILE_STATUS);
	if (!shaderStatus.empty()) {
		// Exit with failure.
		glDeleteShader(vertexShader); // Don't leak the shader.
		printf("Erro no vertex shader:\n%s", shaderStatus.c_str());
		return 0;
	}

	//Create fragment shader
	GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fs, NULL);
	glCompileShader(fragmentShader);

	shaderStatus = checkShaderStatus(fragmentShader, GL_COMPILE_STATUS);
	if (!shaderStatus.empty()) {
		// Exit with failure.
		glDeleteShader(vertexShader); // Don't leak the shader.
		glDeleteShader(fragmentShader); // Don't leak the shader.
		printf("Erro no fragment shader:\n%s", shaderStatus.c_str());
		return 0;
	}

	//Create shader program.
	GLint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	shaderStatus = checkProgramStatus(shaderProgram, GL_LINK_STATUS);
	if (!shaderStatus.empty()) {
		// Exit with failure.
		glDeleteShader(vertexShader); // Don't leak the shader.
		glDeleteShader(fragmentShader); // Don't leak the shader.
		glDeleteProgram(shaderProgram); // Don't leak the shader.
		printf("Error when linking program:\n%s", shaderStatus.c_str());
		return 0;
	}

	return shaderProgram;
}



bool _update_fps_counter(GLFWwindow* window) {
	static double previous_seconds;
	static int frame_count;
	static double colorseconds = 0.0;

	double current_seconds;
	double elapsed_seconds;

	current_seconds = glfwGetTime();
	elapsed_seconds = current_seconds - previous_seconds;
	colorseconds += elapsed_seconds;
	
	static bool ret = false;
	if (elapsed_seconds > 0.25) {
		previous_seconds = current_seconds;
		char tmp[128];
		double fps = (double) frame_count / elapsed_seconds;
		sprintf(tmp, "openGL @ fps: %.2f", fps);
		glfwSetWindowTitle(window, tmp);
		frame_count = 0;
		printf("seconds: %f\n", colorseconds);
		
	}
	if (colorseconds > 5.0) {
		ret = !ret;
		colorseconds = 0.0;
	}

	frame_count ++;
	return ret;
}

int main() {
	if (!glfwInit()) {
		fprintf(stderr, "Error: Could not start freaking GLFW\n");
		return 1;
	}

	printf("Vou tentar setarerror.\n");
	glfwSetErrorCallback(error_callback);
	printf("Setei..\n");
// glfwWindowHint(GLFW_DEPTH_BITS, 16);
//Probably going to need this on mac.
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow( 900, 600, "Gears", NULL, NULL );

	// //Try to open a window...
	if (!window) {
		fprintf(stderr, "Error: Could not create window.\n");
		glfwTerminate();
		return 1;
	}
	// glfwSetWindowCloseCallback(window, window_close_callback);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
	glEnable (GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//Now lets get the version number:
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	printf("Renderer: %s. Version: %s. GLSL version: %s\n", renderer, version, glslversion);
	GLfloat points[] = {
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);


	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	GLint shaderProgram = createShaderProgram();
	GLint colorUniform = glGetUniformLocation(shaderProgram, "inputColor");

	printf("ShaderProgram: %u\n", shaderProgram);
	bool updateColor = false;
	while ( !glfwWindowShouldClose(window) )
	{

		// render(shaderProgram);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		
		glUseProgram(shaderProgram);


		glBindVertexArray(vao);

		//draw 3 points
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();
		glfwSwapBuffers(window);
		updateColor = _update_fps_counter(window);
		if (updateColor == true) {
			glUniform4f(colorUniform, 0.2, 0.2, 0.2, 1.0);
		} else {
			glUniform4f(colorUniform, 0.5, 0.0, 0.5, 1.0);
		}
		// sleep(1);

		// Draw gears
		// draw();

		// Update animation
		// animate();

		// Swap buffers
		// glfwSwapBuffers(window);
	}

	// Terminate GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	// Exit program





	// printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
	return 0;
}