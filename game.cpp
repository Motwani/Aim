#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace std;

#include "opengl_def.cpp"
/**************************
 * Customizable functions *
 **************************/
float camera_rotation_angle = 90;
float rectangle_rotation = 0;
float triangle_rotation = 0;
float triangle_rot_dir = 1,x=0;
float rectangle_rot_dir = 1;
bool triangle_rot_status = true;
bool rectangle_rot_status = false;
float bullx;
float bully;
float v = 20;
float vx,vy;
int bul_move = 0;
float canon_move = 0;
float barr1_dir = 1;
float barr2_dir = -1;
float barr1_y = 0;
float barr2_y = 0;

vector <obstacle> obstacle_list;
/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
#include "keyboard.cpp"
#include "object_definitions.cpp"



/* Render the scene with openGL */
/* Edit this function according to your assignment */
#include "draw.cpp"

/* Initialise glfw window, I/O callbacks and the renderer to use */
/* Nothing to Edit here */


GLFWwindow* initGLFW (int width, int height)
{
    GLFWwindow* window; // window desciptor/handle

    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Sample OpenGL 3.3 Application", NULL, NULL);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval( 1 );

    /* --- register callbacks with GLFW --- */

    /* Register function to handle window resizes */
    /* With Retina display on Mac OS X GLFW's FramebufferSize
     is different from WindowSize */
    glfwSetFramebufferSizeCallback(window, reshapeWindow);
    glfwSetWindowSizeCallback(window, reshapeWindow);

    /* Register function to handle window close */
    glfwSetWindowCloseCallback(window, quit);

    /* Register function to handle keyboard input */
    glfwSetKeyCallback(window, keyboard);      // general keyboard input
    glfwSetCharCallback(window, keyboardChar);  // simpler specific character handling

    /* Register function to handle mouse click */
    glfwSetMouseButtonCallback(window, mouseButton);  // mouse button clicks

    return window;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL (GLFWwindow* window, int width, int height)
{
    /* Objects should be created before any other gl function and shaders */
	// Create the models
	createTriangle(); // Generate the VAO, VBOs, vertices data & copy into the array buffer
	createRectangle();
  createCanon();
  createRoller();
  createBullet();
  createBase();
  createBarrier();

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "Sample_GL.vert", "Sample_GL.frag" );
	// Get a handle for our "MVP" uniform
	Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


	reshapeWindow (window, width, height);

    // Background color of the scene
	glClearColor (0.0f, 0.38f, 0.54f, 0.7f); // R, G, B, A
	glClearDepth (1.0f);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int main (int argc, char** argv)
{
	int width = 800;
	int height = 800;
  srand(time(NULL));

    GLFWwindow* window = initGLFW(width, height);

	initGL (window, width, height);

    double last_update_time = glfwGetTime(), current_time;

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {


        // OpenGL Draw commands
        draw();

        // Swap Frame Buffer in double buffering
        glfwSwapBuffers(window);

        // Poll for Keyboard and mouse events
        glfwPollEvents();

        // Control based on time (Time based transformation like 5 degrees rotation every 0.5s)
        current_time = glfwGetTime(); // Time in seconds
        if ((current_time - last_update_time) >= 2) { // atleast 0.5s elapsed since last frame
            float radius = rand()%6 + 2; //range is 2 to 7
            float theta = (rand()%41 - 20)*M_PI/180; // range is -20 to 20
            float velocity = rand()%17 + 17; // range is 17 to 33
            float velocity_x = velocity * sin(-1*theta);
            float velocity_y = velocity * cos(theta);
            //cout<<"$$$"<<rand()<<endl;
            //cout<<radius<<"#"<<theta<<"#"<<velocity<<"#"<<velocity_x<<"#"<<velocity_y<<endl;
            obstacle o = createObstacle(radius);
            o.vx = velocity_x;
            o.vy = velocity_y;
            o.x = 26;
            o.y = -20;
            o.move = 1;
            o.i = 0;
            o.radius = radius;
            obstacle_list.push_back(o);
            last_update_time = current_time;
        }
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
