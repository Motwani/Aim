VAO *triangle, *rectangle, *tri,*rect, *canon,*roller,*base;

// Creates the triangle object used in this sample code
void createTriangle ()
{
  /* ONLY vertices between the bounds specified in glm::ortho will be visible on screen */

  /* Define vertex array as used in glBegin (GL_TRIANGLES) */
  static const GLfloat vertex_buffer_data [] = {
    0, -36,0, // vertex 0
    12,-36,0, // vertex 1
    12,-30,0, // vertex 2
  };

  static const GLfloat color_buffer_data [] = {
    0.4,0.54,0, // color 0
    0.7,0.65,0, // color 1
    0.53,0.6,1, // color 2
  };

  static const GLfloat vert [] = {
	  20,0,0,
	  -20,-20,0,
	  20,-30,0,
  };

  // create3DObject creates and returns a handle to a VAO that can be used later
  triangle = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, color_buffer_data, GL_FILL);
  tri = create3DObject(GL_TRIANGLES, 3 , vert, color_buffer_data, GL_LINE);
}

obstacle createObstacle(float radius){
	GLfloat vertex_buffer_data [9005];
	int j=0;
	for(int i=0;i<1000;i++){
		vertex_buffer_data[j++]=radius*cos(2*3.14159*i/1000.0);
		vertex_buffer_data[j++]=radius*sin(2*3.14159*i/1000.0);
		vertex_buffer_data[j++]=0;
		vertex_buffer_data[j++]=radius*cos(2*3.14159*(i+1)/1000.0);
		vertex_buffer_data[j++]=radius*sin(2*3.14159*(i+1)/1000.0);
		vertex_buffer_data[j++]=0;
		vertex_buffer_data[j++]=0;
		vertex_buffer_data[j++]=0;
		vertex_buffer_data[j++]=0;
	}
  float color[] = {0 , 0.2 , 0.4 , 0.54, 0.65 , 0.7 , 0.8 , 0.9 , 1.0};
  int r = rand()%10;
  int g = rand()%10;
  int b = rand()%10;

	GLfloat color_buffer_data [9005];
	for(int i=0;i<9000;i+=3){
		color_buffer_data[i]=color[r];
		color_buffer_data[i+1]=color[g];
		color_buffer_data[i+2]=color[b];
	}
  obstacle ball;
  ball.radius = radius;
	ball.vao = create3DObject(GL_TRIANGLES, 3000, vertex_buffer_data, color_buffer_data, GL_LINE);
  return ball;
}
int rr = 5;
void createRoller(){
	GLfloat vertex_buffer_data [9005];
	int j=0;
	for(int i=0;i<1000;i++){
		vertex_buffer_data[j++]=rr*cos(2*3.14159*i/1000.0);
		vertex_buffer_data[j++]=rr*sin(2*3.14159*i/1000.0);
		vertex_buffer_data[j++]=0;
		vertex_buffer_data[j++]=rr*cos(2*3.14159*(i+1)/1000.0);
		vertex_buffer_data[j++]=rr*sin(2*3.14159*(i+1)/1000.0);
		vertex_buffer_data[j++]=0;
		vertex_buffer_data[j++]=0;
		vertex_buffer_data[j++]=0;
		vertex_buffer_data[j++]=0;
	}

	GLfloat color_buffer_data [9005];
	for(int i=0;i<9000;i+=3){
		color_buffer_data[i]=0;
		color_buffer_data[i+1]=0;
		color_buffer_data[i+2]=0;
	}
	roller = create3DObject(GL_TRIANGLES, 3000, vertex_buffer_data, color_buffer_data, GL_LINE);
}

