#include <stdio.h>
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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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
	GLFloat point[] = {
		0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f
	};

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	
    while( !glfwWindowShouldClose(window) )
    {
    	
        // Draw gears
        // draw();

        // Update animation
        // animate();

        // Swap buffers
        // glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    // Exit program
    




	// printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
    return 0;
}