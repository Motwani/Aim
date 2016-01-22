void move_block(glm::mat4 MVP, glm::mat4 VP)
{
  glm::mat4 translateRectangle = glm::translate (glm::vec3(-70.0f, -70.0f, 0.0f));        // glTranslatef
  Matrices.model = (translateRectangle);
  MVP = VP * Matrices.model;
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  draw3DObject(rectangle);
}

void move_roller( glm::mat4 MVP , glm::mat4 VP)
{
  glm::mat4 translateCircle = glm::translate (glm::vec3(-60.0f,-30.0f,0.0f));
  Matrices.model = translateCircle;
  MVP = VP * Matrices.model;
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  draw3DObject(roller);
}
obstacle move_obstacle(glm::mat4 MVP , glm::mat4 VP, obstacle obs)
{
    if(obs.move == 1){
    //cout<<"OBSTACLE MOVE "<<obs.vy<<endl;
    obs.x += obs.vx * 0.01;
    obs.y += obs.vy * 0.01;
    obs.vy -= 0.1;
    //cout<<"OBSTACLE MOVE 2 "<<obs.vy<<endl;
    obs.i += 1;
    if(obs.i  == 300)
      obs.move = 0;
    }
  glm::mat4 translateRectangle = glm::translate (glm::vec3(obs.x, obs.y, 0.0f));        // glTranslatef
  //glm::mat4 rotateRectangle = glm::rotate((float)(rectangle_rotation*M_PI/180.0f), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
  Matrices.model = (translateRectangle);
  MVP = VP * Matrices.model;
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  draw3DObject(obs.vao);
  return obs;
}



void move_canon(glm::mat4 MVP , glm::mat4 VP)
{
  glm::mat4 translateRectangle = glm::translate (glm::vec3(-60.0f, -30.0f, 0.0f));        // glTranslatef
  glm::mat4 rotateRectangle = glm::rotate((float)(rectangle_rotation*M_PI/180.0f), glm::vec3(0,0,1)); // rotate about vector (-1,1,1)
  Matrices.model = (translateRectangle * rotateRectangle);
  MVP = VP * Matrices.model;
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  draw3DObject(canon);
}

void move_bullet(glm::mat4 MVP , glm::mat4 VP)
{
  //glm::mat4 rotateBullet = glm::rotate((float)(rectangle_rotation*M_PI/180.0f), glm::vec3(0,0,1));
  glm::mat4 translateBullet = glm::translate (glm::vec3(bullx,bully,0.0f));
  Matrices.model =  translateBullet;
  MVP = VP * Matrices.model;
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  draw3DObject(bullet);
}

