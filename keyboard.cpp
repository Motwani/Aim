void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
     // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE || GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_UP:
                  v += 0.5;
                break;
            case GLFW_KEY_DOWN:
                  v -= 0.5;
                break;
            case GLFW_KEY_RIGHT:
                rectangle_rot_dir = -1;
                rectangle_rot_status = true;
                break;
            case GLFW_KEY_LEFT:
                rectangle_rot_dir = 1;
                rectangle_rot_status = true;
                // do something ..
                break;
            case GLFW_KEY_SPACE:
                bul_move = 1;
                break;
            case GLFW_KEY_W:
              if(canon_move <= 58)
                canon_move += 1;
                break;
            case GLFW_KEY_S:
              if(canon_move >= 1)
                canon_move -= 1;
                break;
            case GLFW_KEY_K:
                if(pane <= 5)
                  pane += 0.5;
                  Matrices.projection = glm::ortho(factor*(-70.0f + pane),factor*( 70.0f + pane), -40.0f, 40.0f, 0.1f, 500.0f);
                break;
            case GLFW_KEY_J:
                if(pane >= -5)
                  pane -= 0.5;
                  Matrices.projection = glm::ortho(factor*(-70.0f + pane),factor*( 70.0f + pane), -40.0f, 40.0f, 0.1f, 500.0f);
                break;
            case GLFW_KEY_Z:
                if(check == -1)
                {
                  check = 0;
                  zoom = 1 - zoom;
                }
                break;
            default:
                break;
        }
    }
    else if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                quit(window);
                break;
            default:
                break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar (GLFWwindow* window, unsigned int key)
{
	switch (key) {
		case 'Q':
		case 'q':
    // for(int i=0;i<obstacle_list.size();i++)
    // {
    //   cout<<i<<"**"<<obstacle_list[i].vx<<"**"<<obstacle_list[i].vy<<endl;
    //   //move_obstacle(MVP,VP,obstacle_list[i]);
    // }
            quit(window);
            break;
		default:
			break;
	}
}

/* Executed when a mouse button is pressed/released */
void mouseButton (GLFWwindow* window, int button, int action, int mods)
{
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            if (action == GLFW_RELEASE)
                triangle_rot_dir *= -1;
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            if (action == GLFW_RELEASE) {
                rectangle_rot_dir *= -1;
            }
            break;
        default:
            break;
    }
}


/* Executed when window is resized to 'width' and 'height' */
/* Modify the bounds of the screen here in glm::ortho or Field of View in glm::Perspective */
void reshapeWindow (GLFWwindow* window, int width, int height)
{
    int fbwidth=width, fbheight=height;
    /* With Retina display on Mac OS X, GLFW's FramebufferSize
     is different from WindowSize */
    glfwGetFramebufferSize(window, &fbwidth, &fbheight);

	GLfloat fov = 90.0f;

	// sets the viewport of openGL renderer
	glViewport (0, 0, (GLsizei) fbwidth, (GLsizei) fbheight);

	// set the projection matrix as perspective
	/* glMatrixMode (GL_PROJECTION);
	   glLoadIdentity ();
	   gluPerspective (fov, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1, 500.0); */
	// Store the projection matrix in a variable for future use
    // Perspective projection for 3D views
    // Matrices.projection = glm::perspective (fov, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1f, 500.0f);

    // Ortho projection for 2D views
    Matrices.projection = glm::ortho(-70.0f + pane, 70.0f + pane, -40.0f, 40.0f, 0.1f, 500.0f);
}