float rad = 2;
VAO *bullet;
void createBullet(){
	GLfloat vertex_buffer_data [9005];
	int j=0;
	for(int i=0;i<1000;i++){
		vertex_buffer_data[j++]=rad*cos(2*3.14159*i/1000.0);
		vertex_buffer_data[j++]=rad*sin(2*3.14159*i/1000.0);
		vertex_buffer_data[j++]=0;
		vertex_buffer_data[j++]=rad*cos(2*3.14159*(i+1)/1000.0);
		vertex_buffer_data[j++]=rad*sin(2*3.14159*(i+1)/1000.0);
		vertex_buffer_data[j++]=0;
		vertex_buffer_data[j++]=0;
		vertex_buffer_data[j++]=0;
		vertex_buffer_data[j++]=0;
	}
  float color[] = {0 , 0.2 , 0.4 , 0.54, 0.65 , 0.7 , 0.8 , 0.9 , 1.0};
  int r = rand()%10;
  int g = rand()%10;
  int b = rand()%10;
	GLfloat color_buffer_data [9005];
	// for(int i=0;i<9000;i+=18){
	// 	color_buffer_data[i]=1;
	// 	color_buffer_data[i+1]=0;
	// 	color_buffer_data[i+2]=0;
  //
  //   color_buffer_data[i+3]=0;
  //   color_buffer_data[i+4]=0;
  //   color_buffer_data[i+5]=1;
  //
  //   color_buffer_data[i+6]=0;
  //   color_buffer_data[i+7]=1;
  //   color_buffer_data[i+8]=0;
  //
  //   color_buffer_data[i+9]=0;
  //   color_buffer_data[i+10]=1;
  //   color_buffer_data[i+11]=0;
  //
  //   color_buffer_data[i+12]=0.3;
  //   color_buffer_data[i+13]=0.3;
  //   color_buffer_data[i+14]=0.3;
  //
  //   color_buffer_data[i+15]=1;
  //   color_buffer_data[i+16]=0;
  //   color_buffer_data[i+17]=0;
	// }
  for(int i=0;i<9000;i+=3){
    color_buffer_data[i]=color[r];
    color_buffer_data[i+1]=color[g];
    color_buffer_data[i+2]=color[b];
  }
	bullet = create3DObject(GL_TRIANGLES, 3000, vertex_buffer_data, color_buffer_data, GL_LINE);
}
// Creates the rectangle object used in this sample code
void createRectangle ()
{
  // GL3 accepts only Triangles. Quads are not supported
  static const GLfloat vertex_buffer_data [] = {
    0,0,0, // vertex 1
    0,10,0, // vertex 2
    20,10,0, // vertex 3

    20,10,0, // vertex 3
    20,0,0, // vertex 4
    0,0,0,  // vertex 1
  };

  static const GLfloat color_buffer_data [] = {
    0.5,0.64,0.58, // color 1
    0.5,0.64,0.58, // color 2
    0.5,0.64,0.58, // color 3

    0.5,0.64,0.58, // color 3
    0.5,0.64,0.58, // color 4
    0.5,0.64,0.58,  // color 1
  };

  // create3DObject creates and returns a handle to a VAO that can be used later
  rectangle = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void createBase ()
{
  // GL3 accepts only Triangles. Quads are not supported
  static const GLfloat vertex_buffer_data [] = {
    -70,-35,0, // vertex 1
    -70,-37,0, // vertex 2
    70,-35,0, // vertex 3

    70,-35,0, // vertex 3
    70,-37,0, // vertex 4
    -70,-37,0,  // vertex 1
  };

  static const GLfloat color_buffer_data [] = {
    0.5,0.64,0.58, // color 1
    0.5,0.64,0.58, // color 2
    0.5,0.64,0.58, // color 3

    0.5,0.64,0.58, // color 3
    0.5,0.64,0.58, // color 4
    0.5,0.64,0.58,  // color 1
  };

  // create3DObject creates and returns a handle to a VAO that can be used later
  base = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void createCanon ()
{
  // GL3 accepts only Triangles. Quads are not supported
  static const GLfloat vertex_buffer_data [] = {
     1,4,0, // vertex 1
     1,-4,0, // vertex 2
    -1,-4,0, // vertex 3

    -1,-4,0, // vertex 3
    -1,4,0, // vertex 4
     1,4,0,  // vertex 1
  };

  static const GLfloat color_buffer_data [] = {
    0.5,0.64,0.58, // color 1
    0.5,0.64,0.58, // color 2
    0.5,0.64,0.58, // color 3

    0.5,0.64,0.58, // color 3
    0.5,0.64,0.58, // color 4
    0.5,0.64,0.58,  // color 1
  };

  // create3DObject creates and returns a handle to a VAO that can be used later
  canon = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_buffer_data, GL_FILL);
}