void draw ()
{

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  glUseProgram (programID);

  glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
  glm::vec3 target (0, 0, 0);
  glm::vec3 up (0, 1, 0);

  Matrices.view = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0)); // Fixed camera for 2D (ortho) in XY plane


  glm::mat4 VP = Matrices.projection * Matrices.view;

  glm::mat4 MVP ;	// MVP = Projection * View * Model


  // Load identity to model matrix
  Matrices.model = glm::mat4(1.0f);

  /* Render your scene */

    //  glm::mat4 translateTriangle = glm::translate (glm::vec3(0.0f, 0.0f, 0.0f)); // glTranslatef
  // glm::mat4 rotateTriangle = glm::rotate((float)(triangle_rotation*M_PI/180.0f), glm::vec3(0,0,1));  // rotate about vector (1,0,0)
  // glm::mat4 triangleTransform = translateTriangle * rotateTriangle;
  // Matrices.model = translateTriangle;
    MVP = VP * Matrices.model;
   glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

  // MVP = VP * Matrices.model; // MVP = p * V * M
     draw3DObject(triangle);
     draw3DObject(base);
  //  Don't change unless you are sure!!
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

  // draw3DObject draws the VAO given to it using current MVP matrix

  //draw3DObject(tri);

  // Pop matrix to undo transformations till last push matrix instead of recomputing model matrix
  // glPopMatrix();
  //Matrices.model = glm::mat4(1.0f);
  for(int i = 0;i<obstacle_list.size();i++)
  {
    for(int j = 1;j<obstacle_list.size();j++)
    {
      if(i != j)
      {
      float sumr = obstacle_list[i].radius + obstacle_list[j].radius;
      float distance = sqrt(pow(obstacle_list[j].x - obstacle_list[i].x,2) + pow(obstacle_list[j].y - obstacle_list[i].y,2));
      if(distance < sumr)
      {
        if (obstacle_list[i].radius > obstacle_list[j].radius)
        {
          if(obstacle_list[j].move == 0)
          {
            // cout<<"COLLIDE "<<obstacle_list[i].radius<<" $$ "<<obstacle_list[j].radius<<" $$ "<<distance<<endl;
            obstacle rep = createObstacle(min(obstacle_list[i].radius+obstacle_list[j].radius * 0.5,14.0));
            rep.x = obstacle_list[i].x;
            rep.y = obstacle_list[i].y;
            rep.vx = obstacle_list[i].vx;
            rep.vy = obstacle_list[i].vy;
            rep.move = obstacle_list[i].move;
            rep.i = obstacle_list[i].i;
            obstacle_list[i] = rep;
            obstacle_list.erase(obstacle_list.begin()+j);
          }
        }
        else
        {
          if(obstacle_list[i].move == 0)
          {
            // cout<<"COLLIDE "<<obstacle_list[i].radius<<" $$ "<<obstacle_list[j].radius<<" $$ "<<distance<<endl;
            obstacle rep = createObstacle(min(obstacle_list[j].radius+obstacle_list[i].radius * 0.5,14.0));
            rep.x = obstacle_list[j].x;
            rep.y = obstacle_list[j].y;
            rep.vx = obstacle_list[j].vx;
            rep.vy = obstacle_list[j].vy;
            rep.move = obstacle_list[j].move;
            rep.i = obstacle_list[j].i;
            obstacle_list[j] = rep;
            obstacle_list.erase(obstacle_list.begin()+i);
          }
        }
      }
    }
    }
  }
  for(int i = 0;i<obstacle_list.size();i++)
  {
    float sum = rad + obstacle_list[i].radius;
    float dist = sqrt(pow(bullx - obstacle_list[i].x,2) + pow(bully - obstacle_list[i].y,2));
    if (dist < sum)
      obstacle_list.erase(obstacle_list.begin()+i);
    //cout<<i<<"**"<<obstacle_list[i].move<<endl;
    obstacle_list[i]=move_obstacle(MVP,VP,obstacle_list[i]);
  }
  //
  // move_block(MVP,VP);
  //
     move_roller(MVP,VP);
     move_canon(MVP,VP);



      if(bul_move == 1) {
        bullx += vx * 0.01;
        bully += vy * 0.01;
        vy -= 0.1;
        if( bully <= -35 )
          vy = -1*vy;
        if(bullx >= 69 || bullx <= -69)
            bul_move = 0;
      }
      else{
        bullx = float(8*sin(float(-1*rectangle_rotation*M_PI/180.0f))-60.0f);
        bully = float(8*cos(float(rectangle_rotation*M_PI/180.0f))-30.0f);
        vx =  v * sin(-1* rectangle_rotation*M_PI/180.0f);
        vy = v * cos(rectangle_rotation*M_PI/180.0f);
      }
      move_bullet(MVP,VP);
  //
  // move_bullet(MVP,VP);
  // Increment angles
  float increments = 4;

  //camera_rotation_angle++; // Simulating camera rotation
  triangle_rotation = triangle_rotation + increments*triangle_rot_dir*triangle_rot_status;
   if(rectangle_rotation < 112 && rectangle_rot_dir ==1 || rectangle_rotation > -108 && rectangle_rot_dir == -1)
    rectangle_rotation = rectangle_rotation + increments*rectangle_rot_dir*rectangle_rot_status;
  rectangle_rot_status = false;
}
